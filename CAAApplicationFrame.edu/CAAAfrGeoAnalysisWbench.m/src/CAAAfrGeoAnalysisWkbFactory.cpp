// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include <CAAAfrGeoAnalysisWkb.h>

// To create the TIE object
#include <CAAAfrGeoAnalysisWkbFactory.h>
#include <TIE_CAAIAfrGeoAnalysisWkbFactory.h>

// Macro to automatically create the factory class for the 
// CAAAfrGeoAnalysisWkb workbench, as a data extension of the CATApplicationFrame 
// class .
// 
CATImplementConfigurationFactory(CAAAfrGeoAnalysisWkb, CAAIAfrGeoAnalysisWkbFactory);

//
// To declare that CATApplicationFrame implements CAAIAfrGeoAnalysisWkbFactory, 
// insert the following line in the interface dictionary:
//
//    CATApplicationFrame CAAIAfrGeoAnalysisWkbFactory  libCAAAfrGeoAnalysisWbench
//

// To declare that the factory creates an instance of the CAAAfrGeoAnalysisWkb  
// class, insert the following line in the factory dictionary:
//
//    CAAAfrGeoAnalysisWkb          CAAIAfrGeoAnalysisWkbFactory
