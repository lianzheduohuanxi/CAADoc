// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserMachFeature.h
//
//===================================================================
#ifndef CAAESmiUserMachFeature_H
#define CAAESmiUserMachFeature_H

#include "CATBaseUnknown.h"
#include "CATListOfCATGeometries.h"

class CAAESmiUserMachFeature: public CATBaseUnknown
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserMachFeature ();
     virtual ~CAAESmiUserMachFeature ();

	 // Gets parameter of the guide of our Machining Feature.
	 HRESULT GetGuideParameter (CATBaseUnknown_var &oParameter);
	
	 // Gets geometry of guide.
     HRESULT GetGuides (CATLISTP(CATGeometry) & oGeometries) ;

	 // Determines if all the necessary datas are filled up.
	 HRESULT IsComplete(int &oIsComplete);

  private:
  
	 // The copy constructor and the equal operator must not be implemented
     CAAESmiUserMachFeature (CAAESmiUserMachFeature &);
     CAAESmiUserMachFeature& operator=(CAAESmiUserMachFeature&);

};

#endif
