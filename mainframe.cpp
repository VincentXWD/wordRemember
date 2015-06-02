#include "mainframe.h"
#include <random>
#include <algorithm>
#include <iomanip>

__MAINFRAME::__MAINFRAME() {}

__MAINFRAME::~__MAINFRAME() {}

void outputBlank(int n)					//输出回车，规划界面。
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
	}
}

void mainFrame::CLIwordInit()		//命令行版初始化界面
{
	int choice;
	bool initFlag = true;
	bool exitflag = false;
	system("cls");
	while (1)
	{
		if (exitflag == true)
		{
			return;
		}
		cout << "*******************************欢迎进入wordKiller*******************************" << endl;
		cout << "****                                                                       ****" << endl;
		cout << "****                           1.录入新单词                                ****" << endl;
		cout << "****                           2.显示词典                                  ****" << endl;
		cout << "****                           3.显示已斩单词                              ****" << endl;
		cout << "****                           4.恢复已斩单词                              ****" << endl;
		cout << "****                           5.背单词                                    ****" << endl;
		cout << "****                           6.海底捞模式                                ****" << endl;
		cout << "****                           7.修改单词                                  ****" << endl;
		cout << "****                           8.删除单词                                  ****" << endl;
		cout << "****                           9.退出软件                                  ****" << endl;
		outputBlank(1);
		if (initFlag == true)
		{
			cout << "请选择你想要使用的功能：     ";
		}
		else
		{
			cout << "你的输入有误，请重试！" << endl;
		}
		cin >> choice;
		if (choice > 0 && choice < 10)
		{
			initFlag = true;
		}
		else
		{
			initFlag = false;
			system("cls");
			continue;
		}
		switch (choice)
		{
		case 1:	wordInput();	 break;
		case 2: wordShow();		 break;
		case 3: killShow();		 break;
		case 4: killedRescue();	 break;
		case 5: wordExercise();  break;
		case 6: wordExam();		 break;
		case 7: wordChange(); 	 break;
		case 8: wordDelete();	 break;
		case 9: exitflag = true; break;
		}
		system("cls");
	}
}

void mainFrame::wordInput()	//录入新单词
{
	string curEnglish = "!";
	string curChinese;

	system("cls");
	cout << "****                           1.录入新单词                                ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		cout << "请输入你想要录入的英文单词，按#退出：      ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			break;
		}
		if (dataBase.searchWord(curEnglish) >= 0)	//存在
		{
			/*提示单词已存在，不需要添加,返回*/
			cout << "单词已存在，并不需要再次添加。" << endl;
		}
		else
		{
			/*输出提示信息，并且输入 中文单词*/
			cout << "请输入汉语释意：      ";
			cin >> curChinese;
			wordList BUFFER(curEnglish, curChinese);
			dataBase.addWord(BUFFER);
			cout << "录入完毕，您录入的单词为: " << curEnglish << "， 它的解释为： " << curChinese << endl;
		}
	}
}

void mainFrame::wordShow()	//显示词典
{
	int LEN = dataBase.wordSize();
	/*输出提示信息：查看完单词表后请关闭*/
	system("cls");
	cout << "****                           2.显示词典                                  ****" << endl;
	outputBlank(2);
	cout << "您的词典里一共有 " << dataBase.wordSize() << "个单词。" << endl << endl;
	for (int i = 0; i < LEN; i++)
	{
		wordList BUFFER;
		BUFFER = dataBase.getWord(i);
		cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	}
	//	system("notepad Data\\dictionary.dat");	//读取文件
	outputBlank(2);
	cout << "按任意键返回。 " << endl;
	fflush(stdin);
	getchar();
}

void mainFrame::sortWord()	//单词排序
{
	dataBase.sortWord();
}

void mainFrame::wordChange()	//修改单词
{
	int Num;
	string curEnglish = "!";
	string curChinese;
	system("cls");
	cout << "****                           7.修改单词                                  ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		if (dataBase.wordIsEmpty())
		{
			bool ADD;
			cout << "你还没有添加任何单词，是否要添加单词(1添加/0不添加)？" << endl;
			cin >> ADD;
			fflush(stdin);
			if (ADD)
			{
				wordInput();
				break;
			}
			else
			{
				return;
			}
		}
		cout << "请输入你想要修改的单词的拼写，输入#退出：      ";
		cin >> curEnglish;
		fflush(stdin);	//清空缓冲区
		if (dataBase.searchWord(curEnglish) < 0)
		{
			/*提示单词不存在，输入错误，返回*/
			cout << "此单词并不能存在，请重试。" << endl;
		}
		else
		{
			/*输出提示信息，输入单词的中文*/
			cout << "请输入你想要修改单词对应的中文解释：      ";
			cin >> curChinese;
			fflush(stdin);
			Num = dataBase.searchWord(curEnglish);
			wordList BUFFER(curEnglish, curChinese);
			dataBase.changeWordNum(Num, BUFFER);
			cout << "修改成功！按任意键退出。 " << endl;
			getchar();
			return ;
			/*提示修改成功*/
		}
	}
}

