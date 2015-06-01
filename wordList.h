#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

typedef class __WORDLIST
{
public:							/*构造析构函数*/
	__WORDLIST();				//默认必须是空，否则在getWord函数返回的就不是NULL指针了
	__WORDLIST(string, string);	//用于初始化新增单词以及修改单词的构造函数
	~__WORDLIST();
public:	
	const string &getEnglish() const;		//获取单词信息，为了dataBase中的排序闭包，因此返回const
	const string &getChinese() const;
	void changeEnglish(string);	//修改单词成员
	void changeChinese(string);
protected:						//单词双意
	string English;
	string Chinese;
}wordList;

