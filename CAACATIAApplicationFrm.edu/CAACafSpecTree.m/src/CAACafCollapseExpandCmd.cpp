// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework 
#include "CAACafCollapseExpandCmd.h"

//ApplicationFrame Framework
#include "CATFrmLayout.h"    
#include "CATFrmWindow.h"    

// CATIAApplicationFrame Framework
#include "CATFrmNavigGraphicWindow.h"
#include "CATNavigBox.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"
#include "CATDialogState.h"

// ObjectModelerNavigator Framework
#include "CATNavigController.h"
#include "CATINavigContainer.h"
#include "CATINavigateObject.h"
#include "CATINavigElement.h"
#include "CATIGraphNode.h"
 
// Visualization Framework
#include "CATPathElement.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATGetEnvValue.h"  
#include "CATIAlias.h"
#include "CATUnicodeString.h"            

//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAACafCollapseExpandCmd);

//----------------------LifeCycle's PART ----------------------------------
CAACafCollapseExpandCmd::CAACafCollapseExpandCmd():
                   CATStateCommand("CAACafCollapseExpandCmdId"),
                        _daObjectToExpandNode(NULL),
                        _pNavigController(NULL),
                        _pExpandMode(NULL)

                        
{
  cout << "CAACafCollapseExpandCmd constructor" << endl ; 

  GetNavigController();

  ::CATGetEnvValue("CAACafSpecTreeExpandMode",&_pExpandMode);  

}

//-----------------------------------------------------------------------

CAACafCollapseExpandCmd::~CAACafCollapseExpandCmd()
{
  cout << "CAACafCollapseExpandCmd destructor" << endl ;

  if ( NULL != _daObjectToExpandNode ) 
  {
     _daObjectToExpandNode -> RequestDelayedDestruction() ;
     _daObjectToExpandNode = NULL ;
  }

  if ( NULL != _pExpandMode )
  {
     free (_pExpandMode) ;
     _pExpandMode = NULL ;
  }

  _pNavigController = NULL ;



}

//----------------------BuildGraph PART -----------------------------------

void CAACafCollapseExpandCmd::BuildGraph()
{
  cout << "CAACafCollapseExpandCmd BuildGraph" << endl ;
  
   //1- Creates the dialog agent  
   //    -  it gets only Navigate Object elements 
   //    -  an element is selected with the right button 
   //    -  the repeat mode allows you to reuse this agent, so to revalue it
   //    -  the selected object will be highlighted
   _daObjectToExpandNode = new CATPathElementAgent("SelObjectToExpandNodeId");
   _daObjectToExpandNode -> AddElementType (IID_CATINavigateObject);
   
   _daObjectToExpandNode -> SetBehavior (CATDlgEngRepeat | CATDlgEngWithPSOHSO );
                            
 
   //2- Creates the state. See NLS file for the message in the status bar

   CATDialogState *stGetObjState = GetInitialState("stGetObjStateId");
   stGetObjState -> AddDialogAgent(_daObjectToExpandNode);

   // 3- The transition loops on the transition state 
   //   
   CATDialogTransition *pTransition =    AddTransition
   (
      stGetObjState,
      stGetObjState,
      IsLastModifiedAgentCondition(_daObjectToExpandNode)  , 
      Action((ActionMethod) & CAACafCollapseExpandCmd::ExpandObject)
   );  

}

//----------------------Action methods's PART -----------------------------

