/*直接对文件操作的类*/

#pragma once

#include <iostream> 
#include <vector>
#include "wordList.h"
using namespace std;


typedef class __DATABASE
{
public:									/*构造、析构函	数*/
	__DATABASE();
	~__DATABASE();
public:
	int wordSize();						//统计单词数，返回值为单词数
	bool wordIsEmpty();					//判断词典是否为空，返回值为判断是否为空
	void sortWord();					//按字典序对词典进行排序
	void addWord(wordList);				//添加新单词
	int searchWord(string);				//根据英文查找对应单词，返回值为单词序号（二分）
	bool wordCompare(wordList, wordList);//辅助词典排序使用的sort函数。
protected:
	vector<wordList> word;
	wordList wordlist;
}DATABASE;
