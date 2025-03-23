/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright (c) 2025 ViXion Inc. All Rights Reserved.
 */
/**
 * @file blink.c
 * @brief Implementation of Blink API for mruby/c
 *
 * Implements the Blink class and its methods for the mruby/c VM,
 * providing functionality to check for reload requests.
 */
#include "blink.h"

#include "../app/blink.h"
#include "../lib/fn.h"
#include "../main.h"
#include "mrubyc.h"

/**
 * @brief Forward declaration for the mruby/c method implementation
 *
 * @param vm Pointer to the mruby/c VM
 * @param v Pointer to the method arguments
 * @param argc Number of arguments
 */
static void c_get_reload(mrb_vm *vm, mrb_value *v, int argc);
static void c_reset_blink(mrb_vm *vm, mrb_value *v, int argc);

/**
 * @brief Defines the Blink class and methods for mruby/c
 *
 * Creates the Blink class and registers the req_reload? method
 * which allows Ruby code to check if a reload has been requested.
 *
 * @return kSuccess always
 */
fn_t api_blink_define(void) {
  mrb_class *class_blink;
  class_blink = mrbc_define_class(0, "Blink", mrbc_class_object);
  mrbc_define_method(0, class_blink, "req_reload?", c_get_reload);
  mrbc_define_method(0, class_blink, "factory_reset!", c_reset_blink);
  return kSuccess;
}

/**
 * @brief Implementation of the req_reload? method for the Blink class
 *
 * Returns the current state of the reload request flag.
 *
 * @param vm Pointer to the mruby/c VM
 * @param v Pointer to the method arguments
 * @param argc Number of arguments
 */
static void c_get_reload(mrb_vm *vm, mrb_value *v, int argc) {
  SET_BOOL_RETURN(app_mrubyc_vm_get_reload());
}

/**
 * @brief Implementation of the factory_reset! method for the Blink class
 *
 * Resets the device to factory blink bytecodes.
 *
 * @param vm Pointer to the mruby/c VM
 * @param v Pointer to the method arguments
 * @param argc Number of arguments
 */
static void c_reset_blink(mrb_vm *vm, mrb_value *v, int argc) {
  if (0 == blink_delete()) {
    esp_restart();
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}
