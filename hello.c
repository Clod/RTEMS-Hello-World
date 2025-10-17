/*
 * Button-triggered Hello World for RTEMS
 */
#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <rtems/version.h>

/* STM32H743 RCC (Reset and Clock Control) */
#define RCC_BASE        0x58024400
#define RCC_AHB4ENR     (*(volatile uint32_t *)(RCC_BASE + 0xE0))
#define RCC_AHB4ENR_GPIOCEN  (1 << 2)  /* Enable GPIOC clock */

/* STM32H743 GPIO Port C */
#define GPIOC_BASE   0x58020800
#define GPIOC_MODER  (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_IDR    (*(volatile uint32_t *)(GPIOC_BASE + 0x10))

/* PC13 is the blue button */
#define BUTTON_PIN   13

rtems_task Init(
  rtems_task_argument ignored
)
{
  int counter = 0;
  bool last_button_state = false;
  bool current_button_state;
  
  printf( "\n\n*** BUTTON-TRIGGERED HELLO WORLD TEST ***\n" );
  printf( "Press the blue button to print message...\n" );
  printf( "Board: STM32H743ZI Nucleo\n" );
  printf( "RTEMS Version: %s\n\n", rtems_version() );
  
  /* Enable GPIOC clock */
  RCC_AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
  
  /* Configure PC13 as input (clear both mode bits) */
  GPIOC_MODER &= ~(0x3 << (BUTTON_PIN * 2));
  
  /* Configure PC13 with no pull-up/pull-down (button has external pull-up) */
  GPIOC_PUPDR &= ~(0x3 << (BUTTON_PIN * 2));
  
  printf( "GPIO configured, waiting for button press...\n" );
  
  while (1) {
    /* Read button state (active low, so invert) */
    current_button_state = !(GPIOC_IDR & (1 << BUTTON_PIN));
    
    /* Detect button press (transition from not pressed to pressed) */
    if (current_button_state && !last_button_state) {
      printf( "Version 10 - Button pressed! Hello World #%d\n", counter );
      counter++;
    }
    
    last_button_state = current_button_state;
    
    /* Debounce delay - 50ms */
    rtems_task_wake_after(RTEMS_MILLISECONDS_TO_TICKS(50));
  }
  
  /* Never reached */
  exit( 0 );
}
