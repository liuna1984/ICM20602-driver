#include "dvc_AT24C01.h"
#define TRUE 1
#define FALSE 0

     
//extern void HAL_Delay(__IO uint32_t nTime);
     
/* 
 * ������: SDA_OUT(void)
 * ����  : ����SDA����Ϊ�������
 * ����  : ��
 * ���  : ��
 * ˵��  : ��
 */
void SDA_OUT(void)
{   
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
}
/* 
 * ������: SDA_IN(void)
 * ����  : ����SDA����Ϊ��������
 * ����  : ��
 * ���  : ��
 * ˵��  : ��
 */
void SDA_IN(void)
{   
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  
}
     
/* 
 * ������: void I2C_delay(void)
 * ����  : ������ʱ
 * ����  : ��
 * ���  : ��
 * ˵��  : �ڲ������i�����Ż��ٶȣ���������͵�5����д��
 */
static void I2C_delay(void)
{   
    uint8_t i=100; 
    while(i) 
    { 
        i--; 
    } 
}
     
/* 
 * ������: uint8_t I2C_Start(void)
 * ����  : ��ʼ�ź�
 * ����  : ��
 * ���  : TRUE : �ɹ�
                     FALSE : ʧ��
 * ˵��  : 
 */
static uint8_t I2C_Start(void)
{
    SDA_OUT();
	SDA_H;
    SCL_H;
    I2C_delay();
//	SDA_IN();
//    if(!SDA_read)
//        return FALSE;   //SDA��Ϊ�͵�ƽ������æ,�˳�
//  SDA_OUT();
    SDA_L;
    I2C_delay();
//  SDA_IN();
//    if(SDA_read) 
//        return FALSE;   //SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
//    SDA_L;
	SCL_L;
    I2C_delay();
    return TRUE;
}
/* 
 * ������: static void I2C_Stop(void)
 * ����  : ��ֹ�ź�
 * ����  : ��
 * ���  : ��
 * ˵��  : 
 */
static void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
	SDA_OUT();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}
/* 
 * ������: static void I2C_Ack(void)
 * ����  : Ӧ���ź�
 * ����  : ��
 * ���  : ��
 * ˵��  : 
 */
static void I2C_Ack(void)
{   
    SCL_L;
    I2C_delay();
	SDA_OUT();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}
/* 
 * ������: void I2C_NoAck(void)
 * ����  : ��Ӧ���ź�
 * ����  : ��
 * ���  : ��
 * ˵��  : 
 */
static void I2C_NoAck(void)
{   
	SCL_L;
    I2C_delay();
	SDA_OUT();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}
/* 
 * ������: uint8_t I2C_Start(void)
 * ����  : �ȴ�Ӧ���ź�
 * ����  : ��
 * ���  : TRUE : ��Ӧ��
                     FALSE : ��Ӧ��
 * ˵��  : 
 */
static uint8_t I2C_WaitAck(void)   
{
  //  SDA_OUT();
	uint8_t uscount=0;
	SCL_L;
    I2C_delay();
    SDA_H;          
    I2C_delay();
	SDA_IN();
    SCL_H;
    I2C_delay();

//    if(SDA_read)
//    {
//        SCL_L;
//        return FALSE;
//    }
	while(SDA_read)
	{
		uscount++;
		if(uscount>250)
		{
	       SCL_L;
           return FALSE;
		}
	}
    SCL_L;
//	SDA_OUT();
    return TRUE;
}
/* 
 * ������: static void I2C_SendByte(uint8_t SendByte) 
 * ����  : ����һ���ֽ�
 * ����  : SendByte : �ֽ�����
 * ���  : ��
 * ˵��  : ���ݴӸ�λ����λ
 */
