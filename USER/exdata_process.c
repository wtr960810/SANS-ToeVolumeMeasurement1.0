#include "key.h"
#include "exdata_process.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"
#include "hw_config.h"
#include "ulitity.h"
#include "string.h"
#include "AD1232.h"
#include "config.h"
#include "led.h"
#include "myiic.h"
#include "24cxx.h"
#include "dht11.h"
#include "w25qxx.h"
#include "ADC_BAT.h"
#include "usart3.h"
#include "AD1232.h"
#include <math.h>
#include <stdlib.h>
#include "dht11.h"
#include "crc.h"
#include "language.h"
#include "globalhead.h"

/*****************Define Flags*******************/
uint8  cmd_buffer[CMD_MAX_SIZE];                                   
uint8_t bReadInitFlag = INCOMPLETE;
uint8_t bReadToeFlag  = INCOMPLETE;
uint8_t bExNameFlag   = INCOMPLETE;
uint8_t DataOverflowFlag   = FALSE;
uint8_t bPedalKeyStatus    = FALSE;
uint8_t bPedalButtonStatus = FALSE;
uint8_t bExStatusFlag = FINISH;
uint8_t bInitFlag = TRUE;
uint8_t bDelete = INCOMPLETE;  
uint8_t KEY_FLAG = ON;
uint8_t iLanguageType = CHINESE; 
uint8_t rtc_timer[7];								               
uint8_t ExNameBuff[64];
uint8_t ExName[64];                                           
uint8_t timer_buff[64];
uint8_t name_buff[32];
uint8   ExNameSize = 0;    
u16     fExData[33];  
u8      fTHData[2]; 

uint16  current_screen_id    = 0; 
uint8_t ExNameCount          = 0;                                                       
uint8_t timerout             = 0;
uint8_t iVerifyPedalCount    = 0; 
u8 BeepStatus = 0xff;
u8 Temperature  = 0;  	    
u8 Humidity     = 0; 
u8 iExTimes     = 0;   
u32 WEIGHT_SUM  = 0;
u16 AVE     = 0;
u16 SD      = 0;
u32 fWeightInit = 0;
u32 fWeightToe  = 0;
uint8_t EX_offset;              
uint8_t EX_offsetmax;           
uint8_t EX_offsetNmax;  
uint16_t EX_SUM  = 0; 
uint8_t iPedalCountButton = 0;
uint8_t iPedalCountKey    = 1;
uint8_t iSequence = 0;                                 
uint16_t iDisplayExNum = 0;
static int32 Progress_Value = 0;  
long long SD_SUM  = 0;
int timing = 0;


extern uint8_t iReceiveFlag;

extern LanguageType_t language;
extern Prompt_t prompt;
extern char WarnningPrompt[LanguageTypeMax][PromptNumMax][128];

void LCD_HANDLE()
{
  if(bInitFlag == TRUE) 
	{
	  InitConfig();
	  bInitFlag = FALSE;
	}
	
  qsize  size = 0; 
	size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);                      
	if(size>0)                                          
	{                                                                           
		 ProcessMessage((PCTRL_MSG)cmd_buffer, size);
	}

	if(timerout>=5)         
	{
		 UpdateUI();
	}
	
  return;
}


void ProcessMessage( PCTRL_MSG msg, uint16 size )
{
    uint8 cmd_type = msg->cmd_type;
    uint8 ctrl_msg = msg->ctrl_msg;
    uint8 control_type = msg->control_type;
    uint16 screen_id = PTR2U16(&msg->screen_id);
    uint16 control_id = PTR2U16(&msg->control_id);
    uint32 value = PTR2U32(msg->param);
		uint32 Dsize = size-13;

    switch(cmd_type)
   {	
	  case GET_lag:
		    iLanguageType = ctrl_msg;
	      break;
    case NOTIFY_TOUCH_PRESS:
    case NOTIFY_TOUCH_RELEASE:
        NotifyTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4));
        break;
    case NOTIFY_WRITE_FLASH_OK:
        NotifyWriteFlash(1);
        break;
    case NOTIFY_WRITE_FLASH_FAILD:
        NotifyWriteFlash(0);
        break;
    case NOTIFY_READ_FLASH_OK:
        NotifyReadFlash(1,cmd_buffer+2,size-6);
        break;
    case NOTIFY_READ_FLASH_FAILD:
        NotifyReadFlash(0,0,0);
        break;
    case NOTIFY_READ_RTC:
        NotifyReadRTC(cmd_buffer[2],cmd_buffer[3],cmd_buffer[4],cmd_buffer[5],cmd_buffer[6],cmd_buffer[7],cmd_buffer[8]);
        break;
    case NOTIFY_CONTROL:
        {
            if(ctrl_msg==MSG_GET_CURRENT_SCREEN)
            {
                NotifyScreen(screen_id);
            }
            else
            {
                switch(control_type)
                {
                case kCtrlButton:
                    NotifyButton(screen_id,control_id,msg->param[1]);
                    break;
                case kCtrlText:
                    NotifyText(screen_id,control_id,msg->param,Dsize);
                    break;
                case kCtrlProgress:
                    NotifyProgress(screen_id,control_id,value);
                    break;
                case kCtrlSlider:
                    NotifySlider(screen_id,control_id,value);
                    break;
                case kCtrlMeter:
                    NotifyMeter(screen_id,control_id,value);
                    break;
                case kCtrlMenu:
                    NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);
                    break;
                case kCtrlSelector:
                    NotifySelector(screen_id,control_id,msg->param[0]);
                    break;
                case kCtrlRTC:
                    NotifyTimer(screen_id,control_id);
                    break;
                default:
                    break;
                }
            }
            break;
        }
    case NOTIFY_HandShake:
        NOTIFYHandShake();
        break;
    default:
        break;
   }
}



void UpdateUI()
{
	  timing++;
	  if(timing>=50){iReceiveFlag = FALSE;}
	  else if(timing<50){iReceiveFlag = TRUE;}
	  if(timing>300){timing=50;}
	  UpdateGlobalData();
    if(current_screen_id == 1)                                              
    {
			if(iPedalCountButton==0)
      {
         DisplayPickupIcon();
			}
			else if(iPedalCountButton)
      {
         DisplayPutdownIcon();
			}
			GetSensorData();
      GetTempHum();
			PEDAL_KEY_DETECTION();
			CheckSensorStatus();
	  }
		timerout = 0;
}




void CheckSensorStatus()
{ 
 	 if(iReceiveFlag == TRUE)
   {
			SetControlVisiable(1,94,1);
	 }
	 else
   {
		  SetControlVisiable(1,94,0);
	 }
}




void UpdateGlobalData()
{
	if(EX_SUM > Ex_Time_Max) DataOverflowFlag = TRUE;
	else DataOverflowFlag = FALSE;
  AT24CXX_Write(2,&DataOverflowFlag,1);
}


void NotifyTouchXY(uint8 press,uint16 x,uint16 y)
{ 

}

void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length)
{

}

void NotifyWriteFlash(uint8 status)
{
   
}

