// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Class "CAAEV5V6OsmBehaviorCustomizationSquare":
// ----------------------------------
//
// This is the implementation of the CATIFmFeatureBehaviorCustomization interface 
// for the "CAAOsmSquare" feature.
// A "Build" operation calculates the values of attributes according to their
// pre-defined function.  Its execution is triggered by the execution of an
// "Update" operation so as to update all current values.  To perform this "Build"
// operation, the two attributes of the "CAAOsmSquare" feature are retrieved, the value
// of the first, "Num", is squared and the result stored as the value of the
// second, "Square" attribute.  Thus, the attribute "Square" will have an updated
// value whenever an "Update" operation is requested on this feature.
//
//=============================================================================

#ifndef CAAEV5V6OsmBehaviorCustomizationSquare_H_ 
#define CAAEV5V6OsmBehaviorCustomizationSquare_H_ 

#include "CATFmFeatureCustomizationAdaptor.h"

class CAAEV5V6OsmBehaviorCustomizationSquare : public CATFmFeatureCustomizationAdaptor
{
	CATDeclareClass;

public:

      virtual HRESULT	Build() ; 
private:
	
	// Standard constructors and destructors for an implementation class
	CAAEV5V6OsmBehaviorCustomizationSquare();
	  virtual ~CAAEV5V6OsmBehaviorCustomizationSquare();

};
#endif
