/*
 * screen.h
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#ifndef GRAPHICS_GUI_SCREEN_H_
#define GRAPHICS_GUI_SCREEN_H_

#include "main.h"
#include "iron.h"
#include "pid.h"
#include "settings.h"
#include "display.h"

#include "widgets.h"
#include "adc_global.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include "tempsensors.h"
#include "voltagesensors.h"

typedef enum {
    screen_boot,
    screen_main,
      screen_settings,
          screen_iron,
            screen_advFilter,
            screen_ntc,
          screen_system,
              screen_display,
                screen_display_adv,
              screen_reset,
                screen_reset_confirmation,
          screen_debug,
            screen_pid_debug,
          screen_tip_list,
            screen_tip_settings,
          screen_calibration,
              screen_calibration_start,
              screen_calibration_settings,
              screen_calibration_input,
          screen_addons,
              screen_fume_extractor_settings,
              screen_switch_off_reminder_settings,
}screens_t;

typedef struct screen_t screen_t;
typedef enum{ screen_Idle=0, screen_Erase, screen_Erased } screenState_t;

struct screen_t
{
  struct screen_t *next_screen;
  widget_t *widgets;
  widget_t *current_widget;
  void (*init)(screen_t *scr);
  void (*create)(screen_t *scr);
  int (*processInput)(struct screen_t *scr, RE_Rotation_t input, RE_State_t *);
  void (*update)(screen_t *scr);
  uint8_t (*draw)(screen_t *scr);
  void (*onEnter)(screen_t *scr);
  void (*onExit)(screen_t *scr);
  uint8_t backup_combo_scroll;
  uint8_t backup_combo_index;
  screenState_t state;
  bool enabled;
  screens_t index;
};

widget_t *screen_tabToWidget(screen_t * scr, uint8_t tab);
void screen_addWidget(widget_t *widget, screen_t *scr);
uint8_t default_screenDraw(screen_t *scr);
int default_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *);
void default_screenUpdate(screen_t *scr);
void screen_setDefaults(screen_t *scr);
void default_init(screen_t *scr);

#endif /* GRAPHICS_GUI_SCREEN_H_ */
