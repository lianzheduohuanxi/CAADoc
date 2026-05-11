// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrInit.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"

// C++ standrad library 
#include <iostream.h>  

// System framework 
#include "CATErrorDef.h"  // For the SUCCEEDED macro
#include "CATInstantiateComponent.h"


//---------------------------------------------------------------------------------
//
// To create TIE Objects
#include "TIE_CATInit.h"              
TIE_CATInit(CAAEAfrInit); 

// To declare that the class is a data extension of (the late type) CAADoc 
// (which is the document suffix)
//
CATImplementClass(CAAEAfrInit, DataExtension, CATBaseUnknown,CAADoc);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAEAfrInit implements  CATIinit  insert 
// the following lines in the interface dictionary:
//
//    CAADoc CATInit  libCAAAfrSampleDocument
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------

CAAEAfrInit::CAAEAfrInit():_pSampContainer(NULL)
{
  cout << "Constructing CAAEAfrInit"  << endl;
}

//---------------------------------------------------------------------------------

CAAEAfrInit::~CAAEAfrInit()
{ 
  cout << "Destructing CAAEAfrInit"  << endl; 
  
  if ( NULL != _pSampContainer )
  {
    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pSampContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      piSysCollection->Empty();
      piSysCollection->Release(); 
      piSysCollection = NULL ;
    }
    _pSampContainer->Release();
    _pSampContainer = NULL ;
  }

}

//---------------------------------------------------------------------------------

void CAAEAfrInit::Init(CATBoolean iDestroyExistingData)  
{
   cout << "CAAEAfrInit::Init"  << endl;
   
  // Creation of the container of the document
  // which contains all the objects of the document
   ::CATInstantiateComponent("CAASysSampCont",IID_CATBaseUnknown,(void**)&_pSampContainer);
 
}

//---------------------------------------------------------------------------------

CATBaseUnknown* CAAEAfrInit::GetRootContainer (const CATIdent InterfaceID)
{
  cout << "CAAEAfrInit::GetRootContainer"  << endl;

  if ( NULL != _pSampContainer )
  {
	 return ( _pSampContainer->QueryInterface(InterfaceID) );                                      
  }
  return _pSampContainer ;

}








