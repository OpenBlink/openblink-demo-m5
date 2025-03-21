/****
 *  my_mrubydef.h
 *  configuration of my mruby/c library
 *****/

#ifndef _MY_MRUBYDEF_H_
#define _MY_MRUBYDEF_H_

#define USE_DISPLAY_GRAPHICS  // Display to support graphics functions
#define USE_SPEAKER           // to support Speaker functions
#define USE_CANVAS            // to support Canvas functions
#define USE_TOUCH
#define USE_FONT

#include "c_m5.h"
#include "mrubyc.h"

inline const char *val_to_s(mrb_vm *vm, mrb_value *v, mrbc_value &recv,
                            int regofs) {
  const char *str;
  if (recv.tt == MRBC_TT_STRING) {
    str = (const char *)recv.string->data;
  } else {
    mrbc_value val = mrbc_send(vm, v, regofs, &recv, "to_s", 0);
    str = (const char *)val.string->data;
  }
  return str;
}
inline int val_to_i(mrb_vm *vm, mrb_value *v, mrbc_value &recv, int regofs) {
  int i;
  if (recv.tt == MRBC_TT_FIXNUM) {
    i = recv.i;
  } else {
    mrbc_value val = mrbc_send(vm, v, regofs, &recv, "to_i", 0);
    i = val.i;
  }
  return i;
}

inline float val_to_f(mrb_vm *vm, mrb_value *v, mrbc_value &recv, int regofs) {
  float f;
  if (recv.tt == MRBC_TT_FLOAT) {
    f = recv.d;
  } else {
    mrbc_value val = mrbc_send(vm, v, regofs, &recv, "to_f", 0);
    f = val.d;
  }
  return f;
}

inline void put_null_data(mrb_value *v) {
  *(uint8_t **)v->instance->data = nullptr;
  // try in future // v->tt = MRBC_TT_EMPTY;
}

#define get_checked_data(cls, vm, v)                               \
  *(cls **)(v->instance->data);                                    \
  if (*(cls **)(v->instance->data) == nullptr) {                   \
    mrbc_raise(vm, MRBC_CLASS(RuntimeError), "already destroyed"); \
    return;                                                        \
  }

/*  This does not work
inline uint8_t* get_checked_data(mrb_vm *vm, mrbc_value *v) {
    if( *(uint8_t**)v->instance->data == nullptr){
        mrbc_raise(vm, MRBC_CLASS(RuntimeError), "instance destroyed");
    }
    return v->instance->data;
}
*/
#endif  // _MY_MRUBYDEF_H_