#include "PXWindow.h"

#include <stdio.h>

#include <Event/PXEvent.h>
#include <Media/PXText.h>
#include <Graphic/PXGraphic.h>

#include <OS/Memory/PXMemory.h>
#include <OS/Monitor/PXMonitor.h>
#include <OS/Thread/Await.h>
#include <Math/PXMath.h>

#if OSUnix

#include <X11/cursorfont.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xmd.h>

#define DefautPositionX 00000000000000
#define DefautPositionY 00000000000000

#define MouseButtonLeft 1
#define MouseButtonMiddle 2
#define MouseButtonRight 3
#define MouseScrollUp 4
#define MouseScrollDown 5

#elif OSWindows
#include <windowsx.h>
#include <WinUser.h>
#include <wtypes.h>
//#include <hidusage.h>
#include <Dbt.h>

#define DefautPositionX CW_USEDEFAULT
#define DefautPositionY CW_USEDEFAULT

#endif

PXWindow* currentWindow = 0;

#if OSWindows

typedef enum WindowEventType_
{
    WindowEventInvalid,
    WindowEventNoMessage,
    WindowEventCreate,
    WindowEventDestroy,
    WindowEventMove,
    WindowEventSize,
    WindowEventActivate,
    WindowEventRedrawSet,
    WindowEventFocusSet,
    WindowEventFocusKill,
    WindowEventEnable,
    WindowEventTextSet,
    WindowEventTextGet,
    WindowEventTextGetLength,
    WindowEventPaint,
    WindowEventClose,
    WindowEventSessionQuerryEnd,
    WindowEventSessionEnd,
    WindowEventQuerryOpen,
    WindowEventQuit,
    WindowEventBackgroundErase,
    WindowEventSystemColorChange,
    WindowEventShowWindow,
    WindowEventIconChange,
    WindowEventSettingChange,
    WindowEventDeviceModeChange,
    WindowEventActivateApp,
    WindowEventFontChange,
    WindowEventTimeChange,
    WindowEventCancelMode,
    WindowEventCursorSet,
    WindowEventMouseActivate,
    WindowEventChildActivate,
    WindowEventQueueSync,
    WindowEventSizeChange,
    WindowEventIconPaint,
    WindowEventIconBackgroundErase,
    WindowEventDialogControlNext,
    WindowEventSPOOLERSTATUS,
    WindowEventItemDraw,
    WindowEventItemMeasure,
    WindowEventItemDelete,
    WindowEventVKEYTOITEM,
    WindowEventCHARTOITEM,
    WindowEventFontSet,
    WindowEventFontGet,
    WindowEventSETHOTKEY,
    WindowEventGETHOTKEY,
    WindowEventQUERYDRAGICON,
    WindowEventCOMPAREITEM,
    WindowEventGETOBJECT,
    WindowEventCOMPACTING,
    WindowEventCOMMNOTIFY,
    WindowEventWINDOWPOSCHANGING,
    WindowEventWINDOWPOSCHANGED,
    WindowEventPOWER,
    WindowEventCOPYDATA,
    WindowEventCANCELJOURNAL,
    WindowEventNOTIFY,
    WindowEventINPUTLANGCHANGEREQUEST,
    WindowEventINPUTLANGCHANGE,
    WindowEventTCARD,
    WindowEventHELP,
    WindowEventUSERCHANGED,
    WindowEventNOTIFYFORMAT,
    WindowEventCONTEXTMENU,
    WindowEventSTYLECHANGING,
    WindowEventSTYLECHANGED,
    WindowEventDISPLAYCHANGE,
    WindowEventGETICON,
    WindowEventSETICON,
    WindowEventNCCREATE,
    WindowEventNCDESTROY,
    WindowEventNCCALCSIZE,
    WindowEventNCHITTEST,
    WindowEventNCPAINT,
    WindowEventNCACTIVATE,
    WindowEventGETDLGCODE,
    WindowEventSYNCPAINT,
    WindowEventNCMOUSEMOVE,
    WindowEventNCLBUTTONDOWN,
    WindowEventNCLBUTTONUP,
    WindowEventNCLBUTTONDBLCLK,
    WindowEventNCRBUTTONDOWN,
    WindowEventNCRBUTTONUP,
    WindowEventNCRBUTTONDBLCLK,
    WindowEventNCMBUTTONDOWN,
    WindowEventNCMBUTTONUP,
    WindowEventNCMBUTTONDBLCLK,
    WindowEventNCXBUTTONDOWN,
    WindowEventNCXBUTTONUP,
    WindowEventNCXBUTTONDBLCLK,
    WindowEventINPUT_DEVICE_CHANGE,
    WindowEventINPUT,
    WindowEventKEYFIRST,
    WindowEventKEYDOWN,
    WindowEventKEYUP,
    WindowEventCHAR,
    WindowEventDEADCHAR,
        WindowEventSYSKEYDOWN,
        WindowEventSYSKEYUP,
        WindowEventSYSCHAR,
        WindowEventSYSDEADCHAR,
        WindowEventUNICHAR,
        WindowEventKEYLAST,
    //UNICODE_NOCHAR,
        WindowEventIME_STARTCOMPOSITION,
        WindowEventIME_ENDCOMPOSITION,
        WindowEventIME_COMPOSITION,
        WindowEventIME_KEYLAST,
        WindowEventINITDIALOG,
        WindowEventCOMMAND,
        WindowEventSYSCOMMAND,
        WindowEventTIMER,
        WindowEventHSCROLL,
        WindowEventVSCROLL,
        WindowEventINITMENU,
        WindowEventINITMENUPOPUP,
        WindowEventGESTURE,
        WindowEventGESTURENOTIFY,
        WindowEventMENUSELECT,
        WindowEventMENUCHAR,
        WindowEventENTERIDLE,
        WindowEventMENURBUTTONUP,
        WindowEventMENUDRAG,
        WindowEventMENUGETOBJECT,
        WindowEventUNINITMENUPOPUP,
        WindowEventMENUCOMMAND,
        WindowEventCHANGEUISTATE,
        WindowEventUPDATEUISTATE,
        WindowEventQUERYUISTATE,
        WindowEventCTLCOLORMSGBOX,
        WindowEventCTLCOLOREDIT,
        WindowEventCTLCOLORLISTBOX,
        WindowEventCTLCOLORBTN,
        WindowEventCTLCOLORDLG,
        WindowEventCTLCOLORSCROLLBAR,
        WindowEventCTLCOLORSTATIC,
        WindowEventGETHMENU,
        WindowEventMOUSEFIRST,
        WindowEventMOUSEMOVE,
        WindowEventLBUTTONDOWN,
        WindowEventLBUTTONUP,
        WindowEventLBUTTONDBLCLK,
        WindowEventRBUTTONDOWN,
        WindowEventRBUTTONUP,
        WindowEventRBUTTONDBLCLK,
        WindowEventMBUTTONDOWN,
        WindowEventMBUTTONUP,
        WindowEventMBUTTONDBLCLK,
        WindowEventMOUSEWHEEL,
        WindowEventXBUTTONDOWN,
        WindowEventXBUTTONUP,
        WindowEventXBUTTONDBLCLK,
        WindowEventMOUSEHWHEEL,
        WindowEventMOUSELAST,
        WindowEventPARENTNOTIFY,
        WindowEventENTERMENULOOP,
        WindowEventEXITMENULOOP,
        WindowEventNEXTMENU,
        WindowEventSIZING,
        WindowEventCAPTURECHANGED,
        WindowEventMOVING,
        WindowEventPOWERBROADCAST,
        WindowEventDEVICECHANGE,
        WindowEventMDICREATE,
        WindowEventMDIDESTROY,
        WindowEventMDIACTIVATE,
        WindowEventMDIRESTORE,
        WindowEventMDINEXT,
        WindowEventMDIMAXIMIZE,
        WindowEventMDITILE,
        WindowEventMDICASCADE,
        WindowEventMDIICONARRANGE,
        WindowEventMDIGETACTIVE,
        WindowEventMDISETMENU,
        WindowEventENTERSIZEMOVE,
        WindowEventEXITSIZEMOVE,
        WindowEventDROPFILES,
        WindowEventMDIREFRESHMENU,
        WindowEventPOINTERDEVICECHANGE,
        WindowEventPOINTERDEVICEINRANGE,
        WindowEventPOINTERDEVICEOUTOFRANGE,
        WindowEventTOUCH,
        WindowEventNCPOINTERUPDATE,
        WindowEventNCPOINTERDOWN,
        WindowEventNCPOINTERUP,
        WindowEventPOINTERUPDATE,
        WindowEventPOINTERDOWN,
        WindowEventPOINTERUP,
        WindowEventPOINTERENTER,
        WindowEventPOINTERLEAVE,
        WindowEventPOINTERACTIVATE,
        WindowEventPOINTERCAPTURECHANGED,
        WindowEventTOUCHHITTESTING,
        WindowEventPOINTERWHEEL,
        WindowEventPOINTERHWHEEL,
        WindowEventPOINTERROUTEDTO,
        WindowEventPOINTERROUTEDAWAY,
        WindowEventPOINTERROUTEDRELEASED,
        WindowEventIME_SETCONTEXT,
        WindowEventIME_NOTIFY,
        WindowEventIME_CONTROL,
        WindowEventIME_COMPOSITIONFULL,
        WindowEventIME_SELECT,
        WindowEventIME_CHAR,
        WindowEventIME_REQUEST,
        WindowEventIME_KEYDOWN,
        WindowEventIME_KEYUP,
        WindowEventMOUSEHOVER,
        WindowEventMOUSELEAVE,
        WindowEventNCMOUSEHOVER,
        WindowEventNCMOUSELEAVE,
        WindowEventWTSSESSION_CHANGE,
        WindowEventTABLET_FIRST,
        WindowEventTABLET_LAST,
        WindowEventDPICHANGED,
        WindowEventDPICHANGED_BEFOREPARENT,
        WindowEventDPICHANGED_AFTERPARENT,
        WindowEventGETDPISCALEDSIZE,
        WindowEventCUT,
        WindowEventCOPY,
        WindowEventPASTE,
        WindowEventCLEAR,
        WindowEventUNDO,
        WindowEventRENDERFORMAT,
        WindowEventRENDERALLFORMATS,
        WindowEventDESTROYCLIPBOARD,
        WindowEventDRAWCLIPBOARD,
        WindowEventPAINTCLIPBOARD,
        WindowEventVSCROLLCLIPBOARD,
        WindowEventSIZECLIPBOARD,
        WindowEventASKCBFORMATNAME,
        WindowEventCHANGECBCHAIN,
        WindowEventHSCROLLCLIPBOARD,
        WindowEventQUERYNEWPALETTE,
        WindowEventPALETTEISCHANGING,
        WindowEventPALETTECHANGED,
        WindowEventHOTKEY,
        WindowEventPRINT,
        WindowEventPRINTCLIENT,
        WindowEventAPPCOMMAND,
        WindowEventTHEMECHANGED,
        WindowEventCLIPBOARDUPDATE,
        WindowEventDWMCOMPOSITIONCHANGED,
        WindowEventDWMNCRENDERINGCHANGED,
        WindowEventDWMCOLORIZATIONCOLORCHANGED,
        WindowEventDWMWINDOWMAXIMIZEDCHANGE,
        WindowEventDWMSENDICONICTHUMBNAIL,
        WindowEventDWMSENDICONICLIVEPREVIEWBITMAP,
        WindowEventGETTITLEBARINFOEX,
        WindowEventHANDHELDFIRST,
        WindowEventHANDHELDLAST,
        WindowEventAFXFIRST,
        WindowEventAFXLAST,
        WindowEventPENWINFIRST,
        WindowEventPENWINLAST,
        WindowEventAPP
}WindowEventType;