void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second)
{   
	uint8_t   sec,years,months,weeks,days,hours,minutes;
	
  sec    =(0xff & (second>>4))*10 +(0xf & second);                                  
  years   =(0xff & (year>>4))*10 +(0xf & year);                                      
  months  =(0xff & (month>>4))*10 +(0xf & month);                                     
  weeks   =(0xff & (week>>4))*10 +(0xf & week);                                      
  days    =(0xff & (day>>4))*10 +(0xf & day);                                      
  hours   =(0xff & (hour>>4))*10 +(0xf & hour);                                       
  minutes =(0xff & (minute>>4))*10 +(0xf & minute);                                      
    
	rtc_timer[0]=sec;
	rtc_timer[1]=minutes;
	rtc_timer[2]=hours;
	rtc_timer[3]=weeks;
	rtc_timer[4]=days;
	rtc_timer[5]=months;
	rtc_timer[6]=years;                                            
}



void NOTIFYHandShake()
{
   SetButtonValue(3,2,1);
}

int times =0;

void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state)
{ 
/*-------------------Experimental Interface------------------*/
	  if(screen_id == 1)                                                              
    {
			/*********Delete Button********/
			if(control_id==83)                                                          
			{
				 if(iExTimes) SetControlEnable(1,89,1);
			   fExData[iExTimes] = 0;
         SetTextValue(1,45+iExTimes-1,(uchar*)"");
				 if(iExTimes > 0)
				 {
					 iExTimes--;
				 }
				 else
				 {
				   iExTimes = 0;
				 }
				 fExData[0] = iExTimes;
				 SetTextInt32(1,80,iExTimes,0,1);
         CALCULATE_AVR_SD();
			}
			
			/*********Pedal Button********/
			if(control_id==89)                                                        
			{
				if(bExStatusFlag == START) {PEDAL_BUTTON_DECTION();}
			}
			
      /*********Go Back Button********/
			if(control_id==1&&state==1)
			{
				if(bExNameFlag == FINISH && bExStatusFlag == START)
				{
					SetButtonValue(1,91,0); 					                        
					SAVE_DATA();
				}
				CLEAN_EX_INTERFACE();
		  }
			/*********Start Button********/
			if(control_id==91)                                                                                   
			{
				 times++;
				 if(times == 1)
				 {
			     if(EX_SUM >= Ex_Time_Max)
	    	   {
		         DisplayDataOverflowDialog();
						 times=0;
	     	   }
					 else
					 {
					   ReadRTC(); 
				     DHT11_Read_Data(&Temperature,&Humidity);
             SetTextValue(1,5,(uchar*)WarnningPrompt[iLanguageType][ExperimentFinish]);		 
             bExStatusFlag = START;
					 }
				   
				                                        //Press start button
				 }

				 if(times == 2)
				 { 
           SetTextValue(1,5,(uchar*)WarnningPrompt[iLanguageType][ExperimentStart]);
					 times = 0;
					 SetControlEnable(1,83,0);
					 SetControlEnable(1,89,0);
					 SetControlEnable(1,91,0);
				 }
			}
			
			/*********New Button********/
			if(control_id==93)                                                                                         
			{
				if(bExNameFlag == FINISH && bExStatusFlag == START)
				{
				 SetButtonValue(1,91,0); 					                      
			   SAVE_DATA();
				}
			  CLEAN_EX_INTERFACE();
			}
    }		
		
/*-------------------System Setting Interface------------------*/
		if(screen_id == 2)
    {
      if(control_id==10)
			{
				BeepStatus = ~BeepStatus;
				SetBeepSound(BeepStatus);
				AT24CXX_Write(31,&BeepStatus,1);
			}
		}

/*-------------------Primary History Interface------------------*/
		
    if(screen_id == 3)                                                                 
    {				
			/*********PageUp Button********/
			if(control_id==22&&state==1)                                                                                
			{
				if(EX_offset>0)
				{
					for(int i=4;i<14;i++)
					SetTextValue(3,i,(uchar*)"");
					EX_offset--;
					Display_Primary_History_Interface();
				}
			}
			/*********PageDown Button********/
			if(control_id==23&&state==1)
			{
				if(EX_offset<EX_offsetNmax-1)
				{
					for(int i=4;i<14;i++)
					SetTextValue(3,i,(uchar*)"");
					EX_offset++;
					Display_Primary_History_Interface();
				}
			}
			
			if(control_id == 15)
			{
			  EXPORT_ALL_EXDATA();
			}
			
			if(control_id == 25)
      {
			  DisplayClearDataDialog();
			}	
      
			if(control_id == 33)
			{
			  CLEAN_EXDATA();
			}
		  if(control_id == 34)
			{
			  HideClearDataDialog();
			}
			if(control_id == 41)
			{
			  HideExportAllDataDialog();
				EnableScreen3Button();
			}
			
			switch(control_id)
			{
				case 27: iSequence = 5;  break;
					
				case 28: iSequence = 4;  break;
					
				case 29: iSequence = 3;  break;
					
				case 30: iSequence = 2;  break;
					
				case 31: iSequence = 1;  break;
        
				default: break;
			}
			
			
			
    } 

/*-------------------Secondary History Interface------------------*/
	 if(screen_id == 4)
	 {
      if(control_id==104)
			{
				EXPORT_EXDATA();
			}

	    if(control_id==102)
			{
        DisplayDeleteDataDialog();//Display ClearData Dialog
			}
			
		  if(control_id==91)          //delete data
		  {
			  if(bDelete == INCOMPLETE)
			  {
          DELETE_EXDATA();
			  }
		  	bDelete = COMPLETE;
		  }
		
		
		 
	}
/*-------------------Language Setting Interface------------------*/
	 if(screen_id == 5)
	 {

      if(control_id==3)
			{
         iLanguageType = ENGLISH;
				 SetControlEnable(5,2,1);
				 SetControlEnable(5,3,0);
			}
			else
			{
			   iLanguageType = CHINESE;
				 SetControlEnable(5,2,0);
				 SetControlEnable(5,3,1);
			}
		 AT24CXX_Write(8,&iLanguageType,1);
		 
	 }	

	 
	 if(screen_id == 6)
	 { 
		  if(control_id==12)
			{ 
	 	    SetButtonValue(6,2,0);
		    SetButtonValue(6,9,0);
			}
	 }
	 
	 if(screen_id == 7)
	 { 
		  if(control_id==12)
			{ 
	 	    SetButtonValue(7,10,0);
		    SetButtonValue(7,11,0);
			}
	 }
	 
}

void EnableScreen3Button()
{
	for(int i=27;i<32;i++)
	{
	   SetControlEnable(3,i,1);
	}
	SetControlEnable(3,1,1);
	SetControlEnable(3,15,1);
	SetControlEnable(3,22,1);
	SetControlEnable(3,23,1);
	SetControlEnable(3,25,1);
}

void DisEnableScreen3Button()
{
	for(int i=27;i<32;i++)
	{
	   SetControlEnable(3,i,0);
	}
	SetControlEnable(3,1,0);
	SetControlEnable(3,15,0);
	SetControlEnable(3,22,0);
	SetControlEnable(3,23,0);
	SetControlEnable(3,25,0);
}



