//mainframe.h
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "dataBase.h"
#include "killedList.h"

using namespace std;

typedef class __MAINFRAME
{
public:					/*构造、析构函数*/
		__MAINFRAME();
		~__MAINFRAME() = default;
public:					/*功能*/
	int CLIwordInit();	//初始化界面
	void wordInput(string);	//录入新单词
	void wordShow();	//显示词典
	void killShow();	//显示已斩单词
	void wordChange();	//修改单词
	void wordDelete();	//删除单词
	void wordLooking();//查询单词
	int wordKiller(int);//斩词
	void killedRescue();//恢复已斩单词
	void wordExercise();//背单词(可斩词)
	void wordExam();	//考试模式
	void wordReview();	//复习单词功能
	void aboutMe();		//关于作者		
	void famousMotto();	//打印名言		**
	void wordExit();	//退出本软件
	int datainit();	//初始化询问
//public:							//test
//	__DATABASE getDatabase();	//test
protected:
	__DATABASE dataBase;	//单词数据库
	__KILLEDLIST killedBase;//已斩单词数据库
	vector<string>	motto;	//存放名言
}mainFrame;
