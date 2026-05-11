#ifndef CAASysLineSetting_H
#define CAASysLineSetting_H

// COPYRIGHT DASSAULT SYSTEMES 2000	 

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  This use case is intended to show you how to create settings to store 
//  persistent object properties, and how to encapsulate their 
//  management in a class, the current one, that makes your clients independant
//  from the actual setting repository management. This is the best way for 
//  enabling client applications to access you setting repository.
//
//=============================================================================
//  Abstract of the class:
//  ----------------------
//  This class manages line object properties : thickness, color ans linestyle. 
//
//=============================================================================

// System Framework
#include "IUnknown.h"		  // for HRESULT 

class CATUnicodeString;
class CATSettingRepository;

class CAASysLineSetting
{
public:

  // Constructor
  CAASysLineSetting();
  virtual ~CAASysLineSetting();
  

  // Initialization  of the object with the default  hardcoded values or with
  // the read ones.
  HRESULT Init();
  
  //Setting the Attribute Thickness
  HRESULT SetThickness ( int iThickness);


  // Retrieving the  Value of the Attribute Name
  HRESULT GetThickness (int *oThickness );
  

  // Setting the Attribute Color
  HRESULT SetColor ( int iRed, int iGreen, int iBlue);
  

  // Retrieving the  Value of the Attribute Name
   HRESULT GetColor (int *oRed, int *oGreen, int *oBlue);
  

  // Setting the  Value of the Attribute Name
  HRESULT SetName ( CATUnicodeString* iName);
  

  // Retrieving the  Value of the Attribute Name
  HRESULT  GetName (CATUnicodeString *oName);
  

  // Saving the setting (to file)
  HRESULT Save();
  

  // Committing the setting (Saving in memory)
  HRESULT  Commit();

  // Restoring the setting from the last commited state
  HRESULT  Rollback();


private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysLineSetting( const CAASysLineSetting& iCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAASysLineSetting & operator = ( const CAASysLineSetting& iCopy);

private:

  // static Pointer on the underlying CATSettingRepository (there is only
  // one instance of the CATSettingRepository class named CAASysLineSetting )
  static CATSettingRepository *_pSetting;

    
};

#endif

