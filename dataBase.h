/*直接对文件操作的类*/

#pragma once

#include <iostream> 
#include <vector>
#include "wordList.h"

using namespace std;

typedef class __DATABASE
{
public:	
	__DATABASE();	//读取文件
	~__DATABASE();	//保存文件
public:
	int wordSize();						//统计单词数，返回值为单词数
	bool wordIsEmpty();					//判断词典是否为空，返回值为判断是否为空
	void sortWord();					//按字典序对词典进行排序
	void addWord(__WORDLIST);			//添加新单词
	bool removeWord(int);				//根据英文序号查找并删除单词
	__WORDLIST getWord(int);			//根据英文序号对应单词，返回值为单词类
	int searchWord(string);				//根据英文查找对应单词，返回值为单词序号（二分）
	bool changeWordNum(int, __WORDLIST);//按序号对应单词并修改，返回是否成功
protected:
	vector<__WORDLIST> word;
	__WORDLIST wordlist;
}DATABASE;
