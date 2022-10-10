#ifndef QOIInclude
#define QOIInclude

#include <Format/Type.h>

#include <Error/ActionResult.h>
#include <Format/Image.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Tag Image File Format
	typedef struct TIFF_
	{
		unsigned int __dummy__;
	}
	TIFF;

	PXPublic size_t TIFFFilePredictSize(const size_t width, const size_t height, const size_t bbp);

	PXPublic ActionResult TIFFParse(TIFF* tiff, const void* data, const size_t dataSize, size_t* dataRead);
	PXPublic ActionResult TIFFParseToImage(Image* const image, const void* const data, const size_t dataSize, size_t* dataRead);

	PXPublic ActionResult TIFFSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten);

#ifdef __cplusplus
}
#endif

#endif