void NotifyScreen(uint16 screen_id)
{
    current_screen_id = screen_id;                                               
		if(screen_id == 0)                                                           
		{
			GET_Language();
			
			SetBeepSound(BeepStatus);

			uint8_t back[1]={0};
			AT24CXX_Read(7,back,1);
			SetProgressValue(2,4,back[0]);
      SetTextInt32(2,6,back[0],0,1);
			
			uint8_t sound[1]={0};
			AT24CXX_Read(10,sound,1);
			SetProgressValue(6,14,sound[0]);
			SetProgressValue(7,14,sound[0]);
		}
		
		if(screen_id == 1)                                                            
		{
			HideExNameRepeatDialog();
			HideDataOverflowDialog();
			HideExNameOverflowDialog();
			SetTextValue(1,5,(uchar*)WarnningPrompt[iLanguageType][ExperimentStart]);
			SetControlEnable(1,91,0);
			SetButtonValue(1,91,0);
			CLEAN_EX_INTERFACE();
      SetTextValue(1,92,(uchar*)WarnningPrompt[iLanguageType][CalibrateValue]);
		}
		
		if(screen_id == 2)
    {

	  }
		
		if(screen_id == 3)
    { 
      EnableScreen3Button();
			
			
			HideExportAllDataDialog();
			HideClearDataDialog();
      Display_Primary_History_Interface();
			CLEAN_SECONDARY_HISTORY_INTERFACE();
    }
		
		if(screen_id == 4)
    {
		 HideDeleteDataDialog();
		 HideExportDataDialog();
		 switch(iSequence)
		 {
				 case 5: iDisplayExNum = EX_SUM -  EX_offset*5 - 0;  break;
					
				 case 4: iDisplayExNum = EX_SUM -  EX_offset*5 - 1;  break;
					
				 case 3: iDisplayExNum = EX_SUM -  EX_offset*5 - 2;  break;
					
				 case 2: iDisplayExNum = EX_SUM -  EX_offset*5 - 3;  break;
					
				 case 1: iDisplayExNum = EX_SUM -  EX_offset*5 - 4;  break;
        
				 default: break;
		 }
		Display_Secondary_History_Interface(iDisplayExNum);
  }

	if(screen_id == 5)              																							
  {
		 if(iLanguageType == ENGLISH) 
		 { 
			 SetControlEnable(5,2,1);
			 SetControlEnable(5,3,0);
		 }
		 if(iLanguageType == CHINESE) 
		 {
			 SetControlEnable(5,2,0);
			 SetControlEnable(5,3,1);
		 }
	}

	if(screen_id == 6)              			//play vidio																				
  {
		uint8_t sound[1]={0};
		AT24CXX_Read(10,sound,1);
		SetButtonValue(6,2,0);
		SetButtonValue(6,9,0);
		SetProgressValue(6,14,sound[0]);

	}
	
	
	if(screen_id == 7)              			//play vidio																				
  {
		uint8_t sound[1]={0};
		AT24CXX_Read(10,sound,1);
		SetButtonValue(7,10,0);
		SetButtonValue(7,11,0);
		SetProgressValue(7,14,sound[0]);
	}
}

/************************************************************************/

u16 CrcRes = 0;

void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str ,uint8_t size)
{
    if(screen_id==1)                                                                 //STE EXPERIMENT NAME
    {   			
			if(control_id==93)
			{ 
			  if(bExNameFlag == COMPLETE)
				{
					SetButtonValue(1,91,0); 					                        
					SAVE_DATA();
					CLEAN_EX_INTERFACE();
					bExNameFlag = INCOMPLETE;
				} 
				ExNameSize  = size;
				if(ExNameSize>10){ScrollText(1,77,50);}
        else{ScrollText(1,77,0);}
				ExNameCount = 0;
				memset(&ExName[0],0,sizeof(ExName));
				memcpy(&ExName[0],str,ExNameSize);
				uint8_t CrcResBuff[2] = {0};
				CrcRes = GetCRC(ExName,ExNameSize);
				CrcResBuff[0] = CrcRes >> 8;
				CrcResBuff[1] = CrcRes;
				
				int resrange  = DetectNameRange();
	      int resrepeat = DetectNameRepeat(CrcResBuff);
				
				if(resrange == FALSE && resrepeat == TRUE)                //Check experiment name resrepeat
				{
           memset(&ExName[0],0,sizeof(ExName));
	         bExNameFlag = INCOMPLETE;
					 DisplayExNameOverflowDialog();
				}
				 else if(resrange == TRUE && resrepeat == FALSE)          //Check experiment name resrange
				{
           memset(&ExName[0],0,sizeof(ExName));
	         bExNameFlag = INCOMPLETE;
					 DisplayExNameRepeatDialog();
				}
				else
        {
				   memset(&ExNameBuff[0],0,sizeof(ExNameBuff));
				   memcpy(&ExNameBuff[0],str,ExNameSize);
           SetTextValue(1,77,str);
           bExNameFlag = COMPLETE;
				   SetControlEnable(1,83,1);
				   SetControlEnable(1,89,1);
				   SetControlEnable(1,91,1);
				}
			}
    }
}


uint8_t DetectNameRange()
{
	if(ExNameSize<=16){return TRUE;}
	else{return FALSE;}
}


uint8_t DetectNameRepeat(uint8_t *ptr)
{	
	int count_t=0;
	uint8_t CRCBUFF[2]={0};
	for(int i=1;i<=EX_SUM;i++)
  {
		int count_n=0;
		AT24CXX_Read(128+64+(i-1)*143,CRCBUFF,2);
	  for(int j=0;j<2;j++)
		{
		  if(ptr[j]==CRCBUFF[j]){count_n++;}
			else{break;}
		}
		if(count_n==2){return FALSE;}
    count_t++;
	}
	if(count_t==EX_SUM){return TRUE;}
}

/*********************************************************/

                                                                            
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value)           
{  
    if(screen_id == 2)
    {
        Progress_Value = value;                                  
        SetTextInt32(2,4,Progress_Value,0,1);
    }    
}   


/*******************************************************/

                                                                           
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value)
{                                                             
    uint8_t back[1] = {0};
  	uint8_t sound[1] = {0};
    if(screen_id==2&&control_id==4)                                                
    {            
        if(value<100||value>0)
        {                                                                            
            SetProgressValue(2,4,value);
            SetTextInt32(2,6,value,0,1);
            sprintf((char*)back,"%c",(255-(value*2+55)));
            SetBackLight(back[0]);
					  back[0]=value;
					  AT24CXX_Write(7,back,1);
        }
    }
		
		if((screen_id==6||screen_id==7)&&control_id==14)                                                
    {            
        if(value<100||value>0)
        {                                                                            
            SetProgressValue(6,14,value);
					  SetProgressValue(7,14,value);
            sprintf((char*)sound,"%c",(value));
					  UnlockDeviceConfig();
            SetSound(sound[0]);
					  LockDeviceConfig();
					  sound[0] = value;
					  AT24CXX_Write(10,sound,1);
        }
    }
		
}

