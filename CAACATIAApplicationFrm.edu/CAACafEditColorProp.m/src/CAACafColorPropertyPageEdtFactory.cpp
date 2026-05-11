//===========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include <CAACafColorPropertyPageEdtFactory.h>

// Macro to automatically create the factory class as a data 
// extension of the CATEditorManager class.
//
CAT_EDITOR_DEFINE_FACTORY(CAACafColorPropertyPageEdt, CAACafColorPropertyPageEdt);


// To create the TIE object
// Warning : CAACafColorPropertyPageEdtFactory = CAACafColorPropertyPageEdt + Factory
// where CAACafColorPropertyPageEdt is the class created by the factory. 
// 
#include <TIE_CAAICafColorPropertyPageEdtFactory.h>
TIE_CAAICafColorPropertyPageEdtFactory(CAACafColorPropertyPageEdtFactory);


//
// To declare that CATEditorManager implements CAAIColorPropertyPageEdtFactory, 
// insert the following line in the interface dictionary:
// 
//   CATEditorManager  CAAIColorPropertyPageEdtFactory  libCATAfrEduEditProp
//


//
// To declare that the factory creates an instance of the CAACafColorPropertyPageEdt 
// class, insert the following line in the factory dictionary:
// 
//   CAACafColorPropertyPageEdt         CAAICafColorPropertyPageEdtFactory

