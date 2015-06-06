#include "mainframe.h"
#include <random>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cctype>

__MAINFRAME::__MAINFRAME() 
{
}

__MAINFRAME::~__MAINFRAME() 
{
}

void outputBlank(int n)					//输出回车，规划界面。
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
	}
}

void mainFrame::famousMotto()	//打印名言
{
	fflush(stdin);
	ifstream fileOpen("Data\\motto.dat");
	string temp;
	vector<string> motto;
	while (fileOpen >> temp)
	{
		motto.push_back(temp);
	}
	random_device rd;	//种子
	uniform_int_distribution<int> dicSeed(0, 10);	//生成从词典取单词的随机数的种子
	int mtrdm = dicSeed(rd);
	cout << "*********今日名言： " << motto[mtrdm] << "*********" << endl;
	fileOpen.close();
}

void mainFrame::aboutMe()		//关于作者
{
	fflush(stdin);
	system("cls");
	outputBlank(10);
	cout << "                  您发现了彩蛋，Young man！" << endl;
	system("Data\\egg.exe");
	outputBlank(10);
	system("pause");
}

int mainFrame::CLIwordInit()		//命令行版初始化界面
{
	fflush(stdin);

	int choice;
	bool initFlag = true;
	bool exitflag = false;
	//	system("cls");
	while (1)
	{
		if (exitflag == true)
		{
			outputBlank(12);
			cout << setw(50) << "谢谢您的使用！" << setw(20);
			outputBlank(12);
			return EXIT_SUCCESS;
		}
		//		famousMotto();
		cout << "*******************************欢迎进入wordKiller*******************************" << endl;
		cout << "****                                                                       ****" << endl;
		cout << "****                           0.单词查询                                  ****" << endl;
		cout << "****                           1.录入新单词                                ****" << endl;
		cout << "****                           2.显示词典                                  ****" << endl;
		cout << "****                           3.显示已斩单词                              ****" << endl;
		cout << "****                           4.恢复已斩单词                              ****" << endl;
		cout << "****                           5.背单词                                    ****" << endl;
		cout << "****                           6.考试模式                                  ****" << endl;
		cout << "****                           7.修改单词                                  ****" << endl;
		cout << "****                           8.删除单词                                  ****" << endl;
		cout << "****                           9.复习错词                                  ****" << endl;
		cout << "****                           10.退出软件                                 ****" << endl;
		outputBlank(1);
		if (initFlag == true)
		{
			cout << "请选择您想要使用的功能：     ";
		}
		else
		{
			cout << "您的输入有误，请重试！    ";
			fflush(stdin);
		}
		if (!scanf_s("%d", &choice))	//利用scanf的返回值判断是不是输入的整数
		{
			initFlag = false;
			fflush(stdin);
		}
		if (choice == 12345 || (choice >= 0 && choice <= 10))
		{
			initFlag = true;
		}
		else
		{
			initFlag = false;
			system("cls");
			continue;
		}
		if (initFlag)
		{
			switch (choice)
			{
				case 1:	wordInput("!");	 break;
				case 2: wordShow();		 break;
				case 3: killShow();		 break;
				case 4: killedRescue();	 break;
				case 5: wordExercise();  break;
				case 6: wordExam();		 break;
				case 7: wordChange(); 	 break;
				case 8: wordDelete();	 break;
				case 9: wordReview();	 break;
				case 0: wordLooking();	 break;
				case 10: exitflag = true; break;
				case 12345: aboutMe();	 break;
			}
		}
		system("cls");
	}
}

void mainFrame::wordLooking()//查询单词
{
	fflush(stdin);
	system("cls");
	string curEnglish = "!";
	cout << "****                           0.单词查询                                  ****" << endl;
	outputBlank(2);
	char add = '!';
	while (curEnglish != "#")
	{
		cout << "请输入您想要查询的单词的拼写，输入\"#\"退出查询功能：    ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			return;
		}
		fflush(stdin);
		int wd = dataBase.searchWord(curEnglish);
		if (wd == -1)
		{
			cout << "并没有找到该单词！您希望添加这个单词吗？   (1是/0否)    ";
			while (cin >> add)
			{
				if (add == '1')
				{
					wordInput(curEnglish);
					return ;
				}
				else if (add == '0')
				{
					cout << endl;
					break;
				}
				else
				{
					cout << "您输入的信息有误！请重新输入！    ";
					fflush(stdin);
				}
			}
		}
		else
		{
			cout << "单词 " << curEnglish << " 的中文解释为： " << dataBase.getChinese(wd) << endl << endl;
		}
	}
}

