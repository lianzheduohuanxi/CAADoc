// COPYRIGHT DASSAULT SYSTEMES 2003

//=============================================================================
//
//  Header to declare the CLSID of the component CAASysComponent.
//
//  The CLSID is the first argument of the global function CATCreateInstance
//  used to create an instance of the component having this CLSID.
//
//  The CLSID of a component is referred to by the name : CLSID_<component name>.
//  Here we hence declare a variable named CLSID_CAASysComponent
//
//  In CAASystem.edu/Cnext/code/dictionary/CAASystem.edu.clsid we have :
//  # component CLSID     component name      component implementation library
//
//    {*-*-GUID-*-*}      CAASysComponent     CAASysComponentImpl
//  
//=============================================================================

// System Framework
#include "IUnknown.h"

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysComponentCLSID
#define ExportedByCAASysComponentCLSID __declspec(dllexport)
#else
#define ExportedByCAASysComponentCLSID __declspec(dllimport)
#endif
#else
#define ExportedByCAASysComponentCLSID
#endif

extern "C" ExportedByCAASysComponentCLSID const CLSID CLSID_CAASysComponent;
