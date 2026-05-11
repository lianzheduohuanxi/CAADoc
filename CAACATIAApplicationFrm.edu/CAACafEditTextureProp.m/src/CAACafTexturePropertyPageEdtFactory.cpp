//===========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include <CAACafTexturePropertyPageEdtFactory.h>

// Macro to automatically create the factory class as a data 
// extension of the CATEditorManager class.
//
CAT_EDITOR_DEFINE_FACTORY(CAACafTexturePropertyPageEdt, CAACafTexturePropertyPageEdt);


// To create the TIE object
// Warning : CAACafTexturePropertyPageEdtFactory = CAACafTexturePropertyPageEdt + Factory
// where CAACafTexturePropertyPageEdt is the class created by the factory. 
// 
#include <TIE_CAAICafTexturePropertyPageEdtFactory.h>
TIE_CAAICafTexturePropertyPageEdtFactory(CAACafTexturePropertyPageEdtFactory);


//
// To declare that CATEditorManager implements CAAITexturePropertyPageEdtFactory, 
// insert the following line in the interface dictionary:
// 
//   CATEditorManager  CAAITexturePropertyPageEdtFactory  libCATAfrEduEditTextureProp
//


//
// To declare that the factory creates an instance of the CAACafTexturePropertyPageEdt 
// class, insert the following line in the factory dictionary:
// 
//   CAACafTexturePropertyPageEdt         CAAICafTexturePropertyPageEdtFactory

