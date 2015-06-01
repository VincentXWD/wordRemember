#include <iostream>
#include <algorithm>
#include <string>
#include "dataBase.h"

__DATABASE::__DATABASE() {}


__DATABASE::~__DATABASE(){}

int DATABASE::wordSize()
{
	return word.size();
}

bool DATABASE::wordIsEmpty()
{
	return wordSize() == 0 ? true : false;
}

void DATABASE::sortWord()
{
	sort(begin(word), end(word), [](const wordList &a, const wordList &b) //±Õ°ü
	{
		return a.getEnglish() < b.getEnglish();
	});
}

void DATABASE::addWord(wordList curwordlist)
{
	word.push_back(curwordlist);
	sortWord();
	return ;
}

int DATABASE::searchWord(string curEnglish)
{
	return 1;
}