void mainFrame::wordInput(string curEnglish = "!")	//录入新单词
{
	fflush(stdin);
	string curChinese;

	system("cls");
	cout << "****                           1.录入新单词                                ****" << endl;
	outputBlank(2);
	if (curEnglish != "!")
	{
		/*输出提示信息，并且输入 中文单词*/
		while (curEnglish != "#")
		{
			cout << "您要添加的单词为: " << curEnglish << " ，请输入汉语释意：      ";
			cin >> curChinese;
			char flag = '0';
			cout << "您要录入的单词为: " << curEnglish << "， 它的解释为：\"" << curChinese << "\"，确认录入本单词吗？(1确认0再想想) ";
			while (1)
			{
				cin >> flag;
				if (flag == '1')
				{
					wordList BUFFER(curEnglish, curChinese, 0);
					dataBase.addWord(BUFFER);
					cout << "录入完毕，您录入的单词为: " << curEnglish << "， 它的解释为： " << curChinese << endl << endl;
					system("pause");
					return;
				}
				else if (flag == '0')
				{
					cout << "撤销成功！" << endl << endl;
					system("pause");
					return;
				}
				else
				{
					cout << "您输入的信息有误！请重新输入！(1确认0再想想)    ";
					fflush(stdin);	//清空缓冲区，防止多次循环
				}
			}
		}
	}
	else
	{
		while (curEnglish != "#")
		{
			cout << "请输入您想要录入的英文单词，按#退出：      ";
			cin >> curEnglish;
			if (curEnglish == "#")
			{
				return;
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
				char flag = '0';
				int exflag = 0;
				cout << "您要录入的单词为: " << curEnglish << "， 它的解释为： " << curChinese << "确认录入本单词吗？(1确认0再想想) ";
				while (!exflag)
				{
					cin >> flag;
					if (flag == '1')
					{
						wordList BUFFER(curEnglish, curChinese, 0);
						dataBase.addWord(BUFFER);
						cout << "录入完毕，您录入的单词为: " << curEnglish << "， 它的解释为： " << curChinese << endl << endl;
						exflag = 1;
					}
					else if (flag == '0')
					{
						cout << "撤销成功！" << endl << endl;
						exflag = 1;
					}
					else
					{
						cout << "您输入的信息有误！请重新输入！(1确认0再想想)    ";
						fflush(stdin);	//清空缓冲区，防止多次循环
						continue;
					}
				}
			}
		}
	}
}

void mainFrame::wordShow()	//显示词典信息
{
	fflush(stdin);
	int LEN = dataBase.wordSize();
	/*输出提示信息：查看完单词表后请关闭*/
	system("cls");
	cout << "****                           2.显示词典                                  ****" << endl;
	outputBlank(2);
	for (int i = 0; i < LEN; i++)
	{
		wordList BUFFER;
		BUFFER = dataBase.getWord(i);
		cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	}
	//	system("notepad Data\\dictionary.dat");	//读取文件
	cout << "您的词典里一共有 " << dataBase.wordSize() << "个单词。" << endl;
	outputBlank(2);
	fflush(stdin);
	system("pause");
}

