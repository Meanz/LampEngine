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

LampBinaryFileReadResult readBinaryFile(std::string filePath)
{
	LampBinaryFileReadResult fileReadResult;

	std::ifstream file(filePath.c_str());
	if (!file.is_open())
	{
		fileReadResult.readComplete = false;
		return fileReadResult;
	}

	// get length of file:
	file.seekg(0, file.end);
	int length = (int)file.tellg();
	file.seekg(0, file.beg);


	//Otherwise read the tdata
	fileReadResult.length = length;

	//Create our buffer
	fileReadResult.bytes = new char[length];

	//Read into our buffer
	file.read(fileReadResult.bytes, length);

	//Close the file
	file.close();

	//Flag read complete
	fileReadResult.readComplete = true;

	//Return the result!
	return fileReadResult;
}

LampBinaryBuffer::LampBinaryBuffer()
{

}

LampBinaryBuffer::~LampBinaryBuffer()
{

}

char LampBinaryBuffer::getByte()
{
	return 0;
}

int LampBinaryBuffer::getInt()
{
	return 0;
}

unsigned int LampBinaryBuffer::getUInt()
{
	return 0;
}

std::string LampBinaryBuffer::getString()
{
	std::string str = "";
	char c = 0;
	while ((c = getByte()) != '\0') str.append((const char*)c);
	return str;
}