WindowEventType ToWindowEventType(const unsigned int windowEventID)
{
    switch(windowEventID)
    {
        case WM_NULL: return WindowEventNoMessage;
        case WM_CREATE: return WindowEventCreate;
        case WM_DESTROY: return WindowEventDestroy;
        case WM_MOVE: return WindowEventMove;
        case WM_SIZE: return WindowEventSize;
        case WM_ACTIVATE: return WindowEventActivate;
        case WM_SETFOCUS: return WindowEventFocusSet;
        case WM_KILLFOCUS: return WindowEventFocusKill;
        case WM_ENABLE: return WindowEventEnable;
        case WM_SETREDRAW: return WindowEventRedrawSet;
        case WM_SETTEXT: return WindowEventTextSet;
        case WM_GETTEXT: return WindowEventTextGet;
        case WM_GETTEXTLENGTH: return WindowEventTextGetLength;
        case WM_PAINT: return WindowEventPaint;
        case WM_CLOSE: return WindowEventClose;
        case WM_QUERYENDSESSION: return WindowEventSessionQuerryEnd;
        case WM_QUERYOPEN: return WindowEventQuerryOpen;
        case WM_ENDSESSION: return WindowEventSessionEnd;
        case WM_QUIT: return WindowEventQuit;
        case WM_ERASEBKGND: return WindowEventBackgroundErase;
        case WM_SYSCOLORCHANGE: return WindowEventSystemColorChange;
        case WM_SHOWWINDOW: return WindowEventShowWindow;
        case WM_WININICHANGE: return WindowEventIconChange;
            //case WM_SETTINGCHANGE                WM_WININICHANGE
        case WM_DEVMODECHANGE: return WindowEventDeviceModeChange;
        case WM_ACTIVATEAPP: return WindowEventActivateApp;
        case WM_FONTCHANGE: return WindowEventFontChange;
        case WM_TIMECHANGE: return WindowEventTimeChange;
        case WM_CANCELMODE: return WindowEventCancelMode;
        case WM_SETCURSOR: return WindowEventCursorSet;
        case WM_MOUSEACTIVATE: return WindowEventMouseActivate;
        case WM_CHILDACTIVATE: return WindowEventChildActivate;
        case WM_QUEUESYNC: return WindowEventQueueSync;
        case WM_GETMINMAXINFO: return WindowEventSizeChange;
        case WM_PAINTICON: return WindowEventIconPaint;
        case WM_ICONERASEBKGND: return WindowEventIconBackgroundErase;
        case WM_NEXTDLGCTL: return WindowEventDialogControlNext;
        case WM_SPOOLERSTATUS: return WindowEventSPOOLERSTATUS;
        case WM_DRAWITEM: return WindowEventItemDraw;
        case WM_MEASUREITEM: return WindowEventItemMeasure;
        case WM_DELETEITEM: return WindowEventItemDelete;
        case WM_VKEYTOITEM: return WindowEventVKEYTOITEM;
        case WM_CHARTOITEM: return WindowEventCHARTOITEM;
        case WM_SETFONT: return WindowEventFontSet;
        case WM_GETFONT: return WindowEventFontGet;
        case WM_SETHOTKEY: return WindowEventSETHOTKEY;
        case WM_GETHOTKEY: return WindowEventGETHOTKEY;
        case WM_QUERYDRAGICON: return WindowEventQUERYDRAGICON;
        case WM_COMPAREITEM: return WindowEventCOMPAREITEM;
        case WM_GETOBJECT: return WindowEventGETOBJECT;
        case WM_COMPACTING: return WindowEventCOMPACTING;
        case WM_COMMNOTIFY: return WindowEventCOMMNOTIFY;   /* no longer suported */
        case WM_WINDOWPOSCHANGING: return WindowEventWINDOWPOSCHANGING;
        case WM_WINDOWPOSCHANGED: return WindowEventWINDOWPOSCHANGED;
        case WM_POWER: return WindowEventPOWER;
        case WM_COPYDATA: return WindowEventCOPYDATA;
        case WM_CANCELJOURNAL: return WindowEventCANCELJOURNAL;
        case WM_NOTIFY: return WindowEventNOTIFY;
        case WM_INPUTLANGCHANGEREQUEST: return WindowEventINPUTLANGCHANGEREQUEST;
        case WM_INPUTLANGCHANGE: return WindowEventINPUTLANGCHANGE;
        case WM_TCARD: return WindowEventTCARD;
        case WM_HELP: return WindowEventHELP;
        case WM_USERCHANGED: return WindowEventUSERCHANGED;
        case WM_NOTIFYFORMAT: return WindowEventNOTIFYFORMAT;
        case WM_CONTEXTMENU: return WindowEventCONTEXTMENU;
        case WM_STYLECHANGING: return WindowEventSTYLECHANGING;
        case WM_STYLECHANGED: return WindowEventSTYLECHANGED;
        case WM_DISPLAYCHANGE: return WindowEventDISPLAYCHANGE;
        case WM_GETICON: return WindowEventGETICON;
        case WM_SETICON: return WindowEventSETICON;
        case WM_NCCREATE: return WindowEventNCCREATE;
        case WM_NCDESTROY: return WindowEventNCDESTROY;
        case WM_NCCALCSIZE: return WindowEventNCCALCSIZE;
        case WM_NCHITTEST: return WindowEventNCHITTEST;
        case WM_NCPAINT: return WindowEventNCPAINT;
        case WM_NCACTIVATE: return WindowEventNCACTIVATE;
        case WM_GETDLGCODE: return WindowEventGETDLGCODE;
        case WM_SYNCPAINT: return WindowEventSYNCPAINT;
        case WM_NCMOUSEMOVE: return WindowEventNCMOUSEMOVE;
        case WM_NCLBUTTONDOWN: return WindowEventNCLBUTTONDOWN;
        case WM_NCLBUTTONUP: return WindowEventNCLBUTTONUP;
        case WM_NCLBUTTONDBLCLK: return WindowEventNCLBUTTONDBLCLK;
        case WM_NCRBUTTONDOWN: return WindowEventNCRBUTTONDOWN;
        case WM_NCRBUTTONUP: return WindowEventNCRBUTTONUP;
        case WM_NCRBUTTONDBLCLK: return WindowEventNCRBUTTONDBLCLK;
        case WM_NCMBUTTONDOWN: return WindowEventNCMBUTTONDOWN;
        case WM_NCMBUTTONUP: return WindowEventNCMBUTTONUP;
        case WM_NCMBUTTONDBLCLK: return WindowEventNCMBUTTONDBLCLK;
        case WM_NCXBUTTONDOWN: return WindowEventNCXBUTTONDOWN;
        case WM_NCXBUTTONUP: return WindowEventNCXBUTTONUP;
        case WM_NCXBUTTONDBLCLK: return WindowEventNCXBUTTONDBLCLK;
        case WM_INPUT_DEVICE_CHANGE: return WindowEventINPUT_DEVICE_CHANGE;
        case WM_INPUT: return WindowEventINPUT;
            // ?? case WM_KEYFIRST: return WindowEventKEYFIRST;
        case WM_KEYDOWN: return WindowEventKEYDOWN;
        case WM_KEYUP: return WindowEventKEYUP;
        case WM_CHAR: return WindowEventCHAR;
        case WM_DEADCHAR: return WindowEventDEADCHAR;
        case WM_SYSKEYDOWN: return WindowEventSYSKEYDOWN;
        case WM_SYSKEYUP: return WindowEventSYSKEYUP;
        case WM_SYSCHAR: return WindowEventSYSCHAR;
        case WM_SYSDEADCHAR: return WindowEventSYSDEADCHAR;
       // case WM_UNICHAR: return WindowEventUNICHAR;
            //case WM_KEYLAST: return WindowEventKEYLAST;
               // case UNICODE_NOCHAR: return WindowEventXXXXXXXXXXXXXXX;

        case WM_IME_STARTCOMPOSITION: return WindowEventIME_STARTCOMPOSITION;
        case WM_IME_ENDCOMPOSITION: return WindowEventIME_ENDCOMPOSITION;
        case WM_IME_COMPOSITION: return WindowEventIME_COMPOSITION;
            //case WM_IME_KEYLAST: return WindowEventIME_KEYLAST;
        case WM_INITDIALOG: return WindowEventINITDIALOG;
        case WM_COMMAND: return WindowEventCOMMAND;
        case WM_SYSCOMMAND: return WindowEventSYSCOMMAND;
        case WM_TIMER: return WindowEventTIMER;
        case WM_HSCROLL: return WindowEventHSCROLL;
        case WM_VSCROLL: return WindowEventVSCROLL;
        case WM_INITMENU: return WindowEventINITMENU;
        case WM_INITMENUPOPUP: return WindowEventINITMENUPOPUP;
      //  case WM_GESTURE: return WindowEventGESTURE;
     //   case WM_GESTURENOTIFY: return WindowEventGESTURENOTIFY;
        case WM_MENUSELECT: return WindowEventMENUSELECT;
        case WM_MENUCHAR: return WindowEventMENUCHAR;
        case WM_ENTERIDLE: return WindowEventENTERIDLE;
        case WM_MENURBUTTONUP: return WindowEventMENURBUTTONUP;
        case WM_MENUDRAG: return WindowEventMENUDRAG;
        case WM_MENUGETOBJECT: return WindowEventMENUGETOBJECT;
        case WM_UNINITMENUPOPUP: return WindowEventUNINITMENUPOPUP;
        case WM_MENUCOMMAND: return WindowEventMENUCOMMAND;
        case WM_CHANGEUISTATE: return WindowEventCHANGEUISTATE;
        case WM_UPDATEUISTATE: return WindowEventUPDATEUISTATE;
        case WM_QUERYUISTATE: return WindowEventQUERYUISTATE;
        case WM_CTLCOLORMSGBOX: return WindowEventCTLCOLORMSGBOX;
        case WM_CTLCOLOREDIT: return WindowEventCTLCOLOREDIT;
        case WM_CTLCOLORLISTBOX: return WindowEventCTLCOLORLISTBOX;
        case WM_CTLCOLORBTN: return WindowEventCTLCOLORBTN;
        case WM_CTLCOLORDLG: return WindowEventCTLCOLORDLG;
        case WM_CTLCOLORSCROLLBAR: return WindowEventCTLCOLORSCROLLBAR;

        case WM_CTLCOLORSTATIC: return WindowEventCTLCOLORSTATIC;
      //  case MN_GETHMENU: return WindowEventGETHMENU;
            //case WM_MOUSEFIRST: return WindowEventMOUSEFIRST;
        case WM_MOUSEMOVE: return WindowEventMOUSEMOVE;

        case WM_LBUTTONDOWN: return WindowEventLBUTTONDOWN;
        case WM_LBUTTONUP: return WindowEventLBUTTONUP;
        case WM_LBUTTONDBLCLK: return WindowEventLBUTTONDBLCLK;
        case WM_RBUTTONDOWN: return WindowEventRBUTTONDOWN;
        case WM_RBUTTONUP: return WindowEventRBUTTONUP;

        case WM_RBUTTONDBLCLK: return WindowEventRBUTTONDBLCLK;
        case WM_MBUTTONDOWN: return WindowEventMBUTTONDOWN;
        case WM_MBUTTONUP: return WindowEventMBUTTONUP;
        case WM_MBUTTONDBLCLK: return WindowEventMBUTTONDBLCLK;
        case WM_MOUSEWHEEL: return WindowEventMOUSEWHEEL;

        case WM_XBUTTONDOWN: return WindowEventXBUTTONDOWN;
        case WM_XBUTTONUP: return WindowEventXBUTTONUP;
        case WM_XBUTTONDBLCLK: return WindowEventXBUTTONDBLCLK;
     //   case WM_MOUSEHWHEEL: return WindowEventMOUSEHWHEEL;
            //case WM_MOUSELAST: return WindowEventMOUSELAST;
        case WM_PARENTNOTIFY: return WindowEventPARENTNOTIFY;
        case WM_ENTERMENULOOP: return WindowEventENTERMENULOOP;
        case WM_EXITMENULOOP: return WindowEventEXITMENULOOP;
        case WM_NEXTMENU: return WindowEventNEXTMENU;
        case WM_SIZING: return WindowEventSIZING;
        case WM_CAPTURECHANGED: return WindowEventCAPTURECHANGED;
        case WM_MOVING: return WindowEventMOVING;
        case WM_POWERBROADCAST: return WindowEventPOWERBROADCAST;
        case WM_DEVICECHANGE: return WindowEventDEVICECHANGE;
        case WM_MDICREATE: return WindowEventMDICREATE;
        case WM_MDIDESTROY: return WindowEventMDIDESTROY;
        case WM_MDIACTIVATE: return WindowEventMDIACTIVATE;
        case WM_MDIRESTORE: return WindowEventMDIRESTORE;
        case WM_MDINEXT: return WindowEventMDINEXT;

        case WM_MDIMAXIMIZE: return WindowEventMDIMAXIMIZE;
        case WM_MDITILE: return WindowEventMDITILE;
        case WM_MDICASCADE: return WindowEventMDICASCADE;
        case WM_MDIICONARRANGE: return WindowEventMDIICONARRANGE;
        case WM_MDIGETACTIVE: return WindowEventMDIGETACTIVE;
        case WM_MDISETMENU: return WindowEventMDISETMENU;
        case WM_ENTERSIZEMOVE: return WindowEventENTERSIZEMOVE;
        case WM_EXITSIZEMOVE: return WindowEventEXITSIZEMOVE;
        case WM_DROPFILES: return WindowEventDROPFILES;
        case WM_MDIREFRESHMENU: return WindowEventMDIREFRESHMENU;
            //case WM_POINTERDEVICECHANGE: return WindowEventPOINTERDEVICECHANGE;
        //case WM_POINTERDEVICEINRANGE: return WindowEventPOINTERDEVICEINRANGE;
        //case WM_POINTERDEVICEOUTOFRANGE: return WindowEventPOINTERDEVICEOUTOFRANGE;
      //  case WM_TOUCH: return WindowEventTOUCH;
            //case WM_NCPOINTERUPDATE: return WindowEventNCPOINTERUPDATE;
        //case WM_NCPOINTERDOWN: return WindowEventNCPOINTERDOWN;
        //case WM_NCPOINTERUP: return WindowEventNCPOINTERUP;
        //case WM_POINTERUPDATE: return WindowEventPOINTERUPDATE;
        //case WM_POINTERDOWN: return WindowEventPOINTERDOWN;
        //case WM_POINTERUP: return WindowEventPOINTERUP;
        //case WM_POINTERENTER: return WindowEventPOINTERENTER;
        //case WM_POINTERLEAVE: return WindowEventPOINTERLEAVE;
        //case WM_POINTERACTIVATE: return WindowEventPOINTERACTIVATE;
        //case WM_POINTERCAPTURECHANGED: return WindowEventPOINTERCAPTURECHANGED;
        //case WM_TOUCHHITTESTING: return WindowEventTOUCHHITTESTING;
        //case WM_POINTERWHEEL: return WindowEventPOINTERWHEEL;
        //case WM_POINTERHWHEEL: return WindowEventPOINTERHWHEEL;
            //case WM_POINTERROUTEDTO: return WindowEventPOINTERROUTEDTO;
            //case WM_POINTERROUTEDAWAY: return WindowEventPOINTERROUTEDAWAY;
        //case WM_POINTERROUTEDRELEASED: return WindowEventPOINTERROUTEDRELEASED;
        case WM_IME_SETCONTEXT: return WindowEventIME_SETCONTEXT;
        case WM_IME_NOTIFY: return WindowEventIME_NOTIFY;
        case WM_IME_CONTROL: return WindowEventIME_CONTROL;
        case WM_IME_COMPOSITIONFULL: return WindowEventIME_COMPOSITIONFULL;
        case WM_IME_SELECT: return WindowEventIME_SELECT;
        case WM_IME_CHAR: return WindowEventIME_CHAR;
        case WM_IME_REQUEST: return WindowEventIME_REQUEST;
        case WM_IME_KEYDOWN: return WindowEventIME_KEYDOWN;
        case WM_IME_KEYUP: return WindowEventIME_KEYUP;
        case WM_MOUSEHOVER: return WindowEventMOUSEHOVER;
        case WM_MOUSELEAVE: return WindowEventMOUSELEAVE;
        case WM_NCMOUSEHOVER: return WindowEventNCMOUSEHOVER;
        case WM_NCMOUSELEAVE: return WindowEventNCMOUSELEAVE;
      //  case WM_WTSSESSION_CHANGE: return WindowEventWTSSESSION_CHANGE;
      //  case WM_TABLET_FIRST: return WindowEventTABLET_FIRST;
      //  case WM_TABLET_LAST: return WindowEventTABLET_LAST;
            //case WM_DPICHANGED: return WindowEventDPICHANGED;
            //case WM_DPICHANGED_BEFOREPARENT: return WindowEventDPICHANGED_BEFOREPARENT;
            //case WM_DPICHANGED_AFTERPARENT: return WindowEventDPICHANGED_AFTERPARENT;
            // case WM_GETDPISCALEDSIZE: return WindowEventGETDPISCALEDSIZE;
        case WM_CUT: return WindowEventCUT;
        case WM_COPY: return WindowEventCOPY;
        case WM_PASTE: return WindowEventPASTE;
        case WM_CLEAR: return WindowEventCLEAR;
        case WM_UNDO: return WindowEventUNDO;
        case WM_RENDERFORMAT: return WindowEventRENDERFORMAT;
        case WM_RENDERALLFORMATS: return WindowEventRENDERALLFORMATS;
        case WM_DESTROYCLIPBOARD: return WindowEventDESTROYCLIPBOARD;
        case WM_DRAWCLIPBOARD: return WindowEventDRAWCLIPBOARD;
        case WM_PAINTCLIPBOARD: return WindowEventPAINTCLIPBOARD;
        case WM_VSCROLLCLIPBOARD: return WindowEventVSCROLLCLIPBOARD;
        case WM_SIZECLIPBOARD: return WindowEventSIZECLIPBOARD;
        case WM_ASKCBFORMATNAME: return WindowEventASKCBFORMATNAME;
        case WM_CHANGECBCHAIN: return WindowEventCHANGECBCHAIN;
        case WM_HSCROLLCLIPBOARD: return WindowEventHSCROLLCLIPBOARD;
        case WM_QUERYNEWPALETTE: return WindowEventQUERYNEWPALETTE;
        case WM_PALETTEISCHANGING: return WindowEventPALETTEISCHANGING;
        case WM_PALETTECHANGED: return WindowEventPALETTECHANGED;
        case WM_HOTKEY: return WindowEventHOTKEY;
        case WM_PRINT: return WindowEventPRINT;
        case WM_PRINTCLIENT: return WindowEventPRINTCLIENT;
        case WM_APPCOMMAND: return WindowEventAPPCOMMAND;
        case WM_THEMECHANGED: return WindowEventTHEMECHANGED;
      //  case WM_CLIPBOARDUPDATE: return WindowEventCLIPBOARDUPDATE;
      //  case WM_DWMCOMPOSITIONCHANGED: return WindowEventDWMCOMPOSITIONCHANGED;
     //   case WM_DWMNCRENDERINGCHANGED: return WindowEventDWMNCRENDERINGCHANGED;
     //   case WM_DWMCOLORIZATIONCOLORCHANGED: return WindowEventDWMCOLORIZATIONCOLORCHANGED;
    //    case WM_DWMWINDOWMAXIMIZEDCHANGE: return WindowEventDWMWINDOWMAXIMIZEDCHANGE;
    //    case WM_DWMSENDICONICTHUMBNAIL: return WindowEventDWMSENDICONICTHUMBNAIL;
     //   case WM_DWMSENDICONICLIVEPREVIEWBITMAP: return WindowEventDWMSENDICONICLIVEPREVIEWBITMAP;
     //   case WM_GETTITLEBARINFOEX: return WindowEventGETTITLEBARINFOEX;
        case WM_HANDHELDFIRST: return WindowEventHANDHELDFIRST;
        case WM_HANDHELDLAST: return WindowEventHANDHELDLAST;
        case WM_AFXFIRST: return WindowEventAFXFIRST;
        case WM_AFXLAST: return WindowEventAFXLAST;
        case WM_PENWINFIRST: return WindowEventPENWINFIRST;
        case WM_PENWINLAST: return WindowEventPENWINLAST;
        case WM_APP: return WindowEventAPP;

        default: return WindowEventInvalid;
}
}

