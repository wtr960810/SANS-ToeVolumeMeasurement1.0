#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "sys.h"
#include "exdata_process.h"

#define  Ins_debug   0xfa  //调试指令
#define  Ins_pass    0xe0  //密码指令
#define  Ins_update  0xee  //上传数据指令
#define  Ins_upsta   0xea  //上传状态指令
#define  Ins_start   0x01  //开始指令
#define  Ins_history 0xeb  //上传历史数据
#define  mac_id      0x01  //地址位
#define  debug_flag  1

#define  AN          1      //0.中文   1.英文

typedef struct _CONFIG_MSG
{
  uint8_t op[4];//header: FIND;SETT;FACT;FIRM...
	uint8_t mac[6];//MAC地址
	char device_id[16];//设备ID
	uint8_t state;//软件状态
  /****************************************************************************************/
  /********** ONLY BELOW PARAMS INCLUDED IN CRC16 CACULATION AND STORED IN FLASH **********/
  uint8_t sw_ver[3];
	
  char device_type[16];  //设备类型 W5500S2E 不可更改
  char device_name[16];  //设备名称
  //char username[16];   //web config username
  char pwd[16];        //device password web and at 
	char temp_range[2]; // SET temp_range up and down
  
  uint16_t http_port;    //http server port numberdefault: 80
  uint32_t fw_len;      //received firmware length from http or firmware server
  uint32_t fw_checksum; //calculated checksum of received firmware
	uint8_t	echo_flag;		//回显标志位	0——关闭回显， 1——打开回显  
	uint8_t	bios_flag;	//==1 开启netbios服务

 //crc16	
  uint8_t start_mode;    //开机工作模式 0 AT命令模式 1 数据模式
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

extern uint8_t senddate[h_buff_max/2];                                   //上位机交互缓存
extern uint8_t senddate_size;                                  //上位机交互长度

extern uint8_t BEN[2];                            //上位机数据头
extern uint8_t OVER[2];														 //上位机数据尾
extern int test_vel1;


extern CONFIG_MSG  ConfigMsg;
#endif
