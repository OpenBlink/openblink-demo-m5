#include "c_display_button.h"

#include <M5Unified.h>

#include "drawing.h"
#include "my_mrubydef.h"

static void class_display_color_value(mrb_vm *vm, mrb_value *v, int argc) {
  if (argc > 2) {
    uint8_t r = val_to_i(vm, v, GET_ARG(1), argc);
    uint8_t g = val_to_i(vm, v, GET_ARG(2), argc);
    uint8_t b = val_to_i(vm, v, GET_ARG(3), argc);
    uint16_t color = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
    SET_INT_RETURN(color);
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_display_available(mrb_vm *vm, mrb_value *v, int argc) {
  if (M5.getDisplayCount() > 0) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_display_dimension(mrb_vm *vm, mrb_value *v, int argc) {
  draw_get_dimension(&M5.Display, vm, v, argc);
}

static void class_display_set_text_size(mrb_vm *vm, mrb_value *v, int argc) {
  draw_set_text_size(&M5.Display, vm, v, argc);
}
static void class_display_set_text_color(mrb_vm *vm, mrb_value *v, int argc) {
  draw_set_text_color(&M5.Display, vm, v, argc);
}
static void class_display_print(mrb_vm *vm, mrb_value *v, int argc) {
  draw_print(&M5.Display, vm, v, argc);
}
static void class_display_puts(mrb_vm *vm, mrb_value *v, int argc) {
  draw_puts(&M5.Display, vm, v, argc);
}
static void class_display_clear(mrb_vm *vm, mrb_value *v, int argc) {
  draw_clear(&M5.Display, vm, v, argc);
}
static void class_display_set_cursor(mrb_vm *vm, mrb_value *v, int argc) {
  draw_set_cursor(&M5.Display, vm, v, argc);
}
static void class_display_get_cursor(mrb_vm *vm, mrb_value *v, int argc) {
  draw_get_cursor(&M5.Display, vm, v, argc);
}

static void class_display_set_rotation(mrb_vm *vm, mrb_value *v, int argc) {
  draw_set_rotation(&M5.Display, vm, v, argc);
}

#ifdef USE_DISPLAY_GRAPHICS

static void class_display_fill_rect(mrb_vm *vm, mrb_value *v, int argc) {
  draw_fill_rect(&M5.Display, vm, v, argc);
}

static void class_display_draw_rect(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_rect(&M5.Display, vm, v, argc);
}

static void class_display_flll_circle(mrb_vm *vm, mrb_value *v, int argc) {
  draw_flll_circle(&M5.Display, vm, v, argc);
}

static void class_display_draw_circle(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_circle(&M5.Display, vm, v, argc);
}

static void class_display_draw_line(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_line(&M5.Display, vm, v, argc);
}

#ifdef USE_FILE_FUNCTION
static void class_display_draw_bmp(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_bmp(&M5.Display, vm, v, argc);
}

static void class_display_draw_jpg(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_jpg(&M5.Display, vm, v, argc);
}

static void class_display_draw_png(mrb_vm *vm, mrb_value *v, int argc) {
  draw_draw_png(&M5.Display, vm, v, argc);
}
#endif  // USE_FILE_FUNCTION

static void class_display_draw_bmpstr(mrb_vm *vm, mrb_value *v, int argc)
{
    draw_draw_bmpstr(&M5.Display,vm,v,argc);
}

static void class_display_draw_jpgstr(mrb_vm *vm, mrb_value *v, int argc)
{
    draw_draw_jpgstr(&M5.Display,vm,v,argc);
}

static void class_display_draw_pngstr(mrb_vm *vm, mrb_value *v, int argc)
{
    draw_draw_pngstr(&M5.Display,vm,v,argc);
}

static void class_display_scroll(mrb_vm *vm, mrb_value *v, int argc) {
  draw_scroll(&M5.Display, vm, v, argc);
}

static void class_display_wait_display(mrb_vm *vm, mrb_value *v, int argc) {
  M5.Display.waitDisplay();
}

static void class_display_start_write(mrb_vm *vm, mrb_value *v, int argc) {
  M5.Display.startWrite();
}

static void class_display_end_write(mrb_vm *vm, mrb_value *v, int argc) {
  M5.Display.endWrite();
}

#endif  // USE_DISPLAY_GRAPHICS

static void class_btn_is_pressed(mrb_vm *vm, mrb_value *v, int argc) {
  int no = *v->instance->data;
  m5::Button_Class btns[] = {M5.BtnA, M5.BtnB, M5.BtnC,
#ifdef USE_FULL_BUTTONS
                             M5.BtnEXT, M5.BtnPWR
#endif
  };
  if (0 <= no && no < sizeof(btns)) {
    if (btns[no].isPressed()) {
      SET_TRUE_RETURN();
    } else {
      SET_FALSE_RETURN();
    }
  }
}

static void class_btn_was_pressed(mrb_vm *vm, mrb_value *v, int argc) {
  int no = *v->instance->data;
  m5::Button_Class btns[] = {M5.BtnA, M5.BtnB, M5.BtnC};
  if (0 <= no && no < sizeof(btns)) {
    if (btns[no].wasPressed()) {
      SET_TRUE_RETURN();
    } else {
      SET_FALSE_RETURN();
    }
  }
}

static void class_btn_no(mrb_vm *vm, mrb_value *v, int argc) {
  SET_INT_RETURN(*v->instance->data);
}

void class_display_button_init() {
  mrb_class *class_display;
  class_display = mrbc_define_class(0, "Display", mrbc_class_object);
  mrbc_define_method(0, class_display, "available?", class_display_available);

  mrbc_define_method(0, class_display, "print", class_display_print);
  mrbc_define_method(0, class_display, "println", class_display_puts);
  mrbc_define_method(0, class_display, "puts", class_display_puts);
  mrbc_define_method(0, class_display, "set_text_size",
                     class_display_set_text_size);
  mrbc_define_method(0, class_display, "set_text_color",
                     class_display_set_text_color);
  mrbc_define_method(0, class_display, "clear", class_display_clear);
  mrbc_define_method(0, class_display, "set_cursor", class_display_set_cursor);
  mrbc_define_method(0, class_display, "get_cursor", class_display_get_cursor);

  mrbc_define_method(0, class_display, "color565", class_display_color_value);
  mrbc_define_method(0, class_display, "dimension", class_display_dimension);

#ifdef USE_DISPLAY_GRAPHICS
  mrbc_define_method(0, class_display, "start_write",
                     class_display_start_write);
  mrbc_define_method(0, class_display, "end_write", class_display_end_write);
  mrbc_define_method(0, class_display, "fill_rect", class_display_fill_rect);
  mrbc_define_method(0, class_display, "draw_rect", class_display_draw_rect);
  mrbc_define_method(0, class_display, "fill_circle",
                     class_display_flll_circle);
  mrbc_define_method(0, class_display, "draw_circle",
                     class_display_draw_circle);
  mrbc_define_method(0, class_display, "draw_line", class_display_draw_line);
#ifdef USE_FILE_FUNCTION
  mrbc_define_method(0, class_display, "draw_bmpfile", class_display_draw_bmp);
  mrbc_define_method(0, class_display, "draw_jpgfile", class_display_draw_jpg);
  mrbc_define_method(0, class_display, "draw_pngfile", class_display_draw_png);
#endif  // USE_FILE_FUNCTION
  mrbc_define_method(0, class_display, "wait_display", class_display_wait_display);
  mrbc_define_method(0, class_display, "draw_bmpstr", class_display_draw_bmpstr);
  mrbc_define_method(0, class_display, "draw_jpgstr", class_display_draw_jpgstr);
  mrbc_define_method(0, class_display, "draw_pngstr", class_display_draw_pngstr);

  mrbc_define_method(0, class_display, "scroll", class_display_scroll);
  mrbc_define_method(0, class_display, "set_rotation",
                     class_display_set_rotation);
#endif  // USE_DISPLAY_GRAPHICS

  mrb_class *class_btn, *class_btna, *class_btnb, *class_btnc;
  class_btn = mrbc_define_class(0, "BtnClass", mrbc_class_object);
  mrbc_define_method(0, class_btn, "is_pressed?", class_btn_is_pressed);
  mrbc_define_method(0, class_btn, "was_pressed?", class_btn_was_pressed);
  mrbc_define_method(0, class_btn, "number", class_btn_no);

  mrbc_value btn = mrbc_instance_new(0, class_btn, sizeof(int));
  *btn.instance->data = 0;  // btnA
  mrbc_set_const(mrbc_str_to_symid("BtnA"), &btn);

  btn = mrbc_instance_new(0, class_btn, sizeof(int));
  *btn.instance->data = 1;  // btnB
  mrbc_set_const(mrbc_str_to_symid("BtnB"), &btn);

  btn = mrbc_instance_new(0, class_btn, sizeof(int));
  *btn.instance->data = 2;  // btnC
  mrbc_set_const(mrbc_str_to_symid("BtnC"), &btn);

#ifdef USE_FULL_BUTTONS
  btn = mrbc_instance_new(0, class_btn, sizeof(int));
  *btn.instance->data = 3;  // btnEXT
  mrbc_set_const(mrbc_str_to_symid("BtnEXT"), &btn);

  btn = mrbc_instance_new(0, class_btn, sizeof(int));
  *btn.instance->data = 4;  // btnPWR
  mrbc_set_const(mrbc_str_to_symid("BtnPWR"), &btn);
#endif  // USE_ FULL_BUTTONS
}