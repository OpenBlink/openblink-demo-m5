#include <M5Unified.h>

#include "my_mrubydef.h"

#ifdef USE_CANVAS
#include "c_canvas.h"
#include "drawing.h"

static mrbc_class *canvas_class;

static void c_canvas_new(mrb_vm *vm, mrb_value *v, int argc) {
  v[0] = mrbc_instance_new(vm, v[0].cls, sizeof(M5Canvas));
  mrbc_instance_call_initialize(vm, v, argc);
}

static void c_canvas_initialize(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = new M5Canvas(&M5.Display);
  *(M5Canvas **)v->instance->data = canvas;

  if (argc > 2) {
    int depth = val_to_i(vm, v, GET_ARG(3), argc);
    canvas->setColorDepth(depth);
  }
  if (argc > 1) {
    int width = val_to_i(vm, v, GET_ARG(1), argc);
    int height = val_to_i(vm, v, GET_ARG(2), argc);
    auto ptr = canvas->createSprite(width, height);
    if (ptr == nullptr) {
      delete canvas;
      *(M5Canvas **)v->instance->data = nullptr;
      mrbc_raise(vm, MRBC_CLASS(RuntimeError), "sprite creation failed");
    }
  } else {
    mrbc_raise(vm, MRBC_CLASS(ArgumentError), "w/h");
  }
}

static void c_canvas_create_sprite(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  if (argc == 2) {
    int width = val_to_i(vm, v, GET_ARG(1), argc);
    int height = val_to_i(vm, v, GET_ARG(2), argc);
    canvas->createSprite(width, height);
  } else {
    mrbc_raise(vm, MRBC_CLASS(ArgumentError), "width must be specified");
    SET_FALSE_RETURN();
  }
}

static void c_canvas_push_sprite(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);

  if (argc == 2) {
    int x = val_to_i(vm, v, GET_ARG(1), argc);
    int y = val_to_i(vm, v, GET_ARG(2), argc);
    canvas->pushSprite(x, y);
  } else if (argc == 3) {
    LovyanGFX *dst;
    if (mrbc_obj_is_kind_of(&GET_ARG(1), canvas_class)) {
      dst = get_checked_data(M5Canvas, vm, (&GET_ARG(1)));
    } else {
      dst = &M5.Display;  // no error, fall on default
    }
    int x = val_to_i(vm, v, GET_ARG(2), argc);
    int y = val_to_i(vm, v, GET_ARG(3), argc);
    canvas->pushSprite(dst, x, y);
  } else {
    mrbc_raise(vm, MRBC_CLASS(ArgumentError), "x-y");
    SET_FALSE_RETURN();
  }
}

static void c_canvas_delete_sprite(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  canvas->deleteSprite();
}

static void c_canvas_scroll(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  ;
  draw_scroll(canvas, vm, v, argc);
}

static void c_canvas_get_dimension(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_get_dimension(canvas, vm, v, argc);
}

static void c_canvas_set_text_color(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_set_text_color(canvas, vm, v, argc);
}

static void c_canvas_set_text_size(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_set_text_size(canvas, vm, v, argc);
}

static void c_canvas_set_cursor(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_set_cursor(canvas, vm, v, argc);
}

static void c_canvas_get_cursor(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_get_cursor(canvas, vm, v, argc);
}

static void c_canvas_print(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_print(canvas, vm, v, argc);
}

static void c_canvas_puts(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_puts(canvas, vm, v, argc);
}

static void c_canvas_clear(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_clear(canvas, vm, v, argc);
}

static void class_canvas_fill_rect(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_fill_rect(canvas, vm, v, argc);
}

static void class_canvas_draw_rect(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_rect(canvas, vm, v, argc);
}

static void class_canvas_flll_circle(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_flll_circle(canvas, vm, v, argc);
}

static void class_canvas_draw_circle(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_circle(canvas, vm, v, argc);
}

static void class_canvas_draw_line(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_line(canvas, vm, v, argc);
}

#ifdef USE_FILE_FUNCTION
static void class_canvas_draw_bmp(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_bmp(canvas, vm, v, argc);
}