#endif



#if OSUnix

#define CursorIconNormalID 1
#define CursorIconIBeamID 2
#define CursorIconWaitID 3
#define CursorIconCrossID 4
#define CursorIconUpID 5
#define CursorIconSizeID 6
#define CursorIconIconID 7
#define CursorIconResizeClockwiseCounterID 8
#define CursorIconResizeClockwiseID 10
#define CursorIconResizeHorizontalID 11
#define CursorIconResizeVerticalID 12
#define CursorIconResizeAllID 13
#define CursorIconCursorID 14
#define CursorIconNoAllowedID 15
#define CursorIconHandID 16
#define CursorIconAppStartingID 17

#elif OSWindows

#include <winuser.rh> // MISSING
#define CursorIconNormalID OCR_NORMAL
#define CursorIconIBeamID OCR_IBEAM
#define CursorIconWaitID OCR_WAIT
#define CursorIconCrossID OCR_CROSS
#define CursorIconUpID OCR_UP
#define CursorIconSizeID OCR_SIZE               // OBSOLETE: use OCR_SIZEALL
#define CursorIconIconID OCR_ICON               // OBSOLETE: use OCR_NORMAL
#define CursorIconResizeClockwiseCounterID OCR_SIZENWSE
#define CursorIconResizeClockwiseID OCR_SIZENESW
#define CursorIconResizeHorizontalID OCR_SIZEWE
#define CursorIconResizeVerticalID OCR_SIZENS
#define CursorIconResizeAllID OCR_SIZEALL
#define CursorIconCursorID OCR_ICOCUR             // OBSOLETE: use OIC_WINLOGO
#define CursorIconNoAllowedID OCR_NO

#if defined(WindowsAtleast2000)
#define CursorIconHandID OCR_HAND
#else
#define CursorIconHandID 32649
#endif

#if defined(WindowsAtleastNT)
#define CursorIconAppStartingID OCR_APPSTARTING
#else
#define CursorIconAppStartingID 32650
#endif

#endif