void mainFrame::wordChange()	//修改单词
{
	fflush(stdin);
	int Num;
	char flag = '1';
	string curEnglish = "!";
	string curChinese;
	system("cls");
	cout << "****                           7.修改单词                                  ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		if (dataBase.wordIsEmpty())
		{
			int ADD = 3;
			while (ADD != 0 || ADD != 1)
			{
				cout << endl << "您还没有添加任何单词，是否要添加单词(1添加/0不添加)？    ";
				cin >> ADD;
				if (ADD == 1)
				{
					wordInput();
					break;
				}
				else if (ADD == 0)
				{
					return;
				}
				else
				{
					cout << "您输入的信息有误！" << endl << endl;
					fflush(stdin);
				}
			}
			return;
		}
		while (curEnglish != "#")
		{
			char cont = '1';
			cout << "请输入您想要修改的单词的拼写，输入#退出：      ";		//词库太大，不提供序号修改服务
			cin >> curEnglish;
			fflush(stdin);	//清空缓冲区
			if (curEnglish == "#")
			{
				return ;
			}
			if (dataBase.searchWord(curEnglish) < 0)
			{
				/*提示单词不存在，输入错误，返回*/
				cout << "此单词并不存在，请重试。 " << endl;
			}
			else
			{
				Num = dataBase.searchWord(curEnglish);
				cout << "此单词的中文解释为： " << dataBase.getChinese(Num) << endl;
				cout << "请输入您想要修改单词对应的中文解释：    ";
				cin >> curChinese;
				fflush(stdin);
				cout << "您要修改的单词为:" << curEnglish << "。它的解释为\"" << curChinese << "\"。确认修改吗?(1是/0否)  ";
				char comflag;
				bool finish = false;
				while (cin >> comflag && !finish)
				{
					if (comflag == '1')
					{
						wordList BUFFER(curEnglish, curChinese, dataBase.getWordWrongTime(Num));	/*写*/
						dataBase.changeWordNum(Num, BUFFER);
						cout << "修改成功！ 是否继续修改（1是/0否）？     ";
						while (cin >> cont)
						{
							if (cont == '0')
							{
								return ;
							}
							else if (cont == '1')
							{
								break ;
							}
							else
							{
								cout << "您输入的信息有误，请重试！    ";
							}
						}
						break;
					}
					else if (comflag == '0')
					{
						finish = true;
						cout << "撤销成功！ 是否继续修改（1是/0否）？     ";
						while (cin >> cont)
						{
							if (cont == '0')
							{
								return;
							}
							else if (cont == '1')
							{
								break;
							}
							else
							{
								cout << "您输入的信息有误，请重试！    ";
							}
						}
					}
					else
					{
						cout << "您输入的信息有误，请重新输入！    ";
						fflush(stdin);
					}
				}
			}
		}
		/*提示修改成功*/
	}
}

void mainFrame::wordDelete()	//删除单词
{
	fflush(stdin);
	system("cls");
	string curEnglish = "!";
	string curChinese;
	int Num;
	cout << "****                           8.删除单词                                  ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		cout << "请输入您想删除的单词的英文，输入#退出：      ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			break;
		}
		if (dataBase.searchWord(curEnglish) < 0)	//不存在
		{
			cout << "您选的单词并不存在，请重新选择！ " << endl << endl;
		}
		else
		{
			string curChinese = dataBase.getChinese(dataBase.searchWord(curEnglish));
			int flag;
			cout << "您所选的单词为 " << curEnglish << " ，它的解释为：\"" << curChinese << "\"。" << endl;
			cout << "确认要删除它吗？（1是/0否）    ";
			cin >> flag;
			fflush(stdin);
			if (flag == 1)
			{
				Num = dataBase.searchWord(curEnglish) + 1;
				dataBase.removeWord(Num);
				cout << "删除成功！您再也见不到它了" << endl << endl;
			}
			else
			{
				cout << "撤销成功！" << endl << endl;
			}
		}
	}
}

void mainFrame::wordExercise()	//背单词
{
	fflush(stdin);
	system("cls");
	cout << "****                           5.背单词                                    ****" << endl;
	if (dataBase.wordIsEmpty())
	{
		int ADD = 3;
		while (ADD != 0 || ADD != 1)
		{
			cout << endl << "您还没有添加任何单词，是否要添加单词(1添加/0不添加)？    ";
			cin >> ADD;
			if (ADD == 1)
			{
				wordInput();
				break;
			}
			else if (ADD == 0)
			{
				return;
			}
			else
			{
				cout << "您输入的信息有误！" << endl << endl;
				fflush(stdin);
			}
		}
		return;
	}
	int flag = 1;
	while (flag == 1)
	{
		random_device rd;
		uniform_int_distribution<int> dicSeed(0, dataBase.wordSize() - 1);	//生成从词典取单词的随机数的种子
		vector<wordList> answers;
		int TIME = 20;
		cout << "欢迎进入背单词模式，接下来将会出现20个单词供您记忆。输入\'#\'退出" << endl << endl;
		system("pause");
		for (int i = 0; i < TIME && !dataBase.wordIsEmpty(); i++)
		{
			if (dataBase.wordSize() > 0)
			{
				int chosen = dicSeed(rd);
				wordList word = dataBase.getWord(chosen);
				answers.push_back(word);
				cout << "Round " << i + 1 << ":  " << answers[i].getEnglish() << "   " << answers[i].getChinese() << endl;
				if (wordKiller(chosen) == 1)	//斩词功能
				{
					return;
				}
			}
		}
		if (!dataBase.wordIsEmpty())
		{
			cout << endl << "不尽兴？还要再来一发吗？(1来一发/0不用了)      ";
			cin >> flag;
			vector<wordList>().swap(answers);
		}
		else
		{
			cout << endl << "您的词库空啦！" << endl;
			system("pause");
			return ; 
		}
	}
}

