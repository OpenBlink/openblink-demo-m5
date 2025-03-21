#include "c_m5u.h"

#include <M5Unified.h>

#include "c_canvas.h"
#include "c_display_button.h"
#include "c_font.h"
#include "c_m5.h"
#include "c_speaker.h"
#include "c_touch.h"
#include "c_utils.h"
#include "my_mrubydef.h"

void init_c_m5u() {
  class_m5_init();
  class_display_button_init();
  class_utils_init();
#ifdef USE_TOUCH
  class_touch_init();
#endif
#ifdef USE_CANVAS
  class_canvas_init();
#endif
#ifdef USE_SPEAKER
  class_speaker_init();
#endif
#ifdef USE_FONT
  class_font_init();
//  c_font_add("JapanGothic_8", &lgfxJapanGothic_8);
#endif
}