#if OSUnix
void PXWindowEventHandler(PXWindow* const PXWindow, const XEvent* const event)
{
    switch(event->type)
    {
        case KeyPress:
        case KeyRelease:
        {
            const XKeyEvent* keyEvent = &event->xkey;
            const unsigned int keyCode = keyEvent->keycode;
            const unsigned char release = event->type == KeyRelease;
            const KeySym keySym = XKeycodeToKeysym(PXWindow->DisplayCurrent, keyCode, 0);
            const char* keyName = XKeysymToString(keySym);

            VirtualKey keyBoardKey = ConvertToVirtualKey(keySym);

            KeyBoardKeyInfo keyBoardKeyInfo;

            keyBoardKeyInfo.Key = keyBoardKey;
            keyBoardKeyInfo.Mode = release ? ButtonStateRelease : ButtonStateDown;
            keyBoardKeyInfo.Repeat = 0;
            keyBoardKeyInfo.ScanCode = keySym;
            keyBoardKeyInfo.SpecialKey = 0;
            keyBoardKeyInfo.KontextCode = 0;
            keyBoardKeyInfo.PreState = 0;
            keyBoardKeyInfo.GapState = 0;

            InvokeEvent(PXWindow->KeyBoardKeyCallBack, PXWindow->EventReceiver, PXWindow, keyBoardKeyInfo);

            if(release)
            {
                printf("[Event] Key-Release %2i %2i %s\n", keyCode, keySym, keyName);
            }
            else
            {
                printf("[Event] Key-Press %2i %2i %s\n", keyCode, keySym, keyName);
            }

            break;
        }
        case ButtonRelease:
        case ButtonPress:
        {
            const XButtonEvent* buttonEvent = &event->xbutton;
            const unsigned int buttonID = buttonEvent->button;
            const ButtonState buttonState = event->type == ButtonPress ? ButtonStateDown : ButtonStateRelease;
            MouseButton mouseButton = MouseButtonInvalid;

            switch(buttonID)
            {
                case MouseButtonLeft:
                    InvokeEvent(PXWindow->MouseClickCallBack, PXWindow->EventReceiver, PXWindow, MouseButtonLeft, buttonState);
                    break;

                case MouseButtonMiddle:
                    InvokeEvent(PXWindow->MouseClickCallBack, PXWindow->EventReceiver, PXWindow, MouseButtonMiddle, buttonState);
                    break;

                case MouseButtonRight:
                    InvokeEvent(PXWindow->MouseClickCallBack, PXWindow->EventReceiver, PXWindow, MouseButtonRight, buttonState);
                    break;

                case MouseScrollUp:
                    InvokeEvent(PXWindow->MouseScrollCallBack, PXWindow->EventReceiver, PXWindow, MouseScrollDirectionUp);
                    break;

                case MouseScrollDown:
                    InvokeEvent(PXWindow->MouseScrollCallBack, PXWindow->EventReceiver, PXWindow, MouseScrollDirectionDown);
                    break;

            }
        }
        case MotionNotify:
        {
            printf("[Event] MotionNotify \n");

            break;
        }
        case EnterNotify:
        {
            InvokeEvent(PXWindow->MouseEnterCallBack, PXWindow->EventReceiver, PXWindow);
            break;
        }
        case LeaveNotify:
        {
            InvokeEvent(PXWindow->MouseLeaveCallBack, PXWindow->EventReceiver, PXWindow);
            break;
        }
        case FocusIn:
        {
            InvokeEvent(PXWindow->FocusEnterCallBack, PXWindow->EventReceiver, PXWindow);
            break;
        }
        case FocusOut:
        {
            InvokeEvent(PXWindow->FocusLeaveCallBack, PXWindow->EventReceiver, PXWindow);
            break;
        }
        case KeymapNotify:
        {
            printf("[Event] KeymapNotify \n");

            break;
        }
        case Expose:
        {
            printf("[Event] Expose \n");

            /*
              XWindowAttributes gwa;

                        XGetWindowAttributes(window.Dis, PXWindowID, &gwa);
                        glViewport(0, 0, gwa.width, gwa.height);


                        glClearColor(1.0, 1.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        glBegin(GL_POLYGON);
                        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
                        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
                        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
                        glEnd();

                        // Flush drawing command buffer to make drawing happen as soon as possible.
                        //glFlush();

                        window.FrameBufferSwap();*/

            break;
        }
        case GraphicsExpose:
        {
            printf("[Event] PXGraphicsExpose \n");

            break;
        }
        case NoExpose:
        {
            printf("[Event] NoExpose \n");

            break;
        }
        case VisibilityNotify:
        {
            printf("[Event] VisibilityNotify \n");

            break;
        }
        case CreateNotify:
        {
            printf("[Event] CreateNotify \n");

            break;
        }
        case DestroyNotify:
        {
            printf("[Event] DestroyNotify \n");

            break;
        }
        case UnmapNotify:
        {
            printf("[Event] UnmapNotify \n");

            break;
        }
        case MapNotify:
        {
            printf("[Event] MapNotify \n");

            break;
        }
        case MapRequest:
        {
            printf("[Event] MapRequest \n");

            break;
        }
        case ReparentNotify:
        {
            printf("[Event] ReparentNotify \n");

            break;
        }
        case ConfigureNotify:
        {
            printf("[Event] ConfigureNotify \n");

            break;
        }
        case ConfigureRequest:
        {
            printf("[Event] Destroyed \n");

            break;
        }
        case GravityNotify:
        {
            printf("[Event] GravityNotify \n");

            break;
        }
        case ResizeRequest:
        {
            const XResizeRequestEvent resizeRequestEvent = event->xresizerequest;
            const int width = resizeRequestEvent.width;
            const int height = resizeRequestEvent.height;

            // glViewport(0,0, width, height);

            InvokeEvent(PXWindow->WindowSizeChangedCallBack, PXWindow->EventReceiver, PXWindow, width, height);

            break;
        }
        case CirculateNotify:
        {
            printf("[Event] CirculateNotify \n");

            break;
        }
        case CirculateRequest:
        {
            printf("[Event] CirculateRequest \n");

            break;
        }
        case PropertyNotify:
        {
            printf("[Event] PropertyNotify \n");

            break;
        }
        case SelectionClear:
        {
            printf("[Event] SelectionClear \n");

            break;
        }
        case SelectionRequest:
        {
            printf("[Event] SelectionRequest \n");

            break;
        }
        case SelectionNotify:
        {
            printf("[Event] SelectionNotify \n");

            break;
        }
        case ColormapNotify:
        {
            printf("[Event] ColormapNotify \n");

            break;
        }
        case ClientMessage:
        {
            printf("[Event] ClientMessage \n");

            break;
        }
        case MappingNotify:
        {
            printf("[Event] MappingNotify \n");

            break;
        }
        case GenericEvent:
        {
            XGenericEventCookie cookie = event->xcookie; // Make Copy

            const int result = XGetEventData(PXWindow->DisplayCurrent, &cookie);
            const unsigned char sucessful = result != 0 && cookie.data;

            if(sucessful)
            {
                switch(cookie.evtype)
                {
                    case XI_RawMotion:
                    {
                        XIRawEvent* re = (XIRawEvent*)cookie.data;

                        if(re->valuators.mask_len)
                        {
                            Mouse* mouse = &PXWindow->MouseCurrentInput;
                            const double* values = re->raw_values;
                            const unsigned char isX = XIMaskIsSet(re->valuators.mask, 0);
                            const unsigned char isY = XIMaskIsSet(re->valuators.mask, 1);
                            double xpos = 0;
                            double ypos = 0;

                            if(isX)
                            {
                                xpos += *values;
                                ++values;
                            }

                            if(isY)
                            {
                                ypos += *values;
                            }


                            mouse->InputAxis[0] = mouse->Position[0] - xpos;
                            mouse->InputAxis[1] = mouse->Position[1] - ypos;

                            mouse->Position[0] = xpos;
                            mouse->Position[1] = ypos;

                            printf("[Event] RawMotion %5.4lf %5.4lf\n", xpos, ypos);

                            InvokeEvent(PXWindow->MouseMoveCallBack, PXWindow->EventReceiver, PXWindow, mouse);

                            //printf("[Event] RawMotion %5.4lf %5.4lf\n", window.MouseDeltaX, window.MouseDeltaY);

                            //InvokeEvent(window.MouseMoveCallBack, window.MousePositionX, window.MousePositionY, window.MouseDeltaX, window.MouseDeltaY);
                        }
                    }
                }
            }
            else
            {
                printf("[Event] GenericEvent %i\n", cookie.evtype);
            }

            XFreeEventData(PXWindow->DisplayCurrent, &cookie);

            break;
        }
        default:
        {
            printf("[Event] default: unkown event \n");

            break;
        }
    }
}
#elif OSWindows
LRESULT CALLBACK PXWindowEventHandler(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam)
{
    const WindowEventType windowEventType = ToWindowEventType(eventID);
    PXWindow* window = PXWindowLookupFind(windowsID);

    if(!window)
    {
        return DefWindowProc(windowsID, eventID, wParam, lParam);
    }

    switch(windowEventType)
    {
        case WindowEventNoMessage:
            break;
        case WindowEventCreate: // Gets called inside the "CreateWindow" function.
        {
            // Do noth�ng here, as it's too soon to regard the window as 'created'

            return DefWindowProc(windowsID, eventID, wParam, lParam);
        }
        case WindowEventDestroy:
        {
            window->IsRunning = PXFalse;
            break;
        }     
        case WindowEventMove:
            break;
        case WindowEventSize:
        {
            window->Width = LOWORD(lParam);
            window->Height = HIWORD(lParam);

            window->HasSizeChanged = PXYes;

            InvokeEvent(window->WindowSizeChangedCallBack, window->EventReceiver, window);

            break;
        }
        case WindowEventActivate:
            break;
        case WindowEventRedrawSet:
            break;
        case WindowEventFocusSet:
            break;
        case WindowEventFocusKill:
            break;
        case WindowEventEnable:
            break;
        case WindowEventTextSet:
            break;
        case WindowEventTextGet:
            break;
        case WindowEventTextGetLength:
            break;
        case WindowEventPaint:
            break;
        case WindowEventClose:
        {
            PXBool closeWindow = 0;

            InvokeEvent(window->WindowClosingCallBack, window->EventReceiver, window, &closeWindow);

            if(closeWindow)
            {
                InvokeEvent(window->WindowClosedCallBack, window->EventReceiver, window);

                const LRESULT result = DefWindowProc(windowsID, WM_CLOSE, wParam, lParam);

                window->IsRunning = PXFalse;

                return result;
            }

            break;
        }
        case WindowEventSessionQuerryEnd:
            break;
        case WindowEventSessionEnd:
            break;
        case WindowEventQuerryOpen:
            break;
        case WindowEventQuit:
            break;
        case WindowEventBackgroundErase:
            break;
        case WindowEventSystemColorChange:
            break;
        case WindowEventShowWindow:
            break;
        case WindowEventIconChange:
            break;
        case WindowEventSettingChange:
            break;
        case WindowEventDeviceModeChange:
            break;
        case WindowEventActivateApp:
            break;
        case WindowEventFontChange:
            break;
        case WindowEventTimeChange:
            break;
        case WindowEventCancelMode:
            break;
        case WindowEventCursorSet:
        {
            const HWND windowsHandle = (HWND)wParam;
            const WORD hitTestResult = LOWORD(lParam);
            const WORD sourceMessage = HIWORD(lParam);
            const unsigned char showCursor = !(window->CursorModeCurrent == PXWindowCursorInvisible || window->CursorModeCurrent == PXWindowCursorLockAndHide);

            if(showCursor)
            {
                while(ShowCursor(1) < 0);
            }
            else
            {
                while(ShowCursor(0) >= 0);
            }

            return 1; // prevent further processing
        }
        case WindowEventMouseActivate:
            break;
        case WindowEventChildActivate:
            break;
        case WindowEventQueueSync:
            break;

#if 0 // Not useable for resize event. Its not what it seems
        case WindowEventSizeChange:
        {
            //wParam is unused
            const MINMAXINFO* minmaxInfo = (MINMAXINFO*)lParam;
            const LONG width = minmaxInfo->ptMaxSize.x;
            const LONG height = minmaxInfo->ptMaxSize.y;

            break;
        }
#endif
        case WindowEventIconPaint:
            break;
        case WindowEventIconBackgroundErase:
            break;
        case WindowEventDialogControlNext:
            break;
        case WindowEventSPOOLERSTATUS:
            break;
        case WindowEventItemDraw:
            break;
        case WindowEventItemMeasure:
            break;
        case WindowEventItemDelete:
            break;
        case WindowEventVKEYTOITEM:
            break;
        case WindowEventCHARTOITEM:
            break;
        case WindowEventFontSet:
            break;
        case WindowEventFontGet:
            break;
        case WindowEventSETHOTKEY:
            break;
        case WindowEventGETHOTKEY:
            break;
        case WindowEventQUERYDRAGICON:
            break;
        case WindowEventCOMPAREITEM:
            break;
        case WindowEventGETOBJECT:
            break;
        case WindowEventCOMPACTING:
            break;
        case WindowEventCOMMNOTIFY:
            break;
        case WindowEventWINDOWPOSCHANGING:
            break;
        case WindowEventWINDOWPOSCHANGED:
            break;
        case WindowEventPOWER:
            break;
        case WindowEventCOPYDATA:
            break;
        case WindowEventCANCELJOURNAL:
            break;
        case WindowEventNOTIFY:
            break;
        case WindowEventINPUTLANGCHANGEREQUEST:
            break;
        case WindowEventINPUTLANGCHANGE:
            break;
        case WindowEventTCARD:
            break;
        case WindowEventHELP:
            break;
        case WindowEventUSERCHANGED:
            break;
        case WindowEventNOTIFYFORMAT:
            break;
        case WindowEventCONTEXTMENU:
            break;
        case WindowEventSTYLECHANGING:
            break;
        case WindowEventSTYLECHANGED:
            break;
        case WindowEventDISPLAYCHANGE:
            break;
        case WindowEventGETICON:
            break;
        case WindowEventSETICON:
            break;
        case WindowEventNCCREATE:
            break;
        case WindowEventNCDESTROY:
            break;
        case WindowEventNCCALCSIZE:
            break;
        case WindowEventNCHITTEST:
            break;
        case WindowEventNCPAINT:
            break;
        case WindowEventNCACTIVATE:
            break;
        case WindowEventGETDLGCODE:
            break;
        case WindowEventSYNCPAINT:
            break;
        case WindowEventNCMOUSEMOVE:
            break;
        case WindowEventNCLBUTTONDOWN:
            break;
        case WindowEventNCLBUTTONUP:
            break;
        case WindowEventNCLBUTTONDBLCLK:
            break;
        case WindowEventNCRBUTTONDOWN:
            break;
        case WindowEventNCRBUTTONUP:
            break;
        case WindowEventNCRBUTTONDBLCLK:
            break;
        case WindowEventNCMBUTTONDOWN:
            break;
        case WindowEventNCMBUTTONUP:
            break;
        case WindowEventNCMBUTTONDBLCLK:
            break;
        case WindowEventNCXBUTTONDOWN:
            break;
        case WindowEventNCXBUTTONUP:
            break;
        case WindowEventNCXBUTTONDBLCLK:
            break;
        case WindowEventINPUT_DEVICE_CHANGE:
            break;
        case WindowEventINPUT:
        {
             // MISSING
            const PXSize inputCode = GET_RAWINPUT_CODE_WPARAM(wParam);
            const HRAWINPUT handle = (HRAWINPUT)lParam;
            const UINT uiCommand = RID_INPUT; // RID_HEADER

            switch(inputCode)
            {
                case RIM_INPUT: // Input occurred while the application was in the foreground.
                {
                    RAWINPUT rawInput;
                    UINT rawInputSize = sizeof(RAWINPUT); // Can't be 'const' !

                    const UINT result = GetRawInputData(handle, uiCommand, &rawInput, &rawInputSize, sizeof(RAWINPUTHEADER));
                    const PXBool sucessful = result != -1;

                    if(sucessful)
                    {
#if UseRawMouseData
                        if(rawInput.header.dwType == RIM_TYPEMOUSE)
                        {
                            int positionX = 0;
                            int positionY = 0;
                            int deltaX = rawInput.data.mouse.lLastX;
                            int deltaY = rawInput.data.mouse.lLastY;

                            PXWindowCursorPositionInWindowGet(window, &positionX, &positionY);

                            TriggerOnMouseMoveEvent(window, positionX, positionY, deltaX, deltaY);

                            // Wheel data needs to be pointer casted to interpret an unsigned short as a short, with no conversion
                            // otherwise it'll overflow when going negative.
                            // Didn't happen before some minor changes in the code, doesn't seem to go away
                            // so it's going to have to be like this.
                            // if (raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
                            //     input.mouse.wheel = (*(short*)&raw->data.mouse.usButtonData) / WHEEL_DELTA;
                        }
#endif
                    }

                    break;
                }
                case RIM_INPUTSINK: // Input occurred while the application was not in the foreground.
                {
                    break;
                }

                default:
                    break;
            }

            break;
        }

        case WindowEventKEYFIRST:
            break;

        case WindowEventKEYDOWN:
        case WindowEventKEYUP:
        {
            ButtonState mode = ButtonStateInvalid;

            switch(eventID)
            {
                case WM_KEYUP:
                {
                    mode = ButtonStateRelease;
                    break;
                }
                case WM_KEYDOWN:
                {
                    mode = ButtonStateDown;
                    break;
                }
            }

            const PXSize character = wParam;
            const PXSize characterInfo = lParam;
            const VirtualKey virtualKey = ConvertToVirtualKey(character);

            KeyBoardKeyPressedSet(&window->KeyBoardCurrentInput, virtualKey, mode == ButtonStateRelease);

            KeyBoardKeyInfo buttonInfo;
            buttonInfo.KeyID = character;
            buttonInfo.Key = virtualKey;
            buttonInfo.Mode = mode;

			// TODO: on system 32 Bit error
			/*
			buttonInfo.Repeat = (characterInfo & 0b00000000000000001111111111111111); // Die Wiederholungsanzahl f�r die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schl�ssel h�lt.Die Wiederholungsanzahl ist immer 1 f�r eine WM _ KEYUP - Nachricht.
            buttonInfo.ScanCode = (characterInfo & 0b00000000111111110000000000000000) >> 16; // Der Scancode.Der Wert h�ngt vom OEM ab.
            buttonInfo.SpecialKey = (characterInfo & 0b00000001000000000000000000000000) >> 24; // Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schl�ssel handelt.andernfalls ist es 0.
            //buttonInfo.ReservedDontUse = (characterInfo & 0b00011110000000000000000000000000) >> 25; //	Reserviert; nicht verwenden.
            buttonInfo.KontextCode = (characterInfo & 0b00100000000000000000000000000000) >> 29; // Der Kontextcode.Der Wert ist f�r eine WM _ KEYUP - Nachricht immer 0.
            buttonInfo.PreState = (characterInfo & 0b01000000000000000000000000000000) >> 30; // Der vorherige Schl�sselzustand.Der Wert ist immer 1 f�r eine WM _ KEYUP - Nachricht.
            buttonInfo.GapState = (characterInfo & 0b10000000000000000000000000000000) >> 31; // Der �bergangszustand.Der Wert ist immer 1 f�r eine WM _ KEYUP - Nachricht.
			*/

            TriggerOnKeyBoardKeyEvent(window, buttonInfo);

            break;
        }

        case WindowEventCHAR:
            break;
        case WindowEventDEADCHAR:
            break;
        case WindowEventSYSKEYDOWN:
            break;
        case WindowEventSYSKEYUP:
            break;
        case WindowEventSYSCHAR:
            break;
        case WindowEventSYSDEADCHAR:
            break;
        case WindowEventUNICHAR:
            break;
        case WindowEventKEYLAST:
            break;
        case WindowEventIME_STARTCOMPOSITION:
            break;
        case WindowEventIME_ENDCOMPOSITION:
            break;
        case WindowEventIME_COMPOSITION:
            break;
        case WindowEventIME_KEYLAST:
            break;
        case WindowEventINITDIALOG:
            break;
        case WindowEventCOMMAND:
            break;
        case WindowEventSYSCOMMAND:
            break;
        case WindowEventTIMER:
            break;
        case WindowEventHSCROLL:
            break;
        case WindowEventVSCROLL:
            break;
        case WindowEventINITMENU:
            break;
        case WindowEventINITMENUPOPUP:
            break;
        case WindowEventGESTURE:
            break;
        case WindowEventGESTURENOTIFY:
            break;
        case WindowEventMENUSELECT:
            break;
        case WindowEventMENUCHAR:
            break;
        case WindowEventENTERIDLE:
            break;
        case WindowEventMENURBUTTONUP:
            break;
        case WindowEventMENUDRAG:
            break;
        case WindowEventMENUGETOBJECT:
            break;
        case WindowEventUNINITMENUPOPUP:
            break;
        case WindowEventMENUCOMMAND:
            break;
        case WindowEventCHANGEUISTATE:
            break;
        case WindowEventUPDATEUISTATE:
            break;
        case WindowEventQUERYUISTATE:
            break;
        case WindowEventCTLCOLORMSGBOX:
            break;
        case WindowEventCTLCOLOREDIT:
            break;
        case WindowEventCTLCOLORLISTBOX:
            break;
        case WindowEventCTLCOLORBTN:
            break;
        case WindowEventCTLCOLORDLG:
            break;
        case WindowEventCTLCOLORSCROLLBAR:
            break;
        case WindowEventCTLCOLORSTATIC:
            break;
        case WindowEventGETHMENU:
            break;
        //case WindowEventMOUSEFIRST:
        //    break;
        //case WindowEventMOUSEMOVE:
        //    break;
        case WindowEventLBUTTONDOWN:
            TriggerOnMouseClickEvent(window, MouseButtonLeft, ButtonStateDown);
            break;

        case WindowEventLBUTTONUP:
            TriggerOnMouseClickEvent(window, MouseButtonLeft, ButtonStateRelease);
            break;

        case WindowEventLBUTTONDBLCLK:
            TriggerOnMouseClickDoubleEvent(window, MouseButtonLeft);
            break;

        case WindowEventRBUTTONDOWN:
            TriggerOnMouseClickEvent(window, MouseButtonRight, ButtonStateDown);
            break;

        case WindowEventRBUTTONUP:
            TriggerOnMouseClickEvent(window, MouseButtonRight, ButtonStateRelease);
            break;

        case WindowEventRBUTTONDBLCLK:
            TriggerOnMouseClickDoubleEvent(window, MouseButtonRight);
            break;

        case WindowEventMBUTTONDOWN:
            TriggerOnMouseClickEvent(window, MouseButtonMiddle, ButtonStateDown);
            break;

        case WindowEventMBUTTONUP:
            TriggerOnMouseClickEvent(window, MouseButtonMiddle, ButtonStateRelease);
            break;

        case WindowEventMBUTTONDBLCLK:
            TriggerOnMouseClickDoubleEvent(window, MouseButtonMiddle);
            break;

        case WindowEventMOUSEWHEEL:
            break;

        case WindowEventXBUTTONUP:
        case WindowEventXBUTTONDOWN:
        {
            MouseButton mouseButton = MouseButtonInvalid;
            ButtonState buttonState = ButtonStateInvalid;

            const WORD releaseID = HIWORD(wParam);
            // const WORD xxxxx = LOWORD(wParam);
            // const WORD fwKeys = GET_KEYSTATE_WPARAM(wParam);
            // const WORD fwButton = GET_XBUTTON_WPARAM(wParam);
            // const int xPos = GET_X_LPARAM(lParam);
            // const int yPos = GET_Y_LPARAM(lParam);

            {
                switch(windowEventType)
                {

                    case WindowEventXBUTTONUP:
                    {
                        buttonState = ButtonStateRelease;
                        break;
                    }

                    case WindowEventXBUTTONDOWN:
                    {
                        buttonState = ButtonStateDown;
                        break;
                    }
                }


                switch(releaseID)
                {
                    case XBUTTON1:
                        mouseButton = MouseButtonSpecialA;
                        break;

                    case XBUTTON2:
                        mouseButton = MouseButtonSpecialB;
                        break;
                }

                /*
                        switch(fwKeys)
                        {
                            case MK_XBUTTON1:
                                mouseButton = MouseButtonSpecialA;
                                break;

                            case MK_XBUTTON2:
                                mouseButton = MouseButtonSpecialB;
                                break;

                            default:
                                mouseButton = MouseButtonInvalid;
                                break;
                        }
                */


                TriggerOnMouseClickEvent(window, mouseButton, buttonState);
            }

            break;
        }

        case WindowEventXBUTTONDBLCLK:
            break;
        case WindowEventMOUSEHWHEEL:
            break;
        case WindowEventMOUSELAST:
            break;
        case WindowEventPARENTNOTIFY:
            break;
        case WindowEventENTERMENULOOP:
            break;
        case WindowEventEXITMENULOOP:
            break;
        case WindowEventNEXTMENU:
            break;
        case WindowEventSIZING:
            break;
        case WindowEventCAPTURECHANGED:
            break;
        case WindowEventMOVING:
            break;
        case WindowEventPOWERBROADCAST:
            break;
        case WindowEventDEVICECHANGE:
            break;
        case WindowEventMDICREATE:
            break;
        case WindowEventMDIDESTROY:
            break;
        case WindowEventMDIACTIVATE:
            break;
        case WindowEventMDIRESTORE:
            break;
        case WindowEventMDINEXT:
            break;
        case WindowEventMDIMAXIMIZE:
            break;
        case WindowEventMDITILE:
            break;
        case WindowEventMDICASCADE:
            break;
        case WindowEventMDIICONARRANGE:
            break;
        case WindowEventMDIGETACTIVE:
            break;
        case WindowEventMDISETMENU:
            break;
        case WindowEventENTERSIZEMOVE:
            break;
        case WindowEventEXITSIZEMOVE:
            break;
        case WindowEventDROPFILES:
            break;
        case WindowEventMDIREFRESHMENU:
            break;
        case WindowEventPOINTERDEVICECHANGE:
            break;
        case WindowEventPOINTERDEVICEINRANGE:
            break;
        case WindowEventPOINTERDEVICEOUTOFRANGE:
            break;
        case WindowEventTOUCH:
            break;
        case WindowEventNCPOINTERUPDATE:
            break;
        case WindowEventNCPOINTERDOWN:
            break;
        case WindowEventNCPOINTERUP:
            break;
        case WindowEventPOINTERUPDATE:
            break;
        case WindowEventPOINTERDOWN:
            break;
        case WindowEventPOINTERUP:
            break;
        case WindowEventPOINTERENTER:
            break;
        case WindowEventPOINTERLEAVE:
            break;
        case WindowEventPOINTERACTIVATE:
            break;
        case WindowEventPOINTERCAPTURECHANGED:
            break;
        case WindowEventTOUCHHITTESTING:
            break;
        case WindowEventPOINTERWHEEL:
            break;
        case WindowEventPOINTERHWHEEL:
            break;
        case WindowEventPOINTERROUTEDTO:
            break;
        case WindowEventPOINTERROUTEDAWAY:
            break;
        case WindowEventPOINTERROUTEDRELEASED:
            break;
        case WindowEventIME_SETCONTEXT:
            break;
        case WindowEventIME_NOTIFY:
            break;
        case WindowEventIME_CONTROL:
            break;
        case WindowEventIME_COMPOSITIONFULL:
            break;
        case WindowEventIME_SELECT:
            break;
        case WindowEventIME_CHAR:
            break;
        case WindowEventIME_REQUEST:
            break;
        case WindowEventIME_KEYDOWN:
            break;
        case WindowEventIME_KEYUP:
            break;
        case WindowEventMOUSEHOVER:
            break;
        case WindowEventMOUSELEAVE:
            break;
        case WindowEventNCMOUSEHOVER:
            break;
        case WindowEventNCMOUSELEAVE:
            break;
        case WindowEventWTSSESSION_CHANGE:
            break;
        case WindowEventTABLET_FIRST:
            break;
        case WindowEventTABLET_LAST:
            break;
        case WindowEventDPICHANGED:
            break;
        case WindowEventDPICHANGED_BEFOREPARENT:
            break;
        case WindowEventDPICHANGED_AFTERPARENT:
            break;
        case WindowEventGETDPISCALEDSIZE:
            break;
        case WindowEventCUT:
        {
            printf("[#][Event] CUT\n");
            break;
        }

        case WindowEventCOPY:
        {
            printf("[#][Event] Copy\n");
            break;
        }
        case WindowEventPASTE:
        {
            printf("[#][Event] Paste\n");
            break;
        }
        case WindowEventCLEAR:
        {
            printf("[#][Event] Clear\n");
            break;
        }
        case WindowEventUNDO:
        {
            printf("[#][Event] Undo\n");
            break;
        }
        case WindowEventRENDERFORMAT:
            break;
        case WindowEventRENDERALLFORMATS:
            break;
        case WindowEventDESTROYCLIPBOARD:
            break;
        case WindowEventDRAWCLIPBOARD:
            break;
        case WindowEventPAINTCLIPBOARD:
            break;
        case WindowEventVSCROLLCLIPBOARD:
            break;
        case WindowEventSIZECLIPBOARD:
            break;
        case WindowEventASKCBFORMATNAME:
            break;
        case WindowEventCHANGECBCHAIN:
            break;
        case WindowEventHSCROLLCLIPBOARD:
            break;
        case WindowEventQUERYNEWPALETTE:
            break;
        case WindowEventPALETTEISCHANGING:
            break;
        case WindowEventPALETTECHANGED:
            break;
        case WindowEventHOTKEY:
            break;
        case WindowEventPRINT:
            break;
        case WindowEventPRINTCLIENT:
            break;
        case WindowEventAPPCOMMAND:
            break;
        case WindowEventTHEMECHANGED:
            break;
        case WindowEventCLIPBOARDUPDATE:
            break;
        case WindowEventDWMCOMPOSITIONCHANGED:
            break;
        case WindowEventDWMNCRENDERINGCHANGED:
            break;
        case WindowEventDWMCOLORIZATIONCOLORCHANGED:
            break;
        case WindowEventDWMWINDOWMAXIMIZEDCHANGE:
            break;
        case WindowEventDWMSENDICONICTHUMBNAIL:
            break;
        case WindowEventDWMSENDICONICLIVEPREVIEWBITMAP:
            break;
        case WindowEventGETTITLEBARINFOEX:
            break;
        case WindowEventHANDHELDFIRST:
            break;
        case WindowEventHANDHELDLAST:
            break;
        case WindowEventAFXFIRST:
            break;
        case WindowEventAFXLAST:
            break;
        case WindowEventPENWINFIRST:
            break;
        case WindowEventPENWINLAST:
            break;
        case WindowEventAPP:
            break;

        case WindowEventInvalid:
        default:
            break;
    }

    // If nothing had grabbed the event by now, let the default funcion handle it.
    return DefWindowProc(windowsID, eventID, wParam, lParam);
}
#endif

