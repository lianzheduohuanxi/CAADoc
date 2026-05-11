#ifndef CAAV5V6ExtMmrVisuProvForExtCont_H
#define CAAV5V6ExtMmrVisuProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2012
//==================================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrVisuProvForExtCont : 
//  implmements CATI3DVisuProvider interface.
//  Extends CATI3DGeoVisu Mechanism to Extension Features contained in the 
//    applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)
//
//==================================================================================================

// ObjectModelerBase Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATI3DVisuProvider.h"


class CAAV5V6ExtMmrVisuProvForExtCont: public CATI3DVisuProvider
{
  CATDeclareClass;

  CAAV5V6ExtMmrVisuProvForExtCont();
  virtual ~CAAV5V6ExtMmrVisuProvForExtCont();

public:

  /**
  * Returns a list of the children of a base feature's extension(s).
  * @param iObj
  *    The base feature object.
  * @param oListChildren
  *    The list of the children of the base feature's extension(s).
  */
  HRESULT GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren);

private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAV5V6ExtMmrVisuProvForExtCont(CAAV5V6ExtMmrVisuProvForExtCont&);
  CAAV5V6ExtMmrVisuProvForExtCont& operator=(CAAV5V6ExtMmrVisuProvForExtCont&);

};
#endif
