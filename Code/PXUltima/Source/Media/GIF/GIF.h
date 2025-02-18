#ifndef GIFInclude
#define GIFInclude

#include <Media/PXType.h>

#include <OS/Error/PXActionResult.h>
#include <Media/PXImage.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct GIFImageDescriptor_
	{
		unsigned char Separator;
		unsigned short LeftPosition;
		unsigned short TopPosition;
		unsigned short Width;
		unsigned short Height;
		unsigned char LocalColorTableSize;
		unsigned char Reserved;
		unsigned char SortFlag;
		unsigned char InterlaceFlag;
		unsigned char LocalColorTableFlag;
	}
	GIFImageDescriptor;

	typedef struct GIF_
	{
		unsigned short Width;
		unsigned short Height;

		unsigned char GlobalColorTableSize;
		unsigned char IsSorted;
		unsigned char ColorResolution;
		unsigned char IsGlobalColorTablePresent;

		unsigned char BackgroundColorIndex;
		unsigned char PixelAspectRatio;
	}
	GIF;

	PXPublic PXSize GIFFilePredictSize(const PXSize width, const PXSize height, const PXSize bbp);

	PXPublic PXActionResult GIFParseToImage(PXImage* const image, PXDataStream* const dataStream);

	PXPublic PXActionResult GIFSerializeFromImage(const PXImage* const image, PXDataStream* const dataStream);

#ifdef __cplusplus
}
#endif

#endif