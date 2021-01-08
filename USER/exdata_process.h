#ifndef _EXDATAPROCESS_H_
#define _EXDATAPROCESS_H_
#include "hmi_driver.h"

#define   Ex_Time_Max  200											//Experiment Max Time		



#define   INCOMPLETE   0
#define   COMPLETE     1
#define   START        0
#define   FINISH       1
#define   CHINESE      0
#define   ENGLISH      1
#define   OFF          0
#define   ON           1
#define   NumMax       100          							
#define   coel_max     151777                                  
#define   h_buff_max   32*1024    

typedef enum{FALSE,TRUE}bool;


extern u32 Weight;
void SAVE_DATA(void);
void UpdateUI(void);
void GetSensorData(void);
void GetTempHum(void);
void LCD_HANDLE(void);
void CLEAN_EX_INTERFACE(void);
void CALCULATE_AVR_SD(void);
void Display_Primary_History_Interface(void); 
void Display_Secondary_History_Interface(int Num);
void CLEAN_EXDATA(void);
void CLEAN_SECONDARY_HISTORY_INTERFACE(void);
void CLEAN_PRIMARY_HISTORY_INTERFACE(void);
void NotifyTouchXY(uint8 press,uint16 x,uint16 y);
void NotifyWriteFlash(uint8 status);
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length);
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second);
void NotifyScreen(uint16 screen_id);
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value);
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value);
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value);
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state);
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item);
void NotifyTimer(uint16 screen_id, uint16 control_id);
void UpdateGlobalData(void);
void read_eer_date(uint8_t read_mun);	
void PEDAL_KEY_DETECTION(void);	
void PEDAL_BUTTON_DECTION(void);
void SetBeepSound(uint8_t pram);
void InitConfig(void);
void DELETE_EXDATA(void);
void EXPORT_AllEXDATA(void);
void EXPORT_EXDATA(void);
void EnableScreen3Button(void);
void DisEnableScreen3Button(void);
float TypeTransformInt2Float(int data);
uint8_t UPPERCASE(uchar * buf);
uint8_t DetectNameRange(void);
uint8_t DetectNameRepeat(uint8_t *ptr);




void CheckSensorStatus(void);
void EXPORT_ALL_EXDATA(void);
void DisplayExportDataDialog(void);
void HideExportDataDialog(void);
void DisplayDeleteDataDialog(void);
void HideDeleteDataDialog(void); 
void DisplayPickupIcon(void);
void DisplayPutdownIcon(void);
void DisplayDataOverflowDialog(void);
void HideDataOverflowDialog(void);
void DisplayClearDataDialog(void);
void HideClearDataDialog(void);
void DisplayExNameOverflowDialog(void);
void HideExNameOverflowDialog(void);
void DisplayExNameRepeatDialog(void);
void HideExNameRepeatDialog(void);
void DisplayExportAllDataDialog(void);
void HideExportAllDataDialog(void);
#endif

