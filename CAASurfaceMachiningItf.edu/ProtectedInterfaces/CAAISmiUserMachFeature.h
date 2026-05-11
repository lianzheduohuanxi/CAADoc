// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CAAISmiUserMachFeature.h
// Allows you to access data of the CAA Machining Feature.
//
//===================================================================
#ifndef CAAISmiUserMachFeature_H
#define CAAISmiUserMachFeature_H

#include "CAASmiUserMachFeatureEnv.h"
#include "CATBaseUnknown.h"
#include "CATListOfCATGeometries.h"

extern ExportedByCAASmiUserMachFeatureEnv IID IID_CAAISmiUserMachFeature ;

// Allows you to access data of CAA Machining Feature.
class ExportedByCAASmiUserMachFeatureEnv CAAISmiUserMachFeature: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

	// Gets parameter of the guide of our Machining Feature.
	virtual HRESULT GetGuideParameter (CATBaseUnknown_var &oParameter) = 0;
	
	// Gets geometry of the guide of our Machining Feature.
	virtual HRESULT GetGuides (CATLISTP(CATGeometry) & oGeometries) = 0;

};

#endif
