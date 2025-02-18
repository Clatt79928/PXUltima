#ifndef PXMouseINCLUDE
#define PXMouseINCLUDE

#define ButtonLeft    0b00000001
#define ButtonMiddle  0b00000010
#define ButtonRight   0b00000100
#define ButtonCustomA 0b00001000
#define ButtonCustomB 0b00010000
#define ButtonCustomC 0b00100000
#define ButtonCustomD 0b01000000
#define ButtonCustomE 0b10000000

#define IsPressedButtonLeft(mouse)	   (mouse->Buttons & ButtonLeft)
#define IsPressedButtonMiddle(mouse)  ((mouse->Buttons & ButtonMiddle) >> 1)
#define IsPressedButtonRight(mouse)   ((mouse->Buttons & ButtonRight) >> 2)
#define IsPressedButtonCustomA(mouse) ((mouse->Buttons & ButtonCustomA) >> 3)
#define IsPressedButtonCustomB(mouse) ((mouse->Buttons & ButtonCustomB) >> 4)
#define IsPressedButtonCustomC(mouse) ((mouse->Buttons & ButtonCustomC) >> 5)
#define IsPressedButtonCustomD(mouse) ((mouse->Buttons & ButtonCustomD) >> 6)
#define IsPressedButtonCustomE(mouse) ((mouse->Buttons & ButtonCustomE) >> 7)

#include <Media/PXType.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXMouse_
	{
		int Position[2]; // Window-Position (0/0 to x/y)
		int Delta[2]; // Relative Input (-x/-y to 0/0 to x/y)
		float PositionNormalisized[2];  // Convert Screenspace (width & height) to normal space -1 to +1
		unsigned char Buttons;
	}
	PXMouse;

	PXPublic void MouseInputReset(PXMouse* const mouse);
	PXPublic void MouseInputPrint(const PXMouse* const mouse);

#ifdef __cplusplus
}
#endif

#endif