CATBoolean CAACafCollapseExpandCmd::ExpandObject(void *iDummy)
{
  cout << "CAACafCollapseExpandCmd::ExpandObject" << endl ;

  if ( NULL != _pNavigController )
  {
     CATPathElement * pObjPathSel = _daObjectToExpandNode -> GetValue();
    
     // Dump the path element of the selected object
     DumpPathElement ( pObjPathSel );
    
     // Extract from the selected path all element which are a mechanical features
     //
     CATPathElement * pObjPath = NULL;
     if(NULL != pObjPathSel)
     {
        pObjPath = pObjPathSel -> GetSubPath ( "CATIMmiMechanicalFeature") ;       
        DumpPathElement ( pObjPath );
     }
     CATBaseUnknown * pObjectToExpand = NULL;
     
     if ( NULL != pObjPath) 
     {
         if ( pObjPath -> GetSize () > 0 )
         { 
            // The leaf of the selection
            pObjectToExpand = (*pObjPath)[pObjPath -> GetSize()-1];
            
            // Display the type of the object to expand
            CATUnicodeString Type;
            if(NULL != pObjectToExpand) 
               Type = pObjectToExpand -> GetImpl() -> IsA() ;
            cout << "pObjectToExpand  Type  = " << Type.ConvertToChar() << endl;

         }

         // Expands from the top to the selected object'father  
         //
         for ( int j = 0 ; j <= pObjPath->GetSize()-2 ; j++)
         {
            CATBaseUnknown * pFatherObjectToExpand = (*pObjPath)[j];
            CATListValCATBaseUnknown_var * pNodeList = NULL ;
            pNodeList = _pNavigController -> GetAssociatedElements ( pFatherObjectToExpand );
        
            if ( NULL != pNodeList )
            {
               int nbNodes = pNodeList->Size();
           
               for ( int k= 1 ; k <= nbNodes ; k++ )
               {
                  CATIGraphNode_var graphNode = (*pNodeList)[k];
                  if ( NULL_var != graphNode )
                  {
                     // To be expanded
                     if ( 0 == graphNode -> IsExpanded() )
                     {
                        CATINavigElement_var spNavigElement = graphNode ;

                        if ( NULL_var != spNavigElement )
                        {
                           spNavigElement->ProcessAfterExpand();
                        }
                     }
                  }
               }
            }
            delete pNodeList ;
            pNodeList = NULL ;
         }
           
         // Processes the leaf
         if ( (NULL != _pExpandMode) && 
          (0==strcmp("CAACafSpecTreeExpandAllNodes",_pExpandMode)) )
         {
             ExpandAllNode(pObjectToExpand);
         }else
         {
             ExpandCollapseNode(pObjectToExpand);
         }
         pObjPath -> Release ();
         pObjPath = NULL;

     }
  }

  return TRUE ;
}

//-------------------------------------------------------------------

void CAACafCollapseExpandCmd::GetNavigController()
{
  cout << "CAACafCollapseExpandCmd::GetNavigController" << endl ;

  // Retrieves the current window 
  CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL != pLayout )
  {
     CATFrmWindow * pCurrentWindow = pLayout->GetCurrentWindow();

     if ( NULL != pCurrentWindow )
     {
         // If it is a CATFrmNavigGraphicWindow, it is possible to
         // retrieve a CATNavigController pointer
         //
         if ( 1 == pCurrentWindow -> IsAKindOf("CATFrmNavigGraphicWindow") )
         {
             CATFrmNavigGraphicWindow * pFrmNavigGraphicWindow = 
                 (CATFrmNavigGraphicWindow*) pCurrentWindow ;

             CATNavigBox * pNavigBox = NULL ;
             pNavigBox = pFrmNavigGraphicWindow->GetNavigBox();

             if ( NULL != pNavigBox )
             {
                _pNavigController = pNavigBox->GetController();
             }
         }
     }
  }
}

//-------------------------------------------------------------------

void CAACafCollapseExpandCmd::ExpandCollapseNode(CATBaseUnknown_var iObject)
{
    cout << "CAACafCollapseExpandCmd::ExpandCollapseNode" << endl ;

    // Expands or collapses the selected object
    //
    if ( NULL_var != iObject )
    {
        CATListValCATBaseUnknown_var * pNodeList = NULL ;
        if( NULL != _pNavigController )
           pNodeList = _pNavigController -> GetAssociatedElements (iObject);

        if ( NULL != pNodeList )
        {
           int nbNodes = pNodeList -> Size();
           for ( int i= 1 ; i <= nbNodes ; i++ )
           {
               CATBaseUnknown_var spNode = (*pNodeList)[i];

               if ( NULL_var != spNode )
               {
                   CATINavigElement_var spNavigElement = spNode ;

                   if ( NULL_var != spNavigElement )
                   {
                      spNavigElement -> ProcessAfterExpand();          
                   }
               }
       
           }
           delete pNodeList ;
           pNodeList = NULL ;
        }
    }
}