static void class_canvas_draw_jpg(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_jpg(canvas, vm, v, argc);
}

static void class_canvas_draw_png(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_draw_png(canvas, vm, v, argc);
}

#endif  // USE_FILE_FUNCTION

static void class_canvas_draw_bmpstr(mrb_vm *vm, mrb_value *v, int argc)
{
    M5Canvas *canvas =get_checked_data(M5Canvas,vm, v);
    draw_draw_bmpstr(canvas,vm,v,argc);
}

static void class_canvas_draw_jpgstr(mrb_vm *vm, mrb_value *v, int argc)
{
    M5Canvas *canvas =get_checked_data(M5Canvas,vm, v);
    draw_draw_jpgstr(canvas,vm,v,argc);
}

static void class_canvas_draw_pngstr(mrb_vm *vm, mrb_value *v, int argc)
{
    M5Canvas *canvas =get_checked_data(M5Canvas,vm, v);
    draw_draw_pngstr(canvas,vm,v,argc);
}

static void class_canvas_set_rotation(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  draw_set_rotation(canvas, vm, v, argc);
}

static void class_canvas_destroy(mrb_vm *vm, mrb_value *v, int argc) {
  M5Canvas *canvas = get_checked_data(M5Canvas, vm, v);
  delete canvas;
  put_null_data(v);
}

void class_canvas_init() {
  // define class
  canvas_class = mrbc_define_class(0, "Canvas", mrbc_class_object);
  mrbc_define_method(0, canvas_class, "new", c_canvas_new);
  mrbc_define_method(0, canvas_class, "initialize", c_canvas_initialize);
  mrbc_define_method(0, canvas_class, "scroll", c_canvas_scroll);
  mrbc_define_method(0, canvas_class, "push_sprite", c_canvas_push_sprite);
  mrbc_define_method(0, canvas_class, "delete_sprite", c_canvas_delete_sprite);
  mrbc_define_method(0, canvas_class, "create_sprite", c_canvas_create_sprite);
  mrbc_define_method(0, canvas_class, "destroy", class_canvas_destroy);

  mrbc_define_method(0, canvas_class, "set_text_color",
                     c_canvas_set_text_color);
  mrbc_define_method(0, canvas_class, "set_text_size", c_canvas_set_text_size);
  mrbc_define_method(0, canvas_class, "set_cursor", c_canvas_set_cursor);
  mrbc_define_method(0, canvas_class, "get_cursor", c_canvas_get_cursor);
  mrbc_define_method(0, canvas_class, "print", c_canvas_print);
  mrbc_define_method(0, canvas_class, "puts", c_canvas_puts);
  mrbc_define_method(0, canvas_class, "clear", c_canvas_clear);

  mrbc_define_method(0, canvas_class, "fill_rect", class_canvas_fill_rect);
  mrbc_define_method(0, canvas_class, "draw_rect", class_canvas_draw_rect);
  mrbc_define_method(0, canvas_class, "fill_circle", class_canvas_flll_circle);
  mrbc_define_method(0, canvas_class, "draw_circle", class_canvas_draw_circle);
  mrbc_define_method(0, canvas_class, "draw_line", class_canvas_draw_line);
#ifdef USE_FILE_FUNCTION
  mrbc_define_method(0, canvas_class, "draw_bmpfile", class_canvas_draw_bmp);
  mrbc_define_method(0, canvas_class, "draw_jpgfile", class_canvas_draw_jpg);
  mrbc_define_method(0, canvas_class, "draw_pngfile", class_canvas_draw_png);
#endif  // USE_FILE_FUNCTION
mrbc_define_method(0, canvas_class, "draw_bmpstr", class_canvas_draw_bmpstr);
mrbc_define_method(0, canvas_class, "draw_jpgstr", class_canvas_draw_jpgstr);
mrbc_define_method(0, canvas_class, "draw_pngstr", class_canvas_draw_pngstr);
mrbc_define_method(0, canvas_class, "set_rotation",
                     class_canvas_set_rotation);
  mrbc_define_method(0, canvas_class, "dimension", c_canvas_get_dimension);
}

#endif  // USE_CANVAS