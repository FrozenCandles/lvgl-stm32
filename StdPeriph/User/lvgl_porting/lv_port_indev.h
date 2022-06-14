
/**
 * @file lv_port_indev_templ.h
 *
 */

 /*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl_lib/lvgl.h"
#include "lcd/bsp_xpt2046_lcd.h"
#include "led/bsp_led.h"

/*********************
 *      DEFINES
 *********************/
#define LV_USE_INDEV_TOUCHPAD 	0x0u
#define LV_USE_INDEV_MOUSE	 	0x1u
#define LV_USE_INDEV_KEYPAD 	0x2u
#define LV_USE_INDEV_ENCODER 	0x4u
#define LV_USE_INDEV_BUTTON 	0x8u
#define LV_USE_INDEV  	LV_USE_INDEV_TOUCHPAD	// use Touchpad ? keypad
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_port_indev_init(void);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
