// COPYRIGHT DASSAULT SYSTEMES  1994 2001

//Local Framework
#include "CAALifBasis.h"
#include "CAALifMyVisitor.h"

// ObjectSpecsModeler 
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

#include "iostream.h"

//LiteralFeatures
#include "CATICkeParm.h"
#include "CATICkeRelation.h"
// ================================================================
// 
// ABSTRACT
// --------
// 
// This class defines the CAALifMyVisitor implementation of the CATIVisitor interface.
// A visitor is an object which performs an action on an instance.
// It used by the method VisitChildren of the CATIParmPublisher interface.
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifPublishMain
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATBaseUnknown
//
//===========================================================================

#include "TIE_CATIVisitor.h"
TIE_CATIVisitor(CAALifMyVisitor);


CATImplementClass(CAALifMyVisitor, Implementation, CATBaseUnknown, CATNull);

CAALifMyVisitor::CAALifMyVisitor() : CATVisitorAdapter()
{    
}

CAALifMyVisitor::~CAALifMyVisitor()
{
}

CAALifMyVisitor::CAALifMyVisitor(const CAALifMyVisitor& iVisit)
{
    
}

/**
* For each instance I want its name only if it is a parameter.
*/

HRESULT CAALifMyVisitor::Visit  (CATBaseUnknown* iInstance )
{
    
    CATICkeParm* piParm = NULL;
    if(iInstance == NULL )
        return S_FALSE;
    
    HRESULT hr = iInstance->QueryInterface(IID_CATICkeParm,(void **)&piParm);
    if (SUCCEEDED(hr))
    {
        cout << "I am a parameter and my name is : " << piParm->Name().ConvertToChar() << endl;
        piParm->Release();
    }
    
    
    return S_OK;
}