/*******************************************************/



void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value)
{
    
}


void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state)
{
   
}


void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item)
{

}


void NotifyTimer(uint16 screen_id, uint16 control_id)
{
    if(screen_id==8&&control_id == 7)
    {
        SetBuzzer(100);
    }
}


/****************************************************/


void SAVE_DATA()
{
	uint8_t iMeasureData[143] = {0};
  iMeasureData[0] = EX_SUM >> 8;
	iMeasureData[1] = EX_SUM ;
	memcpy(&iMeasureData[2],ExName,62);
	iMeasureData[64] = CrcRes >> 8;
	iMeasureData[65] = CrcRes;
	for(int i = 0; i <= iExTimes ; i++)
	{
	  iMeasureData[66+(2*i)] = fExData[i]>>8;
	  iMeasureData[67+(2*i)] = fExData[i];
	}
	iMeasureData[129] = fExData[31]>>8;
	iMeasureData[130] = fExData[31];
	iMeasureData[131] = fExData[32]>>8;
	iMeasureData[132] = fExData[32];
	iMeasureData[133] = Temperature;
	iMeasureData[134] = Humidity;
	memcpy(&iMeasureData[135],rtc_timer,7);
	AT24CXX_Write(128+EX_SUM*143,iMeasureData,143);
	
	u16 EXSUMBUFF = EX_SUM + 1;
	iMeasureData[0] = EXSUMBUFF >> 8;
	iMeasureData[1] = EXSUMBUFF ;
	AT24CXX_Write(0,&iMeasureData[0],2);
  times = 0;
	SetTextValue(1,5,(uchar*)WarnningPrompt[iLanguageType][ExperimentStart]);
	
	if(EX_SUM >= Ex_Time_Max)
	{
		EX_SUM = Ex_Time_Max;
	}
	
	if(EX_SUM < Ex_Time_Max) 
	{
		EX_SUM ++;	
	}

}





void CLEAN_EXDATA()                               
{
  uint8_t R_date[256] = {0};
  for(int i = 0;i<EX_SUM;i++)
  {
     AT24CXX_Write(128+i*143,&R_date[0],143);
  }
  
  for(uint8_t i = 0;i < 10;i++)
  {
	  SetTextValue(3,4+i,(uchar*)"");
  }
  SetTextInt32(3,16,1,0,1);
  SetTextInt32(3,17,1,0,1);
  SetTextInt32(3,19,0,0,1);


  for(uint8_t i = 0;i < 36;i++)
  {
	  SetTextValue(3,48+i,(uchar*)"");
  }
	EX_SUM = 0;
	AT24CXX_Write(0,&R_date[0],2);
}


	
void DELETE_EXDATA()
{
	uint8_t B_SUM[143] = {0};
	if(iDisplayExNum<EX_SUM)
  {
    uint8_t B_DATA[143] = {0};
    for(int i=iDisplayExNum; i<EX_SUM; i++)
	  {
	  	AT24CXX_Read(128+i*143,B_DATA,143);
		  B_DATA[0] = iDisplayExNum>>8;
		  B_DATA[1] = iDisplayExNum;
	    AT24CXX_Write(128+(i-1)*143,&B_DATA[0],143);
      iDisplayExNum++;
	  }
  }
  AT24CXX_Write(128+(EX_SUM-1)*143,&B_SUM[0],143);
	EX_SUM--;
	B_SUM[0] = EX_SUM >> 8;
	B_SUM[1] = EX_SUM ;
	AT24CXX_Write(0,&B_SUM[0],2);
}


void PEDAL_BUTTON_DECTION()
{
				iPedalCountButton++;
	
				switch (iPedalCountButton)
				{
				  case 1:
						     if(bReadInitFlag == INCOMPLETE)
								 {
				          fWeightInit = Weight;
									bReadInitFlag = COMPLETE;
									bReadToeFlag  = INCOMPLETE;
								 }
			            SetTextValue(1,92,(uchar*)WarnningPrompt[iLanguageType][PutDownAnimals]);
					        break;
					
					case 2: 
						      iPedalCountButton = 0;
					      	if(bReadToeFlag == INCOMPLETE)
									{
						        fWeightToe = Weight;
										bReadInitFlag = INCOMPLETE;
									  bReadToeFlag  = COMPLETE;
									}
					          fExData[1+iExTimes] = abs(fWeightToe - fWeightInit);
									  float HistoryExdata = TypeTransformInt2Float(fExData[1+iExTimes]);
				            SetTextFloat(1,45+iExTimes,HistoryExdata,3,1);
									  iExTimes++;
									  fExData[0] = iExTimes;
									  CALCULATE_AVR_SD();
					          
								   	SetTextValue(1,92,(uchar*)WarnningPrompt[iLanguageType][CalibrateValue]); //prompt： Please Calibrate Value
					          
			              if(iExTimes  >= 30)
			              {
											iExTimes = 30;
					            SetControlEnable(1,89,0);
			              }
										else
										{
										  SetControlEnable(1,89,1);
										}
									  SetTextInt32(1,80,iExTimes,0,1);
									break;
									
					default:break;
				}
}





void PEDAL_KEY_DETECTION()
{
  if(((CH1==1)||(CH2==1)) && KEY_FLAG == ON)    
	{
		 KEY_FLAG = OFF;
     PEDAL_BUTTON_DECTION();
  }
	else if((CH1!=1)&&(CH2!=1))
	{
	  KEY_FLAG = ON;
	}
}



void GetSensorData()
{
		 float fweight = TypeTransformInt2Float(Weight);
	   SetTextFloat(1,88,fweight,3,1);
}


void GetTempHum()
{
      DHT11_Read_Data(&Temperature,&Humidity);
			if(Temperature!=0)
			{
				fTHData[0] = Temperature;
				fTHData[1] = Humidity;
				SetTextInt32(1,81,Temperature,0,1);
				SetTextInt32(1,82,Humidity,0,1);
			}
}

void CLEAN_PRIMARY_HISTORY_INTERFACE()
{
  for(int i=0;i<10;i++) SetTextValue(3,4+i,(uchar *)"");
}

void CLEAN_SECONDARY_HISTORY_INTERFACE()
{
	for(int i = 48; i<85 ; i++) SetTextValue(4,i,(uchar*)"");
}



void CLEAN_EX_INTERFACE()
{
  for(int i=0;i<2;i++)   fTHData[i] = 0;
	for(int i=0;i<32;i++)  fExData[i] = 0;
	for(int i=45;i<75;i++) SetTextValue(1,i,(uchar*)"");
	SetTextValue(1,77,(uchar*)"");                        
	SetTextInt32(1,80,0,0,1);                        
	SetTextInt32(1,81,0,0,1);                        
	SetTextInt32(1,82,0,0,1);
	SetTextInt32(1,86,0,0,1);
	SetTextInt32(1,87,0,0,1);
  SetTextValue(1,93,(uchar*)"");
	bExNameFlag   = INCOMPLETE;
	bReadInitFlag = INCOMPLETE;
	bReadToeFlag  = INCOMPLETE;
	bExStatusFlag = FINISH;
	iPedalCountButton = 0;
	iExTimes = 0;
	AVE      = 0;
	SD       = 0;
	SetTextValue(1,92,(uchar*)WarnningPrompt[iLanguageType][CalibrateValue]);
	SetControlEnable(1,89,1);
}





