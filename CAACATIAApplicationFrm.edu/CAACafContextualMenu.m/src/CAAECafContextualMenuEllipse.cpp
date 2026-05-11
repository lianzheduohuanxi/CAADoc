// Local Framework 
#include "CAAECafContextualMenuEllipse.h"

// ApplicationFrame Framework
#include "CATCreateWorkshop.h"

//C library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// To declare that this class is a data extension of CAASysEllipse
//
CATImplementClass(CAAECafContextualMenuEllipse, DataExtension,CATBaseUnknown,CAASysEllipse);
// 
// To declare that CAAECafContextualMenuEllipse implements CATIContextualMenu, 
// insert  this following line in the interface dictionary:
//
//    CAASysEllipse    CATIContextualMenu  libCAACafContextualMenu
//
#include "TIE_CATIContextualMenu.h"
TIE_CATIContextualMenu(CAAECafContextualMenuEllipse);
//--------------------------------------------------------------------------------------------

CAAECafContextualMenuEllipse::CAAECafContextualMenuEllipse()
{
   cout << "CAAECafContextualMenuEllipse::CAAECafContextualMenuEllipse" << endl;
   
   // The menu to customize
   CATCmdContainer * pMenu = NULL ; 

   //Retrieve the default menu ( Cut, Copy, Paste, ...) 
   CATExtIContextualMenu::GetContextualMenu(pMenu);

   if ( NULL != pMenu )
   {
      //Creation of accesses
      NewAccess(CATCmdStarter,pStEllipse,CAACafContextualMenuEllipseStr);
      NewAccess(CATCmdStarter,pStCircle,CAACafContextualMenuCircleStr);
      NewAccess(CATCmdSeparator,pSep1,CAACafContextualMenuSep);

      // Associate command header to each starter 
      // Each header is defined in a workshop or a workbench where is used
      // this contextual menu
      //
      // See CAAApplicationFrame.edu/CAAAfrGeometryWshop.m/CAAAfrGeometryWks.cpp
      // the code of the CAAGeometry workshop
      //

      SetAccessCommand(pStEllipse,"CAAAfrEllipseHdr");
      SetAccessCommand(pStCircle,"CAAAfrCircleHdr");

      // These 3 accesses are tied together 
      // In this order: Ellipse, Circle and the separator is the last access. 
      // The first access, Ellipse, is just next the last item of the
      // default menu
      SetAccessNext(pStEllipse,pStCircle);
      SetAccessNext(pStCircle,pSep1);

      AddAccessChild(pMenu,pStEllipse);
   }
}

CAAECafContextualMenuEllipse::~CAAECafContextualMenuEllipse()
{
  cout << "CAAECafContextualMenuEllipse::~CAAECafContextualMenuEllipse" << endl;
}


