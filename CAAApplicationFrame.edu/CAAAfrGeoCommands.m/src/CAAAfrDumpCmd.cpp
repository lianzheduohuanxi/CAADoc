// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAAfrDumpCmd.h"

//CAASystem.edu Framework
#include "CAAISysCollection.h"
#include "CAAISysPoint.h"
#include "CAAISysLine.h"
#include "CAAISysCircle.h"
#include "CAAISysEllipse.h"
#include "CAAISysPlane.h"
#include "CAAISysPolyline.h"
#include "CAAISysAccess.h"  //To get the container of each object   

// Dialog Framework
#include "CATDlgNotify.h"

//ApplicationFrame Framework
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"  

// System FW
#include "CATMsgCatalog.h"
#include "CATUnicodeString.h"

//Visualization Framework  
#include "CATPathElement.h"   

//C++ standard library
#include "iostream.h"

//Number of differents objects that can contains a CAAGeometry model 
#define NBELT 8 

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAAfrDumpCmd);

//-----------------------------------------------------------------------------

CAAAfrDumpCmd::CAAAfrDumpCmd(): CATCommand (NULL,"CAAAfrDumpCmdId") ,
			 _DumpDialogBox(NULL)
{
  cout << "constructor CAAAfrDumpCmd" << endl;  

  // This command is not exclusive in order not to destroy the current one. 
  // It's shared to be seen by the focus manager, and so to create the 
  // Information Dialog Box in the Activate method 
  RequestStatusChange(CATCommandMsgRequestSharedMode);
}

//-------------------------------------------------------------------------

CAAAfrDumpCmd::~CAAAfrDumpCmd()
{
  cout << "destructor CAAAfrDumpCmd" << endl; 

  if ( NULL != _DumpDialogBox )
  {
    // Requests the dialog box deallocation  
    _DumpDialogBox ->RequestDelayedDestruction();
    _DumpDialogBox = NULL ;
  }
}

//-------------------------------------------------------------------------

CATStatusChangeRC CAAAfrDumpCmd::Activate( CATCommand      *iPublisher,
                                           CATNotification *iNotification)
{
  cout << " CAAAfrDumpCmd::Activate" << endl;

  // Dialob box Creation
  if ( NULL == _DumpDialogBox )
  {
    // Parent dialog of this point dialog box 
    CATApplicationFrame * pFrame = NULL ;
    pFrame = CATApplicationFrame::GetFrame() ;
    if ( NULL != pFrame )
    {
       // father is the Dialog object dedicated to the current document. 
       //
       CATDialog * father = pFrame->GetMainWindow() ;
       
       if ( NULL != father )
       {
          //Construction of the Dialog Box
          _DumpDialogBox = new CATDlgNotify(father,"DumpDialogBoxId",
                                            CATDlgNfyInformation | 
                                            CATDlgNfyOK |
                                            CATDlgWndModal);
          //Title of the Dialog Box
          //This title is in the CAAAfrDumpCmd.CATNls file
          //See in your local CNext/resources/msgcatalog
          //
          CATUnicodeString title = CATMsgCatalog::BuildMessage("CAAAfrDumpCmd", 
                                       "TitleDumpBox",
                                        NULL, 0, "Dump Model");

          _DumpDialogBox->SetTitle(title);

          // Sets the current command as the receiver of the notifications sent 
          // by the dialog box, instead of the main window.
          // It is necessary because this command does not take the focus. 
          _DumpDialogBox->SetFather(this);
		                                 
          // subscribes to dialog box's notification in order to terminate the
          // command
          AddAnalyseNotificationCB(_DumpDialogBox, 
                                   _DumpDialogBox->GetNfyOKNotification(),
                                   (CATCommandMethod)&CAAAfrDumpCmd::CloseBox,
                                   NULL);

          AddAnalyseNotificationCB(_DumpDialogBox, 
                                   _DumpDialogBox->GetWindCloseNotification(),
                                   (CATCommandMethod)&CAAAfrDumpCmd::CloseBox,
                                   NULL);
        
          // Display the contains
          DisplayModelContain();

          _DumpDialogBox->SetVisibility(CATDlgShow);
       }   
     }
  }

  return (CATStatusChangeRCCompleted) ;
}

//---------------------------------------------------------------------------

void CAAAfrDumpCmd::CloseBox (CATCommand          *iPublisher   , 
                              CATNotification     *iNotification,
                              CATCommandClientData iUsefulData)
{
   cout << "CAAAfrDumpCmd::CloseBox "<< endl ;

   _DumpDialogBox->SetVisibility(CATDlgHide);

   RequestDelayedDestruction() ;
}

//---------------------------------------------------------------------------

void CAAAfrDumpCmd::DisplayModelContain()
{
  // The model contains a container which contains all objects
  // 
  CATFrmEditor * pEditor   = CATFrmEditor::GetCurrentEditor();
  if ( NULL != pEditor )
  {
    // the dump is processed on the UI active object's container 
    CATPathElement path = pEditor->GetUIActiveObject();
    CATBaseUnknown * pUIActiveObject = NULL ;
    if ( 0 != path.GetSize() )
    {
      // The UI active object is at the leaf of the path
      pUIActiveObject = path[path.GetSize()-1];

      // This object, as all object in the model, implements an interface CAAISysAccess
      // which keeps the container. 
      //
      if ( NULL != pUIActiveObject )
      {
        CAAISysAccess * piSysAccess = NULL;                
        HRESULT rc = pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
        if (SUCCEEDED(rc))
        {
           CATBaseUnknown  * pContainer = NULL ;
           rc = piSysAccess->GetContainer(&pContainer);
           if (SUCCEEDED(rc))
           {
             // the container implements an interface, CAAISysCollection
             // which contains the list of all objects in the model
             //
             DumpContainer(pContainer);
             pContainer->Release();
             pContainer = NULL ;
           }
           piSysAccess ->Release();
           piSysAccess = NULL ;
        }
      }
    }
  }
}

