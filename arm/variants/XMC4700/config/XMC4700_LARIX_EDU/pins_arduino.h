/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
  Copyright (c) 2018 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC4700.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 4700 Relax Kit
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define  XMC_LED_ON         0

#define NUM_ANALOG_INPUTS   5
#define NUM_PWM             23
#define NUM_LEDS            3
#define NUM_INTERRUPT       2
#define NUM_SERIAL          2
#define NUM_TONE_PINS       16
#define NUM_TASKS_VARIANT   32

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 64000000u 
 
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

extern uint8_t SS; 
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define PIN_SPI_SS_SD    28
#define PIN_SPI_MOSI_SD  29
#define PIN_SPI_MISO_SD  30
#define PIN_SPI_SCK_SD   31

static const uint8_t SS_SD   = PIN_SPI_SS_SD;
static const uint8_t MOSI_SD = PIN_SPI_MOSI_SD;
static const uint8_t MISO_SD = PIN_SPI_MISO_SD;
static const uint8_t SCK_SD  = PIN_SPI_SCK_SD;

#define A0   0  // Isense_ESC
#define A1   1  // Vbat_ESC
#define A2   2  // Vbat
#define A3   3  // P14.8
#define A4   4  // P14.9

#define LED_BUILTIN 2   //Standard Arduino LED: Used LED1
#define LED1        2   // Additional LED1
#define LED2        3   // Additional LED2
#define LED3        4   // Additional LED3
#define GND         50  // needed for serial communication
#define RPI_ON      15  // Raspi on switch pin

#define digitalPinToInterrupt(p)    ((p) == 35 ? 0 : NOT_AN_INTERRUPT)

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][ 2 ] = {
                                        { 22, 0 },
                                        { 23, 1 },
                                        { 24, 2 },
                                        { 25, 3 },
                                        { 72, 4 },
                                        { 96, 5 },
                                        { 63, 6 },
                                        { 36, 7 },
                                        { 78, 8 },
                                        { 90, 9 },
                                        { 91, 10 },
                                        { 255, 255 } };
const uint8_t mapping_pin_PWM8[][ 2 ] = {
                                        { 5, 0 },
                                        { 6, 1 },
                                        { 9, 2 },
                                        { 53, 3 },
                                        { 39, 4 },
                                        { 64, 5 },
                                        { 38, 6 },
                                        { 68, 7 },
                                        { 79, 8 },
                                        { 83, 9 },
                                        { 82, 10 },
                                        { 81, 11 },
                                        { 255, 255 } };
