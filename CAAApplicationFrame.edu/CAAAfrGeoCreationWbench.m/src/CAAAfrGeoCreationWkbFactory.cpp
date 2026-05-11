// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include <CAAAfrGeoCreationWkb.h>
#include <CAAAfrGeoCreationWkbFactory.h>

// To create the TIE object
#include <TIE_CAAIAfrGeoCreationWkbFactory.h>

// Macro to automatically create the factory class for the 
// CAAAfrGeoCreationWkb workbench, as a data extension of the CATApplicationFrame class .
// 
CATImplementConfigurationFactory(CAAAfrGeoCreationWkb, CAAIAfrGeoCreationWkbFactory);

//
// To declare that CATApplicationFrame implements CAAIAfrGeoCreationWkbFactory, insert 
// the following line in the interface dictionary:
//
//    CATApplicationFrame CAAIAfrGeoCreationWkbFactory  libCAAAfrGeoCreationWbench
//

// To declare that the factory creates an instance of the CAAAfrGeoCreationWkb  
// class, insert the following line in the factory dictionary:
// 
//    CAAAfrGeoCreationWkb       CAAIAfrGeoCreationWkbFactory
