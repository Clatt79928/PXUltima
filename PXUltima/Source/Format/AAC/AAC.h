#ifndef AACInclude
#define AACInclude

#include <Format/Type.h>
#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct AAC_
	{
		unsigned int __dummy__;
	}
	AAC;

	PXPublic ActionResult AACParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif