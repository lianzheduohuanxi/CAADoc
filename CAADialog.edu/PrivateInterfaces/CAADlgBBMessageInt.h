#ifdef _WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 1999
// Header used to expose services from the CAADlgBBMessage
// module
//
#if defined(__CAADlgBBMessageInt)
#define ExportedByCAADlgBBMessageInt __declspec(dllexport)
#else
#define ExportedByCAADlgBBMessageInt __declspec(dllimport)
#endif
#else
#define ExportedByCAADlgBBMessageInt
#endif
