#include "OGG.h"

#include <File/PXDataStream.h>
#include <OS/Memory/PXMemory.h>

#define OGGHeaderSignature { 'O','g','g','S' }

#define OGGHeaderTypeContinuation 0x01
#define OGGHeaderTypeBeginningOfStream 0x02
#define OGGHeaderTypeEndOfStream 0x04

PXActionResult OGGParse(OGG* ogg, const void* data, const PXSize dataSize, PXSize* dataRead)
{
	PXDataStream dataStream;

	MemoryClear(ogg, sizeof(OGG));
	*dataRead = 0;
	PXDataStreamConstruct(&dataStream);
	PXDataStreamFromExternal(&dataStream, data, dataSize);

	while(!PXDataStreamIsAtEnd(&dataStream))
	{
		OGGPage page;

		//Check OGG Header
		{
			// Header tag does exist multible times.
			// You can refocus it when the file is corrupted.
			const unsigned char* headerSignature[] = OGGHeaderSignature;
			const PXSize headerSignatureSize = sizeof(headerSignature);
			const unsigned char validHeaderSignature = PXDataStreamReadAndCompare(&dataStream, headerSignature, headerSignatureSize);

			if(!validHeaderSignature)
			{
				printf("Chunk Index missing!\n");
				return PXActionRefusedInvalidHeaderSignature;
			}
		}

		PXDataStreamReadI8U(&dataStream, &page.Version);
		PXDataStreamReadI8U(&dataStream, &page.HeaderType);
		PXDataStreamReadI32UE(&dataStream, &page.GranulePosition, EndianLittle);
		PXDataStreamReadI32UE(&dataStream, &page.SerialNumber, EndianLittle);
		PXDataStreamReadI32UE(&dataStream, &page.SequenceNumber, EndianLittle);
		PXDataStreamReadI32UE(&dataStream, &page.CRC32CheckSum, EndianLittle);
		PXDataStreamReadI8U(&dataStream, &page.PageSegments);

		unsigned char segmentSizeList[0xFF];

		printf
		(
			"|         | %7s | %4s | %8s | %6s | %7s | %11s | %4s |\n"
			"|  Chunk  | %7i | %4i | %8zi | %6i | %7i | %11i | %4i |\n",

			"Version",
			"Type",
			"Position",
			"Serial",
			"Sequenc",
			"CRC",
			"Page",

			page.Version,
			page.HeaderType,
			page.GranulePosition,
			page.SerialNumber,
			page.SequenceNumber,
			page.CRC32CheckSum,
			page.PageSegments
		);

		for(PXSize i = 0; i < page.PageSegments; ++i)
		{
			PXDataStreamReadI8U(&dataStream, &segmentSizeList[i]);

			printf
			(
				"| Segment | %3i/%3i | %3i Bytes %-45s |\n",
				i + 1,
				page.PageSegments,
				segmentSizeList[i],
				""
			);
		}

		for(PXSize i = 0; i < page.PageSegments; ++i)
		{
			unsigned char x = segmentSizeList[i];

			for(PXSize i = 0; i < x; i++)
			{
				unsigned char* currentPos = (unsigned char*)PXDataStreamCursorPosition(&dataStream) + i;

				char print = (*currentPos >= ' ' && *currentPos <= '~') ? *currentPos : '.';

				printf("%c", print);

				if(((i + 1) % 64u) == 0)
				{
					printf("\n");
				}
			}

			printf("\n");

			PXDataStreamCursorAdvance(&dataStream, x);
		}
	}

	*dataRead = dataStream.DataCursor;

	return PXActionSuccessful;
}
