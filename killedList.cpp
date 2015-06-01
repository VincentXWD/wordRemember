#include "killedList.h"
#include <fstream>
using namespace std;


__KILLEDLIST::__KILLEDLIST()
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
	sortWord();
	while (fileRead >> enBuffer >> cnBuffer)	//硬盘文件转入内存
	{
		wordlist.changeChinese(cnBuffer);
		wordlist.changeEnglish(enBuffer);
		word.push_back(wordlist);				//扔入容器中以备操作
	}
	fileRead.close();
}


__KILLEDLIST::~__KILLEDLIST() {}
