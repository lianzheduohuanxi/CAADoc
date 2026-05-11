// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspConnectivity
//
#ifndef CAAPspConnectivity_H
#define CAAPspConnectivity_H

#include "CAAPspBaseEnv.h"

class CATIPspConnectable;
class CATIPspConnector;
class CATIPspConnection;
class CATIPspCntrFlow;

//-----------------------------------------------------------------------------

class CAAPspConnectivity : public CAAPspBaseEnv
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspConnectivity ();
    virtual ~CAAPspConnectivity();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);

	private :
		int QueryCntrFlowFunctions(CATIPspCntrFlow* piPspCntrFlow);
		int QueryConnectableFunctions(CATIPspConnectable* piPspConnectable);

		int QueryConnectorFunctions(CATIPspConnector* piPspConnector);

		int QueryConnectionFunctions(CATIPspConnection* piPspConnection);

		
};
#endif
