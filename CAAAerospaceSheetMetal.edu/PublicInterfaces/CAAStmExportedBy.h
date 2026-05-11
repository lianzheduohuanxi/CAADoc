#ifdef _WINDOWS_SOURCE 

// COPYRIGHT DASSAULT SYSTEMES 2005
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************

#ifdef __CAAStmServices
#define ExportedByCAAStmServices    __declspec(dllexport) 
#else 
#define ExportedByCAAStmServices    __declspec(dllimport) 
#endif 

#else 
#define ExportedByCAAStmServices
#endif
