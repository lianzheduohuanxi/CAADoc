// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgInterApplication.h"

// Local Framework
#include "CAADlgTessellation.h"
#include "CAADlgObject.h"
#include "CAADlgTimeOutCommand.h"

// For Windows
#ifdef _WINDOWS_SOURCE
#include "CATDlgDocument.h"
#endif

//C++ Standard Library
#include <iostream.h>
//-------------------------------------------------------------------------

// ---------------------------------------------------
// Data used by the OnIdleCallbackMethod global method
// ---------------------------------------------------

static CAADlgInterApplication * CAADlgIdleApplication;

// ------------------------------
// On idle callback global method
// ------------------------------

void OnIdleCallbackMethod() 
{
  CAADlgIdleApplication->OnIdle();
}


//-------------------------------------------------------------------------

CAADlgInterApplication::CAADlgInterApplication(const CATString& iIdentifier):
                        CATInteractiveApplication(NULL, iIdentifier) 
{

  cout << endl <<"The CAADlgInterApplication begins..... " <<endl << endl;

  _CAADlgCount=0;
  _pObject=NULL;
  _pTessellation=NULL;
  _pTimeOutCommand=NULL;
}

//------------------------------------------------------------------------

CAADlgInterApplication::~CAADlgInterApplication() 
{

  if ( NULL != _pTessellation)
  {
     _pTessellation->Release();
     _pTessellation = NULL ;
  }
  if ( NULL != _pObject )
  {
     _pObject->Release();
     _pObject = NULL ;     
  }
  if ( NULL != _pTimeOutCommand )
  {
     _pTimeOutCommand->RequestDelayedDestruction();
     _pTimeOutCommand = NULL ;
  }

  cout << endl <<"The CAADlgInterApplication is finished. " <<endl << endl;
}

//------------------------------------------------------------------------

void CAADlgInterApplication::BeginApplication() 
{
  cout <<"CAADlgInterApplication::BeginApplication" << endl;

  // Initialiaze the global data with the current application
  CAADlgIdleApplication=this;

#ifdef _WINDOWS_SOURCE
  // The CATDlgDocument object will be automatically deleted at the end of the application
  CATDlgDocument *doc = new CATDlgDocument(this,"TheWindow");
  doc->SetVisibility(CATDlgShow);
#endif

  // Subscribe to global method OnIdleCallbackMethod. 
  // this method is called when the application does nothing
  Subscribe(CATSubscribeIdle, this, NULL, (void (*)())OnIdleCallbackMethod);

}

//------------------------------------------------------------------------

int CAADlgInterApplication::EndApplication() 
{
  cout << endl << "CAADlgInterApplication::EndApplication" << endl;

  // OK
  return(0);
}

//------------------------------------------------------------------------

void CAADlgInterApplication::OnIdle() 
{
  
  _CAADlgCount++;

  cout << "In the On Idle CallBack : "<< _CAADlgCount << endl;
  
  if (_CAADlgCount==5) 
  {

     // An Object of the model
     _pObject=new CAADlgObject("Surface");

     // This object must be tesselated to be displayed
     _pTessellation=new CAADlgTessellation("Rought");

     // The Tessellation want to be prevent when the 
     // object will be modified
     //
     _pTessellation->Init(_pObject);

  }else if (_CAADlgCount==10) 
  {
    // a Modification occurs
    //
    _pObject->Modification();

  } else if (_CAADlgCount==15)
  {
    // this command will be set a time out  and 
    // when the time is ellapsed, it's destroy the 
    // the current application 
    //
    _pTimeOutCommand=new CAADlgTimeOutCommand(this);

  }
}


//------------------------------------------------------------------------

// Application created
CAADlgInterApplication ApplicationInstance("OnIdleAndTimeoutCallBack");


