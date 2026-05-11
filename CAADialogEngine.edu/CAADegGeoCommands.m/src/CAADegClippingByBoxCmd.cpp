// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegClippingByBoxCmd.h"

// CAAVisualization.edu Framework
#include "CAAIVisTextModel.h"         // Interface to handle the temporary object representing a text
#include "CAAIVisWireBox.h"  

//CAAApplicationFrame.edu Framework
#include "CAAIAfrTemporaryObjectColor.h"  // To access the current color into the Combo color

//DialogEngine Framework
#include "CATIndicationAgent.h"
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"
#include "CATStateActivateNotification.h"

//Visualization Framework
#include "CATPathElement.h"            
#include "CATIModelEvents.h"   
#include "CATCSO.h"
#include "CATModelForRep3D.h"   
#include "CAT3DCustomRep.h" 
#include "CAT3DFixedArrowGP.h" 
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DLineGP.h" 
#include "CATI3DGeoVisu.h" 
#include "CATGraphicPrimitive.h" 
#include "CATDelete.h"

//CAASystem.edu Framework  
#include "CAAISysCollection.h"     
#include "CAAISysPoint.h"  
#include "CAAISysAccess.h"  

// Application Framework
#include "CATFrmEditor.h" 
#include "CATISO.h" 
#include "CATListOfCATBaseUnknown.h"

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

// System Framework
#include "CATInstantiateComponent.h"

//others
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-3

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegClippingByBoxCmd);


//----------------------LifeCycle's PART -------------------------------------
CAADegClippingByBoxCmd::CAADegClippingByBoxCmd():CATStateCommand("ClippingByBoxCmdId"),
           _daIndication(NULL),_daTextSel(NULL),_daForBoxCenter(NULL),         
           _pCenterBoxModel (NULL),_pIWireBox(NULL),_pITextToSelectModel (NULL),
           _pISO(NULL),_pFurtiveISO(NULL),_pUIActiveObject(NULL), _pContainer(NULL),
           _FirstTime(TRUE)
                                        
{
  cout << "CAADegClippingByBoxCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor )
  {
    _pFurtiveISO = pEditor->GetFurtiveISO() ;

    _pISO = pEditor->GetISO() ;

    // Retrieves the root object of the CAAGeometry document
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( 0 != path.GetSize() ) 
    {
      _pUIActiveObject=path[path.GetSize()-1];

      // Keep a interface pointer = AddRef to do
      _pUIActiveObject->AddRef();
    }
  }

  if ( NULL != _pUIActiveObject )
  {
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      // Retrieves the object which implements a factory to delete 
      // geometrical object  ( point,line, circle,....)
      piSysAccess->GetContainer(&_pContainer);

      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   

  // The component to represent the center of the bounding box 
  //
  _pCenterBoxModel     = new CATModelForRep3D(); 

  // The component to represent the bounding box 
  //
  ::CATInstantiateComponent("CAAVisWireBox",IID_CAAIVisWireBox,(void**)&_pIWireBox);

  // Instantiation of the component representing the temporary object 
  // to display a text at the beginning of the command
  //
  ::CATInstantiateComponent("CAAVisTextModel",IID_CAAIVisTextModel,(void**)&_pITextToSelectModel);
                                                                               
}

//------------------------------------------------------------------------
 
CAADegClippingByBoxCmd::~CAADegClippingByBoxCmd()
{
  cout << "CAADegClippingByBoxCmd destructor" << endl ;

  // Agents 
  if ( NULL != _daTextSel )
  {
     _daTextSel ->RequestDelayedDestruction();  
     _daTextSel = NULL ;
  }

  if ( NULL != _daIndication )
  {
     _daIndication ->RequestDelayedDestruction();  
     _daIndication = NULL ;
  }

  if ( NULL != _daForBoxCenter )
  {
     _daForBoxCenter ->RequestDelayedDestruction();
     _daForBoxCenter = NULL ;
  }

  // Temporary objects
  if ( NULL != _pITextToSelectModel )
  {
     _pITextToSelectModel->Release();
     _pITextToSelectModel = NULL ;
  }

  if ( NULL != _pCenterBoxModel )
  {
     _pCenterBoxModel->Release();
     _pCenterBoxModel = NULL ;
  }

  if ( NULL != _pIWireBox )
  {
     _pIWireBox->Release();
     _pIWireBox = NULL ;
  }

  // It is not automatically emptied at the end - See Cancel method
  // 
  _pISO = NULL ; 

  // It is automatically emptied at the end of the state command
  _pFurtiveISO = NULL ; 

  if ( NULL != _pContainer )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }

  if ( NULL != _pUIActiveObject  ) 
  {
     _pUIActiveObject ->Release();
     _pUIActiveObject = NULL ;
  }

}

