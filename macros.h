/*
 * macros.h
 *
 *  Created on: Jan 25, 2024
 *      Author: 13364
 */

#ifndef MACROS_H_
#define MACROS_H_
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define FALSE                (0x00)

// STATES ======================================================================
//#define NONE ('N')
//#define STRAIGHT ('L')
//#define CIRCLE ('C')
//#define Fig8 ('F')
//#define TRIANGLE ('T')
//#define WAIT ('W')
//#define START ('S')
//#define RUN ('R')
//#define RUNT ('U')
//#define END ('E')
#define WHEEL_COUNT_TIME (50)
#define RIGHT_COUNT_TIME (50)
#define LEFT_COUNT_TIME (50)
#define TRAVEL_DISTANCE (20)
#define WAITING2START (200)
#define MINUTES (600)

//====================================================================
//#define FIND_CIRCLE ('A')
//#define TURN_LEFT ('B')
//#define WAIT2 ('D')

// Wheel defined for circle==============================================================
#define RIGHT_CIRCLE_COUNT_TIME (20)
#define LEFT_CIRCLE_COUNT_TIME (50)
#define TRAVEL_DISTANCE_CIRCLE (40)


// Wheel Defined for Fig Eight ===================================================
#define TRAVEL_DISTANCE_FigEight (80)
#define RIGHT_CIRCLE_REVERSE_COUNT_TIME (50)
#define LEFT_CIRCLE_REVERSE_COUNT_TIME (20)

// Wheel Defined for Triangle
#define TRIANGLE_STRAIGHT_DISTANCE (3)
#define RIGHT_TRIANGLE_TURN_COUNT_TIME (0)
#define LEFT_TRIANGLE_TURN_COUNT_TIME (32)
#define TRAVEL_DISTANCE_TRIANGLE_TURN (3)
#define TRIANGLE_SET_DISTANCE (10)
#define TOTAL_TRIANGLE_DISTANCE (6)
#define TRIANGLE_WHEEL_COUNT_TIME (50)

// Defines for Switches
#define DEBOUNCE_TIME (20)
#define PRESSED (1)
#define NOT_OKAY (0)
#define DEBOUNCE_RESTART (0)
#define RELEASED (0)
#define OKAY (1)

// Macros for interrupts
#define P4PUD (P4OUT)

//
#define TB0CCR0_INTERVAL (5000) // 8,000,000 / 2 / 8 / (1 / 5msec) - 10msec
#define TB0CCR1_INTERVAL (7000) // 8,000,000 / 2 / 8 / (1 / 5msec) - 50msec
#define TB0CCR2_INTERVAL (13000) // 8,000,000 / 2 / 8 / (1 / 5msec) - 50msec
#define TB1CCR0_INTERVAL (25000)
#define TB1CCR1_INTERVAL (25000)
//#define TB1CCR2_INTERVAL (25000)

// PWM Value definitions
#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)


// IOT Macros definition
#define SMALL_RING_SIZE (16)
#define BEGINNING (0)

// Definitions for movement cases
#define STOP ('S')
#define LEFT ('L')
#define RIGHT ('R')
#define FRONT ('F')
#define BACK ('B')
#define AUTO ('A')
#define OFF (00000)
#define ARRIVED ('I')
#define DECREMENT ('D')
#define FOR2SEC ('M')
#define EXIT ('E')

#endif /* MACROS_H_ */
