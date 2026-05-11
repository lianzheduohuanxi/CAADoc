// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrDocAlias.h"

// C++ standrad library 
#include <iostream.h>    

//---------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIDocAlias.h"              
TIE_CATIDocAlias(CAAEAfrDocAlias);

// To declare that the class is a data extension of (the late type) CAASample.
// CAASample is the identifier of the document which appears in the File->New
// Dialog Box. 
CATImplementClass(CAAEAfrDocAlias, DataExtension, CATBaseUnknown, CAASample);

// 
// To declare that CAAEAfrDocAlias implements CATIDocAlias, insert 
// the following line in the interface dictionary:
//
//    CAASample CATIDocAlias  libCAAAfrSampleDocument
//
//---------------------------------------------------------------------------------

CAAEAfrDocAlias::CAAEAfrDocAlias()
{
  cout << "Constructing CAAEAfrDocAlias"  << endl;
  // This constructor should not be explicitly called.
}

//---------------------------------------------------------------------------------

CAAEAfrDocAlias::~CAAEAfrDocAlias()
{ 
   cout << "Destructing CAAEAfrDocAlias"  << endl; 
   // This destructor should not be explicitly called.
}

//---------------------------------------------------------------------------------

CATUnicodeString CAAEAfrDocAlias::GiveDocSuffix()
{ 
  // This method returns the suffix of the document's file names.
  // Warning: this string must be less than or equal to 15 characters. 

   // It's the late type of another part of the document 
  // CATInit, CATIEditor and Co ...
  //
  cout << "CAAEAfrDocAlias::GiveDocSuffix"  << endl;

  return (CATUnicodeString("CAADoc"));
}

