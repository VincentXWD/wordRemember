#include "Word.h"

Word::Word()
{
	/*读取json文件，并把配置信息对应写入__CONFIG的confFile结构体内。*/
}

Word::~Word()
{
	/**/
}
void Word::wordInit()
{
	if (confFile.FIRST)
	{
		ifstream fileInit("Data/config.json", ios::_Noreplace);
		/*初始化config.json*/
		confFile.FIRST = false;
		fileInit.close();
	}
}

void Word::wordInput()
{
	ofstream dataWrite("Data/wordList.rw", ios::out|ios::app);
	confFile.wordNum = 0;
	if (!dataWrite)
	{
		cerr << "词库文件打开错误，请重试！" << endl;
		exit(EXIT_FAILURE);
	}
	string Buffer = "#";
	int Sign = 1;
	cout << "欢迎进入单词录入系统，请按照提示步骤进行录入工作 :-)" << endl << endl;
	while (Sign)
	{
		cout << "请输入你想要记忆的单词的英文拼写：" << endl;
		cin >> Buffer;
		dataWrite << Buffer << " ";
		cout << "请输入单词的中文意思：" << endl;
		cin >> Buffer;
		dataWrite << Buffer << endl;
		confFile.wordNum = confFile.wordNum + 1;
		cout << "录入成功，当前单词数为 : " << confFile.wordNum << endl;
		cout << "继续输入请按1，退出输入请按0。" << endl;
		cin >> Sign;
	}
	dataWrite << "__ENDSIGN!@#" << endl;
	dataWrite.close();
}

void Word::wordShow()
{
	ifstream dataRead("Data/wordList.rw");
	string buffer;
	if (!dataRead)
	{
		cerr << "词库文件打开错误，请重试！" << endl;
		exit(EXIT_FAILURE);
	}
	dataRead >> buffer;
	while (buffer != "__ENDSIGN!@#")
	{
		English.push_back(buffer);
		dataRead >> buffer;
		Chinese.push_back(buffer);
		dataRead >> buffer;
	}
	cout << "*******您的词库中有以下单词*******" << endl;
	for (int i = 0; i != English.size(); i++)
	{
		setiosflags(ios::left);
		cout << "|" << left << "[" << i + 1 << "]: " << English[i] << " " << Chinese[i] << endl;
	}
	cout << "**********************************" << endl << endl;
	dataRead.close();
}

void Word::wordChange()
{
	int Num;
	int conCg;
	bool enFlag = false;
	Word::wordShow();
	ofstream dataWrite("Data/wordList.rw", ios::out | ios::app);
	if (!dataWrite)
	{
		cerr << "*词库文件打开错误，请重试！*" << endl;
		exit(EXIT_FAILURE);
	}
	cout << endl;
	cout << "|欢迎进入单词替换修改系统。您想修改哪一个单词？请输入单次编号。输入0终止。" << endl;
	cin >> Num;
	while (Num != 0)
	{
		if (enFlag)
		{
			cout << "|您想修改哪一个单词？请输入单词编号。输入0终止。" << endl;
			cin >> Num;
			if (Num == 0)
			{
				break;
			}
		}
		if (Num <= English.size())
		{
			cout << "||您选择的单词是" << " [" << Num << "] " << English[Num - 1] << " " << Chinese[Num - 1] << endl;
			cout << "|||按1确认修改，重新输入请按0。" << endl;
			cin >> conCg;
			if (conCg == 1)
			{
				/*修改单词操作*/
				cout << "||||修改成功！" << endl << endl;
			}
			else if (conCg == 0)
			{
				/*放弃修改操作*/
				cout << "||||您放弃了修改！" << endl << endl;
			}
			else
			{
				cerr << "||||输入错误！" << endl << endl;
			}
		}
		else if (Num > English.size())
		{
			cout << "|您输入的信息有误！请重新输入！" << endl;
			cin >> Num;
		}
		enFlag = true;
	}
	dataWrite.close();
}

void Word::wordDelete()
{
	int Num;
	int conCg;
	bool enFlag = false;
	Word::wordShow();
	ofstream dataWrite("Data/wordList.rw", ios::out | ios::app);
	if (!dataWrite)
	{
		cerr << "*词库文件打开错误，请重试！*" << endl;
		exit(EXIT_FAILURE);
	}
	cout << endl;
	cout << "|欢迎进入单词替换修改系统。您想删除哪一个单词？请输入单次编号。输入0终止。" << endl;
	cin >> Num;
	while (Num != 0)
	{
		if (enFlag)
		{
			cout << "|您想修改哪一个单词？请输入单词编号。输入0终止。" << endl;
			cin >> Num;
			if (Num == 0)
			{
				break;
			}
		}
		if (Num <= English.size())
		{
			cout << "||您选择的单词是" << " [" << Num << "] " << English[Num - 1] << " " << Chinese[Num - 1] << endl;
			cout << "|||按1确认修改，重新输入请按0。" << endl;
			cin >> conCg;
			if (conCg == 1)
			{
				/*删除单词操作*/
				confFile.wordNum = confFile.wordNum - 1;
				cout << "||||删除成功！现在的单词数为： " << confFile.wordNum << endl << endl;
			}
			else if (conCg == 0)
			{
				/*放弃删除操作*/
				cout << "||||您放弃了删除！" << endl << endl;
			}
			else
			{
				cerr << "||||输入错误！" << endl << endl;
			}
		}
		else if (Num > English.size())
		{
			cout << "|您输入的信息有误！请重新输入！" << endl;
			cin >> Num;
		}
		enFlag = true;
	}
	dataWrite.close();
}