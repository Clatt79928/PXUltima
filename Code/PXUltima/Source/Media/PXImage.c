#include "PXImage.h"

#include <OS/Memory/PXMemory.h>
#include <Media/PXText.h>
#include <Math/PXMath.h>

#include <Media/Bitmap/PXBitmap.h>
#include <Media/GIF/GIF.h>
#include <Media/JPEG/JPEG.h>
#include <Media/PNG/PXPNG.h>
#include <Media/TGA/TGA.h>
#include <Media/TIFF/TIFF.h>
#include <Media/SpriteFont/PXSpriteFont.h>
#include <Media/PXFont.h>

void PXImageConstruct(PXImage* const image)
{
    MemoryClear(image, sizeof(PXImage));
}

void PXImageDestruct(PXImage* const image)
{
    MemoryRelease(image->PixelData, image->PixelDataSize);

    PXImageConstruct(image);
}

PXActionResult PXImageLoadA(PXImage* const image, const PXTextASCII filePath)
{
    PXByte filePathU[PathMaxSize];

    PXTextCopyAU(filePath, PathMaxSize, filePathU, PathMaxSize);

    PXActionResult actionResult = PXImageLoadU(image, filePathU);

    return actionResult;
}

PXActionResult PXImageLoadW(PXImage* const image, const PXTextUNICODE filePath)
{
    PXByte filePathU[PathMaxSize];

    PXTextCopyWU(filePath, PathMaxSize, filePathU, PathMaxSize);

    PXActionResult actionResult = PXImageLoadU(image, filePathU);

    return actionResult;
}

PXActionResult PXImageLoadU(PXImage* const image, const PXTextUTF8 filePath)
{
    PXDataStream dataStream;

    PXDataStreamConstruct(&dataStream);
    PXImageConstruct(image);

    {
        const PXActionResult fileLoadingResult = PXDataStreamMapToMemoryU(&dataStream, filePath, 0, MemoryReadOnly);

        PXActionExitOnError(fileLoadingResult);
    }

    dataStream.FilePath = filePath;

    {
        {
            const FileFormatExtension imageForPXMathint = FilePathExtensionDetectTryA(filePath, PathMaxSize); // Potential error
            const PXActionResult fileParsingResult = PXImageLoadD(image, &dataStream, imageForPXMathint);

            PXActionExitOnSuccess(fileParsingResult);
        }



        PXActionResult fileGuessResult = PXActionInvalid;
        unsigned int fileFormatID = 1;

        do
        {
            const FileFormatExtension imageFileFormat = fileGuessResult + fileFormatID;

            fileGuessResult = PXImageLoadD(image, &dataStream, imageFileFormat);

            fileFormatID++;
        }
        while(fileGuessResult == PXActionRefusedInvalidHeaderSignature);

        PXDataStreamDestruct(&dataStream);

        return fileGuessResult;
    }
}

PXActionResult PXImageLoadD(PXImage* const image, PXDataStream* const dataStream, const FileFormatExtension guessedFormat)
{
    PXSize bytesRead = 0;
    PXImageTranslateFunction parseToImage = 0;

    switch(guessedFormat)
    {
        case FileFormatBitMap:
        {
            parseToImage = PXBitmapParseToImage;
            break;
        }
        case FileFormatGIF:
        {
            parseToImage = GIFParseToImage;
            break;
        }
        case FileFormatJPEG:
        {
            parseToImage = JPEGParseToImage;
            break;
        }
        case FileFormatPNG:
        {
            parseToImage = PXPNGParseToImage;
            break;
        }
        case FileFormatTGA:
        {
            parseToImage = TGAParseToImage;
            break;
        }
        case FileFormatTagImage:
        {
            parseToImage = TIFFParseToImage;
            break;
        }
        default:
        {
            return PXActionRefusedFormatNotSupported;
        }
    }

    const PXActionResult actionResult = parseToImage(image, dataStream);

    return actionResult;
}

PXActionResult PXImageSaveA(PXImage* const image, const PXTextASCII filePath, const FileFormatExtension fileFormat, const PXColorFormat pxColorFormat)
{
    PXByte filePathU[PathMaxSize];

    PXTextCopyAU(filePath, PathMaxSize, filePathU, PathMaxSize);

    PXActionResult actionResult = PXImageSaveU(image, filePathU, fileFormat, pxColorFormat);

    return actionResult;
}