PXThreadResult PXWindowCreateThread(PXWindow* const window)
{
    window->IsRunning = 0;
    window->CursorModeCurrent = PXWindowCursorShow;

#if OSUnix
    XInitThreads();

    // Create display
    {
        const Display* const display = XOpenDisplay(0);   // Create Window
        const PXBool successful = display != 0;

        if (!successful)
        {
            return PXThreadSucessful; // printf("\n\tcannot connect to X server\n\n");
        }

        window->DisplayCurrent = display;
    }

    // Get root window
    {
        const XID windowRoot = DefaultRootWindow(window->DisplayCurrent); // Make windows root
        const PXBool successful = windowRoot != 0;

        window->WindowRoot = successful ? windowRoot : 0;
    }


    const int attributeList[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    const XVisualInfo* const visualInfo = glXChooseVisual(window->DisplayCurrent, 0, attributeList);

    {
        const PXBool successful = visualInfo != 0;

        if (!successful)
        {
            return PXThreadSucessful; // no appropriate visual found
        }
    }

    // Create colormapping
    Colormap colormap = XCreateColormap
    (
        window->DisplayCurrent,
        window->WindowRoot,
        visualInfo->visual,
        AllocNone
    );

    XSetWindowAttributes setWindowAttributes;
    //setWindowAttributes.cursor = ;
    setWindowAttributes.colormap = colormap;
    setWindowAttributes.event_mask =
        KeyPressMask |
        KeyReleaseMask |
        ButtonPressMask |
        ButtonReleaseMask |
        EnterWindowMask |
        LeaveWindowMask |
        PointerMotionMask |
        PointerMotionHintMask |
        Button1MotionMask |
        Button2MotionMask |
        Button3MotionMask |
        Button4MotionMask |
        Button5MotionMask |
        ButtonMotionMask |
        KeymapStateMask |
        ExposureMask |
        VisibilityChangeMask |
        StructureNotifyMask |
        ResizeRedirectMask |
        SubstructureNotifyMask |
        SubstructureRedirectMask |
        FocusChangeMask |
        PropertyChangeMask |
        ColormapChangeMask |
        OwnerGrabButtonMask |
        // XI_RawMotion |
        0;



    // Create window
    {
        int borderWidth = 0;

        PXWindow cccc = *window;

        const XID PXWindowID = XCreateWindow
        (
            window->DisplayCurrent,
            window->WindowRoot,
            window->X,
            window->Y,
            window->Width,
            window->Height,
            borderWidth,
            visualInfo->depth,
            InputOutput,
            visualInfo->visual,
            CWColormap | CWEventMask,
            &setWindowAttributes
        );
        const unsigned char sucessful = PXWindowID;

        printf("[i][Window] Create <%i x %i> \n", window->Width, window->Height);

        window->ID = sucessful ? PXWindowID : 0;
    }

    // Giving the graphic system window context
    window->GraphicInstance.AttachedWindow = window;

    // Set Title
    {
        char windowTitleA[256];

        PXTextCopyWA(window->Title, 256, windowTitleA, 256);

        XMapWindow(window->DisplayCurrent, window->ID);
        XStoreName(window->DisplayCurrent, window->ID, windowTitleA);
    }

#if 0 // Grab means literally Drag%Drop grab. This is not mouse motion
    //bool   ret    = false;
    XID cursor = XCreateFontCursor(display, XC_crosshair);
    int    root = DefaultRootWindow(display);

    const int grabResult = XGrabPointer
    (
        display,
        root,
        0,
        ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        root,
        None,
        CurrentTime
    );
#endif


    // Raw mouse movement
    XIEventMask eventmask;
    const PXSize maskLength = (XI_LASTEVENT + 7) / 8;
    unsigned char mask[maskLength];

    MemoryClear(mask, sizeof(mask));
    MemoryClear(&eventmask, sizeof(XIEventMask));

    XISetMask(mask, XI_RawMotion);
    //XISetMask(mask, XI_RawButtonPress);
    //XISetMask(mask, XI_RawKeyPress);

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = maskLength;
    eventmask.mask = mask;


    XISelectEvents(window->DisplayCurrent, window->WindowRoot, &eventmask, 1u);
    XFlush(window->DisplayCurrent);


#elif OSWindows

    DWORD dwStyle = 0;
    HWND hWndParent = 0;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const wchar_t* lpClassName = L"PXUltima_WindowCreationAsyncThread";
    const HCURSOR cursorID = LoadCursor(hInstance, IDC_ARROW);
    window->CursorID = cursorID;

    if (!window->Mode == PXWindowModeNormal)
    {
        dwStyle |= WS_VISIBLE | WS_OVERLAPPEDWINDOW;
    }

    WNDCLASSW wndclass;

    MemoryClear(&wndclass, sizeof(WNDCLASSW));

    wndclass.style = CS_OWNDC; //  CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = PXWindowEventHandler;
    wndclass.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = window->CursorID;
    wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1); //(HBRUSH)GetStockObject(COLOR_BACKGROUND);
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = lpClassName;

    const WORD classID = RegisterClassW(&wndclass);

    lpClassName = (wchar_t*)classID;


    DWORD windowStyle = WS_EX_APPWINDOW | WS_EX_DLGMODALFRAME | WS_EX_CONTEXTHELP;
    HMENU hMenu = 0;
    void* lpParam = 0;

    PXWindowID windowID = CreateWindowExW
    (
        windowStyle,
        lpClassName,
        window->Title,
        dwStyle,
        window->X,
        window->Y,
        window->Width,
        window->Height,
        hWndParent,
        hMenu,
        hInstance,
        lpParam
    );

    {
        if (!windowID)
        {
            const PXActionResult windowsCreateResult = GetCurrentError();

            // Handle error?

            return PXThreadActionFailed;
        }

        window->ID = windowID;
        window->GraphicInstance.AttachedWindow = window;

        PXWindowPosition(window, 0, 0);
    }

    // MISSING

    // PixelDraw system
    {
        const HDC windowHandleToDeviceContext = GetDC(windowID);

        const WORD  nSize = sizeof(PIXELFORMATDESCRIPTOR);
        const WORD  nVersion = 1;
        const DWORD dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        const BYTE  iPixelType = PFD_TYPE_RGBA; // The kind of framebuffer. RGBA or palette.
        const BYTE  cColorBits = 32;   // Colordepth of the framebuffer.
        const BYTE  cRedBits = 0;
        const BYTE  cRedShift = 0;
        const BYTE  cGreenBits = 0;
        const BYTE  cGreenShift = 0;
        const BYTE  cBlueBits = 0;
        const BYTE  cBlueShift = 0;
        const BYTE  cAlphaBits = 0;
        const BYTE  cAlphaShift = 0;
        const BYTE  cAccumBits = 0;
        const BYTE  cAccumRedBits = 0;
        const BYTE  cAccumGreenBits = 0;
        const BYTE  cAccumBlueBits = 0;
        const BYTE  cAccumAlphaBits = 0;
        const BYTE  cDepthBits = 24; // Number of bits for the depthbuffer
        const BYTE  cStencilBits = 8;  // Number of bits for the stencilbuffer
        const BYTE  cAuxBuffers = 0;  // Number of Aux buffers in the framebuffer.
        const BYTE  iLayerType = PFD_MAIN_PLANE;
        const BYTE  bReserved = 0;
        const DWORD dwLayerMask = 0;
        const DWORD dwVisibleMask = 0;
        const DWORD dwDamageMask = 0;
        const PIXELFORMATDESCRIPTOR pfd =
        {
            nSize,
            nVersion,
            dwFlags,
            iPixelType,
            cColorBits,
            cRedBits,cRedShift,
            cGreenBits, cGreenShift,
            cBlueBits, cBlueShift,
            cAlphaBits, cAlphaShift,
            cAccumBits,
            cAccumRedBits, cAccumGreenBits, cAccumBlueBits, cAccumAlphaBits,
            cDepthBits,
            cStencilBits,
            cAuxBuffers,
            iLayerType,
            bReserved,
            dwLayerMask, dwVisibleMask, dwDamageMask
        };
        const int letWindowsChooseThisPixelFormat = ChoosePixelFormat(windowHandleToDeviceContext, &pfd);
        const PXBool sucessul = SetPixelFormat(windowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

        window->HandleDeviceContext = windowHandleToDeviceContext;
    }
#endif

    PXGraphicInstantiate(&window->GraphicInstance);

    PXWindowLookupAdd(window);

    InvokeEvent(window->WindowCreatedCallBack, window->EventReceiver, window);

    #if OSWindows
    {
        UpdateWindow(windowID);

        if (window->Mode == PXWindowModeNormal)
        {        
            ShowWindow(windowID, SW_SHOW);
        }
    }
    #endif

    window->IsRunning = 1;

#if OSUnix
#if 0
    int numberOfDevices = 0;

    const XDeviceInfo* deviceInfoList = XListInputDevices(display, &numberOfDevices);

    for(int i = 0; i < numberOfDevices; ++i)
    {
        const XDeviceInfo& xDeviceInfo = deviceInfoList[i];

        printf
        (
            "[Device] ID:%i Name:%s Use:%i\n",
            xDeviceInfo.id,
            xDeviceInfo.name,
            xDeviceInfo.use
        );

        // XOpenDevice(display, i); // Cannot open mouse or keyboard??  invalid call

        // XEventClass eventList[8]={0,0,0,0,0,0,0,0};
       //  int listSize = xDeviceInfo.num_classes;

       //  int resultE = XSelectExtensionEvent(display, PXWindowID, eventList, listSize);

        // printf("");
    }
#endif
#elif OSWindows
    // Register input device
    {
        // We're configuring just one RAWINPUTDEVICE, the mouse, so it's a single-element array (a pointer).
        RAWINPUTDEVICE rid;

        rid.usUsagePage = 0x01;//HID_USAGE_PAGE_GENERIC;
        rid.usUsage = 0x02;// HID_USAGE_GENERIC_MOUSE;
        rid.dwFlags = RIDEV_INPUTSINK | RIDEV_DEVNOTIFY;
        rid.hwndTarget = windowID;

        const PXBool result = RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE));

        if (!result)
        {
            printf("Err\n");
        }

        // RegisterRawInputDevices should not be used from a library, as it may interfere with any raw input processing logic already present in applications that load it.
    }