void mainFrame::wordDelete()	//删除单词
{
	system("cls");
	string curEnglish = "!";
	string curChinese;
	int Num;
	cout << "****                           8.删除单词                                  ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		cout << "请输入你想删除的单词的英文，输入#退出：      ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			break;
		}
		if (dataBase.searchWord(curEnglish) < 0)	//不存在
		{
			cout << "少侠选单词并不存在，请重新选择！ " << endl;
		}
		else
		{
			Num = dataBase.searchWord(curEnglish) + 1;
			dataBase.removeWord(Num);
			cout << "删除成功！你再也见不到它了" << endl;
		}
	}
}

void mainFrame::wordExercise()	//背单词
{
	system("cls");
	cout << "****                           5.背单词                                    ****" << endl;
	random_device rd;
	uniform_int_distribution<int> dicSeed(1, dataBase.wordSize() - 1);	//生成从词典取单词的随机数的种子
	dicSeed(rd);
	vector<wordList> answers;
	int len;
	cout << "您的词典里有" << dataBase.wordSize() << "个单词，少侠想背几个单词？      ";
	cin >> len;
	fflush(stdin);
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
	system("cls");
	cout << "****                           6.海底捞模式                                ****" << endl;
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
	cout << "欢迎进入\"海底捞\"模式，少侠希望考几个单词呢？      ";	//界面版改成可选
	cin >> range;
	cout << "Link start!" << endl << endl;
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

void mainFrame::killShow()	//显示已斩单词
{
	system("cls");
	cout << "****                           3.显示已斩单词                              ****" << endl;
	cout << "您一共斩了: " << killedBase.wordSize() << " 个单词，请务必再接再厉！" << endl;
//	system("notepad Data\\killed.dat");	//读取文件
	for (int i = 0; i < killedBase.wordSize(); i++)
	{
		wordList BUFFER;
		BUFFER = killedBase.getWord(i);
		cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	}
	outputBlank(2);
	cout << "按任意键返回。 " << endl;
	fflush(stdin);
	getchar();
}

void mainFrame::wordKiller(int Num)
{
	int judge;
	cout << "输入1斩掉它，输入0饶了它！      ";
	cin >> judge;
	if (judge == 1)
	{
		killedBase.addWord(dataBase.getWord(Num));
		dataBase.removeWord(Num+1);
	}
}

void mainFrame::killedRescue()	//恢复已斩单词
{
	system("cls");
	bool FLAG = true;
	string temp = "!";
	cout << "****                           4.恢复已斩单词                              ****" << endl;
	outputBlank(2);
	while (temp != "#")
	{
		if (killedBase.wordIsEmpty())
		{
			int goKill;
			cout << "您的斩杀名单是空的！想斩个痛快吗？(1去/0不去)" << endl;
			cin >> goKill;
			fflush(stdin);
			if (goKill)
			{
				wordExercise();
				return ;
			}
			else
			{
				return ;
			}
		}
		if (FLAG)
		{
			cout << "您一共斩了: " << killedBase.wordSize() << " 个单词。" << endl;
			for (int i = 0; i < killedBase.wordSize(); i++)
			{
				wordList BUFFER;
				BUFFER = killedBase.getWord(i);
				cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
			}
			FLAG = false;
		}
		else
		{
			cout << "还剩下 " << killedBase.wordSize() << " 个单词。" << endl;
			for (int i = 0; i < killedBase.wordSize(); i++)
			{
				wordList BUFFER;
				BUFFER = killedBase.getWord(i);
				cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
			}
		}
		outputBlank(2);
		cout << "请输入你想恢复的单词的英文拼写，输入#退出恢复功能：" << endl;
		cin >> temp;
		if (temp == "#")
		{
			return ;
		}
		int Num = killedBase.searchWord(temp);
		if (Num == -1)
		{
			cerr << "没有找到该单词！" << endl << endl;
		}
		else
		{
			wordList wtmp = killedBase.getWord(Num);
			killedBase.removeWord(Num + 1);	//删掉已斩词中的单词
			dataBase.addWord(wtmp);		//放回词典中
		}
	}
	fflush(stdin);
	getchar();
}
