//wordList.h
#pragma once

#include <iostream>
#include <string>
#include <cstring>

using namespace std;



typedef class __WORDLIST
{
public:	/*构造析构函数*/
	__WORDLIST() = default;				//默认构造函数
	__WORDLIST(string, string, int);	//用于初始化新增单词而重载的构造函数
	__WORDLIST(string, string);			//用于修改单词而重载的构造函数 
	~__WORDLIST() = default;
public:	
	const string &getEnglish() const;	//获取单词信息，为了dataBase中的排序闭包，因此返回const
	const string &getChinese() const;
	const int &getWrongTimes() const;
	void changeEnglish(string);			//修改单词成员
	void changeChinese(string);
	void changeWrongTimes(int);
	void addWrongTimes();
protected:								//单词双意
	string English;
	string Chinese;
	int WrongTimes;						//单词错的次数
}wordList;