#endif

    while(window->IsRunning)
    {
#if OSUnix
        XEvent windowEvent;

        /*
            Window root_return, child_return;
            int root_x_return, root_y_return;
            int win_x_return, win_y_return;
            unsigned int mask_return;
            /*
             * We need:
             *     child_return - the active window under the cursor
             *     win_{x,y}_return - pointer coordinate with respect to root window
             * /
            int retval = XQueryPointer
            (
                display,
                root_window,
                &root_return,
                &child_return,
                &root_x_return,
                &root_y_return,
                &win_x_return,
                &win_y_return,
                &mask_return
            );*/




        XLockDisplay(window->DisplayCurrent);

        XNextEvent(window->DisplayCurrent, &windowEvent);

        XUnlockDisplay(window->DisplayCurrent);

        PXWindowEventHandler(window, &windowEvent);

#elif OSWindows
        MSG message;

        const PXBool peekResult = PeekMessageW(&message, 0, 0, 0, PM_NOREMOVE);

        if(peekResult)
        {
            const PXBool messageResult = GetMessageW(&message, 0, 0, 0);

            if(messageResult)
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            else
            {
                break; // Unexpected error?
            }
        }
#endif
    }

    return PXThreadSucessful;
}

void PXWindowConstruct(PXWindow* const window)
{
    MemoryClear(window, sizeof(PXWindow));
}

