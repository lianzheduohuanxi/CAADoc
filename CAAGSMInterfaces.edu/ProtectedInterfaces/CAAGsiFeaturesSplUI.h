#ifdef _WINDOWS_SOURCE 

// COPYRIGHT DASSAULT SYSTEMES 2006
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************

#ifdef __CAAGsiFeaturesSplUI
#define ExportedByCAAGsiFeaturesSplUI  __declspec(dllexport) 
#else 
#define ExportedByCAAGsiFeaturesSplUI  __declspec(dllimport) 
#endif 
#else 
#define ExportedByCAAGsiFeaturesSplUI
#endif
