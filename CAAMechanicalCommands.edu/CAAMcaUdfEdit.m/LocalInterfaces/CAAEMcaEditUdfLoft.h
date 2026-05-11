#ifndef CAAEMcaEditUdfLoft_h
#define CAAEMcaEditUdfLoft_h

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//  
//  Associate with a user feature reference a customized dialog box 
//  to edit an instance of this reference. The CATIEdit interface is
//  implemented on a late type, given by the type of the user feature
//  reference.
//  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAUdfLoft component implementing the CATIEdit 
//  interface. 
//  CAAUdfLoft is the type of the user feature reference, CAAUserFeatureSample,
//  created by the CAAMcaUdfCreation use case. 
//  The command to edit the user feature, instance of the CAAUserFeatureSample,
//  is defined in the CAAMcaUdfEdit.m module
//
//=========================================================================== 
//  How to launch ?
//  -------------
//
//  In the InstallRootDirectory/CAAMechanicalCommands.edu/InputData you find the following
//  files:
//    - 1) CAAUdfLoft.CATPart document which contains the  CAAUserFeatureSample 
//       user feature reference without a type
//    - 2) CAAUdfModelWithInstances.CATPart document which contains two 
//       instances of the CAAUserFeatureSample user feature reference without the 
//       CAAUdfLoft type  
//
//    - 3) CAAUdfLoftWithType.CATPart document which contains the  CAAUserFeatureSample 
//       user feature reference with the CAAUdfLoft type
//    - 4) CAAUdfModelWithTypeInst.CATPart document which contains one 
//       instance of the CAAUserFeatureSample user feature reference with the 
//       CAAUdfLoft type
//
//    scenarios:
//    
//    - in Cnext, open the  CAAUdfModelWithTypeInst.CATPart document, 
//      double click on the CAAUserFeatureSampleToEdit feature : the customized 
//      dialog box appears
//    - in Cnext, open the  CAAUdfModelWithInstances.CATPart document, 
//      double click on the CAAUserFeatureSample.1 or on the
//      The Loft with Point2 and Point3 features: the default edit dialog
//      box appears
//
// where InstallRootDirectory is the directory where the CAA CD-ROM is installed.
//===========================================================================

// ApplicationFrame framework
#include "CATExtIEdit.h" // Needed to derive from CATExtIEdit

class CAAEMcaEditUdfLoft : public CATExtIEdit
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEMcaEditUdfLoft();
    virtual ~CAAEMcaEditUdfLoft();

    // Activate
    // --------
    // Creates a state command to modify a feature whose the type is CAAUdfLoft 
    // Caution: This interface is implemented on a late type,
    // so to retrieve the object to modify, it is not this, but use
    // the iPath argument.
    virtual CATCommand  * Activate(CATPathElement * iPath);

 private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMcaEditUdfLoft(const CAAEMcaEditUdfLoft &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMcaEditUdfLoft & operator = (const CAAEMcaEditUdfLoft &iObjectToCopy);

};
#endif
