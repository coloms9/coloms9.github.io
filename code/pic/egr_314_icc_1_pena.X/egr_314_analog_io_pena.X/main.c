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

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    TMR2_StartTimer(); // Starts the timer
    PWM4_Initialize(); // Starts the PWM4 generator
    ADCC_Initialize(); // Starts the ADCC converter
    ADCC_DisableContinuousConversion();
    
    //ADCC_StartConversion(channel_ANA2); // Analog input: RA2

    adc_result_t adc_val;  // A uint16_t variable
    
    float adc_volt;
    
    char adc_val_start_msg[] = "ADC: ";
    char adc_val_end_msg[] = "\r\n";
    char adc_val_rxData[16];
    
    char adc_volt_start_msg[] = "ADC Voltage: ";
    char adc_volt_end_msg[] = "\r\n\n\n";
    char adc_volt_rxData[16];
    
    uint16_t pwm_write_data;

    while (1)
    {
        
        /*if(0 == TMR2_ReadTimer()) // This if statement sets the timer period
        {
            // Do something else...
            // Not sure if anything goes here

            // Reload the TMR value
            TMR2_LoadPeriodRegister();
        }*/
        
        //if(EUSART2_is_tx_ready())
        //{
        
            ADCC_StartConversion(channel_ANA2);
            adc_val = ADCC_GetConversionResult();

            sprintf(adc_val_rxData, "%d", adc_val);

            adc_volt = ((float)adc_val / 1023) * 3.3;
            sprintf(adc_volt_rxData, "%f", adc_volt);

            pwm_write_data = adc_val << 6; // shift 16 bit variable by 6 bits 
            // because the pwm duty load only takes 10 bit variables
            PWM4_LoadDutyValue(pwm_write_data); // Takes a uint16_t as input

            // To send the ADC value
            for(uint8_t i = 0; i < strlen(adc_val_start_msg); i++)
            {
                EUSART2_Write(adc_val_start_msg[i]);
            }

            for(uint8_t i = 0; i < strlen(adc_val_rxData); i++)
            {
                EUSART2_Write(adc_val_rxData[i]);
            }

            for(uint8_t i = 0; i < strlen(adc_val_end_msg); i++)
            {
                EUSART2_Write(adc_val_end_msg[i]);
            }


            // To send the ADC voltage
            for(uint8_t i = 0; i < strlen(adc_volt_start_msg); i++)
            {
                EUSART2_Write(adc_volt_start_msg[i]);
            }

            for(uint8_t i = 0; i < strlen(adc_volt_rxData); i++)
            {
                EUSART2_Write(adc_volt_rxData[i]);
            }

            for(uint8_t i = 0; i < strlen(adc_volt_end_msg); i++)
            {
                EUSART2_Write(adc_volt_end_msg[i]);
            }

        //}
        
        
    }
}
/**
 End of File
*/