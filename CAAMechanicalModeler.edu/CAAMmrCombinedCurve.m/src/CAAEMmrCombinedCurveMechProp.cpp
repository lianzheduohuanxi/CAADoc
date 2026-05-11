// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================

// Local Framework
#include "CAAEMmrCombinedCurveMechProp.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"   // temporary

// Visualization Framework
#include "CATIModelEvents.h"  // to update the display
#include "CATModify.h"        // to update the display

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"  // to refresh the specification tree

// for cout
#include "iostream.h"

CATImplementClass ( CAAEMmrCombinedCurveMechProp ,
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CombinedCurve        );

//-----------------------------------------------------------------------------
#include "TIE_CATIMechanicalProperties.h" // needed to tie the implementation to its interface
TIE_CATIMechanicalProperties( CAAEMmrCombinedCurveMechProp);
//-----------------------------------------------------------------------------

// To declare that CombinedCurve implements CATIMechanicalProperties, insert 
// the following line in the interface dictionary:
//
// CombinedCurve  CATIMechanicalProperties  libCAAMmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEMmrCombinedCurveMechProp::CAAEMmrCombinedCurveMechProp()
{
    cout <<" CAAEMmrCombinedCurveMechProp::CAAEMmrCombinedCurveMechProp" << endl;
    _status = 0 ;
}

//-------------------------------------------------------------------------------------
CAAEMmrCombinedCurveMechProp::~CAAEMmrCombinedCurveMechProp()
{
    cout <<" CAAEMmrCombinedCurveMechProp::~CAAEMmrCombinedCurveMechProp" << endl;
}

//-------------------------------------------------------------------------------------
int CAAEMmrCombinedCurveMechProp::IsInactive() const
{
    cout <<" CAAEMmrCombinedCurveMechProp::IsInactive:" << _status << endl;
    return _status ;
}

//-------------------------------------------------------------------------------------

void CAAEMmrCombinedCurveMechProp::Activate()  
{
    cout <<" CAAEMmrCombinedCurveMechProp::Activate" << endl;

    // begin of temporary code 
    // If you use a knowlege parameter 
    //    - you can manage the parameter in fx command
    //    - to need to use SetUptoDate, the CATModifyEvent will automatically do it 
    // 
    _status = 0 ;
    CATISpecObject * piSpecObject= NULL;                
    HRESULT rc = QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if ( SUCCEEDED(rc) )
    {
        piSpecObject->SetUpToDate(FALSE) ;

        piSpecObject->Release();
        piSpecObject = NULL ;
    }
    // end of temporary code 

    // Refresh the specification tree
    CATIRedrawEvent * piRedrawEvent = NULL;                
    rc = QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
    if ( SUCCEEDED(rc) )
    {
       piRedrawEvent->Redraw();

       piRedrawEvent->Release();
       piRedrawEvent = NULL ;
    }

    //Update the display
    CATIModelEvents * piModelEvent = NULL;                
    rc = QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
    
    if (SUCCEEDED(rc))
    {
         
        CATModify notif = this;
        piModelEvent->Dispatch(notif);
         
        piModelEvent->Release();
        piModelEvent=NULL;
    }
    

}

//-------------------------------------------------------------------------------------

void CAAEMmrCombinedCurveMechProp::InActivate() 
                         
{
    cout <<" CAAEMmrCombinedCurveMechProp::InActivate" << endl;

    // begin of temporary code 
    // If you use a knowlege parameter 
    //    - you can manage the parameter in fx command
    //    - to need to use SetUptoDate, the CATModifyEvent will automatically do it 
    // 
    _status = 1 ;
    CATISpecObject * piSpecObject= NULL;                
    HRESULT rc = QueryInterface(IID_CATISpecObject, (void**)&piSpecObject);
    if ( SUCCEEDED(rc) )
    {
        piSpecObject->SetUpToDate(FALSE) ;
        piSpecObject->Release();
        piSpecObject = NULL ;
    }
    // end of temporary code 


    // Refresh the specification tree
    CATIRedrawEvent * piRedrawEvent = NULL;                
    rc = QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
    if ( SUCCEEDED(rc) )
    {
       piRedrawEvent->Redraw();

       piRedrawEvent->Release();
       piRedrawEvent = NULL ;
    }

    //Update the display
    CATIModelEvents * piModelEvent = NULL;                
    rc = QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
    
    if (SUCCEEDED(rc))
    {
         
        CATModify notif = this;
        piModelEvent->Dispatch(notif);
         
        piModelEvent->Release();
        piModelEvent=NULL;
    }	 



}