void CALCULATE_AVR_SD()
{
/*********************calculate avrage*************************/
	for(int i = 0; i < iExTimes ; i++)
	{
	  WEIGHT_SUM += fExData[i+1];
	}
  AVE = WEIGHT_SUM/(iExTimes);
	WEIGHT_SUM = 0;
	fExData[31] = AVE;
	float fAVE = TypeTransformInt2Float(fExData[31]);
	SetTextFloat(1,86,fAVE,3,1);
/**********************calculate sd************************/
	for(int i = 0; i < iExTimes ; i++)
	{
	  SD_SUM += ((abs(fExData[i+1]-AVE))*(abs(fExData[i+1]-AVE)));
	}
	SD = sqrt(SD_SUM/(iExTimes-1));
	fExData[32] = SD;
	float fSD = TypeTransformInt2Float(fExData[32]);
	SetTextFloat(1,87,fSD,3,1);
	SD_SUM = 0;
	SD  = 0;
	AVE = 0;
}



float TypeTransformInt2Float(int data)
{
	float res = 0 ;
	float Array[10] = {0};
	int i = 0;
  while(1)
  {
    Array[i] = data%10;
		data /= 10;
		if(data == 0) 
		{
			res = Array[9]*1000000 + Array[8]*100000 + Array[7]*10000 + Array[6]*1000 + Array[5]*100 + Array[4]*10 + Array[3]*1 + Array[2]/10 + Array[1]/100 + Array[0]/1000;
			return res;
		}
    i++;		
	}
}



void read_eer_date(uint8_t read_mun)												
	{
		uint8_t R_date[143]={0};
		AT24CXX_Read(128+read_mun*143,R_date,143);
		memcpy(ExName,&R_date[2],64);											   
		memcpy(rtc_timer,&R_date[135],7);                    
	}



void Display_Primary_History_Interface(void)
{
		int i=0;
		uint8_t j=0;
    for(int i = 0 ; i < 5 ; i++) SetControlEnable(3,27+i,1);	
		EX_offsetmax = EX_SUM/5;
	  SetTextInt32(3,14,Ex_Time_Max,0,1);
		if(DataOverflowFlag == FALSE)              																	
		{
			(EX_SUM%5==0) ? (EX_offsetNmax=EX_SUM/5):(EX_offsetNmax=EX_SUM/5+1);
			SetTextInt32(3,19,EX_SUM,0,1);
		}
		else                            																						
		{
			EX_offsetNmax=Ex_Time_Max/5;
			SetTextInt32(3,19,Ex_Time_Max,0,1);
		}
		
		if(EX_offsetNmax == 0) 
		SetTextInt32(3,17,1,0,1);
		else
		SetTextInt32(3,17,EX_offsetNmax,0,1);
		SetTextInt32(3,16,EX_offset+1,0,1);
		
		  if(EX_offset<=EX_offsetmax)
		  {
				if(EX_offset == EX_offsetmax) CLEAN_PRIMARY_HISTORY_INTERFACE();
				
		  	for(i=EX_SUM-EX_offset*5-1;i>=EX_SUM-(EX_offset+1)*5;i--)
			  {
				  if(i>=0)
				  {
						read_eer_date(i);
						sprintf((char*)timer_buff,"%02d-%02d-%02d  %02d :%02d :%02d",
						rtc_timer[6],rtc_timer[5],rtc_timer[4],rtc_timer[2],rtc_timer[1],rtc_timer[0]); 
						SetTextValue(3,j+9,timer_buff);
						memset(name_buff,32,0);
						memcpy(name_buff,&ExName[0],32);
						SetTextValue(3,j+4,name_buff);
						int NameBuffLen = strlen((char *)name_buff);
						if(NameBuffLen>12){ScrollText(3,j+4,50);}         //设置滚动实验名
            else{ScrollText(3,j+4,0);}
						j++;
				  }
		  	}
				
				if(j==0)
				{
					 for(int i = 0 ; i < 5 ; i++)
					 {
						 SetControlEnable(3,27+i,0);
					 }
				}
				if((0<j)&&(j<5))   
				{
					 for(int i=0 ; i < (5-j) ; i++)
					 {
						 SetControlEnable(3,31-i,0);
					 }
				}
				if(j==5)  
				{
					 for(int i = 0 ; i < 5 ; i++)
					 {
						 SetControlEnable(3,27+i,1);
					 }
				}
	    }
}



void Display_Secondary_History_Interface(int Num)
{
	 bDelete = INCOMPLETE;
	 uint8_t HistoryDataBuff[143] = {0};
	 uint8_t Temp[1]={0};
	 uint8_t RH[1]  ={0};
	 u16     ExdataBuff[33] = {0};
	
   AT24CXX_Read(128+(Num-1)*143,HistoryDataBuff,143);
	
	 SetTextInt32(4,83,Num,0,1);                        //Display ExNum 
	 SetTextInt32(4,84,EX_SUM,0,1);                     //Display ExSum 
	
	
	 memset(name_buff,32,0);
	 memcpy(name_buff,&HistoryDataBuff[2],32);
	 SetTextValue(4,78,name_buff);                                                     //Display ExName
	 int NameBuffLen = strlen((char *)name_buff);
	 if(NameBuffLen>9){ScrollText(4,78,50);}
   else{ScrollText(4,78,0);}

	 for(uint8_t i = 0 ; i < 31 ; i++)
	 {
		  ExdataBuff[i]  = HistoryDataBuff[66+(2*i)];
		  ExdataBuff[i]  = ExdataBuff[i] << 8;
		  ExdataBuff[i] += HistoryDataBuff[67+(2*i)];
	 }

	 SetTextInt32(4,80,ExdataBuff[0],0,1);	
	 for(uint8_t i = 0 ; i < ExdataBuff[0] ; i++)
	 {
		 float fExdata = TypeTransformInt2Float(ExdataBuff[1+i]);
	   SetTextFloat(4,48+i,fExdata,3,1);	
	 }
	 ExdataBuff[31]  = HistoryDataBuff[129];
	 ExdataBuff[31]  = ExdataBuff[31] << 8;
	 ExdataBuff[31] += HistoryDataBuff[130];
	 float fAVE = TypeTransformInt2Float(ExdataBuff[31]);
	 SetTextFloat(4,81,fAVE,3,1);
	 
	 ExdataBuff[32]  = HistoryDataBuff[131];
	 ExdataBuff[32]  = ExdataBuff[32] << 8;
	 ExdataBuff[32] += HistoryDataBuff[132];
	 float fSD = TypeTransformInt2Float(ExdataBuff[32]);
	 SetTextFloat(4,82,fSD,3,1);

	 memcpy(rtc_timer,&HistoryDataBuff[135],7);                                        //Display Exdate
	 sprintf((char*)timer_buff,"%02d-%02d-%02d  %02d :%02d :%02d",
	 rtc_timer[6],rtc_timer[5],rtc_timer[4],rtc_timer[2],rtc_timer[1],rtc_timer[0]);
	 SetTextValue(4,79,timer_buff);
	 
	 Temp[0] = HistoryDataBuff[133];
	 RH[0] = HistoryDataBuff[134];
	 SetTextInt32(4,16,Temp[0],0,1);
	 SetTextInt32(4,17,RH[0],0,1);
	
}



	
void SetBeepSound(uint8_t pram)
{
 if(BeepStatus == 0x1F)
 {
	 UnlockDeviceConfig();
   SetTouchPaneOption(1,0,3,0);
   LockDeviceConfig();
	 SetButtonValue(2,10,0);
 }
 else
 {
	 UnlockDeviceConfig();
   SetTouchPaneOption(1,1,3,0);
   LockDeviceConfig();
	 SetButtonValue(2,10,1);
 }	
}

