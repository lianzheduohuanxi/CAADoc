// COPYRIGHT DASSAULT SYSTEMES 2004
//===================================================================
//
// CAAAniImportDefine.h
// Provide implementation to interface  CATISamImportDefine
//
//===================================================================
//
#ifndef CAAAniImportDefine_H
#define CAAAniImportDefine_H

#include "CATESamImportDefineAdaptor.h"
#include "CATError.h"

//-----------------------------------------------------------------------
/**
* Class extending the object CATISamImportDefine.
* <br>
* It implements the interface :
*  <ol>
*  <li>@see CATAnalysisInterfaces.CATISamImportDefine with the adapter CATESamImportDefineAdaptor
*  </ol>
*/
class CAAAniImportDefine: public CATESamImportDefineAdaptor
{
  CATDeclareClass;
  
  public:
  
  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
		CAAAniImportDefine ();
    virtual ~CAAAniImportDefine ();
    
  //
  // CATISamImportDefine interface
  //
    HRESULT GetFileTypes(CATListValCATString& oTypes);

    HRESULT GetCommentForType(const CATString iType,CATUnicodeString& oComment);

    HRESULT Import (CATDocument * iImportedDoc, CATDocument * iAnalysisDoc);
    
  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
		CAAAniImportDefine (CAAAniImportDefine &);
    CAAAniImportDefine& operator=(CAAAniImportDefine&);
};

#endif
