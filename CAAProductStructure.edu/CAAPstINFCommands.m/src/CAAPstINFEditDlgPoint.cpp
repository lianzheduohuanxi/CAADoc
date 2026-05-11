// COPYRIGHT DASSAULT SYSTEMES 2002

//Local Framework
#include "CAAPstINFEditDlgPoint.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgSpinner.h"
#include "CATDlgGridConstraints.h"

// Visualization Framework 
#include "CATModify.h"
#include "CATIModelEvents.h"

// Local Framework
#include "CAAIPstINFPoint.h"

// ObjectModelerBase Framework 
#include "CATILinkableObject.h" 
#include "CATIDocRoots.h"
#include "CATDocument.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// ProductStructure Framework
#include "CATIProduct.h"

// Others
#include "iostream.h"


//-----------------------------------------------------------------------------

CAAPstINFEditDlgPoint::CAAPstINFEditDlgPoint(CATDialog *pParent,                              
                                             const CATString &name,
                                             CATDlgStyle style,
                                             CAAIPstINFPoint *piEdit)
                                      : CATDlgDialog (pParent, name, style),
                                        _piPstINFPointEdit(piEdit),
                                        _XSpinner(NULL),
                                        _YSpinner(NULL),
                                        _ZSpinner(NULL)
{
  cout << "*****CAAPstINFEditDlgPoint::CAAPstINFEditDlgPoint" << endl;
  
  if ( NULL != _piPstINFPointEdit) 
  {
     _piPstINFPointEdit -> AddRef();
  }
}

//-----------------------------------------------------------------------------

CAAPstINFEditDlgPoint::~CAAPstINFEditDlgPoint()
{
  cout << "*****CAAPstINFEditDlgPoint::~CAAPstINFEditDlgPoint" << endl;

  if ( NULL != _piPstINFPointEdit) 
  {
     _piPstINFPointEdit -> Release();
     _piPstINFPointEdit = NULL ;
  }
  
  // Dialog's Object automatically deleted 
  _XSpinner = NULL ;
  _YSpinner = NULL ;
  _ZSpinner = NULL ;
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::Build()
{
  cout << "*****CAAPstINFEditDlgPoint::Build" << endl;
  
   //----------------------------
   // Retrieves the plane origin 
   //----------------------------
   if ( NULL != _piPstINFPointEdit )
   {
      HRESULT rc;
      rc = _piPstINFPointEdit -> GetX(&_X);
      rc = _piPstINFPointEdit -> GetY(&_Y);
	  rc = _piPstINFPointEdit -> GetZ(&_Z);

      //-------------------------------------
      // Frames, labels and spinners creation
      //-------------------------------------

      CATDlgFrame *pXYZFrame = NULL;
      CATDlgFrame *pXFrame   = NULL;
      CATDlgFrame *pYFrame   = NULL;
      CATDlgFrame *pZFrame   = NULL;

      pXFrame = new CATDlgFrame(this,
		                        "XFrame",
                                CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pYFrame = new CATDlgFrame(this, 
		                        "YFrame",
                                CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);
      pZFrame = new CATDlgFrame(this,
		                        "ZFrame",
                                CATDlgFraNoTitle|CATDlgFraNoFrame|CATDlgGridLayout);

      CATDlgLabel *pXLabel = NULL;
      CATDlgLabel *pYLabel = NULL;
      CATDlgLabel *pZLabel = NULL;

      pXLabel = new CATDlgLabel(pXFrame,
		                        "XLabel");

      pYLabel = new CATDlgLabel(pYFrame,
		                        "YLabel");

      pZLabel = new CATDlgLabel(pZFrame, 
		                        "ZLabel");
 
      _XSpinner = new CATDlgSpinner(pXFrame,
		                            "XSpinner",
									CATDlgSpnEntry);
      _XSpinner -> SetRange(-10000.,
		                    10000., 
							20000);
      _XSpinner -> SetCurrentValue(_X); 

      _YSpinner = new CATDlgSpinner(pYFrame,
		                            "YSpinner",
									CATDlgSpnEntry);
      _YSpinner -> SetRange(-10000.,
		                    10000.,
							20000);
      _YSpinner -> SetCurrentValue(_Y); 

      _ZSpinner = new CATDlgSpinner(pZFrame,
		                            "ZSpinner",
									CATDlgSpnEntry);
      _ZSpinner -> SetRange(-10000.,
		                    10000.,
							20000);
      _ZSpinner -> SetCurrentValue(_Z); 

      //------------
      // Arrangement
      //------------
  
      pXFrame -> SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pYFrame -> SetGridConstraints(1,0,1,1,CATGRID_CENTER);
      pZFrame -> SetGridConstraints(2,0,1,1,CATGRID_CENTER);

      pXLabel -> SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pYLabel -> SetGridConstraints(0,0,1,1,CATGRID_CENTER);
      pZLabel -> SetGridConstraints(0,0,1,1,CATGRID_CENTER);

      _XSpinner -> SetGridConstraints(0,1,1,1,CATGRID_CENTER);
      _YSpinner -> SetGridConstraints(0,1,1,1,CATGRID_CENTER);
      _ZSpinner -> SetGridConstraints(0,1,1,1,CATGRID_CENTER);

      //-------------------
      // Sets up callbacks
      //-------------------
      AddAnalyseNotificationCB(this,
		                       this -> GetDiaOKNotification(),
                               (CATCommandMethod)&CAAPstINFEditDlgPoint::ClickOK,
                               NULL);


      AddAnalyseNotificationCB(this,
		                       this -> GetDiaPREVIEWNotification(),
                               (CATCommandMethod)&CAAPstINFEditDlgPoint::ClickPreview,
                               NULL);

      AddAnalyseNotificationCB(this, 
		                       this -> GetDiaCANCELNotification(),
                               (CATCommandMethod)&CAAPstINFEditDlgPoint::ClickCancel,
                               NULL);

      AddAnalyseNotificationCB(this, 
		                       this -> GetWindCloseNotification(),
                               (CATCommandMethod)&CAAPstINFEditDlgPoint::ClickCancel,
                               NULL);
   }
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::ClickOK (CATCommand *pPublisher,
                                     CATNotification *pNotification,
                                     CATCommandClientData usefulData)
{
   cout << "*****CAAPstINFEditDlgPoint::ClickOK" << endl;

   if ((NULL != _XSpinner) && (NULL != _YSpinner) && (NULL != _ZSpinner))
   {
      // Modification of the model and  of the visualization
      ModifyModelAndVisu(_XSpinner -> GetCurrentValue(),
                         _YSpinner -> GetCurrentValue(),
                         _ZSpinner -> GetCurrentValue());
   }

   CloseBox() ;
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::ClickCancel (CATCommand *pPublisher,
                                         CATNotification *pNotification,
                                         CATCommandClientData usefulData)
{
   cout << "*****CAAPstINFEditDlgPoint::ClickCancel" << endl;

   ModifyModelAndVisu(_X, _Y, _Z) ;	                  
   CloseBox();
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::ClickPreview (CATCommand *pPublisher,
                                          CATNotification *pNotification,
                                          CATCommandClientData usefulData)
{
   cout << "*****CAAPstINFEditDlgPoint::ClickPreview" << endl;

   if ((NULL != _XSpinner) && (NULL != _YSpinner) && (NULL != _ZSpinner))
   {
      ModifyModelAndVisu(_XSpinner -> GetCurrentValue(),
                         _YSpinner -> GetCurrentValue(),
                         _ZSpinner -> GetCurrentValue()) ;
   }
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::CloseBox()
{
    cout << "*****CAAPstINFEditDlgPoint::CloseBox" << endl;
    
	SetVisibility(CATDlgHide);
                             
    SendNotification(GetFather(),
		             CATDlgDialog::GetWindCloseNotification());
}

//-----------------------------------------------------------------------------

void CAAPstINFEditDlgPoint::ModifyModelAndVisu (const double iX,
												const double iY,
												const double iZ)
{
	cout << "*****CAAPstINFEditDlgPoint::ModifyModelAndVisu" << endl;

	HRESULT rc;

    if ( NULL != _piPstINFPointEdit )
	{
       //----------------------------------------
       // Modification of the point coordinnates
       //----------------------------------------
     
       rc = _piPstINFPointEdit -> SetX(iX);
	   rc = _piPstINFPointEdit -> SetY(iY);
	   rc = _piPstINFPointEdit -> SetZ(iZ);

       //-----------------------------------
       // Notification to update the display
       //----------------------------------- 
       CATIModelEvents *piModelEvents = NULL;                
       rc = _piPstINFPointEdit -> QueryInterface(IID_CATIModelEvents, 
		                                         (void**)&piModelEvents);
       if (SUCCEEDED(rc))
	   {
	      CATModify Notif (piModelEvents);
          piModelEvents -> Dispatch(Notif);

          piModelEvents-> Release();
          piModelEvents = NULL ;
	   }

	   //--------------------------------------------------------------------------
	   // Update the root product so that it will call update provider to re-build
	   // all impacted objects.
	   //--------------------------------------------------------------------------
       CATILinkableObject *piLinkableOnPoint = NULL;
       rc = _piPstINFPointEdit -> QueryInterface (IID_CATILinkableObject,
	   	                                          (void**) &piLinkableOnPoint);
	   if (SUCCEEDED(rc))
	   {
	  	  CATDocument* pDoc = piLinkableOnPoint -> GetDocument();
	      piLinkableOnPoint -> Release();
	      piLinkableOnPoint = NULL;
		  if (NULL == pDoc) return;

          CATIDocRoots* piDocRootsOnDoc = NULL;
	      rc = pDoc -> QueryInterface(IID_CATIDocRoots,
	   	                              (void**) &piDocRootsOnDoc);
	      if (SUCCEEDED(rc))
		  {
		      // get the root product which is the first element of root elements
	          CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc -> GiveDocRoots();
	          piDocRootsOnDoc -> Release();
			  piDocRootsOnDoc = NULL;
			  CATIProduct_var spRootProduct = NULL_var;
	
	          if (pRootProducts && pRootProducts->Size())
			  {  
				  spRootProduct = (*pRootProducts)[1];
				  delete pRootProducts;
				  pRootProducts = NULL;
				  CATISpecObject *piSpecObjectOnProduct = NULL;
				  rc = spRootProduct -> QueryInterface(IID_CATISpecObject,
		 		                                       (void**) &piSpecObjectOnProduct);
			  	  if (SUCCEEDED(rc))
				  {
				 	  piSpecObjectOnProduct -> Update();
					  piSpecObjectOnProduct -> Release();
					  piSpecObjectOnProduct = NULL;
				  }
			  }
		  }
	   }
	} 
}