char k[10] = {"a"};

void InitConfig()
{
	uint8_t load[1] = {0};
	uint8_t back[1] = {0};
  AT24CXX_Read(7,load,1);
	sprintf((char*)back,"%c",(255-(load[0]*2+55)));  
	SetBackLight(back[0]);
	
	
/**Language Init Setting**/		
 SetLanguage(iLanguageType,0);
 if(iLanguageType == CHINESE) 
 { 
   SetButtonValue(5,2,1);
   SetButtonValue(5,3,0);
 }
 if(iLanguageType == ENGLISH) 
 {
   SetButtonValue(5,2,0);
   SetButtonValue(5,3,1);
 }
}

int GETLEN(int pram)
{
  int i = 0;	
  int ipram = pram;
	
  while(ipram != 0)
  {
    ipram /= 10;
    i++;
  }
  return i;
}


unsigned char LongNameBuf[LONG_NAME_BUF_LEN];	/* 存放长文件名 */

void EXPORT_EXDATA(void)
{

	
	int count = 0;
	uint8_t LineBreak [12]   = {"\n"};
  uint8_t Title     [64]   = {0};
	uint8_t CRCBuff   [32]   = {0};
	char FristLine    [128]  = {0};
	char SecondLine   [128]  = {0};
	char ThirdLine    [128]  = {0};
	uint8_t EXPORTDATA[143]  = {0};
	AT24CXX_Read(128+(iDisplayExNum-1)*143,EXPORTDATA,143);

/**************FristLine*****************/
/*include experiment Name,experiment Date*/

	uint8_t ExName_E[32] = {0};
  memcpy(&ExName_E,&EXPORTDATA[2],32);
  uint8_t ExDate_E[32] = {0};
	memcpy(&ExDate_E,&EXPORTDATA[135],7);
	sprintf(FristLine,"%s,%s,%s,%02d/%02d/%02d-%02d:%02d:%02d%s",(uchar *)"Name:",ExName_E,(uchar *)"Date:",EXPORTDATA[141],EXPORTDATA[140],EXPORTDATA[139],EXPORTDATA[137],EXPORTDATA[136],EXPORTDATA[135],LineBreak);

/**************SecondLine*****************/
/*include experiment Animals,Average,SD,Temperature and Humidity*/

   int Animals[1] = {0};
   Animals[0]  = EXPORTDATA[66];
	 Animals[0]  = Animals[0] << 8;
	 Animals[0] += EXPORTDATA[67];
   uint16_t Average_E[1] = {0};
	 float fAverage_E[1] = {0};
   Average_E[0]  = EXPORTDATA[129];
	 Average_E[0]  = Average_E[0] << 8;
	 Average_E[0] += EXPORTDATA[130];
   uint16_t SD_E[1] = {0};
	 float fSD_E[1] = {0};
   SD_E[0]  = EXPORTDATA[131];
	 SD_E[0]  = SD_E[0] << 8;
	 SD_E[0] += EXPORTDATA[132];
   uint8_t Temperature[1] = {0};
   memcpy(&Temperature,&EXPORTDATA[133],1);
   uint8_t Humidity[1] = {0};
   memcpy(&Humidity,&EXPORTDATA[134],1);
	 fAverage_E[0] = TypeTransformInt2Float(Average_E[0]);
	 fSD_E[0] = TypeTransformInt2Float(SD_E[0]);
	 
   sprintf(SecondLine,"%s,%d,%s,%.3lf,%s,%.3lf,%s,%d,%s,%d%s",(uchar *)"Animals:",Animals[0],(uchar *)"Average:",fAverage_E[0],
	                   (uchar *)"SD:",fSD_E[0],(uchar *)"TEMP:",Temperature[0],(uchar *)"RH:",Humidity[0],LineBreak);

/**************FourthLine*****************/ 
	 
	 sprintf(ThirdLine,"%s,%s%s",(uchar *)"Times",(uchar *)"Value(mL)",LineBreak);

/**************FourthLine*****************/
/*include experiment data*/
   char DataLine[30][16]  = {{0},{0}};
   uint8_t iDataBuff[30] = {0};
	 float   fDataBuff[30] = {0};
   for(uint8_t i = 0 ; i < Animals[0] ; i++)
   {
		iDataBuff[i]  = EXPORTDATA[68+(2*i)];
		iDataBuff[i]  = iDataBuff[i] << 8;
	  iDataBuff[i] += EXPORTDATA[69+(2*i)];
   }
	 
	 for(int i=0;i<Animals[0];i++)
   {
	   fDataBuff[i] = iDataBuff[i];
		 fDataBuff[i] /= 1000;
		 sprintf(DataLine[i],"%d,%.3lf%s",i+1,fDataBuff[i],LineBreak);
	 }
	 
   uint16_t res = mInitCH376Host();  //测试链接
   res = CH376DiskMount();  //测试内存
	 if ( res != USB_INT_SUCCESS )
	 {
		 SetTextValue(4,100,(uchar *)WarnningPrompt[iLanguageType][NotDetectedUsbPrompt]);
		 DisplayExportDataDialog();
		 return ;
	 }
	 else
	 {
			SetTextValue(4,100,(uchar *)WarnningPrompt[iLanguageType][ExportingDataPrompt]);
			SetTextValue(4,101,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);

			SetControlVisiable(4,97,1);
			SetControlVisiable(4,100,1);
			SetControlVisiable(4,101,1);
	 }
		 
   
   
/**********************************************************************/	 
	 uint16_t j;
	 
	 UPPERCASE(ExName_E);
	 
   sprintf((char*)Title,"%s%s",ExName_E,".CSV");
	 
	 for ( j = 0; Title[j] != 0; j++ ) {  /* 复制并转换长文件名到LongNameBuf长文件名缓冲区 */
			LongNameBuf[j*2] = Title[j];  /* 将英文字符转换为两字节的小端UNICODE编码 */
			LongNameBuf[j*2+1] = 0x00;
		}
		LongNameBuf[j*2] = 0x00;  // 末尾用两个0表示结束
		LongNameBuf[j*2+1] = 0x00;
		
	 sprintf((char*)CRCBuff,"%d%d%s",EXPORTDATA[64],EXPORTDATA[65],".CSV"); 
	 res = CH376CreateLongName(CRCBuff,LongNameBuf );
   res = CH376FileOpen(CRCBuff);
	 if ( res == USB_INT_SUCCESS )   {count++;}
/******************************Long Name Export End*************************************************************/		
		
//	 res = CH376DirCreate( (uchar *)"/SANS_TOE" );
//   if ( res == USB_INT_SUCCESS )   {count++;}
//   
//   UPPERCASE(ExName);
//   sprintf((char*)Title,"%s%s",ExName_E,".CSV");
//   res = CH376FileCreate(Title);
//   if ( res == USB_INT_SUCCESS )   {count++;}
  
/*********************************Short Name Export End*************************************/

   CH376LongNameWrite((uchar *)FristLine,strlen(FristLine));
	 CH376ByteLocate(0xFFFFFFFF);
	 CH376LongNameWrite((uchar *)SecondLine,strlen(SecondLine));
	 CH376ByteLocate(0xFFFFFFFF);
	 CH376LongNameWrite((uchar *)ThirdLine,strlen(ThirdLine));
	 CH376ByteLocate(0xFFFFFFFF);
	 for(int i=0;i<Animals[0];i++)
   {
	   CH376LongNameWrite((uchar *)DataLine[i],strlen(DataLine[i]));
	   CH376ByteLocate(0xFFFFFFFF);
	 }
   res = CH376FileClose( TRUE );
   if ( res == USB_INT_SUCCESS )   {count++;}

   if(count==2)
   {
	  SetTextValue(4,100,(uchar *)WarnningPrompt[iLanguageType][ExportDataSuccessPrompt]);
		DisplayExportDataDialog();
   }
   else 
   {
	  SetTextValue(4,100,(uchar *)WarnningPrompt[iLanguageType][ExportDataFailPrompt]);
		DisplayExportDataDialog();
   }
	 return ;
}







