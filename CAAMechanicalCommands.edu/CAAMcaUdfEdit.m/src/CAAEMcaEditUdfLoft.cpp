// COPYRIGHT Dassault Systemes 2002

//Local framework
#include "CAAEMcaEditUdfLoft.h"
#include "CAAMcaUdfLoftEditCreateCmd.h" // The command to edit the user feature

// ObjectModelerBase framework
#include "CATISpecObject.h"   

// Visualization framework
#include "CATPathElement.h"

// C++ Standard Library
#include "iostream.h"


// To declare that the class 
// is a DataExtension of (late type) CAAUdfLoft
//
CATImplementClass( CAAEMcaEditUdfLoft,
                   DataExtension,
                   CATIEdit,
                   CAAUdfLoft);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, CAAEMcaEditUdfLoft);

// 
// To declare that CAAUdfLoft implements CATIEdit, insert 
// the following line in the interface dictionary:
//
//   CAAUdfLoft  CATIEdit libCAAMcaUdfEdit
//
//---------------------------------------------------------------------------


//-----------------------------------------------------------------------------

CAAEMcaEditUdfLoft::CAAEMcaEditUdfLoft()
{
   cout <<"CAAEMcaEditUdfLoft::CAAEMcaEditUdfLoft" << endl;
}

//-----------------------------------------------------------------------------

CAAEMcaEditUdfLoft::~CAAEMcaEditUdfLoft()
{
   cout <<"CAAEMcaEditUdfLoft::CAAEMcaEditUdfLoft" << endl;
}
 
//-----------------------------------------------------------------------------

CATCommand * CAAEMcaEditUdfLoft::Activate (CATPathElement *  iPath)
{
    cout << "CAAEMcaEditUdfLoft::Activate" << endl;

   CATCommand * pCommand = NULL ;

   if ( NULL != iPath ) 
   {
       CATBaseUnknown* piUk= NULL;
       piUk= iPath->CurrentElement();

       if ( NULL != piUk ) 
       {
   	   CATISpecObject *piSpecOnEditFeature = NULL;
   	   HRESULT rc = piUk->QueryInterface(IID_CATISpecObject, 
                                             (void **)&piSpecOnEditFeature);
   	   if (SUCCEEDED(rc))
           {
   	      // creates the edition command
              pCommand =  new CAAMcaUdfLoftEditCreateCmd( piSpecOnEditFeature );

              // releases useless pointer
   	      piSpecOnEditFeature->Release();
              piSpecOnEditFeature = NULL;
           }
       }   
   }
   return pCommand ;
}