static void I2C_SendByte(uint8_t SendByte) 
{
    uint8_t i=8;
	SDA_OUT();
    while(i--)
    {
        SCL_L;
        I2C_delay();
        if(SendByte&0x80)
            SDA_H;  
        else
            SDA_L;   
        SendByte<<=1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}
/* 
 * ������: static uint8_t I2C_ReceiveByte(void) 
 * ����  : ��ȡһ���ֽ�
 * ����  : �� 
 * ���  : �ֽ�����
 * ˵��  : ReceiveByte : ���ݴӸ�λ����λ
 */
static uint8_t I2C_ReceiveByte(void)  
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
//    SDA_OUT();     
//    SDA_H;  
    SDA_IN();	
    while(i--)
    {
        ReceiveByte<<=1;      
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();    
        if(SDA_read)
        {
            ReceiveByte|=0x01;
        }
    }
    SCL_L;
    return ReceiveByte;
}
     
/* 
 * ������: uint8_t I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress)
 * ����  : д��1�ֽ�����  
 * ����  : SendByte : Ҫд������
                     WriteAddress : д���ַ
                     DeviceAddress : ������ַ
 * ���  : TRUE : �ɹ�
                     FALSE : ʧ��
 * ˵��  : 
 */
uint8_t I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress)
{       
    if(!I2C_Start())
            return FALSE;
  //  I2C_SendByte(((WriteAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ
    I2C_SendByte(DeviceAddress & 0xFE);//��������д��ַ 	
    if(!I2C_WaitAck())
        {
            I2C_Stop(); 
            return FALSE;
        }
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   //���õ���ʼ��ַ      
    I2C_WaitAck();  
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
         
    HAL_Delay(10);//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
         
        return TRUE;
}
/* 
 * ������: uint8_t I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress)
 * ����  : д��1������ 
 * ����  : pBuffer : Ҫд�����ݻ�����ָ��
           length : ��д�볤��  
                     WriteAddress : д���ַ
                     DeviceAddress : ������ַ
 * ���  : TRUE : �ɹ�
                     FALSE : ʧ��
 * ˵��  : ע�ⲻ�ܿ�ҳд
 */
uint8_t I2C_BufferWrite(uint8_t* pBuffer, uint8_t length, uint16_t WriteAddress, uint8_t DeviceAddress)
{
    if(!I2C_Start())
            return FALSE;
    //I2C_SendByte(((WriteAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ
    I2C_SendByte(DeviceAddress & 0xFE);//��������д��ַ
    if(!I2C_WaitAck())
        {
            I2C_Stop(); 
            return FALSE;
        }
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   //���õ���ʼ��ַ      
        I2C_WaitAck();  
        while(length--)
        {
            I2C_SendByte(* pBuffer);
            I2C_WaitAck();
            pBuffer++;
        }
        I2C_Stop();
             
        HAL_Delay(10);//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
             
        return TRUE;
}
     
/* 
 * ������: uint8_t I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress)
 * ����  : д��1������ 
 * ����  : pBuffer : Ҫд�����ݻ�����ָ��
           length : ��д�볤��  
                     WriteAddress : д���ַ
                     DeviceAddress : ������ַ
 * ���  : TRUE : �ɹ�
                     FALSE : ʧ��
 * ˵��  : ��ҳд��1������
 */
