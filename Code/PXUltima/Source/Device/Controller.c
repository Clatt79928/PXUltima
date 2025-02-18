#include "Controller.h"

#include <OS/System/OSVersion.h>

#if OSUnix

#elif OSWindowsEE

#include <windows.h>
#include <joystickapi.h> // Missing?? -> documentation says you should use "Dinput.h" but thats not correct.

#pragma comment( lib, "winmm.lib" )
#endif

PXBool ControllerScanDevices(NewControllerDetectedCallback callback)
{
#if OSUnix
#elif OSWindowsEE
const PXSize amountOfJoySticksSupported = joyGetNumDevs();

	for (PXSize i = 0; i < amountOfJoySticksSupported; i++)
	{
		const ControllerID joyID = i;
		JOYCAPSW pjc;
		const unsigned int size = sizeof(JOYCAPSW);
		const MMRESULT devResult = joyGetDevCapsW(joyID, &pjc, size);
		const unsigned char succesful = devResult == JOYERR_NOERROR;

		if (succesful)
		{
			if (callback)
			{
				callback(joyID);
			}
		}

		/*
		//JOYSTICKID1
		switch (devResult)
		{
			case MMSYSERR_BADDEVICEID: // Windows 95 / 98 / Me : The specified joystick identifier is invalid.
			{
				printf("MMSYSERR_BADDEVICEID\n");
				break;
			}
			case JOYERR_NOERROR:
			{




				printf("OK\n");

				break;
			}
			case MMSYSERR_NODRIVER://The joystick driver is not present.
			{
				printf("No Driver\n");
				break;
			}
			case MMSYSERR_INVALPARAM://An invalid parameter was passed.
			{
				printf("Invalid Paramerer\n");
				break;
			}
			case JOYERR_PARMS: //Windows NT / 2000 / XP : The specified joystick identifier is invalid.
			{
				printf("JOYERR_PARMS\n");
				break;
			}
			case JOYERR_UNPLUGGED: // The specified joystick is not connected to the system.
			{
				printf("JOYERR_UNPLUGGED\n");
				break;
			}

			default:
				break;
		}*/
	}
#endif
}

PXBool ControllerDataGet(Controller* controller)
{
#if OSUnix
    return 0u;

#elif OSWindowsEE
#if (WINVER >= 0x0400) // newer than Windows NT 4.0
	JOYINFOEX joystickInfo; // must set the 'dwSize' and 'dwFlags' or joyGetPosEx will fail.

	joystickInfo.dwSize = sizeof(JOYINFOEX);
	joystickInfo.dwFlags = JOY_RETURNALL;

	// For devices that have four to six axes of movement a point-of-view control,
	// or more than four buttons, use the joyGetPosEx function. 'joyGetPos()'
	const MMRESULT positionInfoResult = joyGetPosEx(controller->ID, &joystickInfo);
	const unsigned char successful = positionInfoResult == 0;

	if (successful)
	{
		controller->Axis[ControllerAxisX] = joystickInfo.dwXpos;
		controller->Axis[ControllerAxisY] = joystickInfo.dwYpos;
		controller->Axis[ControllerAxisZ] = joystickInfo.dwZpos;
		controller->Axis[ControllerAxisR] = joystickInfo.dwRpos;
		controller->Axis[ControllerAxisU] = joystickInfo.dwUpos;
		controller->Axis[ControllerAxisV] = joystickInfo.dwVpos;
		controller->ButtonPressedBitList = joystickInfo.dwButtons;
		controller->ButtonAmountPressed = joystickInfo.dwButtonNumber;
		controller->ControlPad = joystickInfo.dwPOV;
	}

	return successful;
#else
	JOYINFO joystickInfo{ 0 };

	const MMRESULT positionInfoResult = joyGetPos(controllerID, &joystickInfo);
	const bool successful = positionInfoResult == 0;

	if (successful)
	{
		controller.Axis[ControllerAxisX] = joystickInfo.wXpos;
		controller.Axis[ControllerAxisY] = joystickInfo.wYpos;
		controller.Axis[ControllerAxisZ] = joystickInfo.wZpos;
		controller.ButtonPressedBitList = joystickInfo.wButtons;
	}

	return successful;
#endif
#endif
}

PXBool ControllerAttachToWindow(const ControllerID controllerID, const PXWindowID PXWindowID)
{
#if OSUnix
    return 0u;

#elif OSWindowsEE
	UINT uPeriod = 1;
	BOOL fChanged = 1u;

	const MMRESULT captureResult = joySetCapture(PXWindowID, controllerID, uPeriod, fChanged);
	const unsigned char successful = captureResult == JOYERR_NOERROR;

	return successful;
#endif
}

PXBool ControllerDetachToWindow(const ControllerID controllerID)
{
#if OSUnix
    return 0u;

#elif OSWindowsEE
	const MMRESULT releaseResult = joyReleaseCapture(controllerID);
	const unsigned char successful = releaseResult == JOYERR_NOERROR;

	return successful;
#endif
}
