#include "stm32f10x.h"

#include "stdio.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
  	/* e.g. write a character to the LCD */
	//lcd_Data_Write((u8)ch);
	USART_SendData(USART2,(u8)ch);
	
	/*Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET)
	{}

  	return ch;
}

/*Khoi tao bien cau hinh*/
GPIO_InitTypeDef			GPIO_InitStructure;
USART_InitTypeDef			UART_InitStructure;
ADC_InitTypeDef 			ADC_InitStructure;
RCC_ClocksTypeDef 				RCC_ClockFreq;

uint8_t data =10;
float value_adc1 = 0,sum_adc1=0, adc_tb=0,tempr=0;
uint32_t clock_source=0;

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void UART_Configuration (void);
void ADC_Configuration(void);
int main(void)
{
	GPIO_Configuration();
	UART_Configuration();
	ADC_Configuration();
	//RCC_GetClocksFreq(&RCC_ClockFreq);
	//clock_source = RCC_ClockFreq.PCLK2_Frequency; // lay gia tri clock source
  while (1)
  {
			// doc 10 lan gia tri ADC roi lay trung binh ket qua
				for(int b=0;b<10;b++)
					{
							value_adc1 = ADC_GetConversionValue(ADC1);
							sum_adc1 = sum_adc1 + value_adc1;
							Delay_ms(1);
					}
				adc_tb = sum_adc1/10;
				tempr = (1.43 - (3.3 *adc_tb/ 4096.0 )) *1000/ 4.3 + 25.0;
				sum_adc1 =0;
				// xuat gia tri trung binh thong qua UART len may tinh
					printf("T=%4.3foC, TB_SUM %f\n",tempr,adc_tb);
				Delay_ms(1000);

  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void UART_Configuration (void)
	{
		/*Cap clock cho USART và port su dung*/
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		
			/* Cau Tx mode AF_PP, Rx mode FLOATING  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		/*Cau hinh USART*/
			UART_InitStructure.USART_BaudRate = 115200;
			UART_InitStructure.USART_WordLength = USART_WordLength_8b;
			UART_InitStructure.USART_StopBits = USART_StopBits_1;
			UART_InitStructure.USART_Parity = USART_Parity_No;
			UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &UART_InitStructure);
				
			/* Cho phep UART hoat dong */
			USART_Cmd(USART2, ENABLE);
	
	}
void ADC_Configuration(void)
	{
		/*cap clock cho chan GPIO va bo ADC1*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
		
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
		
		/*cau hinh ADC1*/
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
		
			/* Cho phep bo ADC1 hoa dong */
		ADC_Cmd(ADC1, ENABLE);   
		/* cho phep cam bien nhiet hoat dong */
		ADC_TempSensorVrefintCmd(ENABLE);
		/* Reset thanh ghi cablib  */   
		ADC_ResetCalibration(ADC1);
		/* Cho thanh ghi cablib reset xong */
		while(ADC_GetResetCalibrationStatus(ADC1));
		/* Khoi dong bo ADC */
		ADC_StartCalibration(ADC1);	
		/* Cho trang thai cablib duoc bat */
		while(ADC_GetCalibrationStatus(ADC1));
		/* Bat dau chuyen doi ADC */ 
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);

		/* Cau hinh chanel, rank, thoi gian lay mau */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
	}
