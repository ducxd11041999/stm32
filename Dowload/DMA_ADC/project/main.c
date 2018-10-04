#include "stm32f10x.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

__IO uint16_t ADC_value=0;

/*Khoi tao bien cau hinh*/
GPIO_InitTypeDef					GPIO_InitStructure;
ADC_InitTypeDef           ADC_InitStructure;
DMA_InitTypeDef           DMA_InitStructure;

void RCC_Configuration(void);
void Delay_ms(uint16_t time);
void ADC_Configuration(void);
void DMA_Configuration(void);

int main(void)
{
	RCC_Configuration();
	DMA_Configuration();
	ADC_Configuration();
	
  while (1)
  {

  }
}
void RCC_Configuration(void)
	{
			/* ADCCLK = PCLK2/8 */
			RCC_ADCCLKConfig(RCC_PCLK2_Div8);   

			/* Enable peripheral clocks ------------------------------------------------*/
			/* Enable DMA1 clock */
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
			/* Enable GPIOA, GPIOC, ADC1 and TIM1 Periph clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1 , ENABLE);
	}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}

void ADC_Configuration(void)
	{
		/*cap clock cho chan GPIO va bo ADC1*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		/*cau hinh chan Input cua bo ADC1 la chan PA0*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		/*cau hinh ADC1*/
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
	
		/* Cau hinh chanel, rank, thoi gian lay mau */
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

		/* Enable ADC1 DMA */
			ADC_DMACmd(ADC1, ENABLE);
	
			/* Cho phep bo ADC1 hoa dong */
		ADC_Cmd(ADC1, ENABLE);   
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
	}

void DMA_Configuration(void)
	{	
		/* cau hinh DMA1 channel 1*/
		DMA_DeInit(DMA1_Channel1);
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_value;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = 1;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		/* cho phep DMA1 channel 1 hoat dong */
		DMA_Cmd(DMA1_Channel1, ENABLE);
		
	}
	