PXActionResult PXImageSaveW(PXImage* const image, const PXTextUNICODE filePath, const FileFormatExtension fileFormat, const PXColorFormat pxColorFormat)
{
    PXByte filePathU[PathMaxSize];

    PXTextCopyWU(filePath, PathMaxSize, filePathU, PathMaxSize);

    PXActionResult actionResult = PXImageSaveU(image, filePathU, fileFormat, pxColorFormat);

    return actionResult;
}

PXActionResult PXImageSaveU(PXImage* const image, const PXTextUTF8 filePath, const FileFormatExtension fileFormat, const PXColorFormat pxColorFormat)
{
    PXByte filePathW[PathMaxSize];
    PXByte* fileExtension = 0;

    PXSize fileSize = 0;
    PXSize writtenBytes = 0;
    PXDataStream dataStream;

    PXImageTranslateFunction serializeFromImageFunction = 0;

    PXDataStreamConstruct(&dataStream);

    const PXInt8U bitPerPixel = PXColorFormatBitsPerPixel(pxColorFormat);

    switch (fileFormat)
    {
        case FileFormatBitMap:
        {
            fileSize = PXBitmapFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = PXBitmapSerializeFromImage;
            fileExtension = "bmp";
            break;
        }
        case FileFormatPNG:
        {
            fileSize = PXPNGFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = PXPNGSerializeFromImage;
            fileExtension = "png";
            break;
        }
        case FileFormatTGA:
        {
            fileSize = TGAFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = TGASerializeFromImage;
            fileExtension = "tga";
            break;
        }
        case FileFormatJPEG:
        {
            fileSize = JPEGFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = JPEGSerializeFromImage;
            fileExtension = "jpg";
            break;
        }
        case FileFormatTagImage:
        {
            fileSize = TIFFFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = TIFFSerializeFromImage;
            fileExtension = "tiff";
            break;
        }
        case FileFormatGIF:
        {
            fileSize = GIFFilePredictSize(image->Width, image->Height, bitPerPixel);
            serializeFromImageFunction = GIFSerializeFromImage;
            fileExtension = "gif";
            break;
        }
        default:
            return PXActionRefusedFormatNotSupported;
    }


    // Chnage file extension
    {
        FilePathSwapExtensionU(filePath, filePathW, fileExtension);
    }

    {
        const PXActionResult mappingResult = PXDataStreamMapToMemoryU(&dataStream, filePathW, fileSize, MemoryWriteOnly);
        const PXBool sucessful = PXActionSuccessful == mappingResult;

        if (!sucessful)
        {
            PXDataStreamDestruct(&dataStream);
            return mappingResult;
        }
    }

    {
        const PXActionResult serializeResult = serializeFromImageFunction(image, &dataStream);
        const PXBool sucessful = PXActionSuccessful == serializeResult;

        if (!sucessful)
        {
            PXDataStreamDestruct(&dataStream);
            return serializeResult;
        }
    }

    PXDataStreamDestruct(&dataStream);

    return PXActionSuccessful;
}

PXActionResult PXImageSaveD(PXImage* const image, PXDataStream* const pxDataStream, const FileFormatExtension fileFormat, const PXColorFormat dataFormat)
{
    return PXActionInvalid;
}

PXBool PXImageResize(PXImage* const image, const PXColorFormat dataFormat, const PXSize width, const PXSize height)
{
    const PXSize bbp = PXColorFormatBytePerPixel(dataFormat);
    const PXSize newSize = width * height * bbp;
    const PXSize oldSize = image->PixelDataSize;

    // Do we need to realloc?
    {
        const PXBool isSizeAlreadyOK = newSize == oldSize;

        if (isSizeAlreadyOK)
        {
            return PXYes;
        }
    }

    // reallocate
    {
        const void* newadress = MemoryReallocate(image->PixelData, sizeof(PXByte) * newSize);

        if (!newadress)
        {
            return PXFalse;
        }

        image->Format = dataFormat;
        image->Width = width;
        image->Height = height;
        image->PixelData = newadress;
        image->PixelDataSize = newSize;
    }

    return PXTrue;
}

