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
NVIC_InitTypeDef			NVIC_InitStructure;

uint8_t data =10;
float value_adc1 = 0,sum_adc1=0, adc_tb=0;

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void UART_Configuration (void);
void ADC_Configuration(void);
int main(void)
{
	GPIO_Configuration();
	UART_Configuration();
	ADC_Configuration();
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
				sum_adc1 =0;
				// xuat gia tri trung binh thong qua UART len may tinh
				printf("Gia tri ADC là: %4.3f\n",adc_tb);
				GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(0));
				Delay_ms(300);

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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		/*cau hinh chan Input cua bo ADC1 la chan PA0*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		/*cau hinh ADC1*/
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
	
		/* Cau hinh chanel, rank, thoi gian lay mau */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 0, ADC_SampleTime_55Cycles5);
		/* Cau hinh Analog watchdog */
		ADC_AnalogWatchdogThresholdsConfig(ADC1,3000, 2000);
		ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_0);
		ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);
		ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
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
		/*Cau hinh ngat cho bo ADC*/
		NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