//---------------------------------------------------------------------------

void CAAAfrDumpCmd::DumpContainer(CATBaseUnknown * iContainer)
{
  if ( NULL != iContainer )
  {
     CAAISysCollection * piSysCollection = NULL;                
     HRESULT rc = iContainer->QueryInterface(IID_CAAISysCollection, 
                                             (void**)&piSysCollection);
     if (SUCCEEDED(rc))
     {
       // NBELT = Number of differents objects that can contains a CAAGeometry model 
       int aNbEltList[NBELT];
       int i, nbeltcont ;
   
       //  Initialize the count of object for each kind
       for (i=0 ; i < NBELT ; i++) aNbEltList[i] = 0 ;
   
       // Retrieves the count of object in the model
       piSysCollection->GetNumberOfObjects(&nbeltcont);
   
       // The first element is the UIActive object
       for (i=2 ; i <=  nbeltcont ; i++)
       {
          CATBoolean find = FALSE ; 
          CATBaseUnknown * pObject = NULL ;
          rc = piSysCollection->GetObject(i,&pObject);
          if (SUCCEEDED(rc))
          {
              CAAISysPoint * piSysPoint  = NULL;                
              rc = pObject ->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
              if (SUCCEEDED(rc))
              {
                 // it's a point
                 aNbEltList[0] ++ ;
                 piSysPoint -> Release();
                 piSysPoint = NULL ;
                 find = TRUE ;
              } 
   
              if ( FALSE == find ) 
              {
                 CAAISysLine * piSysLine  = NULL;                
                 rc = pObject ->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
                 if (SUCCEEDED(rc))
                 {
                    // it's a line
                    aNbEltList[1] ++ ;
                    piSysLine -> Release();
                    piSysLine= NULL ;
                    find = TRUE ;
                 } 
              } 
   
              if ( FALSE == find ) 
              {
                 CAAISysCircle * piSysCircle  = NULL;                
                 rc = pObject ->QueryInterface(IID_CAAISysCircle, (void**)&piSysCircle);
                 if (SUCCEEDED(rc))
                 {
                    // it's a circle
                    aNbEltList[2] ++ ;
                    piSysCircle -> Release();
                    piSysCircle = NULL ;
                    find = TRUE ;
                 } 
              } 
   
              if ( FALSE == find ) 
              {
                 CAAISysEllipse * piSysEllipse  = NULL;                
                 rc = pObject ->QueryInterface(IID_CAAISysEllipse, (void**)&piSysEllipse);
                 if (SUCCEEDED(rc))
                 {
                    // it's an ellipse
                    aNbEltList[3] ++ ;
                    piSysEllipse -> Release();
                    piSysEllipse = NULL ;
                    find = TRUE ;
                 } 
              } 
   
              if ( FALSE == find ) 
              {
                 CAAISysPlane * piSysPlane  = NULL;                
                 rc = pObject ->QueryInterface(IID_CAAISysPlane, (void**)&piSysPlane);
                 if (SUCCEEDED(rc))
                 {
                    // it's a plane
                    aNbEltList[4] ++ ;
                    piSysPlane -> Release();
                    piSysPlane = NULL ;
                    find = TRUE ;
                 } 
              } 
   
              if ( FALSE == find ) 
              {
                 CAAISysPolyline * piSysPolyline  = NULL;                
                 rc = pObject ->QueryInterface(IID_CAAISysPolyline, (void**)&piSysPolyline);
                 if (SUCCEEDED(rc))
                 {
                    // Closed or not polyline ?
                    int close   = 0 ;
                    piSysPolyline->GetCloseStatus(&close);
   
                    if ( 0 == close ) 
                    {
                       // It's a polyline
                       aNbEltList[5] ++ ; 
                    }
                    else
                    {
                       // Retrieves the point count 
                       int NbPoint = 0 ;
                       CATMathPoint *PointList[1] ;
                       piSysPolyline->GetListPoint(&NbPoint,PointList);
   
                       if ( 3 == NbPoint ) 
                       // it's a triangle
                          aNbEltList[6] ++ ;
                       else 
                       // it's a rectangle
                          aNbEltList[7] ++ ;
                    }
                    piSysPolyline -> Release();
                    piSysPolyline = NULL ;
                    find = TRUE ;
                 } 
              } 
              
              // Done with the ieme object 
              pObject  -> Release();
              pObject = NULL ;
          }
       }  
      
       //We have run  all the model
       //and we can update the Dialog box 
   
       // Translate number in CATUnicodeString 
       CATUnicodeString param[NBELT] ;
       for ( i= 0 ; i < NBELT ; i++ )
       {
          param[i].BuildFromNum(aNbEltList[i]);
       }
   
       // Searchs the string to display in the Msg catalog  
       // One Sentence for all element
       CATUnicodeString chaine = CATMsgCatalog::BuildMessage("CAAAfrDumpCmd", 
                                         "Phrase", param, 
                                          NBELT, "Error in Nls File");  
       
       // Sets the sentence 
       _DumpDialogBox->SetText(chaine);
   
       // Done with this pointer
       piSysCollection  -> Release();
       piSysCollection = NULL ;
     }
  }
}

