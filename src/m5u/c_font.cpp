
#include <M5Unified.h>
#include "my_mrubydef.h"

#ifdef USE_FONT

#include "c_font.h"

#include <vector>
#include <lgfx/v1/lgfx_fonts.hpp>

#include "drawing.h"

struct font_info {
    const char* name;
    const lgfx::v1::IFont* font;
};

std::vector<struct font_info> m5fonts;

static void
class_font_by_name(mrb_vm *vm, mrb_value *v, int argc)
{
    if(argc>0){
        const char* fontname = val_to_s(vm, v, GET_ARG(1),argc);
        //search the fonrname from m5fonts vector and return the order number of the font
        for(int i=0; i<m5fonts.size(); i++){
            if(strcmp(m5fonts[i].name, fontname)==0){
                SET_INT_RETURN(i);
                return;
            }
        }
    }
    SET_FALSE_RETURN();
}

static void
class_font_number(mrb_vm *vm, mrb_value *v, int argc)
{
    SET_INT_RETURN(m5fonts.size());
}

static void
class_font_names(mrb_vm *vm, mrb_value *v, int argc)
{
    mrbc_value ret = mrbc_array_new(vm, m5fonts.size());
    for(int i=0; i<m5fonts.size(); i++){
        mrbc_value str = mrbc_string_new_cstr(vm, m5fonts[i].name);
        mrbc_array_set(&ret, i, &str);
    }
    SET_RETURN(ret);
}


void draw_set_font(LovyanGFX *dst, mrb_vm *vm, mrb_value *v, int argc)
{
    if(argc>0){
        if(GET_ARG(1).tt == MRBC_TT_INTEGER){
            unsigned int  fontnumber = val_to_i(vm, v, GET_ARG(1),argc);
            if(fontnumber < m5fonts.size()){
                dst->setFont(m5fonts[fontnumber].font);
                SET_TRUE_RETURN();
                return;
            }
        } else if(GET_ARG(1).tt == MRBC_TT_STRING){   // by_name
            const char* fontname = val_to_s(vm, v, GET_ARG(1),argc);
            for(int i=0; i<m5fonts.size(); i++){
                if(strcmp(m5fonts[i].name, fontname)==0){
                    dst->setFont(m5fonts[i].font);
                    SET_TRUE_RETURN();
                    return;
                }
            }
        }
    } 
    SET_FALSE_RETURN();
}

static void class_display_set_font(mrb_vm *vm, mrb_value *v, int argc)
{
    draw_set_font(&M5.Display,vm,v,argc);
}

static void class_canvas_set_font(mrb_vm *vm, mrb_value *v, int argc)
{
    M5Canvas *canvas =get_checked_data(M5Canvas,vm, v);
    draw_set_font(canvas,vm,v,argc);
}

uint8_t c_font_add(const char* fontname, const lgfx::v1::IFont* font)
{
    struct font_info fi;
    fi.name = fontname;
    fi.font = font;
    m5fonts.push_back(fi);
    return m5fonts.size()-1;
}

void class_font_init()  // order dependency. Font must be defined after Display and Canvas
{
    mrb_class *class_font = mrbc_define_class(0, "Font", mrbc_class_object);
    mrbc_define_method(0, class_font, "by_name", class_font_by_name);  // old i/f
    mrbc_define_method(0, class_font, "count", class_font_number);
    mrbc_define_method(0, class_font, "names", class_font_names);

    c_font_add("default", nullptr);
#ifdef USE_EFONTJA10
    c_font_add("efontJA_10", &efontJA_10);
#endif // USE_EFONTJA10


    mrbc_class *class_display = mrbc_get_class_by_name("Display");
    mrbc_class *class_canvas = mrbc_get_class_by_name("Canvas");
    mrbc_define_method(0, class_display, "set_font", class_display_set_font);
    mrbc_define_method(0, class_canvas, "set_font", class_canvas_set_font);
}

#endif // USE_FONT