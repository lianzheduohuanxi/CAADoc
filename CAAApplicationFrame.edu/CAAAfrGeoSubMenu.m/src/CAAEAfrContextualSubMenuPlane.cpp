// Local Framework 
#include "CAAEAfrContextualSubMenuPlane.h"

// ApplicationFrame Framework
#include "CATCreateWorkshop.h"

//other 
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// To declare that this class is a data extension of CAASysPlane
//
CATImplementClass(CAAEAfrContextualSubMenuPlane,DataExtension,CATBaseUnknown,CAASysPlane);
// 
// To declare that CAAEAfrContextualSubMenuPlane implements CATIContextualMenu, 
// insert  this following line in the interface dictionary:
//
//    CAASysPlane   CATIContextualSubMenu  libCAAAfrGeoSubMenu
//
//---------------------------------------------------------------------------------------------
#include "TIE_CATIContextualSubMenu.h"
TIE_CATIContextualSubMenu(CAAEAfrContextualSubMenuPlane);

//-----------------------------------------------------------------------------------------
CAAEAfrContextualSubMenuPlane::CAAEAfrContextualSubMenuPlane():_pMenu(NULL)	
                      				   
{
   cout << "CAAEAfrContextualSubMenuPlane::CAAEAfrContextualSubMenuPlane" << endl;

   // Creation of the starter
   NewAccess(CATCmdStarter,pStDump,CAAAfrDumpSubMenuStr);
   NewAccess(CATCmdStarter,pStPlane,CAAAfrPlaneSubMenuStr);

   // Associate an instance of  command header to each starter
   SetAccessCommand(pStDump,"CAAAfrDumpHdr");
   SetAccessCommand(pStPlane,"CAAAfrPlaneHdr");

   // These 2 CATCmdAccess are set in the menu  
   _pMenu = pStDump ;
   SetAccessNext(pStDump,pStPlane);
   
}
//-----------------------------------------------------------------------------------------

CAAEAfrContextualSubMenuPlane::~CAAEAfrContextualSubMenuPlane()
{
  cout << "CAAEAfrContextualSubMenuPlane::~CAAEAfrContextualSubMenuPlane" << endl;
  
  if ( NULL != _pMenu) _pMenu->Release() ;
  _pMenu = NULL ;
}

//-----------------------------------------------------------------------------------------

CATCmdAccess *  CAAEAfrContextualSubMenuPlane::GetContextualSubMenu()
{
   cout << "CAAEAfrContextualSubMenuPlane::GetContextualSubMenu" <<  endl; 
   
   return (_pMenu);
}
//-----------------------------------------------------------------------------------------

