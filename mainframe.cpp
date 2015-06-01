#include "mainframe.h"
#include <random>
#include <algorithm>
#include <iomanip>

__MAINFRAME::__MAINFRAME() {}

__MAINFRAME::~__MAINFRAME() {}

void mainFrame::wordInit()		//��ʼ������
{

}

void mainFrame::wordInput()	//¼���µ���
{
	string curEnglish;
	string curChinese;
	/*�����ʾ��Ϣ���������� Ӣ�ĵ���*/
	if (dataBase.searchWord(curEnglish) >= 0)	//����
	{
		/*��ʾ�����Ѵ��ڣ�����Ҫ����,����*/
	}
	else
	{
		/*�����ʾ��Ϣ���������� ���ĵ���*/
		wordList* __BUFFER = new wordList(curEnglish, curChinese);
		dataBase.addWord(*__BUFFER);
		delete __BUFFER;
		/*����ɹ����ӵ��ʵ���Ϣ*/

		//  ����� delete[]�����ڻ��տռ�֮ǰ���ж��󶼻����ȵ����Լ�������������
		//	�������͵Ķ���û���������������Ի��ջ���������ɵ�����ռ��� delete �� delete[] ����Ӧ�ÿ��Եģ�
		//  ���Ƕ�����������飬ֻ���� delete[]��
		//  ���� new �ĵ�������ֻ���� delete ������ delete[] ���տռ䡣
	}
	return ;
}

void mainFrame::wordShow()	//��ʾ�ʵ�
{
	//int LEN = dataBase.wordSize();
	/*�����ʾ��Ϣ���鿴�굥�ʱ�����ر�*/
	//for (int i = 0; i < LEN; i++)
	//{
	//	wordList BUFFER;
	//	BUFFER = dataBase.getWord(i);
	//	cout << BUFFER.getEnglish() << " " << BUFFER.getChinese() << endl;
	//}
	cout << "wordNum: " << dataBase.wordSize() << endl;
	system("notepad Data\\dictionary.dat");	//��ȡ�ļ�
	return ;
}

void mainFrame::sortWord()	//��������
{
	dataBase.sortWord();
	return ;
}
void mainFrame::wordChange()	//�޸ĵ���
{
	string curEnglish;
	string curChinese;
	int Num;
	/*�����ʾ��Ϣ����������Ҫ�޸ĵĵ���*/
//	cin >> curEnglish;
	if(dataBase.searchWord(curEnglish) < 0)
	{
		/*��ʾ���ʲ����ڣ�������󣬷���*/
//		cout << "no" << endl;
	}
	else
	{
		/*�����ʾ��Ϣ�����뵥�ʵ�����*/
//		cout << "yes!" << endl;
		cin >> curEnglish >> curChinese;
		Num = dataBase.searchWord(curEnglish) + 1;
		wordList BUFFER(curEnglish, curChinese);
		dataBase.changeWordNum(Num, BUFFER);
		/*��ʾ�޸ĳɹ�*/
	}
}

void mainFrame::wordDelete()	//ɾ������
{
	string curEnglish;
	string curChinese;
	int Num;
	/*�����ʾ��Ϣ����������Ҫɾ���ĵ���*/
//	cin >> curEnglish;
	if (dataBase.searchWord(curEnglish) < 0)	//������
	{
		/*��ʾ���ʲ����ڣ��������,����*/
	}
	else
	{
		Num = dataBase.searchWord(curEnglish) + 1;
		dataBase.removeWord(Num);
		/*��ʾ����ɾ���ɹ�*/
	}
	return;
}

void mainFrame::wordExercise()//������
{

}

void mainFrame::wordExam()
{
	random_device rd;
	uniform_int_distribution<int> dicSeed(1, dataBase.wordSize() - 1);	//���ɴӴʵ�ȡ���ʵ������������
	uniform_int_distribution<int> ansSeed(0, 3);
	dicSeed(rd);
	wordList optAns[4];	//�洢�ĸ���ѡ��
	string answer;	//������Ŵ�
	int ansNum, chsNum;
	int score = 0, count = 1;
	int range;	//������Ŀ
	double ratio;
	cout << "��ӭ����С����ģʽ����ϣ�������������أ�   ";	//�����ĳɿ�ѡ
	cin >> range;
	cout << endl;
	for (int i = 0; i < range; i++)
	{
		for (int i = 0; i < 4; i++)	//���ĸ��𰸸�ֵ
		{
			optAns[i] = dataBase.getWord(dicSeed(rd));
		}
		ansNum = ansSeed(rd);	//���������
		for (int i = 0; i < 4; i++)
		{
			cout << i+1 << ": " << left << setw(10) << optAns[i].getEnglish();
			if ((i+1) % 2 == 0)
			{
				cout << endl;
			}
		}
		cout << "Round " << count++ << ": ��ѡ��Ӣ��Ϊ\"" << optAns[ansNum].getChinese() << "\"�ĵ��ʡ�    ";
		
		cin >> chsNum;
		chsNum--;	//ƥ��������ϰ��
		if (chsNum == ansNum)
		{
			score++;
			cout << "������" << endl;
		}
		else
		{
			cout << "�Բ��������ˡ�" << endl;
		}
	}
	ratio = double(score) / double(range);
	cout << "���Խ�������һ������ " << score << "��" << "��ȷ��Ϊ " << ratio*100 <<"%�����ٽ�������" << endl;
}

void mainFrame::wordExit()	//�˳�������
{
	exit(EXIT_SUCCESS);
}