void EXPORT_ALL_EXDATA(void)
{
	
  DisEnableScreen3Button();                         



	
	
	
	int Excount = 0;
	while(Excount<=EX_SUM)
	{
		uint8_t count = 0;
		uint8_t LineBreak [12]   = {"\n"};
		uint8_t Title     [64]   = {0};
		uint8_t ExDate_Q  [32]   = {0};
		char FristLine    [128]  = {0};
		char SecondLine   [128]  = {0};
		char ThirdLine    [128]  = {0};
		
		uint8_t EXPORTDATA[143]  = {0};
		AT24CXX_Read(128+(Excount)*143,EXPORTDATA,143);

	/**************FristLine*****************/
	/*include experiment Name,experiment Date*/

		uint8_t ExName_E[32] = {0};
		memcpy(&ExName_E,&EXPORTDATA[2],32);
		uint8_t ExDate_E[32] = {0};
		memcpy(&ExDate_E,&EXPORTDATA[135],7);
		sprintf(FristLine,"%s,%s,%s,%02d/%02d/%02d-%02d:%02d:%02d%s",(uchar *)"Name:",ExName_E,(uchar *)"Date:",EXPORTDATA[141],EXPORTDATA[140],EXPORTDATA[139],EXPORTDATA[137],EXPORTDATA[136],EXPORTDATA[135],LineBreak);

	/**************SecondLine*****************/
	/*include experiment Animals,Average,SD,Temperature and Humidity*/

		 int Animals[1] = {0};
		 Animals[0]  = EXPORTDATA[66];
		 Animals[0]  = Animals[0] << 8;
		 Animals[0] += EXPORTDATA[67];
		 uint16_t Average_E[1] = {0};
		 float fAverage_E[1] = {0};
		 Average_E[0]  = EXPORTDATA[129];
		 Average_E[0]  = Average_E[0] << 8;
		 Average_E[0] += EXPORTDATA[130];
		 uint16_t SD_E[1] = {0};
		 float fSD_E[1] = {0};
		 SD_E[0]  = EXPORTDATA[131];
		 SD_E[0]  = SD_E[0] << 8;
		 SD_E[0] += EXPORTDATA[132];
		 uint8_t Temperature[1] = {0};
		 memcpy(&Temperature,&EXPORTDATA[133],1);
		 uint8_t Humidity[1] = {0};
		 memcpy(&Humidity,&EXPORTDATA[134],1);
		 fAverage_E[0] = TypeTransformInt2Float(Average_E[0]);
		 fSD_E[0] = TypeTransformInt2Float(SD_E[0]);
		 
		 sprintf(SecondLine,"%s,%d,%s,%.3lf,%s,%.3lf,%s,%d,%s,%d%s",(uchar *)"Animals:",Animals[0],(uchar *)"Average:",fAverage_E[0],
											 (uchar *)"SD:",fSD_E[0],(uchar *)"TEMP:",Temperature[0],(uchar *)"RH:",Humidity[0],LineBreak);

	/**************FourthLine*****************/
	/*include experiment title*/	 
		 
		 sprintf(ThirdLine,"%s,%s%s",(uchar *)"Times",(uchar *)"Value(mL)",LineBreak);

	/**************FourthLine*****************/
	/*include experiment data*/

		 char DataLine[30][16]  = {{0},{0}};
		 uint8_t iDataBuff[30] = {0};
		 float   fDataBuff[30] = {0};
		 for(uint8_t i = 0 ; i < Animals[0] ; i++)
		 {
			iDataBuff[i]  = EXPORTDATA[68+(2*i)];
			iDataBuff[i]  = iDataBuff[i] << 8;
			iDataBuff[i] += EXPORTDATA[69+(2*i)];
		 }
		 
		 for(int i=0;i<Animals[0];i++)
		 {
			 fDataBuff[i] = iDataBuff[i];
			 fDataBuff[i] /= 1000;
			 sprintf(DataLine[i],"%d,%.3lf%s",i+1,fDataBuff[i],LineBreak);
		 }
		 
		 
		 uint16_t res = mInitCH376Host();  //测试链接
		 res = CH376DiskMount();  //测试内存
		 if ( res != USB_INT_SUCCESS )
		 {
			 SetTextValue(3,43,(uchar *)WarnningPrompt[iLanguageType][NotDetectedUsbPrompt]);
			 DisplayExportAllDataDialog();
			 return ;
		 }
		 else
		 {
				SetTextValue(3,43,(uchar*)WarnningPrompt[iLanguageType][ExportingDataPrompt]);
				SetTextValue(3,44,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);
				
				SetControlVisiable(3,40,1);
				SetControlVisiable(3,43,1);
				SetControlVisiable(3,44,1);
		 }
		 
		 
	/**********************************************************************/	  
		 uint16_t j;
		 
		 UPPERCASE(ExName_E);	 
		 sprintf((char*)Title,"%s%s",ExName_E,".CSV");
		 
		 for ( j = 0; Title[j] != 0; j++ ) {  /* 复制并转换长文件名到LongNameBuf长文件名缓冲区 */
				LongNameBuf[j*2] = Title[j];  /* 将英文字符转换为两字节的小端UNICODE编码 */
				LongNameBuf[j*2+1] = 0x00;
			}
			LongNameBuf[j*2] = 0x00;  // 末尾用两个0表示结束
			LongNameBuf[j*2+1] = 0x00;
			
		 sprintf((char*)ExDate_Q,"%d%d%s",EXPORTDATA[64],EXPORTDATA[65],".CSV"); 
		 res = CH376CreateLongName(ExDate_Q,LongNameBuf );
		
		
	/**********************************************************************/

		 
		 res = CH376FileOpen(ExDate_Q);
		 if ( res == USB_INT_SUCCESS )   {count++;}
		 CH376ByteWrite((uchar *)FristLine,strlen(FristLine),NULL);
		 CH376ByteLocate(0xFFFFFFFF);
		 CH376ByteWrite((uchar *)SecondLine,strlen(SecondLine),NULL);
		 CH376ByteLocate(0xFFFFFFFF);
		 CH376ByteWrite((uchar *)ThirdLine,strlen(ThirdLine),NULL);
		 CH376ByteLocate(0xFFFFFFFF);
		 for(int i=0;i<Animals[0];i++)
		 {
			 CH376LongNameWrite((uchar *)DataLine[i],strlen(DataLine[i]));
			 CH376ByteLocate(0xFFFFFFFF);
		 }
		 
		 res = CH376FileClose( TRUE );
		 if ( res == USB_INT_SUCCESS )   {count++;}

		 if(count==2)
		 {
			 Excount++;
		 }
		 else 
		 {
				SetTextValue(3,43,(uchar*)WarnningPrompt[iLanguageType][ExportDataFailPrompt]);
				DisplayExportAllDataDialog();
				return ;
		 }
		 
		 if(Excount==EX_SUM)
		 {
        SetTextValue(3,43,(uchar *)WarnningPrompt[iLanguageType][ExportDataSuccessPrompt]);
				DisplayExportAllDataDialog();
				Excount++;
		 }
	}
}




