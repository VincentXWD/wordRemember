#include "mainframe.h"

__MAINFRAME::__MAINFRAME() {}

__MAINFRAME::~__MAINFRAME() {}

void mainFrame::wordInit()		//初始化界面
{

}

void mainFrame::wordInput()	//录入新单词
{
	string curEnglish;
	string curChinese;
	/*输出提示信息，并且输入 英文单词*/
	if (dataBase.searchWord(curEnglish) >= 0)	//存在
	{
		/*提示单词已存在，不需要添加,返回*/
	}
	else
	{
		/*输出提示信息，并且输入 中文单词*/
		wordList* __BUFFER = new wordList(curEnglish, curChinese);
		dataBase.addWord(*__BUFFER);
		delete __BUFFER;
		/*输出成功添加单词的信息*/

		//  如果用 delete[]，则在回收空间之前所有对象都会首先调用自己的析构函数。
		//	基本类型的对象没有析构函数，所以回收基本类型组成的数组空间用 delete 和 delete[] 都是应该可以的；
		//  但是对于类对象数组，只能用 delete[]。
		//  对于 new 的单个对象，只能用 delete 不能用 delete[] 回收空间。
	}
	return ;
}

void mainFrame::wordShow()	//显示词典
{
	int LEN = dataBase.wordSize();
	/*输出提示信息：查看完单词表后请关闭*/
	for (int i = 0; i < LEN; i++)
	{
		wordList BUFFER;
		BUFFER = dataBase.getWord(i);
		cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	}
//	system("notepad Data\\dictionary.dat");	//读取文件
	return ;
}

void mainFrame::sortWord()	//单词排序
{
	dataBase.sortWord();
	return ;
}
void mainFrame::wordChange()	//修改单词
{
	string curEnglish;
	string curChinese;
	int Num;
	/*输出提示信息，并输入想要修改的单词*/
//	cin >> curEnglish;
	if(dataBase.searchWord(curEnglish) < 0)
	{
		/*提示单词不存在，输入错误，返回*/
//		cout << "no" << endl;
	}
	else
	{
		/*输出提示信息，输入单词的中文*/
//		cout << "yes!" << endl;
		cin >> curEnglish >> curChinese;
		Num = dataBase.searchWord(curEnglish) + 1;
		wordList BUFFER(curEnglish, curChinese);
		dataBase.changeWordNum(Num, BUFFER);
		/*提示修改成功*/
	}
}

void mainFrame::wordDelete()	//删除单词
{
	string curEnglish;
	string curChinese;
	int Num;
	/*输出提示信息，并输入想要删除的单词*/
//	cin >> curEnglish;
	if (dataBase.searchWord(curEnglish) < 0)	//不存在
	{
		/*提示单词不存在，输入错误,返回*/
	}
	else
	{
		Num = dataBase.searchWord(curEnglish) + 1;
		dataBase.removeWord(Num);
		/*提示单词删除成功*/
	}
	return;
}

void mainFrame::wordExercise()//背单词
{

}

void mainFrame::wordExit()	//退出本软件
{
	exit(EXIT_SUCCESS);
}

//__DATABASE testMode::getDatabase()	//test
//{
//	return dataBase;
//}