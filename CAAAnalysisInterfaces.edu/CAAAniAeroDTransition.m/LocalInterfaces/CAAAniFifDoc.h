// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CAAFifDoc.h
// Provide implementation to interface  CATIPersistent
// This will allow to consider the extented file as a CATDocument
//===================================================================
//
//
//===================================================================
//
//  Aug 2000  Creation:  GFT
//===================================================================
#ifndef CAAAniFifDoc_H
#define CAAAniFifDoc_H

#include "CATBaseUnknown.h"
#include "CATIPersistent.h"                

class CAAAniFifDoc : public CATBaseUnknown
{  
  CATDeclareClass;
  
 public:
  CAAAniFifDoc();
  ~CAAAniFifDoc();

  // CATIPersistent interface
  CATBoolean Dirty () ;
  void Save () ;
  void SaveAs(char * storagePrintableName,CATBoolean readOnly) ;
  void Load(char * storagePrintableName,CATBoolean readOnly);
  void SaveAs_B (SEQUENCE(octet) storageName, CATBoolean becameCurrent) ;
  void Load_B (SEQUENCE(octet) storageName, CATBoolean readOnly) ;

};

#endif
