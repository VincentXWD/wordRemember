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

void mainFrame::famousMotto()	//打印名言
{
	ifstream fileOpen("Data\\motto.dat");
	string temp;
	vector<string> motto;
	while (fileOpen >> temp)
	{
		motto.push_back(temp);
	}
	random_device rd;	//种子
	uniform_int_distribution<int> dicSeed(0, 10);	//生成从词典取奇怪的东西的随机数的种子
	int mtrdm = dicSeed(rd);
	cout << "*********今日名言： " << motto[mtrdm] << "*********" << endl;
	fileOpen.close();
}

void mainFrame::aboutMe()		//关于作者
{
	system("cls");
	outputBlank(10);
	cout << "HitomiSAMA发现了彩蛋，Young man！" << endl;
	outputBlank(10);
}

int mainFrame::CLIwordInit()		//命令行版初始化界面
{
	int choice;
	bool initFlag = true;
	bool exitflag = false;
//	system("cls");
	while (1)
	{
		if (exitflag == true)
		{
			outputBlank(12);
			cout << setw(50) << "じゃよね！" << setw(20);
			outputBlank(12);
			return EXIT_SUCCESS;
		}
//		famousMotto();
		cout << "*******************************欢迎进入wordKiller*******************************" << endl;
		cout << "****                                                                       ****" << endl;
		cout << "****                           1.添加新奇怪的东西                          ****" << endl;
		cout << "****                           2.显示所有奇怪的东西                        ****" << endl;
		cout << "****                           3.显示已斩奇怪的东西                        ****" << endl;
		cout << "****                           4.复活已斩奇怪的东西                        ****" << endl;
		cout << "****                           5.试练！                                    ****" << endl;
		cout << "****                           6.呵呵哒模式                                ****" << endl;
		cout << "****                           7.定制奇怪的东西                            ****" << endl;
		cout << "****                           8.删除奇怪的东西                            ****" << endl;
		cout << "****                           9.观赏奇怪的东西的迷之残骸                  ****" << endl;
		cout << "****                           0.匿了匿了                                  ****" << endl;
		outputBlank(1);
		if (initFlag == true)
		{
			cout << "请选择HitomiSAMA想要使用的功能：     ";
		}
		else
		{
			cout << "HitomiSAMA的输入有误，请重试！" << endl;
		}
		cin >> choice;
		if (choice >= 0 && choice < 10)
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
		case 9: wordReview();	 break;
		case 0: exitflag = true; break;
		case 12345: aboutMe();	 break;
		}
		system("cls");
	}
}

void mainFrame::wordInput()	//录入新奇怪的东西
{
	string curEnglish = "!";
	string curChinese;

	system("cls");
	cout << "****                           1.添加新奇怪的东西                          ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		cout << "请输入奇怪的东西的魔法名（英文拼写），按#退出：      ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			break;
		}
		if (dataBase.searchWord(curEnglish) >= 0)	//存在
		{
			/*提示奇怪的东西已存在，不需要添加,返回*/
			cout << "奇怪的东西已存在，并不需要再次添加。" << endl;
		}
		else
		{
			/*输出提示信息，并且输入 中文奇怪的东西*/
			cout << "请输入它的真名！（中文名）：      ";
			cin >> curChinese;
			int flag = 0;
			cout << "HitomiSAMA要添加的奇怪的东西为: " << curEnglish << "， 它的真名为： " << curChinese << "确认添加本奇怪的东西吗？(1就是它了0再想想)" << endl;
			cin >> flag;
			if (flag == 1)
			{
				wordList BUFFER(curEnglish, curChinese, 0);
				dataBase.addWord(BUFFER);
				cout << "添加完毕，HitomiSAMA添加的奇怪的东西为: " << curEnglish << "， 它的真名为： " << curChinese << endl;
			}
			else if (flag == 0)
			{
				cout << "撤销成功！" << endl << endl;
			}
			else
			{
				cout << "HitomiSAMA填写的信息有误！好笨！" << endl;
			}
		}
	}
}

