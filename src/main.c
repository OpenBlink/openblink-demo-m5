/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright (c) 2025 ViXion Inc. All Rights Reserved.
 */
/**
 * @file main.c
 * @brief Main application entry point for OpenBlink demo on M5Stack
 *
 * This file contains the main application logic for the OpenBlink demo,
 * including mruby/c VM initialization and execution.
 */
#include "main.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "api/blink.h"
#include "api/input.h"
#include "api/led.h"
#include "app/blink.h"
#include "app/init.h"
#include "drv/ble_blink.h"
#include "lib/fn.h"
#include "mrubyc.h"
#include "rb/slot1.h"
#include "rb/slot2.h"
#include "rb/slot_err.h"

extern void init_c_m5u();  // for features in m5u directory

#define MRBC_HEAP_MEMORY_SIZE (15 * 1024)

static bool request_mruby_reload = false;
static bool blink_locked[MAX_VM_COUNT] = {false};
static mrbc_tcb* tcb[MAX_VM_COUNT] = {NULL};
static uint8_t memory_pool[MRBC_HEAP_MEMORY_SIZE] = {0};
static uint8_t bytecode_slot2[BLINK_MAX_BYTECODE_SIZE] = {0};

/**
 * @brief Main application entry point
 *
 * Initializes the application and runs the mruby/c VM in an infinite loop.
 * Handles loading bytecode, setting up API classes, and managing VM tasks.
 */
void app_main() {
  app_init();

  bool detect_abnormality = false;
  if (esp_reset_reason() == ESP_RST_PANIC) {
    detect_abnormality = true;
  }

  while (1) {
    for (size_t i = 0; i < MAX_VM_COUNT; i++) {
      tcb[i] = NULL;
      blink_locked[i] = false;
    }

    // mruby/c initialize
    mrbc_init(memory_pool, MRBC_HEAP_MEMORY_SIZE);

    ////////////////////
    // Class, Method
    api_led_define();    // LED.*
    api_input_define();  // Input.*
    api_blink_define();  // Blink.*

    init_c_m5u();  // for features in m5u directory

    ////////////////////
    // Clear reload request flag
    request_mruby_reload = false;

    // Load mruby bytecode
    if (detect_abnormality) {
      memcpy(bytecode_slot2, slot_err, sizeof(slot_err));
      printf("ERROR DETECTED \n");
    } else if (0 == blink_load(bytecode_slot2, sizeof(bytecode_slot2) /
                                                   sizeof(bytecode_slot2[0]))) {
      memcpy(bytecode_slot2, slot2, sizeof(slot2));
      printf("DEFAULT CODE LOADED \n");
    }
    detect_abnormality = false;

    ////////////////////
    // mruby/c create task
    tcb[0] = mrbc_create_task(slot1, NULL);
    tcb[1] = mrbc_create_task(bytecode_slot2, NULL);

    if ((tcb[0] == NULL) || (tcb[1] == NULL)) {
    }
    // set priority
    mrbc_change_priority(tcb[0], 1);
    mrbc_change_priority(tcb[1], 2);

    ////////////////////
    int ret = mrbc_run();
    printf("MRUBYC RUN RESULT:%d\n", ret);
    if (ret != 0) {
      detect_abnormality = true;
    }

    ble_print("mruby/c finished");
    ////////////////////
    // mruby/c cleanup
    mrbc_cleanup();
  }
}

/**
 * @brief Sets the mruby/c VM reload request flag
 *
 * @return kSuccess always
 */
fn_t app_mrubyc_vm_set_reload(void) {
  request_mruby_reload = true;
  for (size_t i = 0; i < MAX_VM_COUNT; i++) {
    if ((NULL != tcb[i]) && (false == blink_locked[i])) {
      mrbc_terminate_task(tcb[i]);
      mrbc_delete_task(tcb[i]);
    }
  }
  return kSuccess;
}

/**
 * @brief Gets the current state of the mruby/c VM reload request flag
 *
 * @return true if reload is requested, false otherwise
 */
bool app_mrubyc_vm_get_reload(void) { return request_mruby_reload; }

/**
 * @brief Sets the lock state of the blink request
 *
 * @return kSuccess always
 */
fn_t app_mrubyc_vm_set_blink_lock(const bool kState, const uint8_t kVmId) {
  blink_locked[kVmId] = kState;
  return kSuccess;
}
