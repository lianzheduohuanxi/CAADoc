// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisModelEvents.h"

//others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATIModelEvents.h"
TIE_CATIModelEvents(CAAEVisModelEvents);

// To declare that the class is a data extension of the document objects.
// ( CAASysCircle, CAASysSampRootObj ...)
//

CATBeginImplementClass(CAAEVisModelEvents, DataExtension, CATBaseUnknown, CAASysPoint);
CATAddClassExtension(CAASysSampRootObj);
CATAddClassExtension(CAASysGeomRootObj);
CATAddClassExtension(CAASysLine);
CATAddClassExtension(CAASysEllipse);
CATAddClassExtension(CAASysPlane);
CATAddClassExtension(CAASysCircle);
CATAddClassExtension(CAASysPolyline);
CATAddClassExtension(CAASysCuboid);
CATAddClassExtension(CAASysCylinder);
CATEndImplementClass(CAAEVisModelEvents); 

// 
// To declare that CAAEVisModelEvents implements CATIModelEvents, insert 
// these following lines in the interface dictionary:
//
//    CAASysEllipse    CATIModelEvents  libCAAVisGeoModel
//    CAASysSampRootObj CATIModelEvents  libCAAVisGeoModel
//    ....

//-----------------------------------------------------------------------------

CAAEVisModelEvents::CAAEVisModelEvents()
{
  cout << "CAAEVisModelEvents::CAAEVisModelEvents" << endl;
}

CAAEVisModelEvents::~CAAEVisModelEvents()
{
  cout << "CAAEVisModelEvents::~CAAEVisModelEvents" << endl;
}
