// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrGeoClippingAdn.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Creates the CAAAfrGeoClippingAdnHeader command header class
#include "CATCommandHeader.h"
MacDeclareHeader(CAAAfrGeoClippingAdnHeader);  

#include <iostream.h>

//--------------------------------------------------------------------------
// To create the TIE Object
#include <TIE_CAAIAfrGeometryWksAddin.h>
TIE_CAAIAfrGeometryWksAddin(CAAAfrGeoClippingAdn);

// To declare that the class is a DataExtension of (late type) CAAAfrGeoClippingAddin
//
CATImplementClass(CAAAfrGeoClippingAdn, DataExtension, CATBaseUnknown, CAAAfrGeoClippingAddin);

// 
// To declare that CAAAfrGeoClippingAddin implements CAAIAfrGeometryWksAddin,
// insert the following line in the interface dictionary:
//
//   CAAAfrGeoClippingAddin  CAAIAfrGeometryWksAddin  libCAAAfrGeoWksAddin
//
//-----------------------------------------------------------------------


CAAAfrGeoClippingAdn::CAAAfrGeoClippingAdn()
{
  cout << " CAAAfrGeoClippingAdn::constructor" << endl ;
}

CAAAfrGeoClippingAdn::~CAAAfrGeoClippingAdn()
{
  cout << " CAAAfrGeoClippingAdn::destructor" << endl ;
}

void CAAAfrGeoClippingAdn::CreateCommands()
{
  cout << " CAAAfrGeoClippingAdn::CreateCommands" << endl ;
  
  //--------------------------------------------------------------------------
  // Instantiation of the header class created by the MacDeclareHeader macro.
  // Commands are always available and are represented by a push button
  //--------------------------------------------------------------------------

  new CAAAfrGeoClippingAdnHeader("CAAAfrClippingByBoxHdr",  
                                 "CAADegGeoCommands","CAADegClippingByBoxCmd",  (void *)NULL);

  new CAAAfrGeoClippingAdnHeader("CAAAfrClippingByPlaneHdr",
                                 "CommandLib","ClippingPlaneCmd",(void *)NULL);

  new CAAAfrGeoClippingAdnHeader("CAAAfrClippingBySphereHdr",  
                                 "CAADegGeoCommands","CAADegClippingBySphereCmd",  (void *)NULL);
}

CATCmdContainer * CAAAfrGeoClippingAdn::CreateToolbars()
{
  // ----------------------------
  // Clipping ToolBar
  // -----------------------------  
  NewAccess(CATCmdContainer,pCAAAfrClippingTlb,CAAAfrClippingTlb);

      NewAccess(CATCmdStarter,pCAAAfrTClippingBoxStr, CAAAfrTClippingBoxStr);
      SetAccessCommand(pCAAAfrTClippingBoxStr,"CAAAfrClippingByBoxHdr");
      SetAccessChild(pCAAAfrClippingTlb,pCAAAfrTClippingBoxStr);

      NewAccess(CATCmdStarter,pCAAAfrTClippingPlaneStr,CAAAfrTClippingPlaneStr);
      SetAccessCommand(pCAAAfrTClippingPlaneStr,"CAAAfrClippingByPlaneHdr");
      SetAccessNext(pCAAAfrTClippingBoxStr,pCAAAfrTClippingPlaneStr);

      NewAccess(CATCmdStarter,pCAAAfrTClippingSphereStr,CAAAfrTClippingSphereStr);
      SetAccessCommand(pCAAAfrTClippingSphereStr,"CAAAfrClippingBySphereHdr");
      SetAccessNext(pCAAAfrTClippingPlaneStr,pCAAAfrTClippingSphereStr);

  // Visible toolbar docked at the right of the application window 
  AddToolbarView(pCAAAfrClippingTlb,1,Right); 

  // The pointer of the first toolbar
  return pCAAAfrClippingTlb;
}

