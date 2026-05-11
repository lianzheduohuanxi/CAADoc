#ifndef CAAECafSettingManagmentForGeometryElt_H
#define CAAECafSettingManagmentForGeometryElt_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of  CAACafGeometryEltSettingCtrl to implement the 
//  CATIIniSettingManagment. 
//
//===========================================================================

// InteractiveInterfaces Framework
#include "CATIIniSettingManagment.h" // Implemented interface
#include "CATEIniSettingManagment.h" // To derive from 

class CAAECafSettingManagmentForGeometryElt: public CATEIniSettingManagment
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    //Gives the name of the settting file to the CATEIniSettingManagment class
    CAAECafSettingManagmentForGeometryElt();

    virtual ~CAAECafSettingManagmentForGeometryElt();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafSettingManagmentForGeometryElt(const CAAECafSettingManagmentForGeometryElt &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAECafSettingManagmentForGeometryElt & operator = (const CAAECafSettingManagmentForGeometryElt &iObjectToCopy);

};
#endif
