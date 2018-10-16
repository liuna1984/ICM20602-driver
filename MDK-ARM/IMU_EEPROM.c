#include "dvc_AT24C01.h"
#include "IMU_EEPROM.h"
/* 
 * ������: write_byte(uint8_t* pdata,uint8_t len, uint16_t WriteAddress)
 * ����  : д��1���ֽ����� 
 * ����  : pdata : Ҫд�����ݻ�����ָ��
           len : ��д�볤��  
           WriteAddress : д���ַ
                     
 * ���  : ��
                     
 * ˵��  : ��ҳд��1������
 */
 void write_byte(uint8_t* pdata,uint8_t len, uint16_t WriteAddress)
 {
	 I2C_PageWrite(pdata,len, WriteAddress,0xA0);
 }
 /* 
 * ������: void write_uint32(uint32_t* pdata,uint8_t len, uint16_t WriteAddress)
 * ����  : д��1������������ 
 * ����  : pdata : Ҫд�����ݻ�����ָ��
           len : ��д�볤��  
           WriteAddress : д���ַ
                     
 * ���  : ��
                     
 * ˵��  : ��ҳд��1������
 */
  void write_uint32(uint32_t* pdata,uint8_t len, uint16_t WriteAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_PageWrite(pf,len*4, WriteAddress,0xA0);
 }
  /* 
 * ������: void write_float(uint32_t* float,uint8_t len, uint16_t WriteAddress)
 * ����  : д��1������������ 
 * ����  : pdata : Ҫд�����ݻ�����ָ��
           len : ��д�볤��  
           WriteAddress : д���ַ
                     
 * ���  : ��
                     
 * ˵��  : ��ҳд��1������
 */
  void write_float(float* pdata,uint8_t len, uint16_t WriteAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_PageWrite(pf,len*4, WriteAddress,0xA0);
 }
  /* 
 * ������: write_double(double* pdata,uint8_t len, uint16_t WriteAddress)
 * ����  : д��1��˫�������� 
 * ����  : pdata : Ҫд�����ݻ�����ָ��
           len : ��д�볤��  
           WriteAddress : д���ַ
                     
 * ���  : ��
                     
 * ˵��  : ��ҳд��1������
 */
   void write_double(double* pdata,uint8_t len, uint16_t WriteAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_PageWrite(pf,len*8, WriteAddress,0xA0);
 }
 /* 
 * ������: read_byte(uint8_t* pdata,uint8_t len, uint16_t ReadAddress)
 * ����  : ��ȡ1���ֽ����� 
 * ����  : pdata : Ҫ��ȡ���ݻ�����ָ��
           len : ����ȡ�ĳ���  
           ReadAddress : ��ȡ��ַ
                     
 * ���  : ��
                     
 * ˵��  : ��
 */
 void read_byte(uint8_t* pdata,uint8_t len, uint16_t ReadAddress)
 {
	 I2C_ReadByte(pdata,len,ReadAddress,0xA0);
 }
 /* 
 * ������: void read_uint32(uint32_t* pdata,uint8_t len, uint16_t ReadAddress)
 * ����  : ��ȡ1������������ 
 * ����  : pdata : Ҫ��ȡ���ݻ�����ָ��
           len : ����ȡ�ĳ���  
           ReadAddress : ��ȡ��ַ
                     
 * ���  : ��
                     
 * ˵��  : ��
 */
  void read_uint32(uint32_t* pdata,uint8_t len, uint16_t ReadAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_ReadByte(pf,len*4,ReadAddress,0xA0);
 }
 /* 
 * ������: void read_float(float* pdata,uint8_t len, uint16_t ReadAddress)
 * ����  : ��ȡ1������������ 
 * ����  : pdata : Ҫ��ȡ���ݻ�����ָ��
           len : ����ȡ�ĳ���  
           ReadAddress : ��ȡ��ַ
                     
 * ���  : ��
                     
 * ˵��  : ��
 */
  void read_float(float* pdata,uint8_t len, uint16_t ReadAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_ReadByte(pf,len*4,ReadAddress,0xA0);
 }
 /* 
 * ������: read_double(double* pdata,uint8_t len, uint16_t ReadAddress)
 * ����  : ��ȡ˫�������� 
 * ����  : pdata : Ҫ��ȡ���ݻ�����ָ��
           len : ����ȡ�ĳ���  
           ReadAddress : ��ȡ��ַ
                     
 * ���  : ��
                     
 * ˵��  : ��
 */
   void read_double(double* pdata,uint8_t len, uint16_t ReadAddress)
 {
	uint8_t *pf;
	pf=(uint8_t *)pdata;
    I2C_ReadByte(pf,len*8, ReadAddress,0xA0);
 }