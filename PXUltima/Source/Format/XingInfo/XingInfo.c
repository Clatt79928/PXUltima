#include "XingInfo.h"

#include <File/DataStream.h>

ActionResult XingInfoParse(XingInfo* xingInfo, const void* data, const PXSize dataSize, PXSize* dataRead)
{
	DataStream dataStream;

	DataStreamConstruct(&dataStream);
	DataStreamFromExternal(&dataStream, data, dataSize);

	*dataRead = 0;

	// parse signature
	{
		const char infoTag[] = { 'I', 'n', 'f', 'o' };
		const char xingTag[] = { 'X', 'i', 'n', 'g' };
		char indetifier[4];

		DataStreamReadP(&dataStream, indetifier, 4u);

		const unsigned char isInfo =
			indetifier[0] == infoTag[0] &&
			indetifier[1] == infoTag[1] &&
			indetifier[2] == infoTag[2] &&
			indetifier[3] == infoTag[3];

		const unsigned char isXing =
			indetifier[0] == xingTag[0] &&
			indetifier[1] == xingTag[1] &&
			indetifier[2] == xingTag[2] &&
			indetifier[3] == xingTag[3];

		const unsigned char validHeader = isInfo || isXing;

		if(!validHeader)
		{
			return ActionInvalidHeaderSignature;
		}

		if(isInfo)
		{
			xingInfo->Version = XingInfoVersionInfo;
		}

		if(isXing)
		{
			xingInfo->Version = XingInfoVersionXing;
		}
	}

	unsigned int flags = 0;

	DataStreamReadIU(&dataStream, &flags, EndianBig);

	const unsigned char hasNumberOfFrames = flags & 0b00000001;
	const unsigned char hasSizeInBytes = (flags & 0b00000010) >> 1;
	const unsigned char hasTOCData = (flags & 0b00000100) >> 2;
	const unsigned char hasVBRScale = (flags & 0b00001000) >> 3;

	// (0x0001) if set, then read one 32 bit integer in Big Endian.
	// It represents the total number of frames in the Audio file.
	if(hasNumberOfFrames)
	{
		DataStreamReadIU(&dataStream, &xingInfo->NumberOfFrames, EndianBig);
	}

	// (0x0002) is set, then read one 32 bit integer in Big Endian. 
	// It represents the total number of bytes of MPEG Audio in the file. 
	// This does not include the ID3 tag, however, it includes this very tag.
	if(hasSizeInBytes)
	{
		DataStreamReadIU(&dataStream, &xingInfo->SizeInBytes, EndianBig);
	}

	if(hasTOCData)
	{
		DataStreamReadP(&dataStream, &xingInfo->TOCBuffer, XingInfoTOCBufferSize);
	}

	if(hasVBRScale)
	{
		DataStreamReadIU(&dataStream, &xingInfo->VBRScale, EndianBig);
	}

	*dataRead = dataStream.DataCursor;

	return ActionSuccessful;
}