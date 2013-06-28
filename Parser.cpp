#include "Parser.h"

Parser::Parser(void)
{
	GrammarInit();
}

Parser::~Parser(void)
{
}

void Parser::GrammarInit(void)
{
	vector<string> row;
	string temp;
	ifstream file("Config.ini", ios::in);
	if (!file) throw "File Config.ini not found...";
	int i = 0;
	while (file) {
		file >> temp;
		++i;
		if (!(i % 2) && temp != "->" && temp != "|") {
			i = 1;
			Grammar.push_back(row);
			row.clear();
		}
		if ((i % 2)) row.push_back(temp);
	}
}

bool Parser::CYKParser(string search)
{
	vector<vector<string>> ROWlvl2;
	vector<string> ROWlvl1;
	ROWlvl2 = StringToVecVecStrConvert(search);
	unsigned int str_lng = search.size();
	CYK.push_back(ROWlvl2);
	ROWlvl2.clear();
	for (unsigned int height = 1; height <= str_lng; ++height)
	{
		for (unsigned int width = 0; width <= str_lng - height; ++width)
		{
			if (height == 1)
			{
				for (unsigned int i = 0; i < Grammar.size(); ++i)
				{
					for (unsigned int j = 1; j < Grammar[i].size(); ++j)
					{
						if (Grammar[i][j] == CYK[0][width][0])
						{
							ROWlvl1.push_back(Grammar[i][0]);
						}
					}
				}
			}
			else 
			{
				for (unsigned int k = 1; k < height; ++k)
				{
					for (unsigned int first = 0; first < CYK[k][width].size(); ++first)
					{
						for (unsigned int second = 0; second < CYK[height-k][width+k].size(); ++second)
						{
							for (unsigned int i = 0; i < Grammar.size(); ++i)
							{
								for (unsigned int j = 1; j < Grammar[i].size(); ++j)
								{
									if (Grammar[i][j] == CYK[k][width][first] + CYK[height-k][width+k][second])
									{
										ROWlvl1.push_back(Grammar[i][0]);
									}
								}
							}
						}
					}
				}
			}
			ROWlvl2.push_back(ROWlvl1);
			ROWlvl1.clear();
		}
		CYK.push_back(ROWlvl2);
		ROWlvl2.clear();
	}
	for (unsigned int i = 0; i < CYK[CYK.size() - 1][0].size(); ++i)
		if (CYK[CYK.size() - 1][0][i] == Grammar[0][0])
			return true;
	return false;
}

vector<vector<string>> Parser::StringToVecVecStrConvert(string search)
{
	vector<vector<string>> ROWlvl2;
	vector<string> ROWlvl1;
	string temp;
	for (unsigned int i = 0; i < search.size(); ++i)
	{
		ROWlvl1.push_back(temp + search[i]);
		ROWlvl2.push_back(ROWlvl1);
		ROWlvl1.clear();
	}
	return ROWlvl2;
}
