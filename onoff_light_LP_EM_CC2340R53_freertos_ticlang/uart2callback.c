/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uart2callback.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <semaphore.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART2.h>

/* Driver configuration */
#include "ti_drivers_config.h"
#include <stdarg.h>
#define  LOG_ENALBE

static sem_t sem;
static volatile size_t numBytesRead;

static UART2_Handle uart;

void uart2_printf(char *buffer);
void user_print(const char*f,...);
void arry_printf(char *buf,int len);
void *demo_print(void *arg0);

/*
 *  ======== callbackFxn ========
 */
void callbackFxn(UART2_Handle handle, void *buffer, size_t count, void *userArg, int_fast16_t status)
{
    if (status != UART2_STATUS_SUCCESS)
    {
        /* RX error occured in UART2_read() */
        while (1) {}
    }

    numBytesRead = count;
    UART2_write(uart, buffer, sizeof(buffer), NULL);
    //sem_post(&sem);
}

/*
 *  ======== logThread ========
 */
void *logThread(void *arg0)
{
    char input;
    const char echoPrompt[] = "Echoing characters:\r\n";
    UART2_Params uartParams;
    int32_t semStatus;
    uint32_t status = UART2_STATUS_SUCCESS;

    /* Call driver init functions */
    //GPIO_init();

    /* Configure the LED pin */
    //GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Create semaphore */
    semStatus = sem_init(&sem, 0, 0);

    if (semStatus != 0)
    {
        /* Error creating semaphore */
        while (1) {}
    }

    /* Create a UART in CALLBACK read mode */
    UART2_Params_init(&uartParams);
    uartParams.readMode     = UART2_Mode_CALLBACK;
    uartParams.readCallback = callbackFxn;
    uartParams.baudRate     = 115200;

    uart = UART2_open(CONFIG_UART2_0, &uartParams);

    if (uart == NULL)
    {
        /* UART2_open() failed */
        while (1) {}
    }

    /* Turn on user LED to indicate successful initialization */
    //GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Pass NULL for bytesWritten since it's not used in this example */
    UART2_write(uart, echoPrompt, sizeof(echoPrompt), NULL);
}

void user_print(const char*f,...)
{
#ifdef LOG_ENALBE
        va_list args;           
        char buffer[64] = {0};  
        
        va_start(args,f);        
        vsnprintf(buffer,sizeof(buffer)-1,f,args);        
        va_end(args);
        
        int len=strlen(buffer);
        if(uart)
        {        
                UART2_write(uart,buffer,len,NULL);
        }
#endif
}

void uart2_printf(char *buffer)
{
#ifdef LOG_ENALBE
        int len=strlen(buffer);
        if(uart)
        {
                UART2_write(uart,buffer,len,NULL);
        }
#endif
}

void arry_printf(char *buf,int len)
{
#ifdef LOG_ENALBE
        int i=0;
        char c;
        for(i=0;i<len;i++)
        {
                c=buf[i]>>4;
                c=c>9?c+55:c+48;
                UART2_write(uart,&c,1,NULL);
                c=buf[i]&0x0f;
                c=c>9?c+55:c+48;
                UART2_write(uart,&c,1,NULL);
                c=' ';
                UART2_write(uart,&c,1,NULL);
        }
        c='\n';
        if(uart)
        {
                UART2_write(uart,&c,1,NULL);
        }
#endif
}

void *demo_print(void *arg0)
{
    while (1) {
        uart2_printf("hee\r\n");
        sleep(1);
    }
    
}