float PXWindowScreenRatio(const PXWindow* const window)
{
    return (float)window->Width / (float)window->Height;
}

void PXWindowCreateA(PXWindow* window, const unsigned int width, const unsigned int height, const char* title, const PXBool async)
{
    PXTextCopyAW(title, 256u, window->Title, 256u);

    PXWindowCreate(window, width, height, async);
}

void PXWindowCreateW(PXWindow* const window, const unsigned int width, const unsigned int height, const wchar_t* title, const PXBool async)
{
    PXTextCopyW(title, 256u, window->Title, 256u);

    PXWindowCreate(window, width, height, async);
}

void PXWindowCreateU(PXWindow* const window, const unsigned int width, const unsigned int height, const char* title, const PXBool async)
{
    PXTextCopyAW(title, 256u, window->Title, 256u);

    window->Mode = PXWindowModeNormal;

    PXWindowCreate(window, width, height, async);
}

void PXWindowCreate(PXWindow* const window, const unsigned int width, const unsigned int height, const PXBool async)
{
    window->Width = width;
    window->Height = height;

    {
        const PXBool isDefaultSize = width == -1 && height == -1;

        if (isDefaultSize)
        {
            unsigned int screenWidth = 0;
            unsigned int screenHeight = 0;

            PXMonitorGetSize(&screenWidth, &screenHeight);

            window->X = screenWidth * 0.125f;
            window->Y = screenHeight * 0.125f;
            window->Width = screenWidth * 0.75f;
            window->Height = screenHeight * 0.75f;
        }
    }

    if (async)
    {
        const PXActionResult actionResult = PXThreadRun(&window->MessageThread, PXWindowCreateThread, window);
        const PXBool sucessful = PXActionSuccessful == actionResult;
    }
    else
    {
        PXWindowCreateThread(window);
    }
}

void PXWindowCreateHidden(PXWindow* const window, const unsigned int width, const unsigned int height, const PXBool async)
{
    window->Mode = PXWindowModeHidden;

    PXWindowCreate(window, width, height, async);
}

void PXWindowDestruct(PXWindow* const window)
{
#if OSUnix
    glXMakeCurrent(window->DisplayCurrent, None, NULL);
    //    glXDestroyContext(DisplayCurrent, OpenGLConextID);
    XDestroyWindow(window->DisplayCurrent, window->ID);
    XCloseDisplay(window->DisplayCurrent);
#elif OSWindows
    CloseWindow(window->ID);
#endif

    window->ID = PXNull;
}

PXProcessThreadID PXWindowThreadProcessID(const PXWindowID windowID)
{
#if OSUnix
    return 0;
#elif OSWindows
    return GetWindowThreadProcessId(windowID, PXNull);
#endif
}

PXBool PXWindowTitleSetA(PXWindow* const window, const char* const title, const PXSize titleSize)
{
#if OSUnix
    return 0;
#elif OSWindows
    const PXBool success = SetWindowTextA(window->ID, title, titleSize);

    // could get extended error

    return success;
#endif
}

PXSize PXWindowTitleGetA(const PXWindow* const window, char* const title, const PXSize titleSize)
{
#if OSUnix
    return 0;
#elif OSWindows
    const int result = GetWindowTextA(window->ID, title, titleSize);
    const PXBool success = result > 0;

    // could get extended error

    return result;
#endif
}

