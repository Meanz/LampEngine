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

	std::ifstream file(filePath.c_str(), std::ios::in | std::ios::binary);
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
	fileReadResult.bytes.resize(length);

	char* tempBuffer = new char[length];

	//
	file.read(tempBuffer, length);
		
	for (int i = 0; i < length; i++)
	{
		fileReadResult.bytes[i] = tempBuffer[i];
	}

	delete[] tempBuffer;

	//[vector header][vector data]
	//[   0,    1,    2,   3...]
	//[char, char, char char]

	//Close the file
	file.close();

	//Flag read complete
	fileReadResult.readComplete = true;

	//Return the result!
	return fileReadResult;
}

LampBinaryBuffer::LampBinaryBuffer(std::vector<char>* _buffData) :
m_buffer(_buffData),
m_offset(0)
{

}

LampBinaryBuffer::~LampBinaryBuffer()
{

}

int8_t LampBinaryBuffer::getByte()
{
	//Do out of bounds check
	if (m_offset >= m_buffer->size())
	{
		assert(true);
		assert(false);
	}
	return (*m_buffer)[m_offset++];
}

void LampBinaryBuffer::getBytes(char* putInHere, int length)
{
	for (int i = 0; i < length; i++)
	{
		putInHere[i] = getByte();
	}
}

float LampBinaryBuffer::getFloat()
{
	// Given a specific bit pattern (= 2.34):
	int bits = getInt();

	int sign = ((bits & 0x80000000) == 0) ? 1 : -1;
	int exponent = ((bits & 0x7f800000) >> 23);
	int mantissa = (bits & 0x007fffff);

	mantissa |= 0x00800000;
	// Calculate the result:

	float f = (float)(sign * mantissa * pow(2, exponent - 150));

	if (f < FLT_EPSILON)
		return 0.0f;

	return f;
}

double LampBinaryBuffer::getDouble()
{
	char temp[8];
	getBytes(temp, 8);
	int64_t bitPattern = (int64_t)temp;// use this rather than long long because it is explicitly 64 bits
	//printf("%i bitPattern\n", bitPattern);
	//std::cin.get();
	double d = *(double*)&bitPattern;
	return d;
}

int64_t LampBinaryBuffer::getLong()
{
	char temp[8];
	getBytes(temp, 8);
	return (int64_t)(
		(int64_t)(temp[7]) << 56 |
		(int64_t)(temp[6] & 0xff) << 48 |
		(int64_t)(temp[5] & 0xff) << 40 |
		(int64_t)(temp[4] & 0xff) << 32 |
		(int64_t)(temp[3] & 0xff) << 24 |
		(int64_t)(temp[2] & 0xff) << 16 |
		(int64_t)(temp[1] & 0xff) << 8 |
		(int64_t)(temp[0] & 0xff) << 0
		);
}

int LampBinaryBuffer::getInt()
{
	char temp[4];
	getBytes(temp, 4);
	return (
		(temp[3] & 0xff) << 24 |
		(temp[2] & 0xff) << 16 |
		(temp[1] & 0xff) << 8 |
		(temp[0] & 0xff)
		);
}

int16_t LampBinaryBuffer::getShort()
{
	char temp[2];
	getBytes(temp, 2);
	return (int16_t)(
		(int16_t)(temp[1] & 0xff) << 8 |
		(int16_t)(temp[0] & 0xff) << 0
		);
}

unsigned int LampBinaryBuffer::getUInt()
{
	return 0;
}

std::string LampBinaryBuffer::getString()
{
	std::string str = "";
	char c = 0;
	while ((c = getByte()) != '\0') str += c;
	return str;
}