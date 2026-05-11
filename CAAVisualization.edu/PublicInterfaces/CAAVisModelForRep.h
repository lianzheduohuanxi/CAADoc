// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAVisModelForRep
#define ExportedByCAAVisModelForRep __declspec(dllexport)
#else
#define ExportedByCAAVisModelForRep __declspec(dllimport)
#endif
#else
#define ExportedByCAAVisModelForRep
#endif
