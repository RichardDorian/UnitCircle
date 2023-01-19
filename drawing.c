#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "extapp_api.h"
#include "inc/peripherals.h"

#define PI 3.141592654
#define TOOLBAR_HEIGHT 18
#define SMALL_TEXT_HEIGHT 12
#define CIRCLE_RADIUS 80
#define PRIMARY_COLOR 0x54BC
#define BACKGROUND_COLOR 0x2967
#define TEXT_COLOR 0xD6DC

// Calculcating the origin of the circle
// depending on the sceen size and toolbar height
int16_t origin[2] = {
   LCD_WIDTH / 2,
   (LCD_HEIGHT / 2) + (TOOLBAR_HEIGHT / 2)
};
void draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
   extapp_pushRectUniform(x, y, 1, 1, color);
}

// Modified version of Bresenham's line algorithm
void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t sign(int16_t arg) {
    if (arg < 0) return -1;
    else if (arg == 0) return 0;
    else return 1;
  }

  int16_t x = x0;
  int16_t y = y0;
  int16_t deltaX = abs(x1 - x0);
  int16_t deltaY = abs(y1 - y0);
  int16_t s0 = sign(x1 - x0);
  int16_t s1 = sign(y1 - y0);
  uint8_t interchange = 0;

  if (deltaY > deltaX) {
    int16_t t = deltaX;
    deltaX = deltaY;
    deltaY = t;
    interchange = 1;
  } else {
    interchange = 0;
  }

  int16_t e = 2*deltaY - deltaX;
  int16_t a = 2*deltaY;
  int16_t b = 2*deltaY - 2*deltaX;

  for (int16_t i = 0; i < deltaX; i++) {
    if (e < 0) {
      if (interchange == 1) y = y + s1;
      else x = x + s0;
      e = e + a;
    } else {
      y = y + s1;
      x = x + s0;
      e = e + b;
    }

    draw_pixel(x + origin[0], y + origin[1], color);
  }
}

void draw_circle(uint8_t radius, uint16_t color, bool no_recur) {
   if (!no_recur) {
      draw_circle(radius - 1, 0x5AED, true);
      draw_circle(radius + 1, 0x5AED, true);
   }

   // Mid point circle drawing algorithm
   int16_t x = radius, y = 0;
   int16_t P = 1 - radius;

   while (x > y) {
      y++;

      if (P <= 0) {
         P = P + 2*y +1;
      } else {
         x--;
         P = P + 2*y - 2*x + 1;
      }

      if (x < y) break;

      draw_pixel(x + origin[0], y + origin[1], color);
      draw_pixel(-x + origin[0], y + origin[1], color);
      draw_pixel(x + origin[0], -y + origin[1], color);
      draw_pixel(-x + origin[0], -y + origin[1], color);

      if (x != y) {
         draw_pixel(y + origin[0], x + origin[1], color);
         draw_pixel(-y + origin[0], x + origin[1], color);
         draw_pixel(y + origin[0], -x + origin[1], color);
         draw_pixel(-y + origin[0], -x + origin[1], color);
      }
   }
}

void draw_angle_marks(uint8_t circle_radius) {
  struct NamedAngle {
    double angle;
    char text[6];
  };
  struct NamedAngle angles[16] = {
    { 0, "0" }, { PI/6, "π/6" }, { PI/4, "π/4" }, { PI/3, "π/3" },
    { PI/2, "π/2" }, { 2*PI/3, "2π/3" }, { 3*PI/4, "3π/4" }, { 5*PI/6, "5π/6" },
    { PI, "π" }, { -5*PI/6, "-5π/6" }, { -3*PI/4, "-3π/4" }, { -2*PI/3, "-2π/3" },
    { -PI/2, "-π/2" }, { -PI/3, "-π/3" }, { -PI/4, "-π/4" }, { -PI/6, "-π/6" }
  };

  for (uint8_t i = 0; i < 16; i++) {
    double x = cos((double) angles[i].angle) * circle_radius;
    double y = -sin((double) angles[i].angle) * circle_radius;

    double extX = (circle_radius+10)*x/(circle_radius);
    double extY = (circle_radius+10)*y/(circle_radius);

    draw_line(x, y, extX, extY, PRIMARY_COLOR);

    bool addSelfWidth = false; 
    if (x > 0 && y < 0) extY -= SMALL_TEXT_HEIGHT;
    else if (x < 0 && y > 0) addSelfWidth = true;
    else if ((x < 0 && y < 0)) {
      extY -= SMALL_TEXT_HEIGHT;
      addSelfWidth = true;
    }

    if (addSelfWidth) extX -= extapp_drawTextSmall(angles[i].text, 0, 0, TEXT_COLOR, BACKGROUND_COLOR, true);
    extapp_drawTextSmall(angles[i].text, extX + origin[0], extY + origin[1], TEXT_COLOR, BACKGROUND_COLOR, false);
  }
}

void draw_toolbar() {
  extapp_pushRectUniform(0, 0, LCD_WIDTH, TOOLBAR_HEIGHT, PRIMARY_COLOR);
  int16_t toolbar_title_size = extapp_drawTextSmall("UNIT CIRCLE", 0, 0, TEXT_COLOR, PRIMARY_COLOR, true);
  extapp_drawTextSmall("UNIT CIRCLE", (LCD_WIDTH / 2) - (toolbar_title_size / 2), 3, TEXT_COLOR, PRIMARY_COLOR, false);
}