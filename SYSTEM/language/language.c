#include "language.h"


Prompt_t prompt;


char WarnningPrompt[LanguageTypeMax][PromptNumMax][128] = 
{
    {
			"��",                           //0
			"��",                           //1
			"����",                         //2
			"��ʼ",                         //3
			"����",                         //4
	  	"   �Ƿ�ɾ����������?",            //5
		  "   �Ƿ�ɾ����������?",            //6
			"           ���ڵ�������...",              //7
			"         ��������ʧ�� ������",          //8
			"           �������ݳɹ�",                 //9
			"            U��δ����",                    //10
			"�뵼������ ���������",        //11
			"ʵ�����ƹ��� �������½�ʵ��",  //12
			"�ظ���ʵ������ �������½�ʵ��",//13
			"��У׼��ֵ",                   //14
			"����붯��",                   //15
			
	  },
		
	  {
			"Yes",                                          //0
			"No",                                           //1
			"Warnning",                                     //2
			"START",                                        //3
			"FINISH",                                       //4
	    "Do you want to delete the    experiment data?", //5
			"Do you want to clear the experiment data?",    //6
			"Exporting data in progress...",                //7
			"EXPORT DATA FAIL",                             //8
			"EXPORT DATA SUCCESS",                          //9
			"USB disk not connected",                       //10
			"Please export data and clear it!",             //11
			"The name of experiment is too long, Please create a new experiment",//12
			"Duplicate experiment name, Please create a new experiment",//13
			"Calibrate the value",                          //14
			"Please Put Toes In Beaker",                    //15
			
	  }
};