const uint8_t mapping_pin_DAC[][ 2 ] = {
                                        { 50, 0 },
                                        { 55, 1 },
                                        { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT2 , 7},   // RC_PPM                       P2.7
    /* 1  */    {XMC_GPIO_PORT3 , 4},   // RC_D                         P3.4
    /* 2  */    {XMC_GPIO_PORT1 , 0},   // green LED  (LED1)            P1.0
    /* 3  */    {XMC_GPIO_PORT1 , 1},   // yellow LED (LED2)            P1.1
    /* 4  */    {XMC_GPIO_PORT1 , 2},   // red LED    (LED3)            P1.2
    /* 5  */    {XMC_GPIO_PORT1 , 8},   // CAN_RxD                      P1.8
    /* 6  */    {XMC_GPIO_PORT1 , 9},   // CAN_TxD                      P1.9
    /* 7  */    {XMC_GPIO_PORT1 , 5},   // RPI_RX                       P1.5
    /* 8  */    {XMC_GPIO_PORT1 , 4},   // RPI_TX                       P1.4
    /* 9  */    {XMC_GPIO_PORT0 , 2},   // RPI_GPIO5                    P0.2
    /* 10  */   {XMC_GPIO_PORT0 , 10},  // RPI_GPIO6                    P0.10
    /* 11  */   {XMC_GPIO_PORT2 , 15},  // RPI_GPIO13                   P2.15
    /* 12  */   {XMC_GPIO_PORT2 , 14},  // RPI_GPIO19                   P2.14
    /* 13  */   {XMC_GPIO_PORT3 , 3},   // RPI_GPIO24                   P3.3
    /* 14  */   {XMC_GPIO_PORT0 , 3},   // RPI_GPIO25                   P0.3
    /* 15  */   {XMC_GPIO_PORT0 , 9},   // RPI_ON                       P0.9
    /* 16  */   {XMC_GPIO_PORT0 , 4},   // RPI_MOSI                     P0.4
    /* 17  */   {XMC_GPIO_PORT0 , 5 },  // RPI_MISO                     P0.5
    /* 18  */   {XMC_GPIO_PORT0 , 6},   // RPI_CS0                      P0.6
    /* 19  */   {XMC_GPIO_PORT0 , 11},  // RPI_SCLK                     P0.11
    /* 20  */   {XMC_GPIO_PORT5 , 0},   // RPI_SDA/DPS422_SDA/IMU_SDA   P5.0
    /* 21  */   {XMC_GPIO_PORT5 , 2},   // RPI_SCL/DPS422_SCL/IMU_SCL   P5.2
    /* 22  */   {XMC_GPIO_PORT2 , 5},   // PWM1 CCU41                   P2.5
    /* 23  */   {XMC_GPIO_PORT2 , 4},   // PWM2 CCU41                   P2.4
    /* 24  */   {XMC_GPIO_PORT2 , 3},   // PWM3 CCU41                   P2.3
    /* 25  */   {XMC_GPIO_PORT2 , 2},   // PWM4 CCU41                   P2.2
    /* 26  */   {XMC_GPIO_PORT0 , 0},   // TX_XMC4200                   P0.0
    /* 27  */   {XMC_GPIO_PORT0 , 1},   // XMC4200_RX                   P0.1
    /* 28  */   {XMC_GPIO_PORT4 , 1},   // SD_DAT_3 (SD CARD)           P4.1
    /* 29  */   {XMC_GPIO_PORT3 , 5},   // SD_CMD   (SD CARD)           P3.5
    /* 30  */   {XMC_GPIO_PORT4 , 0},   // SD DAT_0 (SD CARD)           P4.0
    /* 31  */   {XMC_GPIO_PORT3 , 6},   // SD_CLK   (SD CARD)           P3.6
    /* 32  */   {XMC_GPIO_PORT1 , 6},   // SD_DAT_1 (SD_CARD)           P1.6
    /* 33  */   {XMC_GPIO_PORT1 , 7},   // SD_DAT_2 (SD_CARD)           P1.7
    /* 34  */   {XMC_GPIO_PORT1 , 10},  // SD_CD    (SD_CARD)           P1.10
    /* 35  */   {XMC_GPIO_PORT2 , 6},   // DPS_INT                      P2.6

	//Additional pins for port X1 starting here
	/* 36  */   {XMC_GPIO_PORT14 , 5},  // Isense_ESC                     P14.5
	/* 37  */   {XMC_GPIO_PORT14 , 6},  // Vbat_ESC                       P14.6               
	/* 38  */   {XMC_GPIO_PORT14 , 7},  // Vbat                           P14.7
	/* 39  */   {XMC_GPIO_PORT14 , 8},  // P14.8                          P14.8
	/* 40  */   {XMC_GPIO_PORT14 , 9},  // P14.9                          P3.10
	/* 41  */   {XMC_GPIO_PORT3 , 2},   // not connected                  P3.2
	/* 42  */   {XMC_GPIO_PORT3 , 1},   // not connected                  P3.1
	/* 43  */   {XMC_GPIO_PORT15 , 6},  // not connected                  P15.6  
	/* 44  */   {XMC_GPIO_PORT15 , 5},  // not connected                  P15.5  
	/* 45  */   {XMC_GPIO_PORT15 , 3},  // not connected                  P15.3  
	/* 46  */   {XMC_GPIO_PORT14 , 15}, // not connected                  P14.15 
	/* 47  */   {XMC_GPIO_PORT14 , 13}, // not connected                  P14.13 
	/* 48  */   {XMC_GPIO_PORT3 , 9},   // not connected                  P3.9  
	/* 49  */   {XMC_GPIO_PORT15 , 15}, // not connected                  P15.15 
	/* 50  */   {XMC_GPIO_PORT3 , 10},  // not connected                  P14.9  
	/* 51  */   {XMC_GPIO_PORT2 , 13},  // not connected                  P2.13
	/* 52  */   {XMC_GPIO_PORT5 , 10},  // not connected                  P5.10
	/* 53  */   {XMC_GPIO_PORT5 , 11},  // not connected                  P5.11
	/* 54  */   {XMC_GPIO_PORT1 , 14},  // not connected                  P1.14
	/* 55  */   {XMC_GPIO_PORT15 , 12}, // not connected                  P15.12  
	/* 56  */   {XMC_GPIO_PORT15 , 14}, // not connected                  P15.14 
	/* 57  */   {XMC_GPIO_PORT14 , 0},  // not connected                  P14.0  
	/* 58  */   {XMC_GPIO_PORT14 , 12}, // not connected                  P14.12 
	/* 59  */   {XMC_GPIO_PORT14 , 14}, // not connected                  P14.14 
	/* 60  */   {XMC_GPIO_PORT15 , 2},  // not connected                  P15.2  
	/* 61  */   {XMC_GPIO_PORT15 , 4},  // not connected                  P15.4  
	/* 62  */   {XMC_GPIO_PORT15 , 7},  // not connected                  P15.7  
	/* 63  */   {XMC_GPIO_PORT3 , 0},   // not connected                  P3.0
	/* 64  */   {XMC_GPIO_PORT3 , 15},  // not connected                  P3.15
	/* 65  */   {XMC_GPIO_PORT15 , 13}, // not connected                  P15.13
	/* 66  */   {XMC_GPIO_PORT1 , 11},  // not connected                  P1.11
	/* 67  */   {XMC_GPIO_PORT0 , 13},  // not connected                  P0.13
	/* 68  */   {XMC_GPIO_PORT14 , 1},  // not connected                  P14.1
	/* 69  */   {XMC_GPIO_PORT14 , 2},  // not connected                  P0.11

	//Additional pins for port X2 starting here
	/* 70  */   {XMC_GPIO_PORT3 , 13},  // not connected                  P3.13
	/* 71  */   {XMC_GPIO_PORT3 , 11},  // not connected                  P3.11
	/* 72  */   {XMC_GPIO_PORT0 , 14},  // not connected                  P0.14
	/* 73  */   {XMC_GPIO_PORT3 , 14},  // not connected                  P3.14
	/* 74  */   {XMC_GPIO_PORT0 , 7},   // not connected                  P0.7
	/* 75  */   {XMC_GPIO_PORT2 , 12},  // not connected                  P2.12
	/* 76  */   {XMC_GPIO_PORT6 , 1},   // not connected                  P6.1
	/* 77  */   {XMC_GPIO_PORT5 , 3},   // not connected                  P5.3
	/* 78  */   {XMC_GPIO_PORT6 , 5},   // not connected                  P6.5
	/* 79  */   {XMC_GPIO_PORT1 , 15},  // not connected                  P1.15
	/* 80  */   {XMC_GPIO_PORT5 , 1},   // not connected                  P5.1
	/* 81  */   {XMC_GPIO_PORT5 , 3},   // not connected                  P5.3
	/* 82  */   {XMC_GPIO_PORT5 , 5},   // not connected                  P5.5
	/* 83  */   {XMC_GPIO_PORT5 , 7},   // not connected                  P5.7
	/* 84  */   {XMC_GPIO_PORT2 , 11},  // not connected                  P2.11
	/* 85  */   {XMC_GPIO_PORT5 , 6},   // not connected                  P5.6
	/* 86  */   {XMC_GPIO_PORT5 , 4},   // not connected                  P5.4
	/* 87  */   {XMC_GPIO_PORT14 , 4},  // not connected                  P14.4
	/* 88  */   {XMC_GPIO_PORT14 , 3},  // not connected                  P14.3
	/* 89  */   {XMC_GPIO_PORT6 , 6},   // not connected                  P6.6
	/* 90  */   {XMC_GPIO_PORT6 , 4},   // not connected                  P6.4
	/* 91  */   {XMC_GPIO_PORT6 , 2},   // not connected                  P6.2
	/* 92  */   {XMC_GPIO_PORT6 , 0},   // not connected                  P6.0
	/* 93  */   {XMC_GPIO_PORT0 , 8},   // not connected                  P0.8
	/* 94  */   {XMC_GPIO_PORT1 , 3},   // not connected                  P1.3
	/* 95  */   {XMC_GPIO_PORT0 , 15},  // not connected                  P0.15
	/* 96  */   {XMC_GPIO_PORT0 , 12},  // not connected                  P0.12
	/* 97  */   {XMC_GPIO_PORT3 , 12},   // not connected                  P3.12
	/* 36  */   {XMC_GPIO_PORT3 , 7}   // not connected                  P3.7
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC43, 3, 0, CCU40_IN3_P2_6},
};

