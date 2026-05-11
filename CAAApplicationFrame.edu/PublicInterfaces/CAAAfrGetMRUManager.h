#ifndef CAAAfrGetMRUManager_H
#define CAAAfrGetMRUManager_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//
//===========================================================================
#include "IUnknown.h"  // for IID 

#include "CAAAfrCustCommandHdrModel.h"  
     
   // iInterfaceIdentifier 
   //    The identifier of the interface which is queryied on the implementation. 
   // oInterfacePointer 
   //    The address where the returned pointer to the interface is located.
HRESULT ExportedByCAAAfrCustCommandHdrModel
        CAAAfrGetMRUManager(const IID & iInterfaceIdentifier,
							void     ** oInterfacePointer) ;

#endif
