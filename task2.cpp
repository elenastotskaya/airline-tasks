#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <unordered_set>


std::string trimFlightCode(const std::string& code)
{
	static const std::regex codePattern{ R"((?=.{1,7}$)(((?=.{2,3}\d)(([A-Z]\d|[A-Z][A-Z][A-Z]?|\d[A-Z])\ ?))?((?=.{1,5}$)((0*)(\d+)))))" };
	std::smatch match;
	std::regex_match(code, match, codePattern);
	if (match.size()) {
		return match[4].str() + match[8].str();
		//The 4th and 8th substrings refer to the airline code and flight number, without extra spaces or zeros
	}
	else {  //The task does not specify what happens in case of incorrect input
		return "";  //So we simply return an empty string
	}
}

void processFlightCodes(const char* inFileName, const char* outFileName)
{
	if (!inFileName || !outFileName)
	{
		std::cerr << "File name does not exist\n";
		return;
	}
	std::ifstream inFile{ inFileName };
	std::ofstream outFile{ outFileName };
	if (!inFile)
	{
		std::cerr << "Cannot open file " << inFileName << "\n";
		return;
	}
	if (!outFile)
	{
		std::cerr << "Cannot open file " << outFileName << "\n";
		return;
	}

	std::unordered_set<std::string> uniqueFlightCodes;

	for (std::string code; std::getline(inFile, code);)
	{
		code = trimFlightCode(code);
		if (!code.empty()) {  //Ignore empty lines, since correct codes cannot be empty
			uniqueFlightCodes.insert(trimFlightCode(code));
		}
	}

	for (auto iter = uniqueFlightCodes.begin(); iter != uniqueFlightCodes.end(); ++iter) {
		outFile << *iter << "\n";
	}
}

int main()
{
	std::thread secondThread(processFlightCodes, "1_in.txt", "1_out.txt");
	processFlightCodes("2_in.txt", "2_out.txt");
	secondThread.join();
	return 0;
}
