// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrGeoChartWindowAdn.h"
#include "CAAAfrComboColorHeader.h"   // The header to instantiate

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Creates the CAAAfrGeoChartWindowAdnHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAAfrGeoChartWindowAdnHeader);  

#include <iostream.h>

//--------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CAAIAfrGeometryWksAddin.h>
TIE_CAAIAfrGeometryWksAddin(CAAAfrGeoChartWindowAdn);

// To declare that the class is a DataExtension of (late type) CAAAfrGeoChartWindowAddin
//
CATImplementClass(CAAAfrGeoChartWindowAdn, DataExtension, CATBaseUnknown, CAAAfrGeoChartWindowAddin);

// 
// To declare that CAAAfrGeoChartWindowAddin implements CAAIAfrGeometryWksAddin,
// insert the following line in the interface dictionary:
//
//   CAAAfrGeoChartWindowAddin  CAAIAfrGeometryWksAddin  libCAAAfrGeoWksAddin
//
//-----------------------------------------------------------------------


CAAAfrGeoChartWindowAdn::CAAAfrGeoChartWindowAdn()
{
  cout << " CAAAfrGeoChartWindowAdn::constructor" << endl ;
}

CAAAfrGeoChartWindowAdn::~CAAAfrGeoChartWindowAdn()
{
  cout << " CAAAfrGeoChartWindowAdn::destructor" << endl ;
}

void CAAAfrGeoChartWindowAdn::CreateCommands()
{
  cout << " CAAAfrGeoChartWindowAdn::CreateCommands" << endl ;
  
  //--------------------------------------------------------------------------
  // Instantiation of the header class created by the MacDeclareHeader macro.
  // Commands are always available and are represented by a push button
  //--------------------------------------------------------------------------

  new CAAAfrGeoChartWindowAdnHeader("CAAAfrHistogramChartWindowHdr",  
                                 "CAADegGeoCommands","CAADegHistogramChartWindowCmd",  (void *)NULL);

  // Customized header of command 
  new CAAAfrComboColorHeader("CAAAfrComboColorHdr");
}

CATCmdContainer * CAAAfrGeoChartWindowAdn::CreateToolbars()
{
  // ----------------------------
  // ChartWindow Toolbar
  // -----------------------------  
  NewAccess(CATCmdContainer,pCAAAfrChartWindowTlb,CAAAfrChartWindowTlb);

      NewAccess(CATCmdStarter,pCAAAfrHistogramChartWindowStr, CAAAfrHistogramChartWindowStr);
      SetAccessCommand(pCAAAfrHistogramChartWindowStr,"CAAAfrHistogramChartWindowHdr");
      SetAccessChild(pCAAAfrChartWindowTlb,pCAAAfrHistogramChartWindowStr);

  // Visible toolbar docked at the bottom
  AddToolbarView(pCAAAfrChartWindowTlb,1,Bottom); 

  // ----------------------------
  // Customized Header Toolbar
  // -----------------------------  
  NewAccess(CATCmdContainer,pCAAAfrCustoHdrTlb,CAAAfrCustoHdrTlb);
  SetAccessNext(pCAAAfrChartWindowTlb,pCAAAfrCustoHdrTlb);

      NewAccess(CATCmdStarter,pCAAAfrComboColorStr, CAAAfrComboColorStr);
      SetAccessCommand(pCAAAfrComboColorStr,"CAAAfrComboColorHdr");
      SetAccessChild(pCAAAfrCustoHdrTlb,pCAAAfrComboColorStr);

  // Visible toolbar docked at the bottom
  AddToolbarView(pCAAAfrCustoHdrTlb,1,Bottom); 

  //----------------------
  //  Menubar 
  //----------------------
  NewAccess(CATCmdContainer,pCAAAfrChartWindowMbr,CAAAfrChartWindowMbr);

       //  menu Window with the new command
       //------------------------------------------------------
       NewAccess(CATCmdContainer,pCAAAfrChartWindowMnu,CATAfrWindowMnu);
       SetAccessChild(pCAAAfrChartWindowMbr,pCAAAfrChartWindowMnu);

          NewAccess(CATCmdStarter,pCAAAfrMHistogramChartWindowStr, CAAAfrMHistogramChartWindowStr);
          SetAccessCommand(pCAAAfrMHistogramChartWindowStr,"CAAAfrHistogramChartWindowHdr");
          SetAccessChild(pCAAAfrChartWindowMnu,pCAAAfrMHistogramChartWindowStr);

  
  // Sets the menu
  SetAddinMenu(pCAAAfrChartWindowTlb,pCAAAfrChartWindowMbr);

  // The pointer of the first toolbar
  return pCAAAfrChartWindowTlb;
}

