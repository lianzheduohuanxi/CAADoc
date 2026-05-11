//==================================================================================

#include "CAAEEntityBoxSubscriber.h"
#include "CATISpecObject.h"


CATBeginImplementClass (CAAEEntityBoxSubscriber,CacheExtension,CATEAnalysisEntityPreproSubscriber,ANIFreeGroupEntityTst);
CATEndImplementClass   (CAAEEntityBoxSubscriber);  

CATImplementBOA (CATISamMeshSubscriber, CAAEEntityBoxSubscriber);

//==================================================================================
//-----------------------------------------------------------------------------
// CAAEEntityBoxSubscriber : constructor
//-----------------------------------------------------------------------------
CAAEEntityBoxSubscriber::CAAEEntityBoxSubscriber():
    CATEAnalysisEntityPreproSubscriber()
{
}

//-----------------------------------------------------------------------------
// CAAEEntityBoxSubscriber : destructor
//-----------------------------------------------------------------------------
CAAEEntityBoxSubscriber::~CAAEEntityBoxSubscriber()
{
}
 

