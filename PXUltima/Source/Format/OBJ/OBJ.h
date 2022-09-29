#ifndef OBJInclude
#define OBJInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <Format/MTL/MTL.h>
#include <File/DataStream.h>
#include <Format/Model.h>

#define OBJNameSize 64u
#define OBJElementNameLength 50u
#define OBJDebug 0

#ifdef __cplusplus
extern "C"
{
#endif	

	typedef enum OBJLineType_
	{
		OBJLineInvalid,
		OBJLineNone,
		OBJLineComment,
		OBJLineMaterialLibraryInclude,
		OBJLineMaterialLibraryUse,
		OBJLineObjectName,
		OBJLineObjectGroup,
		OBJLineVertexGeometric,
		OBJLineVertexTexture,
		OBJLineVertexNormal,
		OBJLineVertexParameter,
		OBJLineSmoothShading,
		OBJLineFaceElement,
	}
	OBJLineType;

	typedef struct OBJElementMaterialInfo_
	{
		size_t MaterialIndex;
		size_t Size; // Size of buffer to use given material		
	}
	OBJElementMaterialInfo;

	typedef struct OBJElement_
	{
		char Name[OBJElementNameLength];
		float Smoothing;

		OBJElementMaterialInfo* MaterialInfo;
		size_t MaterialInfoSize;

		size_t VertexPositionListSize;
		float* VertexPositionList; 	// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.

		size_t TextureCoordinateListSize;
		float* TextureCoordinateList; 	// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.

		size_t VertexNormalPositionListSize;
		float* VertexNormalPositionList; 	// List of vertex normals in (x,y,z) form; normals might not be unit vectors.

		size_t VertexParameterListSize;
		float* VertexParameterList; // Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.

		size_t FaceElementListSize;
		unsigned int* FaceElementList; // Polygonal face element.	
	}
	OBJElement;

	extern void OBJElementConstruct(OBJElement* objElement);
	extern void OBJElementDestruct(OBJElement* objElement);

	// [.OBJ] Wavefront - 3D model format
	typedef struct OBJ_
	{
		wchar_t Name[OBJNameSize];
		unsigned char VertexStructureSize;

		size_t MaterialFileListSize;
		MTL* MaterialFileList;

		size_t ElementListSize;
		OBJElement* ElementList;
	}
	OBJ;

	CPublic void OBJConstruct(OBJ* const obj);
	CPublic void OBJDestruct(OBJ* const obj);

	CPrivate OBJLineType OBJPeekLine(const void* line, const size_t size);

	CPublic ActionResult OBJFileParse(DataStream* const inputStream, DataStream* const outputStream);

	CPublic ActionResult OBJParseToModel(DataStream* const inputStream, Model* const model);


	CPublic ActionResult OBJParseEEE(OBJ* obj, const void* data, const size_t dataSize, size_t* dataRead, const wchar_t* fileName);

#ifdef __cplusplus
}
#endif

#endif