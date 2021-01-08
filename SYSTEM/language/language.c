#include "language.h"


Prompt_t prompt;


char WarnningPrompt[LanguageTypeMax][PromptNumMax][128] = 
{
    {
			"是",                           //0
			"否",                           //1
			"警告",                         //2
			"开始",                         //3
			"结束",                         //4
	  	"   是否删除本次数据?",            //5
		  "   是否删除所有数据?",            //6
			"           正在导出数据...",              //7
			"         导出数据失败 请重试",          //8
			"           导出数据成功",                 //9
			"            U盘未连接",                    //10
			"请导出数据 并清除数据",        //11
			"实验名称过长 请重新新建实验",  //12
			"重复的实验名称 请重新新建实验",//13
			"请校准初值",                   //14
			"请放入动物",                   //15
			
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



