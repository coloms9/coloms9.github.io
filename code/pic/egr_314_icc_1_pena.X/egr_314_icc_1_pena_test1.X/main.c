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

/* Disable Watch Dog Timer */
#pragma config WDTE = OFF  
/* Low voltage programming enabled , RE3 pin is MCLR */
#pragma config LVP = ON               

#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAX_COMMAND_LEN 10

void executeCommand(char *command)
{
    if(strcmp(command, "ON") == 0)
    {
        LATEbits.LATE0 = 0;
        printf("OK, LED ON.\r\n");
    }
    else if (strcmp(command, "OFF") == 0)
    {
        LATEbits.LATE0 = 1;
        printf("OK, LED OFF.\r\n");
    } 
    else 
    {
        printf("Incorrect command.\r\n");
    }
}

void main(void)
{
    char command[MAX_COMMAND_LEN];
    uint8_t index = 0;
    char c;
    char msg[] = "test\r\n";
    
    while(1) 
    {
        c = getch();
        if(c != '\n')
        {
            command[index++] = c;
            if(index > MAX_COMMAND_LEN)
            {
                index = 0;
            }
        }
        
        if(c == ';')
        {
            command[index] = '\0';
            index = 0;
            for(uint8_t i = 0; i < strlen(msg); i++)
                {
                    EUSART2_Write(msg[i]);
                }
        }
    }
}