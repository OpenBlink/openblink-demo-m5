/*
 * SPDX-License-Identifier: BSD-3-Clause
 * SPDX-FileCopyrightText: Copyright (c) 2025 ViXion Inc. All Rights Reserved.
 */
#ifndef DRV_BLE_BLINK_H
#define DRV_BLE_BLINK_H

#include <stdint.h>

#include "host/ble_uuid.h"
#include "nimble/ble.h"

#define BLINK_VERSION 0x01

#define BLINK_CMD_DATA 'D'
#define BLINK_CMD_PROG 'P'
#define BLINK_CMD_RESET 'R'
#define BLINK_CMD_RELOAD 'L'

#pragma pack(1)
typedef struct {
  uint8_t version;     // [1] Blink Version (0x01)
  uint8_t command;     // [1] 'D':Data 'P':Program 'R':SoftReset
} BLINK_CHUNK_HEADER;  // 2byte
#pragma pack()

#pragma pack(1)
typedef struct {
  BLINK_CHUNK_HEADER header;  // [2] ヘッダ
  uint16_t offset;            // [2] バイトコード転送先のオフセット
  uint16_t size;              // [2] バイトコードサイズ(今回転送分)
} BLINK_CHUNK_DATA;           // 6byte
#pragma pack()

#pragma pack(1)
typedef struct {
  BLINK_CHUNK_HEADER header;  // [2] ヘッダ
  uint16_t length;            // [2]
  uint16_t crc;               // [2] CRC16
  uint8_t slot;               // [1] 書き込みスロット
  uint8_t reserved;           // [1]
} BLINK_CHUNK_PROGRAM;        // 6byte
#pragma pack()

int ble_blink_init(void);
int ble_print(const char *data);

#endif
