#include "mainframe.h"
#include <random>
#include <algorithm>
#include <iomanip>

__MAINFRAME::__MAINFRAME() {}

__MAINFRAME::~__MAINFRAME() {}

void mainFrame::CLIwordInit()		//命令行版初始化界面
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
}

void mainFrame::wordShow()	//显示词典
{
	//int LEN = dataBase.wordSize();
	/*输出提示信息：查看完单词表后请关闭*/
	//for (int i = 0; i < LEN; i++)
	//{
	//	wordList BUFFER;
	//	BUFFER = dataBase.getWord(i);
	//	cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	//}
	cout << "wordNum: " << dataBase.wordSize() << endl;
	system("notepad Data\\dictionary.dat");	//读取文件
}

void mainFrame::sortWord()	//单词排序
{
	dataBase.sortWord();
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
}

void mainFrame::wordExercise()	//背单词
{
	random_device rd;
	uniform_int_distribution<int> dicSeed(1, dataBase.wordSize() - 1);	//生成从词典取单词的随机数的种子
	dicSeed(rd);
	vector<wordList> answers;
	int len;
	/**/
	cin >> len;
	for (int i = 0; i < len; i++)
	{
		int chosen = dicSeed(rd);
		wordList word = dataBase.getWord(chosen);
		answers.push_back(word);
		cout << answers[i].getEnglish() << setw(10) << answers[i].getChinese() << endl;
		wordKiller(chosen);	//斩词功能
	}
}

void mainFrame::wordExam()	//海底捞模式
{
	random_device rd;	//种子
	uniform_int_distribution<int> dicSeed(1, dataBase.wordSize() - 1);	//生成从词典取单词的随机数的种子
	uniform_int_distribution<int> ansSeed(0, 3);						//生成四个数中的一个作为答案的种子
	uniform_int_distribution<int> exaSeed(0, 1);						//生成题目是汉译英还是英译汉的种子
	dicSeed(rd);
	wordList optAns[4];	//存储四个备选答案
	string answer;	//用来存放答案
	int ansNum, chsNum;
	int score = 0, count = 1;
	int range;	//单词数目
	int exam;
	double ratio;
	cout << "欢迎进入小测验模式，你希望背几个单词呢？   ";	//界面版改成可选
	cin >> range;
	cout << endl;
	for (int i = 0; i < range; i++)
	{
		exam = exaSeed(rd);
		if (exam == 0)	/*题干中文选项英语*/
		{
			for (int i = 0; i < 4; i++)	//给四个答案赋值
			{
				optAns[i] = dataBase.getWord(dicSeed(rd));
			}
			ansNum = ansSeed(rd);	//生成随机答案
			for (int i = 0; i < 4; i++)
			{
				cout << i + 1 << ": " << left << setw(10) << optAns[i].getEnglish();
				if ((i + 1) % 2 == 0)
				{
					cout << endl;
				}
			}
			cout << "Round " << count++ << ": 请选择英文为\"" << optAns[ansNum].getChinese() << "\"的单词。    ";

			cin >> chsNum;
			chsNum--;	//匹配存放数字习惯
			if (chsNum == ansNum)
			{
				score++;
				cout << "你答对了" << endl;
			}
			else
			{
				cout << "对不起，你答错了。" << endl;
			}
		}
		else if (exam == 1)	/*题干英语选项中文*/
		{
			for (int i = 0; i < 4; i++)	//给四个答案赋值
			{
				optAns[i] = dataBase.getWord(dicSeed(rd));
			}
			ansNum = ansSeed(rd);	//生成随机答案
			for (int i = 0; i < 4; i++)
			{
				cout << i + 1 << ": " << left << setw(10) << optAns[i].getChinese();
				if ((i + 1) % 2 == 0)
				{
					cout << endl;
				}
			}
			cout << "Round " << count++ << ": 请选择中文为\"" << optAns[ansNum].getEnglish() << "\"的汉语。    ";

			cin >> chsNum;
			chsNum--;	//匹配存放数字习惯
			if (chsNum == ansNum)
			{
				score++;
				cout << "你答对了" << endl;
			}
			else
			{
				cout << "对不起，你答错了。" << endl;
			}
		}
	}
	ratio = double(score) / double(range);
	cout << "考试结束，你一共得了 " << score << "分" << "正确率为 " << ratio*100 <<"%，请再接再厉！" << endl;
}

void mainFrame::killShow()	//显示已斩单词*
{
	cout << "killedNum: " << killedBase.wordSize() << endl;
	system("notepad Data\\killed.dat");	//读取文件
}

void mainFrame::wordKiller(int Num)
{
	int judge;
	cout << "输入1斩掉它" << endl;
	cin >> judge;
	if (judge == 1)
	{
		killedBase.addWord(dataBase.getWord(Num));
		dataBase.removeWord(Num+1);
	}
}

void mainFrame::killedRescue()	//恢复已斩单词
{
	killShow();
	cout << "请输入你想恢复的单词的英文拼写：" << endl;
	string temp;
	cin >> temp;
	int Num = killedBase.searchWord(temp);
	if (Num == -1)
	{
		cerr << "没有找到该单词！" << endl;
	}
	else
	{
		wordList wtmp = killedBase.getWord(Num);
		killedBase.removeWord(Num+1);	//删掉已斩词中的单词
		dataBase.addWord(wtmp);		//放回词典中
	}
}

void mainFrame::wordExit()	//退出本软件
{
	exit(EXIT_SUCCESS);
}
