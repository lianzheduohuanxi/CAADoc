// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombinedCurveContSubMenu
//    Implementation of interface CATIContextualSubMenu for V5V6ExtCombinedCurve 
//
//====================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6ExtMechanicalModeler.edu Framework  
#include "CAAEV5V6ExtMmrCombinedCurveContSubMenu.h"

// AfrFoundation Framework for V6
// ApplicationFrame Framework for V5
#include "CATCreateWorkshop.h"

// CATMecModUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIMechanicalProperties.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass(CAAEV5V6ExtMmrCombinedCurveContSubMenu,DataExtension,CATBaseUnknown,V5V6ExtCombinedCurve);
// 
// To declare that V5V6ExtCombinedCurve implements CATIContextualSubMenu, 
// insert  this following line in the interface dictionary:
//
//        V5V6ExtCombinedCurve     CATIContextualSubMenu     libCAAV5V6ExtMmrCombinedCurveUI
//
//---------------------------------------------------------------------------------------------
#include "TIE_CATIContextualSubMenu.h"
TIE_CATIContextualSubMenu(CAAEV5V6ExtMmrCombinedCurveContSubMenu);
//-----------------------------------------------------------------------------------------
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
CAAEV5V6ExtMmrCombinedCurveContSubMenu::CAAEV5V6ExtMmrCombinedCurveContSubMenu():_pCAAV5V6ExtMmrSwapActiveStr(NULL)
#else
//============================================== 
// V5 only
//==============================================
CAAEV5V6ExtMmrCombinedCurveContSubMenu::CAAEV5V6ExtMmrCombinedCurveContSubMenu():_pMenu(NULL),_pCAAV5V6ExtMmrSwapActiveStr(NULL)
#endif
{
   cout << "CAAEV5V6ExtMmrCombinedCurveContSubMenu::CAAEV5V6ExtMmrCombinedCurveContSubMenu" << endl;

   // Creation of the starters
   NewAccess(CATCmdStarter,pCAAV5V6ExtMmrResetPropertiesStr,CAAV5V6ExtMmrResetPropertiesStr);
   NewAccess(CATCmdStarter,pCAAV5V6ExtMmrParentChildrenStr,CAAV5V6ExtMmrParentChildrenStr);

   // Check that the combined curve implements CATIMechanicalProperties
   // This is the interface to activate / deactivate the feature to the build
   //
   CATIMechanicalProperties * piMechProp = NULL;
   HRESULT rcMechProp = QueryInterface(IID_CATIMechanicalProperties, (void**) &piMechProp);
   if (SUCCEEDED(rcMechProp))
   {
      NewAccess(CATCmdStarter,pCAAV5V6ExtMmrSwapActiveStr,CAAV5V6ExtMmrSwapActiveStr);
      _pCAAV5V6ExtMmrSwapActiveStr = pCAAV5V6ExtMmrSwapActiveStr ;
      
      piMechProp->Release();
      piMechProp = NULL;
   }
   
   // These starters are set in the menu 
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
   _accessChain  = (CATCmdAccess*) pCAAV5V6ExtMmrParentChildrenStr ;
#else
//============================================== 
// V5 only
//==============================================
    _pMenu = pCAAV5V6ExtMmrParentChildrenStr ;
#endif

   SetAccessNext(pCAAV5V6ExtMmrParentChildrenStr,pCAAV5V6ExtMmrResetPropertiesStr);

   if (NULL != _pCAAV5V6ExtMmrSwapActiveStr)
   {    
      SetAccessNext(pCAAV5V6ExtMmrResetPropertiesStr,_pCAAV5V6ExtMmrSwapActiveStr);
   }

   // Associate an instance of  command header to each starter
   // except for the activate/deactivate command- it will be done
   // in the GetContextualSubMenu method
   //
   SetAccessCommand(pCAAV5V6ExtMmrResetPropertiesStr,"CATMmrPrtResetPropHdr");
   SetAccessCommand(pCAAV5V6ExtMmrParentChildrenStr,"CATParentChildrenHdr");
   
}
//-----------------------------------------------------------------------------------------

CAAEV5V6ExtMmrCombinedCurveContSubMenu::~CAAEV5V6ExtMmrCombinedCurveContSubMenu()
{
  cout << "CAAEV5V6ExtMmrCombinedCurveContSubMenu::~CAAEV5V6ExtMmrCombinedCurveContSubMenu" << endl;
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
  AccessRelease(_accessChain);
#else
//============================================== 
// V5 only
//============================================== 
  if ( NULL != _pMenu) _pMenu->Release() ;
  _pMenu = NULL ;
  
#endif

  _pCAAV5V6ExtMmrSwapActiveStr = NULL;
}

//-----------------------------------------------------------------------------------------

CATCmdAccess *  CAAEV5V6ExtMmrCombinedCurveContSubMenu::GetContextualSubMenu()
{
   cout << "CAAEV5V6ExtMmrCombinedCurveContSubMenu::GetContextualSubMenu" << endl; 
   
   // The right command header is associated with the starter named _pCAAV5V6ExtMmrSwapActiveStr,
   // This starter has been created once time in the extension's constructor,
   //  
   // 
   if (NULL != _pCAAV5V6ExtMmrSwapActiveStr)
   {
      CATIMechanicalProperties * piMechProp = NULL;
      HRESULT rcMechProp = QueryInterface(IID_CATIMechanicalProperties, (void**) & piMechProp);
      if (SUCCEEDED(rcMechProp))
      {
         int IsFeatureDeactivate = piMechProp->IsInactive();

         if ( 0 == IsFeatureDeactivate )
         {  
            // from actif -> inactif
            SetAccessCommand(_pCAAV5V6ExtMmrSwapActiveStr,"CATPrtInactiveHdr");
         }
				 else
         {
            // from inactif -> actif 
            SetAccessCommand(_pCAAV5V6ExtMmrSwapActiveStr,"CATPrtActiveHdr");
         }

         piMechProp->Release();
         piMechProp = NULL ;
      }
   }
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
   return (_accessChain);
#else
//============================================== 
// V5 only
//============================================== 
      return (_pMenu);
#endif
}
//-----------------------------------------------------------------------------------------

