#include "wordList.h"


__WORDLIST::__WORDLIST() {}

__WORDLIST::~__WORDLIST() {}

const string &wordList::getEnglish() const
{
	return English;
}

const string &wordList::getChinese() const
{
	return Chinese;
}

void wordList::changeEnglish(string curEnglish)
{
	English = curEnglish;
	return ;
}
void wordList::changeChinese(string curChinese)
{
	Chinese = curChinese;
	return ;
}