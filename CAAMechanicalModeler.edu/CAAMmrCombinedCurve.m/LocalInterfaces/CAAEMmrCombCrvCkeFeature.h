// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEMmrCombCrvCkeFeature.h
// Provide implementation to interface
//    CATKweInstanceAdapter
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//EXTENSION		: CombinedCurve 
//EXTENSIONTYPE	: DataExtension
//BOA			: CATKweInstanceAdapter
//===================================================================
#ifndef CAAEMmrCombCrvCkeFeature_H
#define CAAEMmrCombCrvCkeFeature_H

#include "CATKweInstanceAdapter.h"
#include "CATICkeType.h"


//-----------------------------------------------------------------------

/**
* Implement of CATICkeFeature
* Usage of Knowledge adaptor : CATKweInstanceAdapter
* Implementation reaquired to use the feature in Knowledge tools (Mesure,mdistance ,etc ... ) 
*/
class  CAAEMmrCombCrvCkeFeature: public CATKweInstanceAdapter

{
  CATDeclareClass;

  public:


     CAAEMmrCombCrvCkeFeature ();
     virtual ~CAAEMmrCombCrvCkeFeature ();

     CATICkeType_var GetType () const ;

  private:
  CAAEMmrCombCrvCkeFeature (CAAEMmrCombCrvCkeFeature &);
  CAAEMmrCombCrvCkeFeature& operator=(CAAEMmrCombCrvCkeFeature&);

};

//-----------------------------------------------------------------------

#endif
