#include "wokwi-api.h"
#include <stdlib.h>
typedef struct { pin_t out, led; uint32_t dust; } chip_state_t;
static void update(void *data) {
  chip_state_t *s = data;
  float v = pin_read(s->led) ? 0.9f + attr_read_float(s->dust) * 0.005f : 0;
  pin_dac_write(s->out, v * 0.6f * 5.0f / 3.3f);
}
void chip_init(void) {
  chip_state_t *s = calloc(1, sizeof(chip_state_t));
  pin_init("VCC", INPUT); pin_init("GND", INPUT);
  s->led = pin_init("LED", INPUT);
  s->out = pin_init("VO", ANALOG);
  s->dust = attr_init_float("dust", 50);
  timer_config_t cfg = { .callback = update, .user_data = s };
  timer_start(timer_init(&cfg), 10, true);
  update(s);
}
