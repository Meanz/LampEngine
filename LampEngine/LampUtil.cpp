#include "stdafx.h"
#include "LampUtil.hpp"

#include <iostream>
#include <fstream>

LampFileReadResult readFile(std::string filePath)
{
	LampFileReadResult fileReadResult;

	std::ifstream file(filePath.c_str());
	if (!file.is_open())
	{
		fileReadResult.errorString = "File doesn't exist";
		fileReadResult.fileExists = false;
		fileReadResult.readComplete = false;
		return fileReadResult;
	}
	
	std::string str;
	std::string file_contents;
	while (std::getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}

	file.close();

	fileReadResult.fileContents = file_contents;
	fileReadResult.fileExists = true;
	fileReadResult.readComplete = true;
	return fileReadResult;
}