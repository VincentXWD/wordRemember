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
	while(fileRead >> numbuffer >> enbuffer >> cnbuffer)
	{
		num.push_back(numbuffer);
		en.push_back(enbuffer);
		cn.push_back(cnbuffer);
	}
	fileRead.close();
	ofstream fileWrite("data.dat", ios::out);
	for(int i = 0; i < cn.size(); i++)
	{
		fileWrite << en[i] << " " << cn[i] << endl;
	}
}