#include "wokwi-api.h"
#include <stdlib.h>
typedef struct { pin_t out; uint32_t reading; } chip_state_t;
static void update(void *data) {
 chip_state_t *s = data;
 // Wokwi ADC full scale is represented by 5V; UI uses raw 12-bit counts.
 pin_dac_write(s->out, attr_read(s->reading) * 5.0f / 4095.0f);
}
void chip_init(void) {
 chip_state_t *s = calloc(1,sizeof(chip_state_t));
 pin_init("VCC",INPUT); pin_init("GND",INPUT);
 s->out=pin_init("AO",ANALOG); s->reading=attr_init("reading",600);
 timer_config_t cfg={.callback=update,.user_data=s};
 timer_start(timer_init(&cfg),1000,true); update(s);
}
