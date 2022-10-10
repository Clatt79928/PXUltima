#ifndef WMAInclude
#define WMAInclude

#include <Format/Type.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Windows Media Audio
	typedef struct WMA_
	{
		unsigned int __dummy__;
	}
	WMA;

	PXPublic ActionResult WMAParse(WMA* wma, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif