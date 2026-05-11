#ifndef CAACafTexturePropertyPageEdtFactory_h
#define CAACafTexturePropertyPageEdtFactory_h
//===========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Factory class for CAACafTexturePropertyPageEdt. It implements the 
//  CAAICafTexturePropertyPageEdtFactory interface.
//
//  CAACafTexturePropertyPageEdt is the Texture Property Page Editor 
//
//===========================================================================


// Contains the CAT_EDITOR_DECLARE_FACTORY macro
#include <CATEditorFactory.h>

// Needed by the CAT_EDITOR_DECLARE_FACTORY macro
#include <CAACafTexturePropertyPageEdt.h>

#define ExportedByNOTHING

// Used in conjunction with CAT_EDITOR_DEFINE_FACTORY in the .cpp file 
CAT_EDITOR_DECLARE_FACTORY(NOTHING, CAACafTexturePropertyPageEdt, CAACafTexturePropertyPageEdt);

#endif
