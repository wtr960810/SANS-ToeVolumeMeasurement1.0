#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_


#define PromptNumMax     20
#define PromptLengthMax  256
#define LanguageTypeMax  2


typedef enum 
{
  CHINA = 0,
  ENGLAND = 1,
}LanguageType_t;


typedef enum 
{
	Yes = 0,
	No  = 1,
  WarnningPr = 2,
	ExperimentStart = 3,
	ExperimentFinish = 4,
	
	DeletePromptStart=5,
	DeleteDataPrompt=5,       //是否删除本次数据?
	ClearAllDataPrompt,       //是否清空数据?
	DeletePromptEnd=6,
	
	ExportPromptStart=7,
	ExportingDataPrompt=7,    //正在导出数据
  ExportDataFailPrompt,     //导出数据失败
	ExportDataSuccessPrompt,  //导出数据成功
	NotDetectedUsbPrompt,     //U盘未连接
	ExportPromptEnd=10,
	
	OverFlowPromptStart=11,   
	DataOverFlowPrompt=11,     //数据溢出请导出数据 并清除数据
	NameOverFlowPrompt,       //实验名称过长 请重新新建实验
  NameRepeatedPrompt,       //重复的实验名称 请重新新建实验
	OverFlowPromptEnd=13,
	
	CalibrateValue = 14,      //请校准初值
	PutDownAnimals = 15,      //请放入动物
	
	
}Prompt_t;






#endif

