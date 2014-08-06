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
	std::vector<char> bytes;
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
	std::vector<char>* m_buffer;
	int m_offset;

public:
	LampBinaryBuffer(std::vector<char>* _dataBuffer);
	~LampBinaryBuffer();

	unsigned getUInt();
	float getFloat();
	double getDouble();
	int64_t getLong();
	int32_t getInt();
	int16_t getShort();
	int8_t getByte();
	void getBytes(char* _array, int length);
	std::string getString();

};