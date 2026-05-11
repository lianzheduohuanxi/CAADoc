#ifndef GetCAACafGeometryViewSettingCtrl_H
#define GetCAACafGeometryViewSettingCtrl_H
//
// COPYRIGHT DASSAULT SYSTEMES 2001
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  Global function to retrieve the controler which manages the
//  CAACafGeometryViewSetting.CATSetting file.
//
//  This global function can be exposed to provide to an application
//  the setting values. 
//
//===========================================================================
#include "IUnknown.h"  // for IID 
#include "CAACafCtrlToolsOptions.h" // To export the function

HRESULT ExportedByCAACafCtrlToolsOptions 
        
        // iInterfaceIdentifier 
		//    The identifier of the interface which is queryied on the implementation.
		// oInterfacePointer 
		//    The address where the returned pointer to the interface is located.
        GetCAACafGeometryViewSettingCtrl(const IID & iInterfaceIdentifier,
										void     ** oInterfacePointer) ;

#endif
