#include "TestFont.h"

#include <Media/PXFont.h>
#include <stdio.h>

void TestFontAll()
{
	TestFontParse();
}

void TestFontParse()
{
	PXFont font;

	const PXActionResult fontLoadResult = PXFontLoadA(&font, "_TEST_DATA_INPUT_/A.fnt");

	printf("");
}