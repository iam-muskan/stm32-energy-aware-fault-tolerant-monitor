#include "wokwi-api.h"
#include <stdlib.h>
typedef struct { pin_t out; uint32_t percent; } chip_state_t;
static void update(void *data) {
  chip_state_t *s = data;
  pin_dac_write(s->out, attr_read_float(s->percent) * 0.05f);
}
void chip_init(void) {
  chip_state_t *s = calloc(1, sizeof(chip_state_t));
  pin_init("GND", INPUT);
  s->out = pin_init("SOC", ANALOG);
  s->percent = attr_init_float("percent", 80);
  timer_config_t cfg = { .callback = update, .user_data = s };
  timer_start(timer_init(&cfg), 1000, true);
  update(s);
}
