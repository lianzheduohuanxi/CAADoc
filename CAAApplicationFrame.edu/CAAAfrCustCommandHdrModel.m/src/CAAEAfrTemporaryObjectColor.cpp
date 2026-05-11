// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEAfrTemporaryObjectColor.h"
#include "CAAAfrComboColorNotification.h"

// System Framework
#include "CATCallbackManager.h"

// C++ Standrad Library
#include <iostream.h>

//--------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAIAfrTemporaryObjectColor.h"              
TIE_CAAIAfrTemporaryObjectColor(CAAEAfrTemporaryObjectColor); 


// To declare that the class is a data extension oof CAASysGeomRootObj
// The UI active object of the CAAGeometry document
//
CATImplementClass (CAAEAfrTemporaryObjectColor,DataExtension, CATBaseUnknown, CAASysGeomRootObj);

// 
// To declare that CAAEAfrTemporaryObjectColor implements CAAIAfrGetTemporaryObjectColor, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomRootObj  CAAIAfrTemporaryObjectColor  libCAAAfrCustomizedCommandHeader
//
//-----------------------------------------------------------------------------

CAAEAfrTemporaryObjectColor::CAAEAfrTemporaryObjectColor(): CATBaseUnknown()
                            
{
    cout << " construction of CAAEAfrTemporaryObjectColor" << endl ;

   _RedComp   = 255   ;
   _GreenComp = 10    ;
   _BlueComp  = 0     ; 
}

//------------------------------------------------------------------------------

CAAEAfrTemporaryObjectColor::~CAAEAfrTemporaryObjectColor()
{
    cout << "Destruction of CAAEAfrTemporaryObjectColor" << endl ;
}

//------------------------------------------------------------------------------

HRESULT CAAEAfrTemporaryObjectColor::GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const
{
    
   oRed   = _RedComp ;
   oGreen = _GreenComp ;
   oBlue  = _BlueComp ; 

   return (S_OK) ;

}

//------------------------------------------------------------------------------

HRESULT CAAEAfrTemporaryObjectColor::SetCurrentColor(int & iRed, int & iGreen, int & iBlue) 
{
    
   _RedComp   = iRed   ;
   _GreenComp = iGreen;
   _BlueComp  = iBlue; 

    CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
    if ( NULL != pCBManager )
    {
         CAAAfrComboColorNotification * pNotification = new CAAAfrComboColorNotification();
         pCBManager->DispatchCallbacks(pNotification,this);
         pNotification->Release();
         pNotification= NULL ;
    }

   return (S_OK) ;
}

//------------------------------------------------------------------------------





