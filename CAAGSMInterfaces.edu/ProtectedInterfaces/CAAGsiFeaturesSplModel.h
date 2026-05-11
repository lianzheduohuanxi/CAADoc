#ifdef _WINDOWS_SOURCE 

// COPYRIGHT DASSAULT SYSTEMES 2006
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************

#ifdef __CAAGsiFeaturesSplModel
#define ExportedByCAAGsiFeaturesSplModel    __declspec(dllexport) 
#else 
#define ExportedByCAAGsiFeaturesSplModel    __declspec(dllimport) 
#endif 
#else 
#define ExportedByCAAGsiFeaturesSplModel
#endif
