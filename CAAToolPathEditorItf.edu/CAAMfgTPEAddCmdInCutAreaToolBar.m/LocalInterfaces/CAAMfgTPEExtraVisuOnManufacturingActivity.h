//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//===================================================================
//
// CAAMfgTPEExtraVisuOnManufacturingActivity.h
// Provide implementation to interface CATIMfgTPEExtraVisu
//
//===================================================================

#ifndef CAAMfgTPEExtraVisuOnManufacturingActivity_H
#define CAAMfgTPEExtraVisuOnManufacturingActivity_H

#include "CATExtIVisu.h"

class CAAMfgTPEExtraVisuOnManufacturingActivity: public CATExtIVisu
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAMfgTPEExtraVisuOnManufacturingActivity ();
    virtual ~CAAMfgTPEExtraVisuOnManufacturingActivity ();
    
    CATRep* BuildRep();
    
private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAMfgTPEExtraVisuOnManufacturingActivity (CAAMfgTPEExtraVisuOnManufacturingActivity &);
    CAAMfgTPEExtraVisuOnManufacturingActivity& operator=(CAAMfgTPEExtraVisuOnManufacturingActivity&);
    
};

//-----------------------------------------------------------------------

#endif
