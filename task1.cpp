#include <regex>
#include <iostream>

void printMatch(std::smatch& match)
{
	std::cout << match.size() << "\n";
	for (std::size_t i = 0; i < match.size(); ++i)
	{
		std::ssub_match sub_match = match[i];
		std::string piece = sub_match.str();
		std::cout << "  submatch " << i << ": " << piece << "#\n";
	}
}

bool areFlightCodesEqual(const std::string & code1, const std::string & code2)
{
	static const std::regex codePattern{ R"((?=.{1,7}$)(((?=.{2,3}\d)(([A-Z]\d|[A-Z][A-Z][A-Z]?|\d[A-Z])\ ?))?((?=.{1,5}$)((0*)(\d+)))))" };
	std::smatch match1, match2;
	std::regex_match(code1, match1, codePattern);
	std::regex_match(code2, match2, codePattern);

	// uncomment for debug
	//printMatch(match1);
	//printMatch(match2);

	if (match1.size() && match2.size()) {
		return match1[4].str() == match2[4].str() && match1[8].str() == match2[8].str();
		//The 4th and 8th substrings refer to the airline code and flight number, without extra spaces or zeros
	}
	else {
		std::cerr << "Incorrect flight code\n";
		return false;
	}
}

int main()
{
	std::string test1("A31");
	std::string test2("A3 001");
	std::cout << areFlightCodesEqual(test1, test2);
}