//-------------------------------------------------------------------

void CAACafCollapseExpandCmd::ExpandAllNode(CATBaseUnknown_var iObject)
{
    cout << "CAACafCollapseExpandCmd::ExpandAllNode" << endl ;

    // Expands all from the selected object
    //
    if ( NULL_var != iObject )
    {
        CATListValCATBaseUnknown_var * pNodeList = NULL ;
        if( NULL != _pNavigController )
           pNodeList = _pNavigController->GetAssociatedElements (iObject);

        if ( NULL != pNodeList )
        {
           int nbNodes = pNodeList->Size();
           for ( int i= 1 ; i <= nbNodes ; i++ )
           {
              CATIGraphNode_var graphNode = (*pNodeList)[i];
              if ( NULL_var != graphNode )
              {
                  // To be expanded
                  if ( 0 == graphNode->IsExpanded() )
                  {
                      CATINavigElement_var spNavigElement = graphNode ;

                      if ( NULL_var != spNavigElement )
                      {
                         spNavigElement->ProcessAfterExpand();
                      }
                  }
              }
           }
           delete pNodeList ;
           pNodeList = NULL ;
        }

        // Processes the children
        CATINavigateObject_var spNavigateObject = iObject ;
        if ( NULL_var != spNavigateObject )
        {
           CATListValCATBaseUnknown_var* pListChild = NULL ;
           pListChild = spNavigateObject->GetChildren();

           if ( NULL != pListChild )
           {
              for ( int t = 1 ; t <= pListChild->Size() ; t++)
              {
                 CATBaseUnknown_var spOnChild = (*pListChild)[t];
                 ExpandAllNode(spOnChild);
              }

              delete pListChild ;
              pListChild = NULL ;
           }
        }
  
    }
}


//-----------------------------------------------------------------------------
// DumpPathElement
//-----------------------------------------------------------------------------
HRESULT CAACafCollapseExpandCmd::DumpPathElement (CATPathElement * ipPathElement)
{
   HRESULT rc = E_INVALIDARG;
   if (NULL != ipPathElement)
   {
      cout << " " << endl;
      cout << "++++++++++++++++++ PathElement ++++++++++++++++" << endl;
      ipPathElement -> InitToTopObject();
      CATBaseUnknown * pBaseUnknown = NULL;
      while (pBaseUnknown = ipPathElement -> NextChildObject()) 
      {
         if (pBaseUnknown->IsAKindOf(CATPathElement::ClassName())) 
            DumpPathElement ((CATPathElement*)pBaseUnknown);
         else
         {
            CATUnicodeString Name = ".....";
            CATIAlias_var spAlias = pBaseUnknown;
            if (NULL_var != spAlias)  Name = spAlias -> GetAlias ();
            CATUnicodeString Type = pBaseUnknown -> GetImpl() -> IsA();
            cout << "     Element : " << Name.ConvertToChar () << "   Type : " << Type.ConvertToChar () << endl;
            
            list<CATBaseUnknown> * pBrotherList = ipPathElement -> BrotherList (pBaseUnknown);
            if (NULL != pBrotherList)
            {
               for (int iBrother = 0; iBrother < pBrotherList->length(); iBrother++)
               {
                  CATBaseUnknown * pBrother = (*pBrotherList)[iBrother];
                  if (NULL != pBrother)
                  {
                     if (pBrother->IsAKindOf(CATPathElement::ClassName())) 
                        DumpPathElement ((CATPathElement*)pBrother);
                     else
                     {
                        CATUnicodeString Name = ".....";
                        CATIAlias_var spAlias = pBrother;
                        if (NULL_var != spAlias)  Name = spAlias -> GetAlias ();
                        CATUnicodeString Type = pBrother -> GetImpl() -> IsA();
                        cout << "         Brother Element : " << Name.ConvertToChar () << "   Type : " << Type.ConvertToChar () << endl;
                     }
                  }
               }
            }
         }
      }
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
   }
   return rc;
}
