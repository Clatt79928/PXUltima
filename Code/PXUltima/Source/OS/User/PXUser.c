#include "PXUser.h"

#include <OS/System/OSVersion.h>

#if OSUnix

#elif OSWindows
#include <Windows.h>
// #include <userenv.h> could use GetUserProfileDirectoryW() but not needed yet
#endif

PXSize PXUserNameGetA(PXTextASCII* name, const PXSize nameSizeMax)
{
#if OSUnix

	return 0;

#elif OSWindows
	DWORD size = nameSizeMax;

	const PXBool sucessful = GetComputerNameA(name, &size);
	const PXSize sizeresult = sucessful * size;

	return sizeresult;
#endif
}

PXSize PXUserNameGetW(PXTextUNICODE* name, const PXSize nameSizeMax)
{
#if OSUnix

	return 0;

#elif OSWindows
	DWORD size = nameSizeMax;

	const PXBool sucessful = GetComputerNameW(name, &size);
	const PXSize sizeresult = sucessful * size;

	return sizeresult;
#endif
}

PXSize PXUserNameGetU(PXTextUTF8* name, const PXSize nameSizeMax)
{
#if OSUnix

	return 0;

#elif OSWindows
	DWORD size = nameSizeMax;

	const PXBool sucessful = GetComputerNameA(name, &size);
	const PXSize sizeresult = sucessful * size;

	return sizeresult;
#endif
}