int mainFrame::wordKiller(int Num)		//斩词
{
	fflush(stdin);
	char judge;
	cout << "输入1斩掉它，输入0饶了它！      ";
	while (cin >> judge)
	{
		if (judge == '1')
		{
			killedBase.addWord(dataBase.getWord(Num));
			dataBase.removeWord(Num + 1);
			break;
		}
		else if (judge == '0')
		{
			break;
		}
		else if (judge == '#')
		{
			return 1;
		}
		else
		{
			cout << "您输入的信息有误！请重新输入！    ";
			fflush(stdin);
		}
	}
	return 0;
}

void mainFrame::wordExam()	//考试模式
{
	fflush(stdin);
	system("cls");
	cout << "****                           6.考试模式                                  ****" << endl;
	if (dataBase.wordIsEmpty())
	{
		int ADD = 3;
		while (ADD != 0 || ADD != 1)
		{
			cout << endl << "您还没有添加任何单词，是否要添加单词(1添加/0不添加)？    ";
			cin >> ADD;
			if (ADD == 1)
			{
				wordInput();
				break;
			}
			else if (ADD == 0)
			{
				return;
			}
			else
			{
				cout << "您输入的信息有误！" << endl << endl;
				fflush(stdin);
			}
		}
		return;
	}
	random_device rd;	//种子
	uniform_int_distribution<int> dicSeed(0, dataBase.wordSize() - 1);	//生成从词典取单词的随机数的种子
	uniform_int_distribution<int> ansSeed(0, 3);						//生成四个数中的一个作为答案的种子
	uniform_int_distribution<int> exaSeed(0, 1);						//生成题目是汉译英还是英译汉的种子
	wordList optAns[4];	//存储四个备选答案
	wordList temp;		//用于存储错的单词
	string answer;	//用来存放答案
	int ansNum, chsNum;
	int score = 0, count = 1;
	int range;	//单词数目
	int exam;
	double ratio;
	cout << "欢迎进入考试模式，一共有20个单词，题干可能是中文也可能是英文，祝你好运。" << endl;
	system("pause");
	range = 20;	//test
	cout << "Link start!" << endl << endl;
	fflush(stdin);
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

			scanf_s("%d", &chsNum);
			chsNum--;
			if (chsNum == ansNum)
			{
				score++;
				cout << "您答对了" << endl;
				fflush(stdin);
			}
			else
			{
				int wr = dataBase.searchWord(optAns[ansNum].getEnglish());	//记下错词在词典vector中的位置
				cout << "对不起，您答错了。" << endl;
				dataBase.addWrongTimes(wr);
				//cout << "+1" << endl;
				fflush(stdin);
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
				cout << "您答对了" << endl;
			}
			else
			{
				int wr = dataBase.searchWord(optAns[ansNum].getEnglish());	//记下错词在词典vector中的位置
				cout << "对不起，您答错了。" << endl;
				dataBase.addWrongTimes(wr);	//增加错误次数
				//cout << "+1" << endl;
			}
		}
	}
	ratio = double(score) / double(range);
	cout << "Stop，您一共得了 " << score << "分" << "正确率为 " << ratio * 100 << "%，请再接再厉！" << endl;
	cout << endl << "按任意键退出。" << endl;
	fflush(stdin);
	getchar();
}

void mainFrame::killShow()	//显示已斩单词
{
	fflush(stdin);
	system("cls");
	cout << "****                           3.显示已斩单词                              ****" << endl;
	if (killedBase.wordSize() == 0)
	{
		int flag;
		cout << endl << "您还没有斩任何单词！您想斩个痛快吗？(1是/0否)      ";
		cin >> flag;
		if (flag)
		{
			wordExercise();
			return;
		}
		else
		{
			return;
		}
	}
	cout << "您一共斩了: " << killedBase.wordSize() << " 个单词，请务必再接再厉！" << endl;
	//	system("notepad Data\\killed.dat");	//读取文件
	for (int i = 0; i < killedBase.wordSize(); i++)
	{
		wordList BUFFER;
		BUFFER = killedBase.getWord(i);
		cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	}
	outputBlank(2);
	system("pause");
	fflush(stdin);
}

