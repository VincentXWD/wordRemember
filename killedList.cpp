//killedList.cpp
#include "killedList.h"
#include <fstream>

using namespace std;


__KILLEDLIST::__KILLEDLIST() : __DATABASE()
{
	string enBuffer;
	string cnBuffer;
	int tmBuffer;
	ifstream fileRead("Data/killed.dat");	//打开已斩词典
	if (!fileRead)
	{
		/*提示错误信息*/
		cerr << "找不到斩词文件！" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	vector<wordList>().swap(word);//由于是继承来的，所以在调用子类构造函数时一定会调用父类的。
								  //这时候vector内非空，用这个方法清空vector。
//	word.clear();				  //不可行，得到的值不一定是0（word不一定是空）
//	cout << word.capacity() << endl;
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

__KILLEDLIST::~__KILLEDLIST()
{
	ofstream fileWrite("Data/killed.dat", ios::out);
	for (int i = 0; i < wordSize(); i++)
	{
		fileWrite << word[i].getEnglish() << " " 
				  << word[i].getChinese() << " " 
				  << word[i].getWrongTimes() << endl;
	}
	fileWrite.close();
}
