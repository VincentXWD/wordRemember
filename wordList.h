#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

typedef class __WORDLIST
{
public:							/*构造析构函数*/
	__WORDLIST();
	~__WORDLIST();
public:	
	const string &getEnglish() const;		//获取单词信息，为了排序因此返回const
	const string &getChinese() const;

	void changeEnglish(string);	//修改单词
	void changeChinese(string);
protected:						//单词双意
	string English;
	string Chinese;
}wordList;

