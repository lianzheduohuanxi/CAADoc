#ifndef CAAECafSettingManagmentForGeometryView_H
#define CAAECafSettingManagmentForGeometryView_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of  CAACafGeometryViewSettingCtrl to implement the 
//  CATIIniSettingManagment
//
//===========================================================================

// InteractiveInterfaces Framework
#include "CATIIniSettingManagment.h" // Implemented interface
#include "CATEIniSettingManagment.h" // To derive from 

class CAAECafSettingManagmentForGeometryView: public CATEIniSettingManagment
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    // Gives the name of the setting file to the CATEIniSettingManagment class
    //
    CAAECafSettingManagmentForGeometryView();

    virtual ~CAAECafSettingManagmentForGeometryView();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafSettingManagmentForGeometryView(const CAAECafSettingManagmentForGeometryView &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafSettingManagmentForGeometryView & operator = (const CAAECafSettingManagmentForGeometryView &iObjectToCopy);

};
#endif
