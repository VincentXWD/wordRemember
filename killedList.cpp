#include "killedList.h"
#include <fstream>

using namespace std;


__KILLEDLIST::__KILLEDLIST() : __DATABASE()
{
	string enBuffer;
	string cnBuffer;
	ifstream fileRead("Data/killed.dat");	//打开已斩词典
	if (!fileRead)
	{
		/*提示错误信息*/
		cerr << "找不到斩词文件！" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	vector<wordList>().swap(word);
//	word.clear();
//	cout << word.capacity() << endl;
	sortWord();
	while (fileRead >> enBuffer >> cnBuffer)	//硬盘文件转入内存
	{
		wordlist.changeChinese(cnBuffer);
		wordlist.changeEnglish(enBuffer);
		word.push_back(wordlist);				//扔入容器中以备操作
	}
	fileRead.close();
}

__KILLEDLIST::~__KILLEDLIST()
{
	ofstream fileWrite("Data/killed.dat", ios::out);
	for (int i = 0; i < wordSize(); i++)
	{
		fileWrite << word[i].getEnglish() << " " << word[i].getChinese() << endl;
	}
	fileWrite.close();
}
