#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "dataBase.h"

using namespace std;

typedef class __TESTMODE
{
public:					/*构造、析构函数*/
		__TESTMODE();
		~__TESTMODE();
public:					/*功能*/

	void wordInit();	//初始化界面
	void wordInput();	//录入新单词
	void wordShow();	//显示词典
	void wordChange();	//修改单词
	void wordDelete();	//删除单词
	void wordExam();	//背单词
	void wordExit();	//退出本软件
protected:
	__DATABASE dataBase;
}testMode;