uint8_t UPPERCASE(uchar * buf)
{
  int i;
	for (i = 0; buf[i] != '\0'; i++)
  if (buf[i] >= 'a' && buf[i] <= 'z') buf[i] -= 32;
	return 0;
}


void DisplayExportDataDialog()
{


			SetTextValue(4,99 ,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(4,101,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);

			for(int i=97;i<102;i++){SetControlVisiable(4,i,1);}
}


void HideExportDataDialog()
{
			SetTextValue(4,99,(uchar*)"");
			SetTextValue(4,100,(uchar*)"");
			SetTextValue(4,101,(uchar*)"");
			
	    for(int i=97;i<102;i++){SetControlVisiable(4,i,0);}
}


void DisplayDeleteDataDialog()
{
			SetTextValue(4,93,(uchar*)WarnningPrompt[iLanguageType][DeleteDataPrompt]);
			SetTextValue(4,94,(uchar*)WarnningPrompt[iLanguageType][No]);
			SetTextValue(4,95,(uchar*)WarnningPrompt[iLanguageType][Yes]);
		  SetTextValue(4,96,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);
	
			for(int i=90;i<97;i++){SetControlVisiable(4,i,1);}
}

void HideDeleteDataDialog()
{

			SetTextValue(4,93,(uchar*)"");
			SetTextValue(4,94,(uchar*)"");
			SetTextValue(4,95,(uchar*)"");
			SetTextValue(4,96,(uchar*)"");
			
			for(int i=90;i<97;i++){SetControlVisiable(4,i,0);}
}
/**********************************************************/
void DisplayPickupIcon()
{
   SetControlVisiable(1,95,1);
	 SetControlVisiable(1,96,0);
}

void DisplayPutdownIcon()
{
   SetControlVisiable(1,95,0);
	 SetControlVisiable(1,96,1);
}
/******************************************************/
void DisplayDataOverflowDialog()
{
			SetTextValue(1,100,(uchar*)WarnningPrompt[iLanguageType][DataOverFlowPrompt]);
			SetTextValue(1,101,(uchar*)WarnningPrompt[iLanguageType][No]);
			SetTextValue(1,102,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(1,103,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);

			for(int i=97;i<104;i++){SetControlVisiable(1,i,1);}
}

void HideDataOverflowDialog()
{

			SetTextValue(1,100,(uchar*)"");
			SetTextValue(1,101,(uchar*)"");
			SetTextValue(1,102,(uchar*)"");
			SetTextValue(1,103,(uchar*)"");
			
			for(int i=97;i<104;i++){SetControlVisiable(1,i,0);}
}
/*******************************************************/
void DisplayClearDataDialog()
{

			SetTextValue(3,35,(uchar*)WarnningPrompt[iLanguageType][ClearAllDataPrompt]);
			SetTextValue(3,36,(uchar*)WarnningPrompt[iLanguageType][No]);
			SetTextValue(3,37,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(3,38,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);
			
			for(int i=33;i<40;i++){SetControlVisiable(3,i,1);}
}
void HideClearDataDialog()
{
			SetTextValue(3,35,(uchar*)"");
			SetTextValue(3,36,(uchar*)"");
			SetTextValue(3,37,(uchar*)"");
			SetTextValue(3,38,(uchar*)"");
			
			for(int i=33;i<40;i++){SetControlVisiable(3,i,0);}
}
/*****************************************************/
void DisplayExNameOverflowDialog()
{

			SetTextValue(1,106,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(1,107,(uchar*)WarnningPrompt[iLanguageType][NameOverFlowPrompt]);
			SetTextValue(1,108,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);

			for(int i=104;i<109;i++){SetControlVisiable(1,i,1);}
}
	
void HideExNameOverflowDialog()
{
			SetTextValue(1,106,(uchar*)"");
			SetTextValue(1,107,(uchar*)"");
			SetTextValue(1,108,(uchar*)"");			
			for(int i=104;i<109;i++){SetControlVisiable(1,i,0);}
}

/******************************************************************/
void DisplayExNameRepeatDialog()
{
			SetTextValue(1,111,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(1,112,(uchar*)WarnningPrompt[iLanguageType][NameRepeatedPrompt]);
			SetTextValue(1,113,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);
	
			for(int i=109;i<114;i++){SetControlVisiable(1,i,1);}
}

void HideExNameRepeatDialog()
{
		  SetTextValue(1,111,(uchar*)"");
			SetTextValue(1,112,(uchar*)"");
			SetTextValue(1,113,(uchar*)"");			
			for(int i=109;i<114;i++){SetControlVisiable(1,i,0);}
}
/******************************************************/
void DisplayExportAllDataDialog()
{
			SetTextValue(3,42,(uchar*)WarnningPrompt[iLanguageType][Yes]);
			SetTextValue(3,44,(uchar*)WarnningPrompt[iLanguageType][WarnningPr]);
		
    	for(int i=40;i<45;i++){SetControlVisiable(3,i,1);}
}

void HideExportAllDataDialog()
{
			SetTextValue(3,42,(uchar*)"");
			SetTextValue(3,43,(uchar*)"");
			SetTextValue(3,44,(uchar*)"");
			
			for(int i=40;i<45;i++){SetControlVisiable(3,i,0);}
}


/*******************************************************/

