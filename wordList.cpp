//wordList.cpp
#include "wordList.h"

__WORDLIST::__WORDLIST(string en, string cn, int tm = 0) : English(en), Chinese(cn), WrongTimes(tm){}

__WORDLIST::__WORDLIST(string en, string cn) : English(en), Chinese(cn){}

const string &wordList::getEnglish() const
{
	return English;
}

const string &wordList::getChinese() const
{
	return Chinese;

}
const int &wordList::getWrongTimes() const
{
	return WrongTimes;
}

void wordList::changeEnglish(string curEnglish)
{
	English = curEnglish;
}
void wordList::changeChinese(string curChinese)
{
	Chinese = curChinese;
}

void wordList::changeWrongTimes(int curWrongTime)
{
	WrongTimes = curWrongTime;
}

void wordList::addWrongTimes()
{
	WrongTimes++;
}
