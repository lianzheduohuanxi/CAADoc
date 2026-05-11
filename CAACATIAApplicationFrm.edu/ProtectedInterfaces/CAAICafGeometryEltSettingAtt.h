#ifndef CAAICafGeometryEltSettingAtt_H
#define CAAICafGeometryEltSettingAtt_H

// COPYRIGHT DASSAULT SYSTEMES 2001


// System framework
#include "IUnknown.h"   // To derive From

class CATString;
class CATSettingInfo ;

// Global Unique IDentifier defined in .cpp 
#include "CAACafCtrlToolsOptions.h"  
extern ExportedByCAACafCtrlToolsOptions IID IID_CAAICafGeometryEltSettingAtt;

/**
* Interface to acceed to the CAACafGeometryEltSetting setting file.
*/
class ExportedByCAACafCtrlToolsOptions CAAICafGeometryEltSettingAtt : public IUnknown
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
	* Returns the visibility of the identifier.
	* <br>
	* @param oIdVisibility 
	*  This string can take the following values:
	* <dl>
	*     <dt><tt>IdHide</tt>
	*     <dt><tt>IdShow</tt>
	*     <dt><tt>IdPreSelectShow</tt>
	* </dl> 
	* 
	*/
    virtual  HRESULT   GetIdentifierVisibility(CATString & oIdVisibility)        = 0;

	/**
	* Sets the visibility of the identifier.
	* <br>
	* @param iIdVisibility 
	*  If This string is
	* <dl>
	*     <dt><tt>IdHide</tt>
	*     <dt><tt>IdShow</tt>
	*     <dt><tt>IdPreSelectShow</tt>
	* </dl> 
	* the returned value is S_OK otherwise it is E_FAIL
	*/
    virtual  HRESULT   SetIdentifierVisibility(const CATString & iIdVisibility)  = 0;

    virtual  HRESULT   GetInfoIdentifierVisibility(CATSettingInfo * oInfo)  = 0;

    /**
	* Retrieves the maximun count of point to discretize a curve.
	* <br>
	* @param oMaxPoint 
	* This value  ranges from 2 to 100.
	*/
	virtual  HRESULT   GetMaxPointCurve(int & oMaxPoint)        = 0;

    /**
	* Sets the maximun count of point to discretize a curve.
	* <br>
	* @param iMaxPoint 
	* If this value must range from 2 to 100, the returned value is S_OK 
	* otherwise it is E_FAIL
	*/
    virtual  HRESULT   SetMaxPointCurve(const int iMaxPoint)  = 0;

    virtual  HRESULT   GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * iNbInfo)  = 0;

	/**
	* Returns the visibility of the implicite points.
	* <br>
	* @param oImplPointVisibility 
	*  This string can take the following values:
	* <dl>
	*     <dt><tt>ImplPointShow</tt>
	*     <dt><tt>ImplPointHide</tt>
	* </dl> 
	*/
	virtual  HRESULT   GetImplPointVisibility(CATString & oImplPointVisibility)        = 0;

	/**
	* Sets the visibility of the implicite points.
	* <br>
	* @param iImplPointVisibility 
	*  If This string is
	* <dl>
	*     <dt><tt>ImplPointShow</tt>
	*     <dt><tt>ImplPointHide</tt>
	* </dl> 
	* the returned value is S_OK otherwise it is E_FAIL
	*/
    virtual  HRESULT   SetImplPointVisibility(const CATString & iImplPointVisibility)  = 0;
    
    virtual  HRESULT   GetInfoImplPointVisibility(CATSettingInfo * oInfo)  = 0;

};
#endif