void PXImageFlipHorizontal(PXImage* image)
{
    const PXSize bbp = PXColorFormatBytePerPixel(image->Format);
    const PXSize rowSize = (image->Width * bbp);
    const PXSize length = (image->Width * bbp) / 2;

    for(PXSize x = 0; x < length; x += bbp) //
    {
        const PXSize xB = rowSize - x - bbp;

        for(PXSize y = 0; y < image->Height; y++)
        {
            const PXSize indexA = x + (y * rowSize);
            const PXSize indexB = xB + (y * rowSize);
            unsigned char tempByte[4] = { 0,0,0,0 };
            unsigned char* pixelA = (unsigned char*)image->PixelData + indexA;
            unsigned char* pixelB = (unsigned char*)image->PixelData + indexB;

            MemoryCopy(pixelA, 4, tempByte, bbp);
            MemoryCopy(pixelB, 4, pixelA, bbp);
            MemoryCopy(tempByte, 4, pixelB, bbp);
        }
    }
}

void PXImageFlipVertical(PXImage* image)
{
    const PXSize bbp = PXColorFormatBytePerPixel(image->Format);;
    const PXSize scanLineWidthSize = image->Width * bbp;
    const PXSize scanLinesToSwap = image->Height / 2u;
    unsigned char* copyBufferRow = MemoryAllocate(sizeof(unsigned char) * scanLineWidthSize);

    if(!copyBufferRow)
    {
        return;
    }

    for(PXSize scanlineIndex = 0; scanlineIndex < scanLinesToSwap; scanlineIndex++)
    {
        unsigned char* bufferA = (unsigned char*)image->PixelData + (scanlineIndex * scanLineWidthSize);
        unsigned char* bufferB = (unsigned char*)image->PixelData + ((image->Height - scanlineIndex) * scanLineWidthSize) - scanLineWidthSize;

        MemoryCopy(bufferB, scanLineWidthSize, copyBufferRow, scanLineWidthSize); // A -> Buffer 'Save A'
        MemoryCopy(bufferA, scanLineWidthSize, bufferB, scanLineWidthSize); // B -> A 'Move B to A(override)'
        MemoryCopy(copyBufferRow, scanLineWidthSize, bufferA, scanLineWidthSize); // Buffer -> B 'Move SaveCopy (A) to B'
    }

    MemoryRelease(copyBufferRow, scanLineWidthSize);
}

void PXImageRemoveColor(PXImage* image, unsigned char red, unsigned char green, unsigned char blue)
{
    // DO we have alpha? If not, make one

    const PXSize currentOffset = image->PixelDataSize;
    PXSize dataOffset = 0;

    PXImageResize(image, PXColorFormatRGBAI8, image->Width, image->Height);

    dataOffset = image->PixelDataSize;

    const PXSize length = image->Width * image->Height;

    for (PXSize pixelIndex = 0; pixelIndex < length; ++pixelIndex)
    {
        PXByte* const oldData = (PXByte*)image->PixelData + currentOffset - ((pixelIndex + 1) * 3u);
        PXByte* const newData = (PXByte*)image->PixelData + dataOffset - ((pixelIndex + 1) * 4u);

        newData[0] = oldData[0];
        newData[1] = oldData[1];
        newData[2] = oldData[2];
        newData[3] = !(oldData[0] == red) && (oldData[1] == green) && (oldData[2] == blue);
    }
}

void PXImageFillColorRGBA8(PXImage* const image, const PXByte red, const PXByte green, const PXByte blue, const PXByte alpha)
{
    for (PXSize i = 0; i < image->PixelDataSize; i += 4u)
    {
        unsigned char* const data = (unsigned char*)image->PixelData + i;

        data[0] = red;
        data[1] = green;
        data[2] = blue;
        data[3] = alpha;
    }
}

void* PXImageDataPoint(const PXImage* const image, const PXSize x, const PXSize y)
{
    const PXSize bytesPerPixel = PXColorFormatBytePerPixel(image->Format);
    const PXSize index = x * bytesPerPixel + y * image->Width;

    return (unsigned char*)image->PixelData + index;
}

PXSize PXImagePixelPosition(const PXImage* const image, const PXSize x, const PXSize y)
{
    const PXSize bytesPerPixel = PXColorFormatBitsPerPixel(image->Format);
    const PXSize index = x * bytesPerPixel + y * bytesPerPixel * image->Width;

    return index;
}

void PXImagePixelSetRGB8
(
    PXImage* const image,
    const PXSize x,
    const PXSize y,
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue
)
{
    const PXSize index = PXImagePixelPosition(image, x, y);
    unsigned char* const pixelData = (unsigned char* const)image->PixelData + index;

    pixelData[0] = red;
    pixelData[1] = green;
    pixelData[2] = blue;
}