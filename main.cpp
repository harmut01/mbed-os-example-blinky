/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "stm32f411xe.h"
#include "main.h"
#include "mbed.h"

// DigitalIn button_test(BUTTON1);
InterruptIn button(BUTTON1);

void pb_irq_handler(void){
    if (EXTI->PR & EXTI_PR_PR13){
        GPIOA->BSRR |= GPIO_BSRR_BR5;
        EXTI->PR &= ~EXTI_PR_PR13;
    }
}

int main()
{
    int pb_status = 0;


    led_init();
    //pb_init();

        // enable IRQ for push button 
    button.rise(&pb_irq_handler);
    button.enable_irq();

    if (NVIC_GetEnableIRQ(EXTI15_10_IRQn))
        GPIOA->BSRR |= GPIO_BSRR_BS5;
    
    if (NVIC_GetEnableIRQ(EXTI1_IRQn))
        GPIOA->BSRR |= GPIO_BSRR_BR5;

    while (true) {
        // // read push button to check state         
        // if (!(GPIOC->IDR & GPIO_IDR_ID13)){
        //     // turn led on 
        //     GPIOA->BSRR |= GPIO_BSRR_BS5;
        // } else {
        //     GPIOA->BSRR |= GPIO_BSRR_BR5; // turn led off 
        // }
    }
}


void led_init(){
    // function to configure LED GPIO pin (PA5)
    // set AB1ENR 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // set MODER to output mode (0x00 --> 0x01)
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    // set OTYPER to push-pull (0x00
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
    // OSPEEDR to fast (0x10) 
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5_0;  
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;  
    // set resistor mode to pull up mode (0x00 --> 0x01
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_1;
}

void pb_init(){
    // function to configure PB GPIO pin (PC13)   
    // SET AB1ENR
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 
    // set MODER to input mode (0x00)
    GPIOC->MODER &= ~GPIO_MODER_MODE13;
    // set output speed to fast mode 
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
    // set resistor mode to pull up (0x00 --> 0x01)  
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13_1;
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0;
     
    //pb_irq_init();
}

void pb_irq_init(){
    // map PC13 to EXTI13 
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13_Msk;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
    
    // Configure mask bits of interrupt line (EXTI13) -> EXTI_IMR, 0x1 << 13
    EXTI->IMR |= EXTI_IMR_MR13;

    // Configure trigger selection bits of the interrupt lines (EXTI_RTSR and 
    // FTSR) -> set to trigger on falling edge (EXTI_FTSR = 0x1 << 13; 
    EXTI->RTSR |= EXTI_RTSR_TR13;
 
    // Configure the enable and mask bits that control the NVIC IRQ channel mapped 
    // to the external interrupt controller (EXTI15_10) -> SYSCFG_EXTICR4, 0x0010 << 4
    NVIC_SetPriority(EXTI15_10_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void WWDG_IRQHandler(void){
    while(true){
        // debug function implement
    }
}


