// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Class "CAAEV5V6OsmBehaviorCustomizationAdd":
// -------------------------------
//
// This is the implementation of the CATIFmFeatureBehaviorCustomization interface 
// for the "CAAOsmAdd" feature.
// A "Build" operation calculates the values of attributes according to their
// pre-defined function.  Its execution is triggered by the execution of an
// "Update" operation so as to update all current values.  To perform this "Build"
// operation, the three attributes of the "CAAOsmAdd" feature are retrieved, the values of
// the first two, "First" and "Second" are added together and their sum is stored
// as the value of the "Sum" attribute.  Thus, "Sum" wil have an updated value
// whenever an "Update" operation is requested.

//=============================================================================

#ifndef CAAEV5V6OsmBehaviorCustomizationAdd_H_ 
#define CAAEV5V6OsmBehaviorCustomizationAdd_H_ 

#include "CATFmFeatureCustomizationAdaptor.h"

class CAAEV5V6OsmBehaviorCustomizationAdd : public CATFmFeatureCustomizationAdaptor 
{
 CATDeclareClass;

	public:

	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	  
      virtual HRESULT	Build() ; 
   private:
	
	  CAAEV5V6OsmBehaviorCustomizationAdd();
	  virtual ~CAAEV5V6OsmBehaviorCustomizationAdd();


};
#endif
