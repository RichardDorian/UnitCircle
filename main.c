#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "extapp_api.h"

#include "inc/peripherals.h"
#include "inc/drawing.h"

void extapp_main(void) {
   waitForKeyReleased();

   init_display();
   draw_toolbar();

   draw_circle(CIRCLE_RADIUS, TEXT_COLOR, false);
   draw_angle_marks(CIRCLE_RADIUS);

   // uint8_t circleSize = CIRCLE_RADIUS;

   // while (true) {
   //    if (extapp_isKeydown(KEY_CHAR_0)) break;

   //    if (extapp_isKeydown(KEY_CHAR_MINUS) || extapp_isKeydown(KEY_CHAR_FRAC)) {
   //       init_display();
   //       draw_toolbar();

   //       if (extapp_isKeydown(KEY_CHAR_MINUS)) circleSize++;
   //       else circleSize--;

   //       draw_circle(circleSize, TEXT_COLOR, false);
   //       draw_angle_marks(circleSize);

   //       waitForKeyReleased();
   //    }
   // }

   waitForKeyPressed();
   waitForKeyReleased();

   return;
}