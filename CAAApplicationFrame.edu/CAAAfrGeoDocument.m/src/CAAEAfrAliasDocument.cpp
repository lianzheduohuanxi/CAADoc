// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrAliasDocument.h"

// C++ standrad library 
#include <iostream.h>  


//
//  _______________ Extension of a CAAGeometry Document  _______________
//
// To create TIE Objects
#include "TIE_CATIDocAlias.h"              
TIE_CATIDocAlias(CAAEAfrAliasDocument); 

// To declare that the class is a data extension of (the late type) CAAGeometry.
// CAAGeometry is the identifier of the document which appears in the File->New
// Dialog Box. 
//
CATImplementClass(CAAEAfrAliasDocument, DataExtension, CATBaseUnknown,CAAGeometry);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAEAfrAliasDocument implements  CATIDocAlias  insert 
// the following lines in the interface dictionary:
//
//    CAAGeom CATIDocAlias      libCAAAfrGeoDocument
//
// _______________ Constructor - Destructor _____________________________
//

CAAEAfrAliasDocument::CAAEAfrAliasDocument()
{
  cout << "Constructing CAAEAfrAliasDocument"  << endl;
}

CAAEAfrAliasDocument::~CAAEAfrAliasDocument()
{ 
  cout << "Destructing CAAEAfrAliasDocument"  << endl;    
}

// _______________ CATIDocAlias _____________________________

CATUnicodeString CAAEAfrAliasDocument::GiveDocSuffix()
{ 
  cout << "CAAEAfrAliasDocument::GiveDocSuffix"  << endl;

  // This method returns the suffix of the document's file names.
  // Warning: this string must be less than or equal to 15 characters. 

  // It's the late type of another part of the document 
  // CATInit, CATIEditor and Co ...
  //
  return (CATUnicodeString("CAAGeom") );
}









