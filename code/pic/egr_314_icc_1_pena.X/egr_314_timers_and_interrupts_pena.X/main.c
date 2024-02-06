/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F47Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <string.h>

uint16_t t_ms = 0;
uint16_t t_s = 0;
float t = 0;

float t_b = 0;

uint16_t dc = 0;

void timer_callback(void){
    
    //IO_RE0_SetHigh();
    t_ms++;
    
    if (t_ms >= 1000){
        
        t_ms = t_ms - 1000;
        t_s++;
        IO_RE0_Toggle();
        
    }
    
}

// IO_RA0 (Button connected to RA0)
void pin_up(void){
    
    IO_RC7_SetHigh();
    t_b = (float)t_s + ((float)t_ms/1000);
    
}

// IO_RA1 (Button connected to RA1)
void pin_down(void){
    
    IO_RC7_SetLow();
    t_b = (float)t_s + ((float)t_ms/1000);
    
}


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART2_Initialize();
    PIN_MANAGER_Initialize();
    
    IOCAF0_SetInterruptHandler(pin_up);
    
    IOCAF0_SetInterruptHandler(pin_down);
     
     

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

     // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    
    TMR2_SetInterruptHandler(timer_callback); // Calls the timer interrupt
    // function
    
    TMR2_StartTimer();
    
    while (1)
    {
        
        t = (float)t_s + ((float)t_ms/1000);
        
        printf("t: %f s\r\n", t);
                
        if (IO_RA0_GetValue()== 0){
            
            IO_RC7_SetHigh();
            if (dc < 100){
                
                dc = dc +25;
                
            }
            
            printf("dc: %d%\r\n", dc);
        
        }
        
        else if (IO_RA1_GetValue() == 0){
            
            IO_RC7_SetLow();
            if (dc < 100){
                
                dc = dc +25;
                
            }
            
            printf("dc: %d%\r\n", dc);
        
        }
        
        else {
            
            dc = 0;                
            printf("dc: %d%\r\n", dc);
            
        }
        
    }
    
}
/**
 End of File
*/