void mainFrame::wordShow()	//显示词典信息
{
	int LEN = dataBase.wordSize();
	/*输出提示信息：查看完奇怪的东西表后请关闭*/
	system("cls");
	cout << "****                           2.显示所有奇怪的东西                        ****" << endl;
	outputBlank(2);
	cout << "世界上一共有 " << dataBase.wordSize() << "个奇怪的东西。" << endl;
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

void mainFrame::sortWord()	//奇怪的东西排序
{
	dataBase.sortWord();
}

void mainFrame::wordChange()	//修改奇怪的东西
{
	int Num;
	int flag = 1;
	string curEnglish = "!";
	string curChinese;
	system("cls");
	cout << "****                           7.定制奇怪的东西                            ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		if (dataBase.wordIsEmpty())
		{
			bool ADD;
			cout << endl << "HitomiSAMA还没有添加任何奇怪的东西!是否要添加奇怪的东西(1加一个/0算了)？" << endl;
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
		while (flag == 1 || curEnglish != "#")
		{
			cout << "请HitomiSAMA写入想要定制的奇怪的东西的魔法名（英文拼写）!输入#退出：      ";		//词库太大，不提供序号修改服务
			cin >> curEnglish;
			fflush(stdin);	//清空缓冲区
			if (dataBase.searchWord(curEnglish) < 0)
			{
				/*提示奇怪的东西不存在，输入错误，返回*/
				cout << "此奇怪的东西并不存在，请重试。" << endl;
			}
			else
			{
				Num = dataBase.searchWord(curEnglish);
				cout << "此奇怪的东西的着宁为： " << dataBase.getChinese(Num) << endl;
				cout << "想要改个名么？：      想！我想叫它";
				cin >> curChinese;
				fflush(stdin);
				wordList BUFFER(curEnglish, curChinese, dataBase.getWordWrongTime(Num));	/*写*/
				dataBase.changeWordNum(Num, BUFFER);
				cout << "修改成功！ 是否继续修改（1是/0否）？    ";
				cin >> flag;
			}
		}
			getchar();
			return ;
			/*提示修改成功*/
	}
}

void mainFrame::wordDelete()	//删除奇怪的东西
{
	system("cls");
	string curEnglish = "!";
	string curChinese;
	int Num;
	cout << "****                           8.删除奇怪的东西                            ****" << endl;
	outputBlank(2);
	while (curEnglish != "#")
	{
		cout << "请输入HitomiSAMA想删除的奇怪的东西的魔法名（英文拼写）！输入#退出：      ";
		cin >> curEnglish;
		if (curEnglish == "#")
		{
			break;
		}
		if (dataBase.searchWord(curEnglish) < 0)	//不存在
		{
			cout << "HitomiSAMA选的奇怪的东西并不存在，请重新选择！ " << endl;
		}
		else
		{
			int flag;
			cout << "确认要删除它吗？（1是/0否）    ";
			cin >> flag;
			fflush(stdin);
			if (flag == 1)
			{
				Num = dataBase.searchWord(curEnglish) + 1;
				dataBase.removeWord(Num);
				cout << "删除成功！HitomiSAMA再也见不到它了！" << endl;
			}
			else
			{
				cout << "撤销成功！" << endl;
			}
		}
	}
}

void mainFrame::wordExercise()	//背奇怪的东西
{
	system("cls");
	cout << "****                           5.试练！                                    ****" << endl;
	random_device rd;
	uniform_int_distribution<int> dicSeed(0, dataBase.wordSize() - 1);	//生成从词典取奇怪的东西的随机数的种子
	dicSeed(rd);
	vector<wordList> answers;
	int flag = 1;
	while (flag == 1)
	{
		if (flag != 1)
		{
			return ;
		}
		int TIME;
		cout << "现在有" << dataBase.wordSize() << "个奇怪的东西，HitomiSAMA想练几个？      这个数——";
		cin >> TIME;
		fflush(stdin);
		for (int i = 0; i < TIME; i++)
		{
			int chosen = dicSeed(rd);
			wordList word = dataBase.getWord(chosen);
			answers.push_back(word);
			cout << "Round " << i+1 <<":  " <<  answers[i].getEnglish() << setw(10) << answers[i].getChinese() << endl;
			wordKiller(chosen);	//斩词功能
		}
		cout << endl << "不尽兴？还要再来一发吗？(1来一发/0虚了虚了)      ";
		cin >> flag;
	}
}

void mainFrame::wordExam()	//呵呵哒模式
{
	system("cls");
	cout << "****                           6.呵呵哒模式                                ****" << endl;
	random_device rd;	//种子
	uniform_int_distribution<int> dicSeed(0, dataBase.wordSize() - 1);	//生成从词典取奇怪的东西的随机数的种子
	uniform_int_distribution<int> ansSeed(0, 3);						//生成四个数中的一个作为答案的种子
	uniform_int_distribution<int> exaSeed(0, 1);						//生成题目是汉译英还是英译汉的种子
	dicSeed(rd);
	wordList optAns[4];	//存储四个备选答案
	wordList temp;		//用于存储错的奇怪的东西
	string answer;	//用来存放答案
	int ansNum, chsNum;
	int score = 0, count = 1;
	int range;	//奇怪的东西数目
	int exam;
	double ratio;
	cout << "欢迎进入\"呵呵哒\"模式，HitomiSAMA希望\"鉴赏\"几个奇怪的东西呢？      ";
	cin >> range;
	//range = 5;	//test
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
			cout << "Round " << count++ << ": 请选择魔法名为\"" << optAns[ansNum].getChinese() << "\"的奇怪的东西。    ";

			cin >> chsNum;
			chsNum--;	//匹配存放数字习惯
			if (chsNum == ansNum)
			{
				score++;
				cout << "HitomiSAMA好机智！" << endl;
			}
			else
			{
				int wr = dataBase.searchWord(optAns[ansNum].getEnglish());	//记下错词在词典vector中的位置
				cout << "弱爆了！！~等等！！你恼羞成怒抓了它！拿回去爽么？真是丧心病狂！" << endl;
				dataBase.addWrongTimes(wr);
				//cout << "+1" << endl;
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
			cout << "Round " << count++ << ": 请选择魔法名为\"" << optAns[ansNum].getEnglish() << "\"的真名。    ";

			cin >> chsNum;
			chsNum--;	//匹配存放数字习惯
			if (chsNum == ansNum)
			{
				score++;
				cout << "好机智！" << endl;
			}
			else
			{
				int wr = dataBase.searchWord(optAns[ansNum].getEnglish());	//记下错词在词典vector中的位置
				cout << "弱爆了！" << endl;
				dataBase.addWrongTimes(wr);
				//cout << "+1" << endl;
			}
		}
	}
	ratio = double(score) / double(range);
	cout << "Stop，HitomiSAMA一共得了 " << score << "分" << "正确率为 " << ratio * 100 << "%，请再接再厉！" << endl;
	cout << endl << "按任意键退出。" << endl;
	fflush(stdin);
	getchar();
}

