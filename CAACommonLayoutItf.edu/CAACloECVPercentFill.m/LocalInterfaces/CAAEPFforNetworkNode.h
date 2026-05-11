// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// CAAEPFforNetworkNode.h
// Provide implementation to interface CATIEcvPercentFill
//
//===================================================================
#ifndef CAAEPFforNetworkNode_H
#define CAAEPFforNetworkNode_H

#include "CATBaseUnknown.h"
#include "CATEcwLightNwkNodeForPercentFill.h"
#include "CATEcwLightNwkArcForPercentFill.h"
#include "CATEcwLightNwkCableForPercentFill.h"
#include "CATLISTP_CATEcwLightNwkCableForPercentFill.h"
#include "CATLISTP_CATEcwLightNwkArcForPercentFill.h"

//-----------------------------------------------------------------------

/**
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATIEcvPercentFill
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class CAAEPFforNetworkNode: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAEPFforNetworkNode ();
     virtual ~CAAEPFforNetworkNode ();

    /**
     * Implements a function from an interface.
     * @href CATIEcvPercentFill#ComputePercentFillValue
     */
     HRESULT ComputePercentFillValue (CATEcwLightNwkNodeForPercentFill *  pNwkNode  , CATEcwLightNwkArcForPercentFill *  pNwkArc  , CATLISTP(CATEcwLightNwkArcForPercentFill)  pListOfCATEcwLightNwkArcForPercentFill  , CATEcwLightNwkCableForPercentFill *  pNwkCable  , CATLISTP(CATEcwLightNwkCableForPercentFill)  pListOfCATEcwLightNwkCableForPercentFill  , int  iRoutingMode  , int  iRouteToolsOptionStackCableOption  , int  iPFToBeSetOnNode  , double &  odComputedPercentFill  ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAEPFforNetworkNode (CAAEPFforNetworkNode &);
  CAAEPFforNetworkNode& operator=(CAAEPFforNetworkNode&);

};

//-----------------------------------------------------------------------

#endif