void mainFrame::killedRescue()	//恢复已斩单词
{
	fflush(stdin);
	system("cls");
	bool FLAG = true;
	string temp = "!";
	cout << "****                           4.恢复已斩单词                              ****" << endl;
	outputBlank(2);
	while (temp != "#")
	{
		if (killedBase.wordIsEmpty())
		{
			char goKill;
			cout << "您的斩杀名单是空的！想斩个痛快吗？(1去/0不去)    ";
			while (cin >> goKill)
			{
				fflush(stdin);
				if (goKill == '1')
				{
					wordExercise();
					return;
				}
				else if (goKill == '0')
				{
					return;
				}
				else
				{
					cout << "您的输入有误，请重新输入！   ";
				}
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
		cout << "请输入您想恢复的单词的英文拼写，输入#退出恢复功能：     ";
		cin >> temp;
		if (temp == "#")
		{
			return;
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

void mainFrame::wordReview()	//复习单词功能
{
	fflush(stdin);
	int fuck = 1;
	bool flag = true;
	string curEnglish = "!";
	system("cls");
	cout << "****                           9.复习错词                                  ****" << endl;
	outputBlank(2);
	vector<__WORDLIST> temp = dataBase.getWrongWords();	//获取错词的容器
	if (temp.size() == 0)
	{
		cout << "一个错词都没有！你一定是没有好好背单词！快去背单词！" << endl << endl;
		system("pause");
		wordExam();
		return;
	}
	cout << "在过去的日子里，您一共错了 " << temp.size() << "个单词，它们分别是：   " << endl;
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		cout << temp[i].getEnglish() << "  \""
			<< temp[i].getChinese() << "\"  "
			<< "错了 "	 << temp[i].getWrongTimes() << "次。" << endl;
	}
	outputBlank(5);
	while (fuck == 1)
	{
		if (flag)
		{
			cout << "现在您有一次挑战他们的机会，是否迎战？（提示：此类挑战非同一般）(1是/0否)   ";
			flag = false;
		}
		else if (!flag && curEnglish != "#")
		{
			cout << "爽哉？是否再来一次？(1是/0否)" << endl;
		}
		else
		{
			outputBlank(5);
			cout << "*******************真怂！*******************" << endl;
			outputBlank(5);
			fflush(stdin);
			system("pause");
			return;
		}
		cin >> fuck;
		if (fuck == 1)
		{
			system("cls");
			int rdm;
			cout << "好爽快！此为无尽模式，想撤退的话可以使用\"#\"" << endl << endl;
			while (1)
			{
				int i = 0;
				i++;
				if (curEnglish == "#")
				{
					break;
				}
				random_device rd;	//种子
				uniform_int_distribution<int> dicSeed(0, temp.size() - 1);	//生成从词典取单词的随机数的种子，因为size是会变化的
				rdm = dicSeed(rd);
				cout << "Round " << i + 1 << ": 请写出意思为 \"" << temp[rdm].getChinese() << "\" 的单词的拼写：    ";
				cin >> curEnglish;
				fflush(stdin);
				if (curEnglish != temp[rdm].getEnglish())
				{
					cout << "您回答错了，正确答案应该是： " << temp[rdm].getEnglish() << endl << endl;
				}
				else if (curEnglish == temp[rdm].getEnglish())
				{
					int choice;
					cout << "您回答正确，是否把它放回（放回就不会出现在这里了！）？(1放了吧/0留着)    ";
					cin >> choice;
					if (choice == 1)
					{
						dataBase.rmFromWrong(curEnglish);
						swap(temp[rdm], temp[temp.size() - 1]);
						temp.pop_back();
					}
					if (dataBase.getWrongWords().size() == 0)
					{
						cout << endl << "您没有任何错词了唷~" << endl;
						system("pause");
						return ;
					}
				}
			}
		}
		else if (fuck == 0)
		{
			return;
		}
		else
		{
			cout << "您输入的信息有误，请重新输入！";
		}
	}
	fflush(stdin);
	getchar();
}
