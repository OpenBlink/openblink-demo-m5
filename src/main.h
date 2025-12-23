/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright (c) 2025 ViXion Inc. All Rights Reserved.
 */
/**
 * @file main.h
 * @brief Main application header for OpenBlink demo
 *
 * Defines the main application functions for managing the mruby/c VM.
 */
#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdint.h>

#include "lib/fn.h"

/**
 * @brief Sets the mruby/c VM reload request flag
 *
 * @return kSuccess always
 */
fn_t app_mrubyc_vm_set_reload(void);

/**
 * @brief Gets the current state of the mruby/c VM reload request flag
 *
 * @return true if reload is requested, false otherwise
 */
bool app_mrubyc_vm_get_reload(void);

/**
 * @brief Sets the lock state of the blink request
 *
 * @return kSuccess always
 */
fn_t app_mrubyc_vm_set_blink_lock(const bool kState, const uint8_t kVmId);

#endif
