//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local framework
#include <CAACafViewPropertyPageEdtFactory.h>

// Macro to automatically create the factory class for the
// Tools Options Property page as a 
// data extension of the CATEditorManager2 class .
//
CAT_EDITOR_DEFINE_FACTORY2(CAACafViewPropertyPageEdt, CAACafViewPropertyPageEdt);


// To create the TIE Object
// Warning : CAACafViewPropertyPageEdtFactory = CAACafViewPropertyPageEdt + Factory
// where CAACafViewPropertyPageEdt is the class created by the factory. 
// 
#include <TIE_CAAICafViewPropertyPageEdtFactory.h>
TIE_CAAICafViewPropertyPageEdtFactory(CAACafViewPropertyPageEdtFactory);

//
// To declare that CATEditorManager2 implements CAAICafViewPropertyPageEdtFactory, 
// insert the following line in the interface dictionary:
// 
//   CATEditorManager2 CAAICafViewPropertyPageEdtFactory  libCAACafViewToolsOptions
//

// To declare that the factory creates an instance of the CAACafViewPropertyPageEdt 
// class, insert the following line in the factory dictionary:
// 
//  CAACafViewPropertyPageEdt      CAAICafViewPropertyPageEdtFactory
