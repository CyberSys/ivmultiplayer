#include "Base64Encoder.h"
#include "RakMemoryOverride.h"

const char *Base64Map(void) {return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";}

int Base64Encoding(const char *inputData, int dataLength, char *outputData)
{
	// http://en.wikipedia.org/wiki/Base64

	int outputOffset, charCount;
	int write3Count;
	outputOffset=0;
	charCount=0;
	int j;

	write3Count=dataLength/3;
	for (j=0; j < write3Count; j++)
	{
		// 6 leftmost bits from first byte, shifted to bits 7,8 are 0
		outputData[outputOffset++]=Base64Map()[inputData[j*3+0] >> 2];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
		outputData[outputOffset++]=Base64Map()[((inputData[j*3+0] << 4) | (inputData[j*3+1] >> 4)) & 63];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// 4 low bits from the second byte and the two high bits from the third byte, masked to ignore bits 7,8
		outputData[outputOffset++]=Base64Map()[((inputData[j*3+1] << 2) | (inputData[j*3+2] >> 6)) & 63]; // Third 6 bits
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Last 6 bits from the third byte, masked to ignore bits 7,8
		outputData[outputOffset++]=Base64Map()[inputData[j*3+2] & 63];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}
	}

	if (dataLength % 3==1)
	{
		// One input byte remaining
		outputData[outputOffset++]=Base64Map()[inputData[j*3+0] >> 2];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
		outputData[outputOffset++]=Base64Map()[((inputData[j*3+0] << 4) | (inputData[j*3+1] >> 4)) & 63];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Pad with two equals
		outputData[outputOffset++]='=';
		outputData[outputOffset++]='=';
	}
	else if (dataLength % 3==2)
	{
		// Two input bytes remaining

		// 6 leftmost bits from first byte, shifted to bits 7,8 are 0
		outputData[outputOffset++]=Base64Map()[inputData[j*3+0] >> 2];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
		outputData[outputOffset++]=Base64Map()[((inputData[j*3+0] << 4) | (inputData[j*3+1] >> 4)) & 63];
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// 4 low bits from the second byte, followed by 00
		outputData[outputOffset++]=Base64Map()[(inputData[j*3+1] << 2) & 63]; // Third 6 bits
		if ((++charCount % 76)==0) {outputData[outputOffset++]='\r'; outputData[outputOffset++]='\n'; charCount=0;}

		// Pad with one equal
		outputData[outputOffset++]='=';
		//outputData[outputOffset++]='=';
	}

	// Append \r\n
	outputData[outputOffset++]='\r';
	outputData[outputOffset++]='\n';
	outputData[outputOffset]=0;

	return outputOffset;
}

int Base64Encoding(const char *inputData, int dataLength, char **outputData)
{
	*outputData = (char*) rakMalloc_Ex(dataLength * 2 + 6, _FILE_AND_LINE_);
	return Base64Encoding(inputData, dataLength, *outputData);
}
