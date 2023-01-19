#define PI 3.141592654
#define TOOLBAR_HEIGHT 18
#define SMALL_TEXT_HEIGHT 12
#define CIRCLE_RADIUS 80
#define PRIMARY_COLOR 0x54BC
#define BACKGROUND_COLOR 0x2967
#define TEXT_COLOR 0xD6DC

void draw_pixel(int16_t x, int16_t y, uint16_t color);
void draw_line(uint16_t x0, uint16_t y0, uint16_t x1, int16_t y1);
void draw_circle(uint8_t radius, uint16_t color, bool no_recur);
void draw_angle_marks();
void draw_toolbar();