#ifndef CAACafColorPropertyPageEdtFactory_h
#define CAACafColorPropertyPageEdtFactory_h
//===========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Factory class for CAACafColorPropertyPageEdt. It implements the 
//  CAAICafColorPropertyPageEdtFactory interface.
//
//  CAACafColorPropertyPageEdt is the Color Property Page Editor 
//
//===========================================================================


// Contains the CAT_EDITOR_DECLARE_FACTORY macro
#include <CATEditorFactory.h>

// Needed by the CAT_EDITOR_DECLARE_FACTORY macro
#include <CAACafColorPropertyPageEdt.h>

#define ExportedByNOTHING

// Used in conjunction with CAT_EDITOR_DEFINE_FACTORY in the .cpp file 
CAT_EDITOR_DECLARE_FACTORY(NOTHING, CAACafColorPropertyPageEdt, CAACafColorPropertyPageEdt);

#endif
