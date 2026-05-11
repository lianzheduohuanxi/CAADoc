// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrChangeViewNormalCmd.h"

// To set the current window plane 
//ApplicationFrame framework
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"
#include "CATI3DCamera.h"
#include "CATFrm3DCamera.h"
// Mathematics Framework
#include "CATMathVector.h"
#include "CATMathPoint.h"

//C++ standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAAfrChangeViewNormalCmd,void *);

//-------------------------------------------------------------------------

CAAAfrChangeViewNormalCmd::CAAAfrChangeViewNormalCmd(void *iArgument): 
                       CATCommand(NULL,"ViewNormalId")
{
  cout << "CAAAfrChangeViewNormalCmd void constructor" << endl ; 
  
  //By default a CATCommand is undefined, we change by the exclusive mode
  RequestStatusChange(CATCommandMsgRequestExclusiveMode);

  // To be 64 bits complient
  _ArgumentCmd = CATPtrToINT32(iArgument) ;

}

//--------------------------------------------------------------------------

CAAAfrChangeViewNormalCmd::~CAAAfrChangeViewNormalCmd()
{
  cout << "CAAAfrChangeViewNormalCmd destructor" << endl ;
  _ArgumentCmd = NULL ;
}

//--------------------------------------------------------------------------

CATStatusChangeRC CAAAfrChangeViewNormalCmd::Activate(CATCommand * iFromClient,
                                                      CATNotification *iEvtData)
{
  cout << "CAAAfrChangeViewNormalCmd Activate" <<  _ArgumentCmd << endl ;

  CATMathVector direction ;
  CATMathVector zenith ;
  CATMathPoint     origin ;

  switch ( _ArgumentCmd )
  {
    // normal view = x axis
    case 1 : direction.SetCoord(-1.f,0.f,0.f); zenith.SetCoord(0.f,0.f,1.f);
             break ;
    // normal view = y axis
    case 2 : direction.SetCoord(0.f,-1.f,0.f); zenith.SetCoord(0.f,0.f,-1.f);
             break ;
    // normal view = z axis
    case 3 : direction.SetCoord(0.f,0.f,-1.f); zenith.SetCoord(0.f,1.f,0.f);
             break ;
  }       

  //
  // Change the camera with the new normal view 
  //
  CATFrmLayout * pCurrentLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL != pCurrentLayout )
  {
    CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
    if ( NULL != pCurrentWindow )
    {
      CATFrm3DCamera * pCameraImpl = new CATFrm3DCamera("cam3d",origin,direction,zenith);
      CATI3DCamera * pi3DCamera = NULL;                
      HRESULT rc = pCameraImpl->QueryInterface(IID_CATI3DCamera, (void**)&pi3DCamera);
      if (SUCCEEDED(rc))
      {
        // The camera is applied on the current viewer of
        // the window
        // If the current viewer is a 2D, this call has no effect
        //
        pCurrentWindow->SetCurrentCamera(pi3DCamera);
        pi3DCamera->Release();
        pi3DCamera = NULL ;
      }
      pCameraImpl->Release();
      pCameraImpl = NULL ;
    }
  }  
  return CATStatusChangeRCCompleted ;
}

//---------------------------------------------------------------------

CATStatusChangeRC CAAAfrChangeViewNormalCmd::Cancel(CATCommand * iFromClient,
								 CATNotification *iEvtData)
{
   cout << "CAAAfrChangeViewNormalCmd Cancel" << endl ;

  // This method is called when this command is cancelled by another exclusive
  // command. But a simple CATCommand is not automatically deallocated.
  // A request of deallocation must be done here.
  RequestDelayedDestruction();

  return CATStatusChangeRCCompleted ;
}
