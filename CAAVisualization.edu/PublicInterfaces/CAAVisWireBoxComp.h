// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAVisWireBoxComp
#define ExportedByCAAVisWireBoxComp __declspec(dllexport)
#else
#define ExportedByCAAVisWireBoxComp __declspec(dllimport)
#endif
#else
#define ExportedByCAAVisWireBoxComp
#endif
