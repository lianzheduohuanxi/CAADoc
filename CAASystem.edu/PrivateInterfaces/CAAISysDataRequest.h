#ifndef CAAISysDataRequest_H
#define CAAISysDataRequest_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface implemented by of the CAASysDataMessage class message. 
//  This interface allows to retrieve data contained in the message. 
//
//===========================================================================

//System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysBBMessageInt.h"  // Needed to export the IID and the class

extern ExportedByCAASysBBMessageInt IID IID_CAAISysDataRequest ;

class  ExportedByCAASysBBMessageInt CAAISysDataRequest : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

      virtual HRESULT SetData(const float iRadiusOfCircle      ,
                              const int   iNbOfCircle   ,
                              char      * iColorOfCircle   ,
                              float     * iSagOfCircle) = 0 ;

      virtual HRESULT GetData(float  & oRadiusOfCircle     ,
                              int    & oNbOfCircle     ,
                              char  ** oColorOfCircle   ,
                              float ** oSagOfCircle) = 0 ;
 

};
#endif
