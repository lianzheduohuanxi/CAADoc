// COPYRIGHT DASSAULT SYSTEMES  2007
//=============================================================================
//
// CAACloPlacePart
//
#ifndef CAACloPlacePart_H
#define CAACloPlacePart_H

#include "CAAPspBaseEnvProtected.h"
#include "CATError.h"
#include "CATUnicodeString.h"

class CATIMovable;
class CATMathDirection;

//-----------------------------------------------------------------------------

class CAACloPlacePart : public CAAPspBaseEnvProtected
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAACloPlacePart ();
    virtual ~CAACloPlacePart();

    //-------------------------------------------------------------------------
    // Get a part connector.
    //-------------------------------------------------------------------------
    HRESULT GetPartConnector(const IUnknown *ipiPartUnk, 
                             const int &iConnectorNumber, 
                             IUnknown *&opiPartConnector);

    //-------------------------------------------------------------------------
    // Get location data for a part connector.
    //-------------------------------------------------------------------------
    HRESULT GetPartConnectorData(const IUnknown *ipiPartUnk, 
                                 const int &iConnectorNumber, 
                                 IUnknown *ipiRelAxisUnk, 
                                 CATMathPoint &oCtrPosition, 
                                 CATMathDirection &oCtrAlign, 
                                 CATMathDirection &oCtrUp);

    //-------------------------------------------------------------------------
    // Get part connected to a part ctr.
    //-------------------------------------------------------------------------
    HRESULT GetConnectedPart(const IUnknown *ipiPartUnk, 
                             const int &iConnectorNumber, 
                             IUnknown *&opiConnectedCtr, 
                             IUnknown *&opiConnectedPart);

    //-------------------------------------------------------------------------
    //  Test location data for a part connector.
    //-------------------------------------------------------------------------
    HRESULT TestConnectedPart(const IUnknown *ipiPartUnk, 
                              const int &iConnectorNumber, 
                              const IUnknown *ipiConnectedPart, 
                              const int &iConnectedConnectorNumber);

    //-------------------------------------------------------------------------
    //  Test location data for a part connector.
    //-------------------------------------------------------------------------
    HRESULT TestPartConnectorData(const IUnknown *ipiPartUnk, 
                                  const int &iConnectorNumber, 
                                  IUnknown *ipiRelAxisUnk, 
                                  const CATMathPoint &iCtrPosition, 
                                  const CATMathDirection &iCtrAlign, 
                                  const CATMathDirection &iCtrUp);

    //-------------------------------------------------------------------------
    // Place a part in space.
    //-------------------------------------------------------------------------
    HRESULT PlacePartInSpace();

    //-------------------------------------------------------------------------
    // Route a string part in space.
    //-------------------------------------------------------------------------
    HRESULT RouteStringPartInSpace();

    //-------------------------------------------------------------------------
    // Place a part on a run segment.
    //-------------------------------------------------------------------------
    HRESULT PlacePartOnRunSegment();

    //-------------------------------------------------------------------------
    // Place a part on a run node.
    //-------------------------------------------------------------------------
    HRESULT PlacePartOnRunNode();

    //-------------------------------------------------------------------------
    // Place a part on a part conntector.
    //-------------------------------------------------------------------------
    HRESULT PlacePartOnPartConnector();

     //-------------------------------------------------------------------------
    // Place part on part connector and reconnect run to the placed part.
    //-------------------------------------------------------------------------
    HRESULT PlacePartOnPartConnectorAndReconnectRun();

    //-------------------------------------------------------------------------
    // Input: iuFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    HRESULT DoSample (const CATUnicodeString &iuFileToBeLoaded);
};
#endif
