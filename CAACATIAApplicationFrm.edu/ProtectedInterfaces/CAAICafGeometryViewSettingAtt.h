#ifndef CAAICafGeometryViewSettingAtt_H
#define CAAICafGeometryViewSettingAtt_H

// COPYRIGHT DASSAULT SYSTEMES 2001


// System framework
#include "IUnknown.h"   // To derive From

class CATString ;
class CATSettingInfo ;

// Global Unique IDentifier defined in .cpp 
#include "CAACafCtrlToolsOptions.h"  
extern ExportedByCAACafCtrlToolsOptions IID IID_CAAICafGeometryViewSettingAtt;

/**
* Interface to acceed to the CAACafGeometryViewSetting setting file.
*/
class ExportedByCAACafCtrlToolsOptions CAAICafGeometryViewSettingAtt : public IUnknown
{

  public :

   /**
    * Enables the initialization of the setting file.
    * The goal of this method it meanly to read all the setting's options. The reading is not
    * important, the important things is that in the ReadSetting methods you give the 
    * "Hard Coded" values for each option. If you do not have admin values, this hard coded 
    * values are mandatory for the reset operation. 
    * This method must be called once when the CATSettingRepository associated
    * with the settings file is created. The best place is just after the creation
    * of the controller, it means in the GetSettingController method of the controller
    * component. 
    * This method must not be exposed.
    */
	virtual HRESULT Initialize() = 0;

	/**
	* Returns the mode to represent the 3D.
	* <br>
	* @param oIdMode 
	*  This string can take the following values:
	* <dl>
	*     <dt><tt>IdPlane</tt>
	*     <dt><tt>IdAxis</tt>
	*     <dt><tt>IdWall</tt>
	* </dl> 
	* 
	*/
    virtual  HRESULT   Get3DRepresentationMode(CATString & oIdMode)        = 0;

	/**
	* Sets the mode to represent the 3D.
	* <br>
	* @param iIdMode 
	*  If This string is
	* <dl>
	*     <dt><tt>IdPlane</tt>
	*     <dt><tt>IdAxis</tt>
	*     <dt><tt>IdWall</tt>
	* </dl> 
	* the returned value is S_OK otherwise it is E_FAIL
	*/
    virtual  HRESULT   Set3DRepresentationMode(const CATString & iIdMode)  = 0;

    virtual  HRESULT   GetInfo3DRepresentationMode(CATSettingInfo * oInfo)  = 0;


};
#endif

