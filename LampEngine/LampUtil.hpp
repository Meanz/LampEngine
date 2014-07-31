#pragma once
#include "stdafx.h"

//Simple structure for a file read result
struct LampFileReadResult
{
	bool fileExists;
	bool readComplete;
	std::string errorString;
	std::string fileContents;
};

//Read the file at the given file path
//Return a LampFileRead structure
LampFileReadResult readFile(std::string filePath);