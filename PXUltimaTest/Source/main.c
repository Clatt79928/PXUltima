
#include <stdio.h>

#include "TestSystemInfo.h"
#include "Graphic/TestWindow.h"
#include "Graphic/TestOpenGL.h"
#include "Graphic/TestFont.h"
#include "Compiler/TestPXCompiler.h"
#include "Graphic/TestImage.h"
#include "Compiler/TestYAML.h"
#include "Sound/TestSound.h"
#include "Network/TestSocket.h"

#include <Graphic/DirectX/DirectX.h>

#include <OS/PXProcess.h>
#include <Format/TIFF/TIFF.h>
#include <Format/Image.h>

int main()
{
	printf("[i] Starting testing...\n");

#if 0
	TestSoundAll();
#endif

#if 0
	TestFontAll();
#endif // 

#if 0 // OpenGL Test
	TestOpenGLAll();
#endif


#if 1
	TestSocket();
#endif // 1



	//Image image;

	//ImageLoadA(&image, "D:/_Data/Git/PXUltima/PXUltimaTest/_TEST_DATA_INPUT_/ImageInput.bmp");

	//ImageLoadA(&image, "A:/_WorkSpace/Download/at3_1m4_03.tif");

	//TestYAMLAll();
	//TestSystemInfoAll();
	//TestPXCompilerAll();
	//
	//TestWindowAll();
	//TestImageAll();
	// 
	// 
	// 
	//TestSBPAll();





	printf("[i] Finished testing...\n");

	return 0;
}