//----------------------BuildGraph PART -----------------------------------

void CAADegClippingByBoxCmd::BuildGraph()
{
  cout << "CAADegClippingByBoxCmd BuildGraph" << endl ;

  //1- Creates the dialog agents 
  //............................

  //1-1 Agent to select the text 
  _daTextSel = new CATPathElementAgent("SelText");
  _daTextSel->SetBehavior(CATDlgEngWithPSO | CATDlgEngWithPrevaluation);
  _daTextSel->AddElementType(IID_CAAIVisTextModel);

  //1-2 Agent to select the box center
  //    
  _daForBoxCenter = new CATPathElementAgent("SelBoxCenter");
  _daForBoxCenter->SetBehavior(CATDlgEngWithPSO | CATDlgEngWithPrevaluation);
  _daForBoxCenter->AddElementType(IID_CAAISysPoint);

   // Reads the cso  
  AddCSOClient(_daForBoxCenter); 

 
  //1-3 Agent to define the clipping box
  //    to have direct manipulation and No Undo step 
  //
  _daIndication = new CATIndicationAgent("Indication");
  
  _daIndication->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngAcceptOnPrevaluate |
	                         CATDlgEngWithUndo);
	     

  //2- Creates states. See Nls file 
  //................................

  CATDialogState *stTextState = GetInitialState("stTextStateId");
  stTextState->AddDialogAgent(_daTextSel);

  CATDialogState *stBoxCenterState = AddDialogState("stBoxCenterStateId");
  stBoxCenterState->AddDialogAgent(_daForBoxCenter);

  CATDialogState *stGetEndState = AddDialogState("stGetEndStateId");
  stGetEndState->AddDialogAgent(_daIndication);

  //3-Defines transitions 
  //.....................

  CATDialogTransition *pFirstTransition = AddTransition
  (
     stTextState,
     stBoxCenterState,
     IsOutputSetCondition(_daTextSel) ,
     Action((ActionMethod) & CAADegClippingByBoxCmd::DisplayDialogBox,
            (ActionMethod) & CAADegClippingByBoxCmd::UndoSelText,
            (ActionMethod) & CAADegClippingByBoxCmd::RedoSelText)
  ) ; 

  CATDialogTransition *pSecondTransition = AddTransition
  (
     stBoxCenterState,
     stGetEndState,
     IsOutputSetCondition(_daForBoxCenter) ,
     Action((ActionMethod) & CAADegClippingByBoxCmd::CreateCenterBox,
            (ActionMethod) & CAADegClippingByBoxCmd::UndoCreateCenterBox,
            (ActionMethod) & CAADegClippingByBoxCmd::RedoCreateCenterBox)
  ) ; 
  pSecondTransition->SetResourceID("SecondTransition");

  CATDialogTransition *pLoopTransition = AddTransition
  (
     stGetEndState,
     stGetEndState,
     IsLastModifiedAgentCondition(_daIndication),
     Action( (ActionMethod) & CAADegClippingByBoxCmd::UpdateClippingBox)
  ) ;  

  CATDialogTransition *pFinalTransition = AddTransition
  (
     stGetEndState,
     NULL,
     IsOutputSetCondition(_daIndication),
     Action( (ActionMethod) & CAADegClippingByBoxCmd::ClippingByBox)
  ) ; 
}


//-----------------------Action Method's PART-------------------------------

