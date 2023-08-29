/*
 * uart.c
 *
 *  Created on: Aug 29, 2023
 *      Author: domis
 */

#include "uart.h"
#include "main.h"

#include <stm32f7xx_hal.h>
#include <stm32f7xx_hal_gpio.h>




static void uart2InitGPIO()
{
	//GPIO Init
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//PC10: UART2_TX
	//PC11: UART2_TX
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

static void uart4InitGPIO()
{
	//GPIO Init
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//PC10: UART4_TX
	//PC11: UART4_TX
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void uartInitPeriph(USART_TypeDef *UARTTypeDef, uint32_t Baudrate, DMA_HandleTypeDef *DmaTx, DMA_HandleTypeDef *DmaRx)
{
	//UART Init
	HAL_StatusTypeDef status;
	UART_HandleTypeDef uartInitStruct;

	uartInitStruct.Instance = UARTTypeDef;
	uartInitStruct.Init.BaudRate = Baudrate;
	uartInitStruct.Init.WordLength = UART_WORDLENGTH_8B;
	uartInitStruct.Init.StopBits = UART_STOPBITS_1;
	uartInitStruct.Init.Parity = UART_PARITY_NONE;
	uartInitStruct.Init.Mode = UART_MODE_TX_RX;
	uartInitStruct.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartInitStruct.Init.OverSampling = UART_OVERSAMPLING_16;
	uartInitStruct.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uartInitStruct.hdmarx = DmaRx;
	uartInitStruct.hdmatx = DmaTx;
	uartInitStruct.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	status = HAL_UART_Init(&uartInitStruct);
	assert_param(status == HAL_OK);
}


//==================== PUBLIC FUNCTIONS =======================


void uart2Init()
{
	uart2InitGPIO();
	__USART2_CLK_ENABLE();

	uartInitPeriph(USART2, 9600, NULL, NULL);
}

void uart4Init()
{
	uart4InitGPIO();
	__UART4_CLK_ENABLE();

	uartInitPeriph(UART4, 9600, NULL, NULL);
}
