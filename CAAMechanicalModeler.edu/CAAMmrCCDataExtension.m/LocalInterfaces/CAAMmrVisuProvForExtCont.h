#ifndef CAAMmrVisuProvForExtCont_H
#define CAAMmrVisuProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrVisuProvForExtCont : CATI3DVisuProvider Extension for MmrDataExtensionCont
//
//  Extends CATIVisuPublisher to FeatureExtensions Contained in MmrDataExtensionCont
//==================================================================================


#include "CATI3DVisuProvider.h"

class CATBaseUnknown;


class CAAMmrVisuProvForExtCont: public CATI3DVisuProvider
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  CAAMmrVisuProvForExtCont();
  virtual ~CAAMmrVisuProvForExtCont();

public:

  /**
  * Returns a list of the children of a base feature's extension(s).
  * @param iObj
  *    The base feature object.
  * @param oListChildren
  *    The list of the children of the base feature's extension(s).
  */
  HRESULT GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren);

  //private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAMmrVisuProvForExtCont(CAAMmrVisuProvForExtCont&);
  CAAMmrVisuProvForExtCont& operator=(CAAMmrVisuProvForExtCont&);
};
#endif