void I2C_PageWrite(  uint8_t* pBuffer, uint8_t length, uint16_t WriteAddress, uint8_t DeviceAddress)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
    Addr  = WriteAddress % I2C_PageSize;      //д���ַ�ǿ�ʼҳ�ĵڼ�λ
    count = I2C_PageSize - Addr;                        //�ڿ�ʼҳҪд��ĸ���
    NumOfPage   =  length / I2C_PageSize;     //Ҫд���ҳ��
    NumOfSingle =  length % I2C_PageSize;     //����һҳ�ĸ���
         
    if(Addr == 0)         //д���ַ��ҳ�Ŀ�ʼ 
    {
        if(NumOfPage == 0)  //����С��һҳ 
        {
            I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //д����һҳ������
        }
        else                    //���ݴ��ڵ���һҳ  
        {
            while(NumOfPage)//Ҫд���ҳ��
            {
                I2C_BufferWrite(pBuffer,I2C_PageSize,WriteAddress,DeviceAddress);//дһҳ������
                WriteAddress +=  I2C_PageSize;
                pBuffer      +=  I2C_PageSize;
                NumOfPage--;
                HAL_Delay(10);
            }
            if(NumOfSingle!=0)//ʣ������С��һҳ
            {
                I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //д����һҳ������
                HAL_Delay(10);
            }
        }
    }
         
    else                  //д���ַ����ҳ�Ŀ�ʼ 
    {
        //if(NumOfPage== 0)   //����С��һҳ 
		if(NumOfPage==0)	//byliun
        {
            if(NumOfSingle<=count)
			    I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //д����һҳ������
			else
			{
				I2C_BufferWrite(pBuffer,count,WriteAddress,DeviceAddress);      //����ʼ�Ŀռ�д��һҳ
				WriteAddress += count;
				pBuffer      += count;
				I2C_BufferWrite(pBuffer,(NumOfSingle-count),WriteAddress,DeviceAddress);      //����ʼ�Ŀռ�д��һҳ
			}
        }
        else                //���ݴ��ڵ���һҳ
        {
            length       -= count;
            NumOfPage     = length / I2C_PageSize;  //���¼���Ҫд���ҳ��
            NumOfSingle   = length % I2C_PageSize;  //���¼��㲻��һҳ�ĸ���   
                 
            if(count != 0)
            {  
                I2C_BufferWrite(pBuffer,count,WriteAddress,DeviceAddress);      //����ʼ�Ŀռ�д��һҳ
                WriteAddress += count;
                pBuffer      += count;
            } 
			while(NumOfPage--)  //Ҫд���ҳ��
			{
				I2C_BufferWrite(pBuffer,I2C_PageSize,WriteAddress,DeviceAddress);//дһҳ������
				WriteAddress +=  I2C_PageSize;
				pBuffer      +=  I2C_PageSize; 
			}
			if(NumOfSingle != 0)//ʣ������С��һҳ
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //д����һҳ������ 
			}
		 
        }
    } 
}
     
/* 
 * ������: uint8_t I2C_ReadByte(uint8_t* pBuffer,   uint8_t length,     uint16_t ReadAddress,  uint8_t DeviceAddress)
 * ����  : ����1������
 * ����  : pBuffer : Ҫ��ȡ���ݻ�����ָ��
           length : ����ȡ����  
                     WriteAddress : ��ȡ��ַ
                     DeviceAddress : ������ַ
 * ���  : TRUE : �ɹ�
                     FALSE : ʧ��
 * ˵��  : ��ҳд��1������
 */
uint8_t I2C_ReadByte(uint8_t* pBuffer,   uint8_t length,     uint16_t ReadAddress,  uint8_t DeviceAddress)
{       
    if(!I2C_Start())return FALSE;
  //  I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ
    I2C_SendByte(DeviceAddress & 0xFE);//��������д��ַ	
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));   //���õ���ʼ��ַ      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(DeviceAddress | 0x01);
    I2C_WaitAck();
    while(length)
    {
        *pBuffer = I2C_ReceiveByte();
        if(length == 1)I2C_NoAck();
        else I2C_Ack(); 
        pBuffer++;
        length--;
    }
    I2C_Stop();
    return TRUE;
}
     
/* 
 * ������: void I2C_Test(void)
 * ����  : ���Ժ���
 * ����  : �� 
 * ���  : ��
 * ˵��  : ��
 */
void I2C_Test(void)
{
     
    uint8_t I2cVal_Write = 0xFE;
    uint8_t I2cVal_Read = 0x00;
         
    printf("Start IIC test\r\n");
    printf("The Simulation_IIC has sended data:%d \r\n", I2cVal_Write);
    I2C_WriteByte(I2cVal_Write, 0X01, 0xa0);
         
     
    I2C_ReadByte(&I2cVal_Read, 1, 0x01 ,0xa0);
    printf("The Simulation_IIC has Received data:%d \r\n", I2cVal_Read);
         
    if(I2cVal_Read == I2cVal_Write)
    {
        printf("The Simulation IIC is successful!\r\n");
    }
    else
    {
        printf("The Simulation IIC is failed!\r\n");
    }
     
}