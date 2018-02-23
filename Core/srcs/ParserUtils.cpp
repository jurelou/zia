//
// Created by fumery on 02/02/18.
//

#include "ParserUtils.hpp"

ParserUtils::ParserUtils() {
}

ParserUtils::~ParserUtils() {
	
}

std::string ParserUtils::extract(const std::string& str, const char *beg, const char *end) //utils
{
    std::size_t begPos;
    if ( (begPos = str.find(beg)) != std::string::npos )
    {
        std::size_t endPos ;
		if ((endPos = str.find(end, begPos)) != std::string::npos && endPos != begPos+1 )
            return str.substr(begPos+1, endPos-begPos-1) ;
    }

    return std::string();
}

std::string ParserUtils::getFragment(std::string all, std::string begin, std::string end) //utils
{
	all.erase(0, 1);
	int cmp = 0;
	int c = all.find(begin);
	std::string Frag;
	bool finder = false;
	std::string tmp;

	while (!finder)
	{
		tmp = all[c];
		if (all[c] == end[0])
			cmp--;
		else if (all[c] == begin[0])
			cmp++;
		if (cmp == 0)
		{
			Frag.append(tmp);
			return Frag;
		}
		if (all[c+1] == '\0')
			return Frag;
		Frag.append(tmp);
		c++;
	}
	return Frag;
}

int ParserUtils::getEnd(std::string all, std::string begin, std::string end) //utils
{
	int cmp = 0;
	int c = all.find(begin);
	bool finder = false;

	while (!finder)
	{
		if (all[c] == end[0])
			cmp--;
		else if (all[c] == begin[0])
			cmp++;
		if (cmp == 0)
			finder = true;
		c++;
	}
	return c;
}

bool ParserUtils::CheckStr(std::string All) //utils
{
	if (extract(All, "\"", "\0").find(",") == All.npos && extract(All, "\"", "\0").find("{") != All.npos && extract(All, "\"", "\0").find("[") != All.npos)
		return false;

	return (extract(All, "\"", ",").find("{") == All.npos &&
			extract(All, "\"", ",").find("[") == All.npos);
}

template<typename T, typename P>
T ParserUtils::rmSpc(T start, T end, P p) //utils
{
	T toRet = start;
	for (T cmp = start; cmp != end ; ++cmp) {
		if (!p(*cmp))
			*(toRet++) = *cmp;
	}
	return toRet;
}

std::string ParserUtils::ClearIt(std::string str) //utils
{
	str.erase(rmSpc(str.begin(), str.end(), isspace), str.end());
	return str;
}

bool ParserUtils::CheckFile(std::string All)
{
	All = ClearIt(All);
	if (All[0] != '{' || All[All.length()-1] != '}')
		return false;
	return true;
}