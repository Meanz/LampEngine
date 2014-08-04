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

//Simple structure for a binary file read result
struct LampBinaryFileReadResult
{
	bool readComplete;
	char* bytes;
	int length;
};

//Read the file at the given file path
//Return a LampFileRead structure
LampFileReadResult readFile(std::string filePath);

//Read the file at the given file path
LampBinaryFileReadResult readBinaryFile(std::string filePath);


class LampBinaryBuffer
{

private:
	std::vector<char> dataBuffer;

public:
	LampBinaryBuffer();

	~LampBinaryBuffer();

	unsigned getUInt();
	int getInt();
	char getByte();
	std::string getString();

};