CATBoolean CAADegClippingByBoxCmd::DisplayDialogBox(void *iUsefulData)
{
  cout << "CAADegClippingByBoxCmd::DisplayDialogBox " << endl ;


  // The text is removed from the display
  // but the rep associated with the component is
  // not deleted
  //
  if ( (NULL != _pISO) && (NULL!=_pITextToSelectModel) )
  {
      _pISO->RemoveElement(_pITextToSelectModel,1) ;
  }

  return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::UndoSelText(void *iUsefulData)
{
  cout << "CAADegClippingByBoxCmd::UndoSelText " << endl ;

  if ( (NULL != _pISO) && (NULL!=_pITextToSelectModel) )
  {
     _pISO->AddElement(_pITextToSelectModel) ;
  }

  return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::RedoSelText(void *iUsefulData)
{
  cout << "CAADegClippingByBoxCmd::RedoSelText " << endl ;

  // Removes the text from the ISO
  if ( (NULL != _pISO) && (NULL!=_pITextToSelectModel) )
  {
      _pISO->RemoveElement(_pITextToSelectModel,1) ;
  }

   return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::CreateCenterBox(void *iUsefulData)
{
   cout << "CAADegClippingByBoxCmd::CreateCenterBox " << endl ;

   HRESULT rc = E_FAIL ;

   // The selected point is the center of the box. 
   if ( NULL != _daForBoxCenter )
   {
       CATPathElement * pPathModel = _daForBoxCenter->GetValue();

       CATBaseUnknown * pObject = NULL ;
       if ( (NULL != pPathModel) &&  (0 != pPathModel->GetSize()) )
       {
          pObject = (*pPathModel)[pPathModel->GetSize()-1];
       }

       // The selected point is the leaf of the path
       if ( NULL != pObject )
       {
          // Retrieves the point coordinates
          CAAISysPoint * piSysPoint = NULL;                
          rc =  pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
          if (SUCCEEDED(rc))
          {
             // Gets x,y,z from the selected point 
             float x,y,z ;

             piSysPoint->GetCoord(x,y,z);
             piSysPoint-> Release();
             piSysPoint=NULL;

             // The coordinates are kept in this data member
             _CenterBox.SetX(x);
             _CenterBox.SetY(y);
             _CenterBox.SetZ(z);

             // Displays a temporary object to represent the center of the 
             // bounding box
             if ( (NULL != _pISO) && ( NULL!=_pCenterBoxModel) )
             {
                // Creates the graphic representation and associates
                // it with the temporary component
                rc = CreateRepForCenterBox();  
             
                if ( SUCCEEDED(rc) )
                {
                    // The component is added into the ISO
                    _pISO->AddElement(_pCenterBoxModel);
                }
             }
          }
       }
   }

   if ( SUCCEEDED(rc) )
      return TRUE ;
   else 
     return FALSE;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::UndoCreateCenterBox(void *iUsefulData)
{
  cout << "CAADegClippingByBoxCmd::UndoCreateCenterBox" <<  endl ;

  if ( (NULL != _pISO) && (NULL!=_pCenterBoxModel) && 
       (NULL != _pFurtiveISO) && ( NULL!=_pIWireBox) )
  {
      // The last argument of the RemoveElement method specifies
      // if the graphic representation associated with the component
      // should be deleted (val=0) or just removed (val=1) from the bag of representations
      // associated with the ISO to each viewpoint
      // The default behavior is 0, so the graphic representation will be deleted
      // The Redo step will recreate it.
      //
      _pISO->RemoveElement(_pCenterBoxModel);

      // The graphic representation of the bounding box is
      // automatically destroyed.
      //
      _pFurtiveISO->RemoveElement(_pIWireBox);

      // in case of redo or new selected center box
      // the dimension of the bounding box is re-initialized
      _FirstTime= TRUE ;
  }

  return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::RedoCreateCenterBox(void *iUsefulData)
{
  cout << "CAADegClippingByBoxCmd::RedoCreateCenterBox" <<  endl ;

  // Recreate the rep that the RemoveElement method has deleted 
  // See the undo step just above- the bounding box will be recreated
  // with the initial dimention.
  //
  if ( (NULL != _pISO) && ( NULL!=_pCenterBoxModel) )
  {
     HRESULT rc = CreateRepForCenterBox();  
             
     if ( SUCCEEDED(rc) )
     {
        _pISO->AddElement(_pCenterBoxModel);
     }
  }

  return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::UpdateClippingBox(void *iUsefulData)
{

  if ( (NULL !=_daIndication) && (NULL != _pIWireBox) && 
       ( NULL != _pFurtiveISO) && ( NULL!= _pISO) )
  {
     if ( TRUE == _FirstTime )
     {
        // 
        _FirstTime = FALSE ;

        // Initialize (or re-initialize) the center of the box 
        _pIWireBox->SetCenterBox(_CenterBox);
        _pIWireBox->SetDimBox(.2f);

        //Initialize the position of the mouse
        _PreviousPointInScreenPlane = _daIndication->GetValue();

        // First the component is set in the furtive ISO
        _pFurtiveISO->AddElement(_pIWireBox);

     }else
     {
        // If the mouse is up, the bouding box decreases otherwise it
        // increases.
        CATMathPoint2D CurrentPointInScreenPlane = _daIndication->GetValue(); 

        // Retrieves the current dimension of the bounding box
        float currentdimbox = .2f;
        _pIWireBox->GetDimBox(&currentdimbox);

        if ( CurrentPointInScreenPlane.GetY() > _PreviousPointInScreenPlane.GetY() )
        {
           // It is always possible to increase the bounding box
          currentdimbox += .05f ;
        }else
        {
           // The bounding box is decreased until the lower limit is reached
           if ( (currentdimbox - .2f) > EPSILON )
           { 
              currentdimbox -= 0.05f ;
           }
        }

        // Update the previous mouse position for the next step
        _PreviousPointInScreenPlane = CurrentPointInScreenPlane ;

        _pIWireBox->SetDimBox(currentdimbox) ;

        // The component is updated in the furtive ISO
        // 
        _pFurtiveISO->UpdateElement(_pIWireBox);
     } 
  }
  
  return TRUE ;
}

//-------------------------------------------------------------------------------

CATBoolean CAADegClippingByBoxCmd::ClippingByBox(void *iUsefulData)
{

  // All objects of the model outside the bounding box are deleted 
  //
  if ( (NULL!=_pUIActiveObject) && ( NULL != _pContainer) && ( NULL!=_pIWireBox) )
  {
     float currentdimbox = .2f;
     _pIWireBox->GetDimBox(&currentdimbox);

     // The CAAISysCollection interface implemented by the container of
     // the CAAGeometry document is defined in the CAASystem.edu framework
     //
     CAAISysCollection * piSysCollection = NULL;                
     HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, (void**)&piSysCollection);
                                         
     if (SUCCEEDED(rc))
     {
         int NbElt = 0 ;
         piSysCollection->GetNumberOfObjects(&NbElt);

         //
         // This list will contain the elt to delete
         //
         CATLISTP(CATBaseUnknown) ListToDelete ;

         //
         // The model is not empty. It contains at least: 
         // the UIActive object + one point (the center)
         //
         for ( int i= 2 ; i <= NbElt ; i++ )
         {
            // Retrieve each element 
            CATBaseUnknown * pObject =NULL;
            rc = piSysCollection->GetObject(i,&pObject);
            if ( SUCCEEDED(rc) )
            {
               // Only the point are processed
               CAAISysPoint * piSysPoint = NULL;                
               rc = pObject ->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
               if (SUCCEEDED(rc) )
               {
                   float x,y,z ;
                   piSysPoint->GetCoord(x,y,z);

                   if ( (x > _CenterBox.GetX()- currentdimbox) && 
                     (x < _CenterBox.GetX()+ currentdimbox) &&
                     (y > _CenterBox.GetY()- currentdimbox) && 
                     (y < _CenterBox.GetY()+ currentdimbox) && 
                     (z > _CenterBox.GetZ()- currentdimbox) && 
                     (z < _CenterBox.GetZ()+ currentdimbox) )
                   {
                       pObject->Release();
                       pObject = NULL ;
                   }else
                   {
                       ListToDelete.Append(pObject);
                   }

                   piSysPoint->Release();
                   piSysPoint = NULL ;
               }else
               {
                   pObject->Release();
                   pObject = NULL ;
               }
            }
         }

         //
         // Process the list of elt to delete
         //
         for ( int j= 1 ; j <= ListToDelete.Size() ; j++)
         {
             CATBaseUnknown * pObject =ListToDelete[j] ;
             if ( NULL != pObject )
             {
                // Update the display
                CATIModelEvents * piModelEvent = NULL;                
                rc = pObject->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
                if ( SUCCEEDED(rc))
                {
                   CATDelete notif(pObject);
                   piModelEvent->Dispatch(notif);

                   piModelEvent->Release();
                   piModelEvent=NULL;
                }

                // Remove the element of the list
                piSysCollection->RemoveObject(pObject);

                // release the pointer of GetObject just above
                pObject->Release();
                pObject = NULL ;
             }
         }

         piSysCollection->Release();
         piSysCollection=NULL;

         //
         // Updates the specification tree
         //
         if ( 0 != ListToDelete.Size() )
         {  
            CATIRedrawEvent * piRedrawEvent = NULL;                
            rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
            if (SUCCEEDED(rc))
            {
               piRedrawEvent->Redraw();
        
               piRedrawEvent->Release();
               piRedrawEvent= NULL ;
            }
         }
     }    
  }

  return TRUE ;
}

//--------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegClippingByBoxCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingByBoxCmd::Activate" << endl;
  
  if ( (NULL != iNotif ) && (NULL != _pISO) )
  {
     if (((CATStateActivateNotification *) iNotif) -> GetType() 
                 ==  CATStateActivateNotification::Resume)
     {
        if ( ( TRUE == _CenterBoxModelToRestore ) && ( NULL!=_pCenterBoxModel) )
        {
            HRESULT rc = CreateRepForCenterBox();  
             
            if ( SUCCEEDED(rc) )
            {
              _pISO->AddElement(_pCenterBoxModel);
            }
        }

        if ( (TRUE == _TextModelToRestore) && (NULL!=_pITextToSelectModel) )
        {
            // The rep has not be deleted, the temporary object can be 
            // set back in the ISO
            //
            _pISO->AddElement(_pITextToSelectModel);
        }
     }
     else
     {
         // First activation - the temporary object representing a text is
         // displayed to be selected by the end user. 
         //
         if ( NULL != _pITextToSelectModel )
         {
            HRESULT rc = CreateRepForText();
            if ( SUCCEEDED(rc) )
            {
               _pISO->AddElement(_pITextToSelectModel);
            }
         }
     }

  }   

  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------ 

CATStatusChangeRC CAADegClippingByBoxCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingByBoxCmd::Desactivate" << endl;
  
  _CenterBoxModelToRestore = FALSE ;
  _TextModelToRestore      = FALSE ;

  if ( (NULL != _pISO) && (NULL!=_pCenterBoxModel) && 
       (NULL != _pFurtiveISO) && (NULL!=_pIWireBox) )
  {
      if ( _pISO->IsMember(_pITextToSelectModel) )
      {
         // The temporary object is removed from the ISO
         // but it's Rep is not destroyed
         //
         _pISO->RemoveElement(_pITextToSelectModel,1);
         _TextModelToRestore = TRUE ;
      }

      if ( _pISO->IsMember(_pCenterBoxModel) )
      {
          // The last argument of the RemoveElement method specifies
          // if the graphic representation associated with the component
          // should be deleted (val=0) or just removed (val=1) from the bag of representations
          // associated with the ISO to each viewpoint
          // The default behavior is 0, so the graphic representation will be deleted
          // The Redo step will recreate it.
          //
         _pISO->RemoveElement(_pCenterBoxModel);

         // This data member will be used in the Activate method
         //
         _CenterBoxModelToRestore = TRUE ;
      }

      if ( _pISO->IsMember(_pIWireBox) )
      {

         // The graphic representation of the bounding box is
         // automatically destroyed.
         //
         _pFurtiveISO->RemoveElement(_pIWireBox);

         // To regenerate the bounding box from the initial dimension
         _FirstTime = TRUE ;
        
      }
  }

  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------

CATStatusChangeRC CAADegClippingByBoxCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingByBoxCmd::Cancel" << endl;

  // Empties the ISO 
  // The RemoveElement method checks that the component exists in the ISO
  // before remove it. 
  //

  if ( (NULL != _pISO)  )
  {
      if ( NULL != _pITextToSelectModel )
      {           
         _pISO->RemoveElement(_pITextToSelectModel);  
      }

      if ( NULL != _pCenterBoxModel )
      {           
         _pISO->RemoveElement(_pCenterBoxModel);  
      }
  }

  if ( NULL != _pFurtiveISO )
  {

      if ( NULL != _pIWireBox )
      {
         _pFurtiveISO->RemoveElement(_pIWireBox);
      }
  }
  
  return (CATStatusChangeRCCompleted) ;
}


//----------------------------------------------------------------------------------

HRESULT CAADegClippingByBoxCmd::CreateRepForCenterBox()
{
   if ( NULL == _pCenterBoxModel ) return E_FAIL ;
   
   CAT3DCustomRep * pRepForCenter = new CAT3DCustomRep();

   //
   // Attribut graphique Definition
   //
   CATGraphicAttributeSet   CenterGa ;

   // Retrieves the color from the combo color header 
   // An instance, named CAAAfrComboColorHdr, is created in an addin of the
   // CAAGeometry workshop.
   // see the CAAApplicationFrame.edu Framework and its CAAAfrGeoWksAddinForCustHdr.m
   // module
   //
   CAAIAfrTemporaryObjectColor * pITemporaryObjectColor = NULL ;

   HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAIAfrTemporaryObjectColor,
                                                (void**)&pITemporaryObjectColor);
   if ( SUCCEEDED(rc))
   {
          int r,g,b;
          pITemporaryObjectColor->GetCurrentColor(r,g,b);

          cout <<" r=" << r << " g=" << g << " b=" << b << endl ;

          pITemporaryObjectColor->Release();
          pITemporaryObjectColor = NULL ;

          // To benefit from the RGBA color
          CenterGa.SetColor(TRUECOLOR);

          // The last value 255 means that the color is completly opaque
          CenterGa.SetColorRGBA(r,g,b,255);
      
   }

   //
   // Graphic primitive Creation
   //
   float coord[3] ;
   coord[0] = _CenterBox.GetX() ;
   coord[1] = _CenterBox.GetY() ;
   coord[2] = _CenterBox.GetZ();

   CATMathPointf StartPoint = _CenterBox ;
   CATMathDirectionf DirX (1.f,0.f,0.f);
   CATMathDirectionf DirY (0.f,1.f,0.f);
   CATMathDirectionf DirZ (0.f,0.f,1.f);

   int LengthIn_mm      = 5;
   int ArrowHeadHeight  = 1;
   int BaseLength       = 0 ;

   CAT3DFixedArrowGP * pCenterGpX = new CAT3DFixedArrowGP(StartPoint,DirX,LengthIn_mm,ArrowHeadHeight,BaseLength);
   CAT3DFixedArrowGP * pCenterGpY = new CAT3DFixedArrowGP(StartPoint,DirY,LengthIn_mm,ArrowHeadHeight,BaseLength);
   CAT3DFixedArrowGP * pCenterGpZ = new CAT3DFixedArrowGP(StartPoint,DirZ,LengthIn_mm,ArrowHeadHeight,BaseLength);
   
   //
   // Association of the Gp and the Ga to the Representation
   //
   pRepForCenter->AddGP(pCenterGpX,CenterGa);
   pRepForCenter->AddGP(pCenterGpY,CenterGa);
   pRepForCenter->AddGP(pCenterGpZ,CenterGa);

   // Computes the Bounding sphere
   CAT3DBoundingSphere be(coord,0.f,1.f) ;
   pRepForCenter->SetBoundingElement(be) ;

   // The life cycle of the rep (pRepForCenter) is now managed by the 
   // component
   //
   _pCenterBoxModel->SetRep(pRepForCenter) ;

   return S_OK ;
}

//----------------------------------------------------------------------------------

HRESULT CAADegClippingByBoxCmd::CreateRepForText()
{
   cout <<" CAADegClippingByBoxCmd::CreateRepForText" << endl;

   if ( NULL == _pITextToSelectModel ) return E_FAIL ;

   CAT3DCustomRep * pRepForText= new CAT3DCustomRep();

   CATGraphicAttributeSet   TextGa ;
   
   CATMathPointf    TextPos(0.f,0.f,0.f);
  
   CATUnicodeString TextValue ="ISO Selection" ;
   CAT3DAnnotationTextGP   *pTextGP = new CAT3DAnnotationTextGP(TextPos,TextValue);
 

   pRepForText->AddGP(pTextGP,TextGa);

   // 
   // The life cycle of the rep is now managed by the 
   // component
   //
   
   _pITextToSelectModel->SetGraphicRepresentation(pRepForText) ;

   return S_OK ;
}
//----------------------------------------------------------------------------------




