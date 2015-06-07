#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fileRead("temp.dat");
	vector<int> num;
	vector<string> en;
	vector<string> cn;
	int numbuffer;
	string enbuffer, cnbuffer;
	while(fileRead >> enbuffer >> cnbuffer >> numbuffer)
	{
		en.push_back(enbuffer);
		cn.push_back(cnbuffer);
		num.push_back(numbuffer);		
	}
	fileRead.close();
	ofstream fileWrite("data.dat", ios::out|ios::binary);
	for(int i = 0; i < cn.size(); i++)
	{
		fileWrite << en[i] << " " << cn[i] << " " << 0 << " ";	//初始化词典
	}
}