XMC_PWM4_t mapping_pwm4[] =
{
  {CCU41, CCU41_CC40, 0, mapping_port_pin[22], P2_5_AF_CCU41_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  22  P2.5
  {CCU41, CCU41_CC41, 1, mapping_port_pin[23], P2_4_AF_CCU41_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  23  P2.4
  {CCU41, CCU41_CC42, 2, mapping_port_pin[24], P2_3_AF_CCU41_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  24  P2.3
	{CCU41, CCU41_CC43, 3, mapping_port_pin[25], P2_2_AF_CCU41_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  25  P2.2
		
	//additional pwm outputs starting here
	{CCU40, CCU40_CC40, 0, mapping_port_pin[95] , P0_15_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  95  P0.15
	{CCU40, CCU40_CC41, 1, mapping_port_pin[72] , P0_14_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  72  P0.14
	{CCU40, CCU40_CC43, 3, mapping_port_pin[96] , P0_12_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  96  P0.12
	{CCU42, CCU42_CC40, 0, mapping_port_pin[63] , P3_0_AF_CCU42_OUT0 , XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  63  P3.0
	{CCU42, CCU42_CC42, 2, mapping_port_pin[36] , P3_4_AF_CCU42_OUT2 , XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  36  P3.4
	{CCU43, CCU43_CC40, 0, mapping_port_pin[78] , P6_5_AF_CCU43_OUT0 , XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  78  P6.5
	{CCU43, CCU43_CC41, 1, mapping_port_pin[90] , P6_4_AF_CCU43_OUT1 , XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  90  P6.4
	{CCU43, CCU43_CC43, 3, mapping_port_pin[91] , P6_2_AF_CCU43_OUT3 , XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled  91  P6.2
};

XMC_PWM8_t mapping_pwm8[] =
{
    {CCU81, CCU81_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[5],  P2_12_AF_CCU81_OUT33, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  5  P2.12
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[6],  P2_11_AF_CCU80_OUT22, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  6  P2.11
    {CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],  P1_11_AF_CCU81_OUT11, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  9  P1.11
	//additional pwm outputs starting here
	{CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[53], P5_11_AF_CCU80_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  53 P5.11
	{CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[39], P0_1_AF_CCU80_OUT11,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  39 P0.1
	{CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[64], P0_9_AF_CCU80_OUT12,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  64 P0.9
	{CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[38], P0_3_AF_CCU80_OUT20,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  38 P0.3
	{CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[68], P0_6_AF_CCU80_OUT30,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  68 P0.6
	{CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[79], P1_15_AF_CCU81_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  79 P1.15
	{CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[83], P5_7_AF_CCU81_OUT02,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  83 P5.7
	{CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[82], P5_5_AF_CCU81_OUT12,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  82 P5.5
	{CCU81, CCU81_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[81], P5_3_AF_CCU81_OUT22,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}  // PWM disabled  81 P5.3
};

XMC_ARD_DAC_t mapping_dac[] =
{
	{XMC_DAC0, 1, 12},
	{XMC_DAC0, 0, 12}
};

XMC_ADC_t mapping_adc[] =
{
	//Result reg numbers are now equal to channel numbers
	{VADC, 5, VADC_G0, 0, 5, DISABLED},  //A0
	{VADC, 6, VADC_G0, 0, 6, DISABLED},  //A1
	{VADC, 7, VADC_G0, 0, 7, DISABLED},  //A2
	{VADC, 0, VADC_G1, 1, 0, DISABLED},  //A3
	{VADC, 1, VADC_G1, 1, 1, DISABLED},  //A4
};


/*
 * UART objects
 *
 * Serial 0 is Debug port
 * Serial 1  is on-board port
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;
RingBuffer rx_buffer_1;
RingBuffer tx_buffer_1;

XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART1_CH1,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)0
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)1
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C1_DX0_P0_0,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC1_0_IRQn,
  .irq_service_request  = 0
  };

XMC_UART_t XMC_UART_1 =
  {
  .channel              = XMC_UART0_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
                            .pin  = (uint8_t)4
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
                            .pin  = (uint8_t)5
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_P1_4,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC0_0_IRQn,
  .irq_service_request  = 0
  };

// Debug port
HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );
// On-board port
HardwareSerial Serial1( &XMC_UART_1, &rx_buffer_1, &tx_buffer_1 );

#endif

#endif
