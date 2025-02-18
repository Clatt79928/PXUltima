#ifndef TGAInclude
#define TGAInclude

#include <Media/PXType.h>

#include <OS/Error/PXActionResult.h>
#include <Media/PXImage.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum TGAColorType_
	{
		NoColorMap,
		ColorMapPresent,
		Reserverd,
		Custom
	}
	TGAColorType;

	typedef enum TGABitsPerPixel_
	{
		TGABitsPerPixelInvalid,
		TGABitsPerPixelX1,
		TGABitsPerPixelX8,
		TGABitsPerPixelX15,
		TGABitsPerPixelX16,
		TGABitsPerPixelX24,
		TGABitsPerPixelX32
	}
	TGABitsPerPixel;

	typedef enum TGAImageDataType_
	{
		TGAImageDataInvalid,
		TGAImageDataNoImageDataIsPresent, // 0
		TGAImageDataUncompressedColorMapped, // 1
		TGAImageDataUncompressedTrueColor, // 2
		TGAImageDataUncompressedBlackAndWhite, // 3 (grayscale) image
		TGAImageDataRunLengthEncodedColorMapped,  // 9
		TGAImageDataRunLengthEncodedTrueColor, // 10
		TGAImageDataRunLengthEncodedBlackAndWhite // 11 (grayscale) image 
	}
	TGAImageDataType;

	typedef struct TGA_
	{
		//---[Header]----------------------	
		unsigned char ColorPaletteType;
		TGAImageDataType ImageDataType;

		unsigned short OriginX;
		unsigned short OriginY;
		unsigned short Width;
		unsigned short Height;
		TGABitsPerPixel PixelDepth;
		unsigned char ImageDescriptor;
		//---------------------------------

		//---[Image specification]---------
		PXSize ImageInformationSize;
		char ImageInformation[255]; // Optional field containing identifying information
		PXSize ColorMapDataSize;
		unsigned char* ColorMapData; // Look-up table containing color map data
		PXSize ImageDataSize;
		unsigned char* ImageData; // Stored according to the image descriptor 	
		//----------------------------------


		//---- Versiion 2.0 only----------------
		// Extension Area
		char AuthorName[41]; // Name of the author. If not used, bytes should be set to NULL (\0) or spaces 
		char AuthorComment[324]; // A comment, organized as four lines, each consisting of 80 characters plus a NULL 

		unsigned short DateTimeMonth;// Date and time at which the image was created 
		unsigned short JobTimeDay;
		unsigned short JobTimeYear;
		unsigned short JobTimeHour;
		unsigned short JobTimeMinute;
		unsigned short JobTimeSecond;

		char JobID[41];
		unsigned short JobTimeHours; // spent creating the file (for billing, etc.) 
		unsigned short JobTimeMinutes;
		unsigned short JobTimeSeconds;
		char SoftwareName[41]; // The application that created the file. 
		unsigned short VersionNumber;
		char SoftwareVersion;
		unsigned int BackGroundColor;
		unsigned short PixelAspectRatioCounter;
		unsigned short PixelAspectRatioDenominator;
		unsigned short GammaCounter;
		unsigned short GammaDenominator;

		unsigned int ColorCorrectionOffset; // Number of bytes from the beginning of the file to the color correction table if present
		unsigned int PostagestampOffset; // Number of bytes from the beginning of the file to the postage stamp image if present
		unsigned int ScanlineOffset; // Number of bytes from the beginning of the file to the scan lines table if present 
		unsigned char AttributesType; // Specifies the alpha channel
		//-------------------------------
	}
	TGA;

	static TGABitsPerPixel ConvertToPixelDepth(const unsigned char pixelDepth);
	static unsigned char ConvertFromPixelDepth(const TGABitsPerPixel bitsPerPixel);

	static TGAImageDataType ConvertToImageDataType(const unsigned char id);
	static unsigned char ConvertFromImageDataType(const TGAImageDataType imageDataType);


	PXPublic PXSize TGAFilePredictSize(const PXSize width, const PXSize height, const PXSize bbp);


	PXPublic void TGAConstruct(TGA* const tga); 
	PXPublic void TGADestruct(TGA* const tga);


	PXPublic PXActionResult TGAParse(TGA* tga, const void* data, const PXSize dataSize, PXSize* dataRead);
	PXPublic PXActionResult TGAParseToImage(PXImage* const image, PXDataStream* const dataStream);

	PXPublic PXActionResult TGASerializeFromImage(const PXImage* const image, PXDataStream* const dataStream);

#ifdef __cplusplus
}
#endif

#endif