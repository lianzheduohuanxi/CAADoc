#ifndef CAACafViewPropertyPageEdtFactory_h
#define CAACafViewPropertyPageEdtFactory_h
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

//  
//  Sample to explain how to implement a Tools Options Properties Page   
//  factory interface, named CAAICafViewPropertyPageEdtFactory here. 
//  


// Contains the CAT_EDITOR_DECLARE_FACTORY macro
#include <CATEditorFactory.h>

// Local Framework
#include <CAACafViewPropertyPageEdt.h>

#define ExportedByNOTHING

// Used in conjunction with CAT_EDITOR_DEFINE_FACTORY2 in the .cpp file 
CAT_EDITOR_DECLARE_FACTORY(NOTHING, CAACafViewPropertyPageEdt, CAACafViewPropertyPageEdt);

#endif
