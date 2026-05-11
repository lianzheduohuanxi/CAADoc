#ifndef CAAEV5V6ExtMmrCombCrvCkeFeature_H
#define CAAEV5V6ExtMmrCombCrvCkeFeature_H

// COPYRIGHT Dassault Systemes 2012

#include "CATIAV5Level.h"
#include "CATICkeType.h"

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
#include "CATKweObjectAdapter.h"

#else
//============================================== 
// V5 only
//============================================== 
#include "CATKweInstanceAdapter.h"
#endif


/**
* Implement of CATICkeFeature
* Usage of Knowledge adaptor : CATKweObjectAdapter for V6 
*                              CATKweInstanceAdapter for V5
* Implementation reaquired to use the feature in Knowledge tools (Mesure,mdistance ,etc ... ) 
*/
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
class  CAAEV5V6ExtMmrCombCrvCkeFeature: public CATKweObjectAdapter
#else
//============================================== 
// V5 only
//============================================== 
class  CAAEV5V6ExtMmrCombCrvCkeFeature: public CATKweInstanceAdapter
#endif
{
  CATDeclareClass;

  public:


     CAAEV5V6ExtMmrCombCrvCkeFeature ();
     virtual ~CAAEV5V6ExtMmrCombCrvCkeFeature ();

     CATICkeType_var GetType () const ;

  private:
  CAAEV5V6ExtMmrCombCrvCkeFeature (CAAEV5V6ExtMmrCombCrvCkeFeature &);
  CAAEV5V6ExtMmrCombCrvCkeFeature& operator=(CAAEV5V6ExtMmrCombCrvCkeFeature&);

};

//-----------------------------------------------------------------------

#endif
