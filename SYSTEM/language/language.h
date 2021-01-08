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
	DeleteDataPrompt=5,       //�Ƿ�ɾ����������?
	ClearAllDataPrompt,       //�Ƿ��������?
	DeletePromptEnd=6,
	
	ExportPromptStart=7,
	ExportingDataPrompt=7,    //���ڵ�������
  ExportDataFailPrompt,     //��������ʧ��
	ExportDataSuccessPrompt,  //�������ݳɹ�
	NotDetectedUsbPrompt,     //U��δ����
	ExportPromptEnd=10,
	
	OverFlowPromptStart=11,   
	DataOverFlowPrompt=11,     //��������뵼������ ���������
	NameOverFlowPrompt,       //ʵ�����ƹ��� �������½�ʵ��
  NameRepeatedPrompt,       //�ظ���ʵ������ �������½�ʵ��
	OverFlowPromptEnd=13,
	
	CalibrateValue = 14,      //��У׼��ֵ
	PutDownAnimals = 15,      //����붯��
	
	
}Prompt_t;






#endif

