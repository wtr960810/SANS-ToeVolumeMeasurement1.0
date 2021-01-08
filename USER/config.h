#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "sys.h"
#include "exdata_process.h"

#define  Ins_debug   0xfa  //����ָ��
#define  Ins_pass    0xe0  //����ָ��
#define  Ins_update  0xee  //�ϴ�����ָ��
#define  Ins_upsta   0xea  //�ϴ�״ָ̬��
#define  Ins_start   0x01  //��ʼָ��
#define  Ins_history 0xeb  //�ϴ���ʷ����
#define  mac_id      0x01  //��ַλ
#define  debug_flag  1

#define  AN          1      //0.����   1.Ӣ��

typedef struct _CONFIG_MSG
{
  uint8_t op[4];//header: FIND;SETT;FACT;FIRM...
	uint8_t mac[6];//MAC��ַ
	char device_id[16];//�豸ID
	uint8_t state;//���״̬
  /****************************************************************************************/
  /********** ONLY BELOW PARAMS INCLUDED IN CRC16 CACULATION AND STORED IN FLASH **********/
  uint8_t sw_ver[3];
	
  char device_type[16];  //�豸���� W5500S2E ���ɸ���
  char device_name[16];  //�豸����
  //char username[16];   //web config username
  char pwd[16];        //device password web and at 
	char temp_range[2]; // SET temp_range up and down
  
  uint16_t http_port;    //http server port numberdefault: 80
  uint32_t fw_len;      //received firmware length from http or firmware server
  uint32_t fw_checksum; //calculated checksum of received firmware
	uint8_t	echo_flag;		//���Ա�־λ	0�����رջ��ԣ� 1�����򿪻���  
	uint8_t	bios_flag;	//==1 ����netbios����

 //crc16	
  uint8_t start_mode;    //��������ģʽ 0 AT����ģʽ 1 ����ģʽ
  uint16_t crc16;
	uint8_t userinitflag;
	uint8_t countflag;
	uint8_t timerflag;
	uint8_t TIME1_COUNT;
	uint8_t countty;
	uint8_t count_timer3_flag;
	uint8_t ADC_count;
	uint8_t ads1232_flag;
	uint8_t TIM3_tft_count;
	//IP	
}CONFIG_MSG;

extern uint8_t senddate[h_buff_max/2];                                   //��λ����������
extern uint8_t senddate_size;                                  //��λ����������

extern uint8_t BEN[2];                            //��λ������ͷ
extern uint8_t OVER[2];														 //��λ������β
extern int test_vel1;


extern CONFIG_MSG  ConfigMsg;
#endif