PXWindowID PXWindowFindViaTitleA(const PXTextASCII windowTitle)
{
#if OSUnix
    return 0;
#elif OSWindows
    return FindWindowA(0, windowTitle);
#endif
}

PXWindowID PXWindowFindViaTitleW(const PXTextUNICODE windowTitle)
{
#if OSUnix
    return 0;
#elif OSWindows
    return FindWindowW(0, windowTitle);
#endif
}

PXWindowID PXWindowFindViaTitleU(const PXTextUTF8 windowTitle)
{
#if OSUnix
    return 0;
#elif OSWindows
    return FindWindowA(0, windowTitle);
#endif
}

void PXWindowIconCorner()
{
}

void PXWindowIconTaskBar()
{
}

void PXWindowLookupAdd(const PXWindow* window)
{
    currentWindow = window;
}

PXWindow* PXWindowLookupFind(const PXWindowID PXWindowID)
{
    return currentWindow;
}

void PXWindowLookupRemove(const PXWindow* window)
{
    currentWindow = 0;
}

void PXWindowSize(PXWindow* const pxWindow, unsigned int* x, unsigned int* y, unsigned int* width, unsigned int* height)
{
#if OSUnix
#elif OSWindows
    RECT rect;

    const unsigned char result = GetWindowRect(pxWindow->ID, &rect);
    const unsigned char success = result != 0;

    // Get Last Error

    *x = rect.left;
    *y = rect.top;
    *width = rect.right - *x;
    *height = rect.bottom - *y;
#endif
}

void PXWindowSizeChange(PXWindow* window, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height)
{
#if OSUnix
#elif OSWindows
    RECT rect;

    rect.left = x;
    rect.top = y;
    rect.right = width + x;
    rect.bottom = height + y;

    DWORD style = 0;
    DWORD exStyle = 0;

    //AdjustWindowRectEx();

    const unsigned char result = AdjustWindowRectEx(&rect, style, FALSE, exStyle);
    const unsigned char success = result != 0;

    // Get Last Error
#endif
}

void PXWindowPosition(PXWindow* window, unsigned int* x, unsigned int* y)
{
#if OSUnix

#elif OSWindows
    RECT rectangle;
    const PXBool success = GetWindowRect(window->ID, &rectangle);

    if (success)
    {
        window->X = rectangle.left;
        window->Y = rectangle.top;
        window->Width = rectangle.right - rectangle.left;
        window->Height = rectangle.bottom - rectangle.top;
    }

    printf("Sreen res %i x %i\n", window->Width, window->Height);
#endif
}

void PXWindowPositionChange(PXWindow* window, const unsigned int x, const unsigned int y)
{
}

void PXWindowPositonCenterScreen(PXWindow* window)
{
}

void PXWindowCursor(PXWindow* window)
{
}

void PXWindowCursorTexture()
{
}

void PXWindowCursorCaptureMode(PXWindow* window, const PXWindowCursorMode cursorMode)
{
    unsigned int horizontal = 0;
    unsigned int vertical = 0;

#if OSUnix
#elif OSWindows

    PXMonitorGetSize(&horizontal, &vertical);

    switch(cursorMode)
    {
        case PXWindowCursorShow:
        {
            printf("[Cursor] Show\n");

            while(ShowCursor(1) < 0);

            const unsigned char clipResult = ClipCursor(NULL);
            const HCURSOR cursorSet = SetCursor(window->CursorID);

            break;
        }
        case PXWindowCursorLock:
        {
            printf("[Cursor] Lock\n");

            // Capture cursor
            {
                RECT clipRect;
                GetClientRect(window->ID, &clipRect);
                ClientToScreen(window->ID, (POINT*)&clipRect.left);
                ClientToScreen(window->ID, (POINT*)&clipRect.right);
                ClipCursor(&clipRect);
            }

            break;
        }
        case PXWindowCursorLockAndHide:
        {
            printf("[Cursor] Lock and hide\n");

            while(ShowCursor(0) >= 0);

            {
                RECT clipRect;
                GetClientRect(window->ID, &clipRect);
                ClientToScreen(window->ID, (POINT*)&clipRect.left);
                ClientToScreen(window->ID, (POINT*)&clipRect.right);

                int xOff = (clipRect.right - clipRect.left) / 2;
                int yoFf = (clipRect.bottom - clipRect.top) / 2;

                clipRect.left += xOff;
                clipRect.top += yoFf;
                clipRect.right -= xOff;
                clipRect.bottom -= yoFf;

                unsigned char sucessClip = ClipCursor(&clipRect);
            }


            CURSORINFO cursorInfo;
            cursorInfo.cbSize = sizeof(CURSORINFO);

            const unsigned char sucessfulInfoGet = GetCursorInfo(&cursorInfo);

            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

            CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = 0;
            lpCursor.dwSize = sizeof(CONSOLE_CURSOR_INFO);
            unsigned char y = SetConsoleCursorInfo(console, &lpCursor);

            break;
        }
    }

    window->CursorModeCurrent = cursorMode;
#endif
}

PXBool PXWindowFrameBufferSwap(PXWindow* window)
{
    return PXGraphicImageBufferSwap(&window->GraphicInstance);
}

PXBool PXWindowInteractable(PXWindow* window)
{
    switch (window->CursorModeCurrent)
    {
        default:
        case PXWindowCursorIgnore:
        case PXWindowCursorShow:
            return PXFalse;

        case PXWindowCursorInvisible:
        case PXWindowCursorLock:
        case PXWindowCursorLockAndHide:
            return PXTrue;
    }
}

PXBool PXWindowCursorPositionInWindowGet(PXWindow* window, int* x, int* y)
{
    int xPos = 0;
    int yPos = 0;
    const PXBool sucessfulA = PXWindowCursorPositionInDestopGet(window, &xPos, &yPos);

#if OSUnix
    return PXFalse;

#elif OSWindows
    POINT point;
    point.x = xPos;
    point.y = yPos;

    const PXBool sucessful = ScreenToClient(window->ID, &point);  // are now relative to hwnd's client area

    if(sucessful)
    {
        *x = point.x;
        *y = point.y;
    }
    else
    {
        *x = 0;
        *y = 0;
    }

    return sucessful;
#endif
}

PXBool PXWindowCursorPositionInDestopGet(PXWindow* window, int* x, int* y)
{
#if OSUnix
    return PXFalse;

#elif OSWindows
    POINT point;
    point.x = 0;
    point.y = 0;

    const unsigned char sucessful = GetPhysicalCursorPos(&point);

    if(sucessful)
    {
        *x = point.x;
        *y = point.y;
    }
    else
    {
        *x = 0;
        *y = 0;
    }

    return sucessful;
#endif
}

PXBool PXWindowIsInFocus(const PXWindow* const window)
{
#if OSUnix
    return PXFalse;
#elif OSWindows
    const HWND windowIDInFocus = GetForegroundWindow(); // User32.dll, Windows 2000
    const PXBool isInFocus = window->ID == windowIDInFocus;

    return isInFocus;
#endif
}

void TriggerOnMouseScrollEvent(const PXWindow* window, const PXMouse* mouse)
{

}

void TriggerOnMouseClickEvent(const PXWindow* window, const MouseButton mouseButton, const ButtonState buttonState)
{
    const PXMouse* const mouse = &window->MouseCurrentInput;

    const char* buttonStateText = 0;
    const char* mouseButtonText = 0;

    switch(buttonState)
    {
        case ButtonStateInvalid:
            buttonStateText = "Invalid";
            break;

        case ButtonStateDown:
            buttonStateText = "Down";
            break;

        case ButtonStateHold:
            buttonStateText = "Hold";
            break;

        case ButtonStateRelease:
            buttonStateText = "Release";
            break;
    }

    switch(mouseButton)
    {
        case MouseButtonInvalid:
            mouseButtonText = "Invalid";
            break;

        case MouseButtonLeft:
            mouseButtonText = "Left";
            break;

        case MouseButtonMiddle:
            mouseButtonText = "Middle";
            break;

        case MouseButtonRight:
            mouseButtonText = "Right";
            break;

        case MouseButtonSpecialA:
            mouseButtonText = "Special A";
            break;

        case MouseButtonSpecialB:
            mouseButtonText = "Special B";
            break;

        case MouseButtonSpecialC:
            mouseButtonText = "Special C";
            break;

        case MouseButtonSpecialD:
            mouseButtonText = "Special D";
            break;

        case MouseButtonSpecialE:
            mouseButtonText = "Special E";
            break;
    }

    printf("[#][Event][Mouse] Button:%-10s State:%-10s\n", mouseButtonText, buttonStateText);

    InvokeEvent(window->MouseClickCallBack, window->EventReceiver, window, mouseButton, buttonState);
}

void TriggerOnMouseClickDoubleEvent(const PXWindow* window, const MouseButton mouseButton)
{
    InvokeEvent(window->MouseClickDoubleCallBack, window->EventReceiver, window, mouseButton);
}

void TriggerOnMouseMoveEvent(const PXWindow* window, const int positionX, const int positionY, const int deltaX, const int deltaY)
{
    PXMouse* mouse = &window->MouseCurrentInput;

    mouse->Position[0] = PXMathLimit(positionX, 0, window->Width);
    mouse->Position[1] = window->Height - PXMathLimit(positionY, 0, window->Height);
    mouse->Delta[0] = deltaX;
    mouse->Delta[1] = deltaY;
    mouse->PositionNormalisized[0] = mouse->Position[0] / (window->Width / 2.0f) - 1;
    mouse->PositionNormalisized[1] = mouse->Position[1] / (window->Height / 2.0f) - 1;

    InvokeEvent(window->MouseMoveCallBack, window->EventReceiver, window, mouse);
}

void TriggerOnMouseEnterEvent(const PXWindow* window, const PXMouse* mouse)
{
}

void TriggerOnMouseLeaveEvent(const PXWindow* window, const PXMouse* mouse)
{
}

void TriggerOnKeyBoardKeyEvent(const PXWindow* window, const KeyBoardKeyInfo keyBoardKeyInfo)
{
    printf("[#][Event][Key] ID:%-3i Name:%-3i State:%i\n", keyBoardKeyInfo.KeyID, keyBoardKeyInfo.Key, keyBoardKeyInfo.Mode);

    InvokeEvent(window->KeyBoardKeyCallBack, window->EventReceiver, window, keyBoardKeyInfo);
}

unsigned int CursorIconToID(const CursorIcon cursorIcon)
{
    switch (cursorIcon)
    {
        case CursorIconInvalid:
            return -1;

        case CursorIconNormal:
            return CursorIconNormalID;

        case CursorIconIBeam:
            return CursorIconIBeamID;

        case CursorIconWait:
            return CursorIconWaitID;

        case CursorIconCross:
            return CursorIconCrossID;

        case CursorIconUp:
            return CursorIconUpID;

        case CursorIconHand:
            return CursorIconHandID;

        case CursorIconNotAllowed:
            return CursorIconNoAllowedID;

        case CursorIconAppStarting:
            return CursorIconAppStartingID;

        case CursorIconResizeHorizontal:
            return CursorIconResizeHorizontalID;

        case CursorIconResizeVertical:
            return CursorIconResizeVerticalID;

        case CursorIconResizeClockwise:
            return CursorIconResizeClockwiseID;

        case CursorIconResizeClockwiseCounter:
            return CursorIconResizeClockwiseCounterID;

        case CursorIconResizeAll:
            return CursorIconResizeAllID;
    }
}
