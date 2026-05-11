//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local framework
#include <CAACafElementPropertyPageEdtFactory.h>


// Macro to automatically create the factory class for the
// Tools Options Property page as a 
// data extension of the CATEditorManager2 class .
//
CAT_EDITOR_DEFINE_FACTORY2(CAACafElementPropertyPageEdt, CAACafElementPropertyPageEdt);

// To create the TIE Object
// Warning: CAACafElementPropertyPageEdtFactory = CAACafElementPropertyPageEdt + Factory
// where CAACafElementPropertyPageEdt is the class instantiated by the factory. 
// 
#include <TIE_CAAICafElementPropertyPageEdtFactory.h>
TIE_CAAICafElementPropertyPageEdtFactory(CAACafElementPropertyPageEdtFactory);


//
// To declare that CATEditorManager2 implements CAAICafElementPropertyPageEdtFactory, 
// insert the following line in the interface dictionary:
// 
//   CATEditorManager2 CAAICafElementPropertyPageEdtFactory  libCAACafEltToolsOptions
//


// To declare that the factory creates an instance of the CAACafElementPropertyPageEdt 
// class, insert the following line in the factory dictionary:
// 
//  CAACafElementPropertyPageEdt      CAAICafElementPropertyPageEdtFactory