void mainFrame::killShow()	//显示已斩奇怪的东西
{
	system("cls");
	cout << "****                           3.显示已斩奇怪的东西                              ****" << endl;
	if (killedBase.wordSize() == 0)
	{
		int flag;
		cout << endl << "HitomiSAMA还没有斩掉任何奇怪的东西！HitomiSAMA想斩个痛快吗？(1是/0否)      ";
		cin >> flag;
		if (flag)
		{
			wordExercise();
			return ;
		}
		else
		{
			return ;
		}
	}
	cout << "HitomiSAMA一共斩了: " << killedBase.wordSize() << " 个奇怪的东西，请务必再接再厉！" << endl;
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

void mainFrame::wordKiller(int Num)		//斩词
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

void mainFrame::killedRescue()	//恢复已斩奇怪的东西
{
	system("cls");
	bool FLAG = true;
	string temp = "!";
	cout << "****                           4.复活已斩奇怪的东西                        ****" << endl;
	outputBlank(2);
	while (temp != "#")
	{
		if (killedBase.wordIsEmpty())
		{
			int goKill;
			cout << "HitomiSAMA的斩杀名单是空的！想斩个痛快吗？(1去/0不去)    ";
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
			cout << "HitomiSAMA一共斩了: " << killedBase.wordSize() << " 个奇怪的东西哦。" << endl;
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
			cout << "还剩下 " << killedBase.wordSize() << " 个奇怪的东西。" << endl;
			for (int i = 0; i < killedBase.wordSize(); i++)
			{
				wordList BUFFER;
				BUFFER = killedBase.getWord(i);
				cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
			}
		}
		outputBlank(2);
		cout << "HitomiSAMA想要复活哪个奇怪的东西？写入它的魔法名(英文拼写)，（#退出复活功能）：" << endl;
		cin >> temp;
		if (temp == "#")
		{
			return ;
		}
		int Num = killedBase.searchWord(temp);
		if (Num == -1)
		{
			cerr << "没有找到该奇怪的东西！它可能没出现或者是还活着！（怕" << endl << endl;
		}
		else
		{
			wordList wtmp = killedBase.getWord(Num);
			killedBase.removeWord(Num + 1);	//删掉已斩词中的奇怪的东西
			dataBase.addWord(wtmp);		//放回词典中
			cout << "读条中........托您的福啊，它复活了" << endl;
		}
	}
	fflush(stdin);
	getchar();
}

void mainFrame::wordReview()	//复习奇怪的东西功能
{
	int fuck = 1;
	bool flag = true;
	string curEnglish = "!";
	system("cls");
	cout << "****                           9.复习错词                                  ****" << endl;
	outputBlank(2);
	vector<__WORDLIST> temp = dataBase.getWrongWords();	//获取错词的容器
	int LEN = temp.size();
	if (LEN == 0)
	{
		cout << "HitomiSAMA一个错词都没有！你一定是没有好好记奇怪的东西！快去背奇怪的东西！" << endl;
		system("pause");
		wordExam();
		return;
	}
	cout << "HitomiSAMA一共爽过了 " << temp.size() << "个奇怪的东西，它们分别是：   " << endl;
	for (int i = LEN - 1; i >= 0; i--)
	{
		cout << temp[i].getEnglish() << "  \"" 
			 << temp[i].getChinese() << "\"  " 
			 << "错了 " << temp[i].getWrongTimes() << "次。" << endl;
	}
	outputBlank(5);
	while (fuck == 1)
	{
		if (flag)
		{
			cout << "你又来？HitomiSAMA是不见棺材不落泪么？（提示：此挑战非同一般）(1怕你啊/0怂了)   ";
			flag = false;
		}
		else if (!flag && curEnglish != "#")
		{
			cout << "HitomiSAMA爽哉？再来一发么？(1是/0否)" << endl;
		}
		else
		{
			outputBlank(5);
			cout << "*******************HitomiSAMA真怂！*******************" << endl;
			outputBlank(5);
			fflush(stdin);
			system("pause");
			return ;
		}
		cin >> fuck;
		if (fuck == 1)
		{
			system("cls");
			random_device rd;	//种子
			uniform_int_distribution<int> dicSeed(0, LEN - 1);	//生成从词典取奇怪的东西的随机数的种子
			dicSeed(rd);
			int rdm;
			cout << "哦哟好屌哦，来战20个回合！（弱弱地：想撤退的话可以使用\"#\"" << endl << endl;
			for (int i = 0; i < 20; i++)
			{
				if (curEnglish == "#")
				{
					break;
				}
				rdm = dicSeed(rd);
				cout << "Round " << i + 1 << ": 你知道什么是 \"" << temp[rdm].getChinese() << "\" 么？    \"知道啊，不就是";
				cin >> curEnglish;
				fflush(stdin);
				if (curEnglish != temp[rdm].getEnglish())
				{
					cout << "哈哈哈我就知道你会错！正确答案其实是" << temp[rdm].getEnglish() << "啦！喵桑都知道！" << endl << endl;
				}
				else if (curEnglish == temp[rdm].getEnglish())
				{
					int choice;
					cout << "我擦，竟然对了。放了它？（奇怪的东西菌：你真的要抛弃我么？……）(1放了吧/0留着)    ";
					cin >> choice;
					if (choice == 1)
					{
						dataBase.rmFromWrong(curEnglish);
					}
				}
			}
		}
		else
		{
			return ;
		}
	}
	fflush(stdin);
	getchar();
}
