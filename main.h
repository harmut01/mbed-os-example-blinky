#ifndef MAIN_H
#define MAIN_H
// @brief function initialises PA5 as gpio output for led  
// @inputs none 
// @outputs none 
void led_init();

// @brief function initialises PC13 gpio output for push button 
// @inputs none 
// @outputs none 
void pb_init(); 


// @brief function setups isr to respond to push buttons 
// @inputs none 
// @outputs none 
void pb_irq_init();

// @brief push button irq handler, increments frequency and pb counter  
// @inputs none 
// @outputs none 
void pb_irq_handler(void); 

void WWDG_IRQHandler(void);

#endif