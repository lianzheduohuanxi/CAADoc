// COPYRIGHT DASSAULT SYSTEMES 1994-2000

// Local framework
#include "CAAEOmmVerticalLine.h"     // needed as class header file

// ObjectModelerBase framework
#include "CATIAlias.h"               // needed to set and get feature end user name

// ObjectSpecsModeler framework
#include "CATISpecObject.h"          // needed to use the vertical line as a specification
#include "CATISpecAttrKey.h"       // needed to read and write specification attrbutes
#include "CATISpecAttrAccess.h"       // needed to read and write specification attrbutes

// MecModInterfaces framework
#include "CATIAHybridShapes.h"       // needed to set the vertical line in the exposed model
#include "CATMecModAutoServices.h"   // needed to convert internal objects with exposed ones

// sytem resources
#include <iostream.h>               // needed to insures code traces
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIAOmmVerticalLine.h"
TIE_CAAIAOmmVerticalLine( CAAEOmmVerticalLine);

CATImplementClass( CAAEOmmVerticalLine,
                   DataExtension,
                   CATBaseUnknown,
                   CAAOmmVerticalLine );
// Dictionary entry to be added :
// CAAOmmVerticalLine CAAIAOmmVerticalLine libCAAOmmImpl
 
//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : constructor
//-----------------------------------------------------------------------------
CAAEOmmVerticalLine::CAAEOmmVerticalLine(): CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : destructor
//-----------------------------------------------------------------------------
CAAEOmmVerticalLine::~CAAEOmmVerticalLine()
{
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_Application
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmVerticalLine::get_Application(CATIAApplication *& opiApplicationOnCATIA)
{
 cout  << "--> CAAEOmmVerticalLine::get_Application" << endl;

 HRESULT rc=E_FAIL;
 opiApplicationOnCATIA=NULL;

 // Retrieves OLE exposed parent class
 CATBaseDispatch* piBaseOnParent=NULL;
 rc=get_Parent(piBaseOnParent);

 // Then delegates the job to the parent (gets up until CATIA is found out)
 if (SUCCEEDED(rc)) {
    // NB : get_Parent methos returns a CATIABase based interface 
    // casted into a CATBaseDispatch one
    rc = ( (CATIABase*) piBaseOnParent)->get_Application(opiApplicationOnCATIA);
    piBaseOnParent->Release();
    piBaseOnParent = NULL ;
    }

  cout  << "<-- CAAEOmmVerticalLine::get_Application" << endl;


 return rc;
}


//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_Name
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmVerticalLine::get_Name(CATBSTR & oName)
{
   cout  << "CAAEOmmVerticalLine::get_Name" << endl;

   HRESULT     rc            = E_FAIL;
   CATIAlias* ipAliasOnThis = NULL;

   // Returns the OLE object name according to the model object name
   rc=QueryInterface(IID_CATIAlias, (void**) &ipAliasOnThis);
   if (SUCCEEDED(rc)) {
      CATUnicodeString str = ipAliasOnThis->GetAlias();
      ipAliasOnThis->Release();
      ipAliasOnThis = NULL ;
      str.ConvertToBSTR (&oName);
      } 
   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : put_Name
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmVerticalLine::put_Name(const CATBSTR & iName)
{
   cout  << "CAAEOmmVerticalLine::put_Name" << endl;
   // Method cannot be implemented in this case
   HRESULT rc = E_NOTIMPL;

   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : GetItem
//-----------------------------------------------------------------------------
HRESULT CAAEOmmVerticalLine::GetItem(const CATBSTR & iName, CATBaseDispatch *& opiBaseOnChildObject)
{
   cout  << "CAAEOmmVerticalLine::GetItem" << endl;
   // Method cannot be implemented in this case : unresolved symbols management should be done
   // thru CATIGenTrac interface
   HRESULT rc = E_NOTIMPL;

   return rc;
}


//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_Parent
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAEOmmVerticalLine::get_Parent(CATBaseDispatch *& opiBaseOnOLEParent)
{
   cout  << "--> CAAEOmmVerticalLine::get_Parent" << endl;
   HRESULT rc=E_FAIL;
   opiBaseOnOLEParent=NULL;

   // Gets the parent object as regards the OLE exposed model
   // i.e. the Hybrid Shapes collection, object aggregating this line
   CATISpecObject* ipSpecObjectOnThis = NULL;
   rc=QueryInterface(IID_CATISpecObject, (void**) &ipSpecObjectOnThis);
   if (SUCCEEDED(rc)) { 
      CATISpecObject * pParent = ipSpecObjectOnThis->GetFather();
      ipSpecObjectOnThis->Release();
      ipSpecObjectOnThis = NULL ;

      while ((NULL != pParent) && (NULL == opiBaseOnOLEParent)) 
      {
         CATISpecObject * pParentCurrent = pParent ;

         rc =  pParentCurrent->QueryInterface(IID_CATIAHybridShapes, (void**) &opiBaseOnOLEParent);

         pParent =  pParentCurrent -> GetFather();

         pParentCurrent->Release();
         pParentCurrent = NULL ;
      }
   }

   cout  << "<-- CAAEOmmVerticalLine::get_Parent" << endl;
   return rc;
}


//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : Compute()
//----------------------------------------------------------------------------
HRESULT __stdcall CAAEOmmVerticalLine::Compute()
{
   cout  << "CAAEOmmVerticalLine::Compute" << endl;
   HRESULT rc=E_FAIL;
   
   // Only calls the feature update mechanism
   CATISpecObject* ipSpecOnThis = NULL;
   rc=QueryInterface(IID_CATISpecObject, (void**) &ipSpecOnThis);
   if (SUCCEEDED(rc)) {
      ipSpecOnThis->Update();
      ipSpecOnThis->Release();
      ipSpecOnThis = NULL ;
      }
   
   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : AppendHybridShape()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::AppendHybridShape (CATIAHybridShape *ipiHybridShapeOnShape)
{
    // Returns E_FAIL since no other Shape cann be inserted in the line
   return (E_FAIL);
}


HRESULT  __stdcall CAAEOmmVerticalLine::get_Thickness (CATIAHybridShape * oThickness)
{
   return (E_FAIL);
}
//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_GeometricType()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::get_GeometricType(CatGeometricType & oType) 
{
    // Returns Unknown type, only used by sketcher objects 
   oType = catGeoTypeUnknown; 
   return S_OK;
}
 
//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_Point1()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::get_Point1(CATIAReference *& opiReferenceOnPoint1)
{
    // Method not implemented in this sample
    return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : put_Point1()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::put_Point1(CATIAReference *  ipiReferenceOnPoint1)
{
   cout  << "--> CAAEOmmVerticalLine::put_Point1" << endl;

   // Gets the current object as a Specification
   HRESULT rc=E_FAIL;

   CATISpecAttrAccess * piSpecAttrAccessOnThis=NULL;
   rc=QueryInterface(IID_CATISpecAttrAccess, (void**) &piSpecAttrAccessOnThis);
   if (FAILED(rc)) {
      return rc;
      }


   // Retrieves Point1 attribute
   CATISpecAttrKey* piAttrKeyOnSpec = piSpecAttrAccessOnThis->GetAttrKey("Point1");
   if (NULL==piAttrKeyOnSpec) {
       return E_FAIL;
       }

   // Decodes the reference and converts it as a feature
   CATISpecObject_var spSpecOnPoint1;
   rc = ::GetSpecFromReference (ipiReferenceOnPoint1, spSpecOnPoint1); 
   if (!SUCCEEDED(rc)) {
       return rc;
       }

   // Stores the pointed feature as an attribute
   piSpecAttrAccessOnThis->SetSpecObject(piAttrKeyOnSpec,spSpecOnPoint1);
   piAttrKeyOnSpec->Release();
   piAttrKeyOnSpec = NULL ;

   piSpecAttrAccessOnThis->Release();
   piSpecAttrAccessOnThis = NULL ;

   cout  << "<-- CAAEOmmVerticalLine::put_Point1" << endl;
   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : get_Point2()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::get_Point2(CATIAReference *& opiReferenceOnPoint2)
{
    // Method not implemented in this sample
    return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
// CAAEOmmVerticalLine : put_Point2()
//----------------------------------------------------------------------------
HRESULT  __stdcall CAAEOmmVerticalLine::put_Point2(CATIAReference *  ipiReferenceOnPoint2)
{
   cout  << "--> CAAEOmmVerticalLine::put_Point2" << endl;

   HRESULT rc=E_FAIL;

   CATISpecAttrAccess * piSpecAttrAccessOnThis=NULL;
   rc=QueryInterface(IID_CATISpecAttrAccess, (void**) &piSpecAttrAccessOnThis);
   if (FAILED(rc)) {
      return rc;
      }


   // Retrieves Point1 attribute
   CATISpecAttrKey* piAttrKeyOnSpec = piSpecAttrAccessOnThis->GetAttrKey("Point2");
   if (NULL==piAttrKeyOnSpec) {
       return E_FAIL;
       }

   // Decodes the reference and converts it as a feature
   CATISpecObject_var spSpecOnPoint2;
   rc = ::GetSpecFromReference (ipiReferenceOnPoint2, spSpecOnPoint2); 
   if (!SUCCEEDED(rc)) {
       return rc;
       }

   // Stores the pointed feature as an attribute
   piSpecAttrAccessOnThis->SetSpecObject(piAttrKeyOnSpec,spSpecOnPoint2);
   piAttrKeyOnSpec->Release();
   piAttrKeyOnSpec = NULL ;

   piSpecAttrAccessOnThis->Release();
   piSpecAttrAccessOnThis = NULL ;

   cout  << "<-- CAAEOmmVerticalLine::put_Point2" << endl;
   return rc;
}
