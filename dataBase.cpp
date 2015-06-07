#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "dataBase.h"

#define NOTFOUND_INT -1
#define NOTFOUND_BOOL false
#define CHANGESUCCESS true

using namespace std;

__DATABASE::__DATABASE()	/*初始化操作*/
{
	string enBuffer;
	string cnBuffer;
	int tmBuffer;

	ifstream fileRead("Data/dictionary.dat");	//打开词典
	if (!fileRead)
	{	
		/*提示错误信息*/
		cerr << "找不到词典文件！请将词典文件放入Data文件夹内！" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	sortWord();
	while (fileRead >> enBuffer >> cnBuffer >> tmBuffer)	//硬盘文件转入内存
	{
		wordlist.changeChinese(cnBuffer);
		wordlist.changeEnglish(enBuffer);
		wordlist.changeWrongTimes(tmBuffer);

		word.push_back(wordlist);				//扔入容器中以备操作
	}
	fileRead.close();
}

__DATABASE::~__DATABASE()						//保存词典
{
	ofstream fileWrite("Data/dictionary.dat", ios::out);
	for (int i = 0; i < wordSize(); i++)
	{
		fileWrite << word[i].getEnglish() << " " 
				  << word[i].getChinese() << " " 
				  << word[i].getWrongTimes() << endl;
	}
	fileWrite.close();
}

int DATABASE::wordSize()		//统计单词数，返回值为单词数
{
	return word.size();
}

bool DATABASE::wordIsEmpty()	//判断词典是否为空，返回值为判断是否为空
{
	return wordSize() == 0 ? true : false;
}

void DATABASE::sortWord()		//按字典序对词典进行排序
{
	sort(begin(word), end(word), [](const wordList &a, const wordList &b) //闭包解决sort传值问题
	{
		return a.getEnglish() < b.getEnglish();
	});
}

void DATABASE::addWord(wordList curwordlist)	//添加新单词
{
	word.push_back(curwordlist);
	sortWord();
}

wordList DATABASE::getWord(int num)				//根据英文序号对应单词，返回值为单词节点
{
	if (num < 0 || num > wordSize() - 1)
	{
		wordList *null = new wordList();
		return *null;							//下表不合法，返回一个空节点
	}
	return word[num];
}

bool DATABASE::removeWord(int num)				//删除单词
{
	if(num < 0 || num > wordSize())
	{
		return NOTFOUND_BOOL;
	}
	else
	{
		word.erase(begin(word) + num - 1);
		return CHANGESUCCESS;
	}
}

int DATABASE::searchWord(string curEnglish)		//根据英文查找对应单词，返回值为单词序号（二分）
{
	sortWord();												//想二分，先排序
	int left = 0;
	int right = wordSize() - 1;
	int middle;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if (word[middle].getEnglish() == curEnglish)
		{
			return middle;
		}
		else if (word[middle].getEnglish() > curEnglish)	//在左
		{
			right = middle - 1;
		}
		else												//在右
		{
			left = middle + 1;
		}
	}
	return NOTFOUND_INT;
}

bool DATABASE::changeWordNum(int num, wordList curwordlist)				//按序号对应单词并修改，返回是否成功
{
	if (num < 0 || num > wordSize() - 1)
	{
		return NOTFOUND_BOOL;
	}
	word[num] = curwordlist;
	sortWord();				//排序
	return CHANGESUCCESS;
}

int DATABASE::getWordWrongTime(int num)	//获取该词错次数
{
	return word[num].getWrongTimes();
}

string DATABASE::getChinese(int num)	//获取中文翻译
{
	return word[num].getChinese();
}


void DATABASE::addWrongTimes(int num)
{
	word[num].addWrongTimes();
}

vector<__WORDLIST> DATABASE::getWrongWords()	//获取错词信息
{
	vector<__WORDLIST> wrongWords;
	int LEN = wordSize();
	for (int i = 0; i < LEN; i++)
	{
		if (word[i].getWrongTimes() != 0)
		{
			wrongWords.push_back(word[i]);
		}
	}
	sort(begin(wrongWords), end(wrongWords), [](const wordList &a, const wordList &b)
	{
		return a.getWrongTimes() < b.getWrongTimes();
	});
	return wrongWords;
}

int DATABASE::getWordNum(string curEnglish)				//获取单词序号，用于统计错词
{
	return searchWord(curEnglish);
}

void DATABASE::rmFromWrong(string curEnglish)			//从错词库中删除
{
	int temp = searchWord(curEnglish);
	word[temp].changeWrongTimes(0);
}

//bool DATABASE::changeWordWod(wordList tarwordlist, wordList curwordlist)//按单词对应单词并修改，返回是否成功
//{
//	int LEN = wordSize() - 1;
//	bool FOUND = false;
//	for (int i = 0; i < LEN; i++)
//	{
//		if ()
//	}
//	if (FOUND)
//	{
//		return FOUND;
//	}
//	else
//	{
//		return NOTFOUND_BOOL;
//	}
//}
