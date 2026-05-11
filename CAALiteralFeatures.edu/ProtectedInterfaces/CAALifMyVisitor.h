// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifMyVisitor_H
#define CAALifMyVisitor_H


// LiteralFeatures interfaces
#include "CATIVisitor.h"
#include "CATBaseUnknown.h"

#include "CATVisitorAdapter.h"

#include "CAALifBasis.h"
// ================================================================
// 
// ABSTRACT
// --------
// 
// This class defines the CAALifMyVisitor implementation.
//
// ===========================================================================
//  Usage:
//  ------
//      Use in CAALifPublishMain
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//
//===========================================================================
class  ExportedByCAALifBasis CAALifMyVisitor : public CATVisitorAdapter
{
	  CATDeclareClass;
	  
public:
	  // Constructors
	  CAALifMyVisitor();
	  
	  // Destructor
	  virtual ~CAALifMyVisitor();
	  
	  /**
	  * Used by KBWare to append user parameters and relations to this object.
	  * In this case, this object is the Applications Root Feature that implements this interface
	  * @param iKBwareObject : 
	  *    Kbware object to append to the root object.
	  */
	  virtual HRESULT Visit         (CATBaseUnknown* iInstance );
	  	  
	  
private:
	  CAALifMyVisitor(const CAALifMyVisitor&);
	  
};

#endif
