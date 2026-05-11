// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch showing how to create settings and manage them using a setting class.
//
//  Illustrates:
//
//     A- Creating The Setting Encapsulating class 
//
//         see: the CAASysLineSetting class
//
//     B- Using the Settings
//         0 Creation of a CAASysLineSetting class 
//         1 Read hardcoded values
//         2 Write new values 
//         3 Commit
//         4 Write new values
//         5 Read new values  
//         6 Restore (Rollback) before the commit
//         7 Read old values 
//         8 Save the repository wi
//         9 Delete the CAASysLineSetting class
//         10 Recreate one
//         11 Read some values
//         12 Delete the CAASysLineSetting class
//
//=============================================================================
//  How to launch:
//  -------------
//
//  Type:
//    CAASysLineSetting  
//  
//  The different traces of the sample appears on the standard output.
//
//  Return Code:
//     0 : OK
//     1 : KO
//
//=============================================================================

// Local Framework
#include "CAASysLineSetting.h"	  // header file of the current class

// System Framework
#include "CATSettingRepository.h" 
#include "CATUnicodeString.h"	  
#include "IUnknown.h"		 

//C++ Standard library
#include <iostream.h>

int
main()
{

  cout << "The CAASysLineSetting program begins ...."<< endl << endl;

  // ---------------------------------
  // 0 - Creation of the repository class
  // ---------------------------------
  CAASysLineSetting * Setting=NULL;
  Setting = new CAASysLineSetting;

  //-----------------------------------------------------
  // 1-a Read the harcoded default color ie RGB = {255,0,0}.
  // -----------------------------------------------------
  int Red =0, Blue =0, Green =0;

  HRESULT rc = Setting ->GetColor ( &Red, &Green, &Blue);
  if ( FAILED(rc) )
  {
     cout << "Error in Reading a color "<< endl;
     exit(1);
  }

  cout << "Hardcoded Default Values for Attribute Color " << endl;
  cout << " Red   = " << Red << endl;
  cout << " Green = " << Green << endl;
  cout << " Blue  = " << Blue << endl;
  
  //-----------------------------------------------------
  // 1-b Read the harcoded default thickness ie 1 .
  // -----------------------------------------------------
  int Thickness=0;

  rc = Setting ->GetThickness ( &Thickness);
  if ( FAILED(rc) )
  {
     cout << "Error in Reading the thickness "<< endl;
     exit(1);
  }

  cout << "Hardcoded Default Values for Attribute Thickness " << endl;
  cout << " Thickness = " << Thickness << endl;

  //-----------------------------------------------------
  // 1-c Read the harcoded default ie "Solid"
  // -----------------------------------------------------
  CATUnicodeString string;
  
  rc = Setting ->GetName( &string);
  if ( FAILED(rc) )
  {
     cout << "Error in Reading the name  "<< endl;
     exit(1);
  }
  
  cout << "Hardcoded Default Values for Attribute Name " <<endl;
  cout << " Name = " << string.ConvertToChar() << endl;
  
  //-----------------------------------------------------
  // 2- Writing new values
  // -----------------------------------------------------
  int NewRed =  127, NewBlue = 127, NewGreen= 127;
  
  // writing
  rc = Setting->SetColor( NewRed, NewGreen, NewBlue);
  if ( FAILED (rc))
  {
    cout << "Error in Writing a color "<< endl;
    exit(1);
  }

  // Verifications
  rc = Setting ->GetColor ( &Red, &Green, &Blue);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a color "<< endl;
    exit(1);
  }
  
  cout << "Current Values for Attribute Color " << endl;
  cout << " Red   = " << Red << endl;
  cout << " Green = " << Green << endl;
  cout << " Blue  = " << Blue << endl;
     
  //-----------------------------------------------------
  // 3- Commit. We also take an picture in memory of 
  //            the state of the setting
  // -----------------------------------------------------
  
  cout << " Commiting the CAASysLineSetting " << endl;
 
  rc = Setting->Commit();
  if ( FAILED (rc))
  {
     cout << "Error in the Commit operation" << endl;
     exit(1);
  }

  // -----------------
  // 4- Writing again
  // -----------------
    
  // Writing new Color 
  NewRed =  100;
  NewBlue = 100;
  NewGreen= 100;

  rc = Setting->SetColor( NewRed, NewGreen, NewBlue);
  if ( FAILED (rc))
  {
    cout << "Error in Writing a color "<< endl;
    exit(1);
  }

  // Writing a new thickness
  int NewThickness = 5;

  rc = Setting->SetThickness( NewThickness);
  if ( FAILED (rc))
  {
    cout << "Error in writing Thickness"<< endl;
    exit(1);
  }

  // --------------------
  // 5- Read new values
  // --------------------
  rc = Setting ->GetColor ( &Red, &Green, &Blue);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a color "<< endl;
    exit(1);
  }

  cout << "Current  Values for Attribute Color " << endl;
  cout << " Red   = " << Red << endl;
  cout << " Green = " << Green << endl;
  cout << " Blue  = " << Blue << endl << endl;

  rc = Setting ->GetThickness ( &Thickness);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a thickness "<< endl;
    exit(1);
  }

  cout << "Current Values for Attribute Thickness " << endl;
  cout << " Thickness = " << Thickness << endl;

  // -------------------------------------------------------
  // 6- We restore the state of the setting at the commit
  // -------------------------------------------------------
  
  cout << "Rollback " << endl;
  rc = Setting->  Rollback();
  if ( FAILED (rc))
  {
    cout << "pb in the Roolback operation" << endl;
    exit(1);
  }

  // -----------------------------------
  // 7- Read old values ( before commit)
  // ------------------------------------
  rc = Setting ->GetColor ( &Red, &Green, &Blue);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a color "<< endl;
    exit(1);
  }
  cout << "Current  Values for Attribute Color " << endl;
  cout << " Red   = " << Red << endl;
  cout << " Green = " << Green << endl;
  cout << " Blue  = " << Blue << endl;

  rc = Setting ->GetThickness ( &Thickness);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a Thickness "<< endl;
    exit(1);
  }
  cout << endl;
  cout << "Current Values for Attribute Thickness " << endl;
  cout << " Thickness = " << Thickness << endl;

  rc = Setting ->GetName( &string);
  if ( FAILED (rc))
  {
    cout << "Error in Reading name "<< endl;
    exit(1);
  }

  cout << "Current Values for Attribute Name " <<endl;
  cout << " Name = " << (const char*) string << endl;

  // -------------------------------------------------------
  // 8- Saving Operation
  // -------------------------------------------------------
  
  cout << " Saving CAASysLineSetting" <<endl;
  rc = Setting ->Save();
  if ( FAILED (rc))
  {
      cout << "Saving Problem !!!" <<endl;
      exit(1);
  }
  
  // -------------------------------------------------------
  // 9 - Delete the CAASysLineSetting class 
  // -------------------------------------------------------
  
  // The class setting is deleted
  delete Setting;
  Setting = NULL;
  
  // ----------------------------
  // 10- recreate one
  // --------------------------
  Setting = new CAASysLineSetting;

  // ---------------------------------------------------
  // 11- Read values from the unic CATSettingRepository
  //     which is not deleled by the CAASysLineSetting
  //     class destruction ( step 9)
  // ----------------------------------------------------
  rc = Setting ->GetColor ( &Red, &Green, &Blue);
  if ( FAILED (rc))
  {
    cout << "Error in Reading a color "<< endl;
    exit(1);
  }

  cout << "Current  Values for Attribute Color " << endl;
  cout << " Red   = " << Red << endl;
  cout << " Green = " << Green << endl;
  cout << " Blue  = " << Blue << endl;

  rc = Setting ->GetThickness ( &Thickness);
  if ( FAILED (rc))
  {
    cout << "Error in Reading Thickness"<< endl;
    exit(1);
  }
  cout << endl;
  cout << "Current Values for Attribute Thickness " << endl;
  cout << " Thickness = " << Thickness << endl;

  rc = Setting ->GetName( &string);
  if ( FAILED (rc))
  {
    cout << "Error in Reading name"<< endl;
    exit(1);
  }
    
  cout << "Current Values for Attribute Name " <<endl;
  cout << " Name = " << string.ConvertToChar() << endl;

  // -------------------------------------------------------
  // 12- Delete the CAASysLineSetting class 
  // -------------------------------------------------------
  delete Setting;
  Setting = NULL ;

  cout << "The CAASysLineSetting program is finished ...."<< endl << endl;
  return 0;
  
}
