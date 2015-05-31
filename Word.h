#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "json11-master/json11.hpp"
using namespace json11;
using namespace std;

typedef struct __CONFIG
{
	bool FIRST = false;	//是否是第一次使用
	int VER;			//版本号
	int wordNum;		//单词数量
	/*...*/
}__CONFIG;

class Word
{
public:
	/*初始化以及回收*/
	Word();
	~Word();
	void wordInit();	//仅供第一次使用本软件时调用
public:
	/*词典设置功能*/
	void wordInput();
	void wordShow();
	void wordChange();
	void wordDelete();
public:
	/*记忆功能*/
	void wordRmber();
protected:
	vector<string> English;
	vector<string> Chinese;
	__CONFIG confFile;
};
