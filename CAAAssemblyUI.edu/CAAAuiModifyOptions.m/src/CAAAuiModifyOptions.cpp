/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 2004
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Modify the options of Assembly Design workbench.
//
// Type            : Batch program
// Inputs          : -
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Opening a CATIA session                              (1)
//                   o Searching for the setting controller 
//                     for Assembly Design General options                  (2)
//                   o Modifying general options                            (3)
//                   o Searching for the setting controller 
//                     for Assembly Design Constraints options              (4)
//                   o Modifying constraints options                        (5)
//                   o ending the session                                   (6)
//
// Return codes :
//
//  02 - Creation of session failed  
//  03 - Access to the 'general' setting controller failed
//  04 - Modifying several options failed
//  05 - Access to the 'constraints' setting controller failed
//  06 - Modifying constraints options failed
//  07 - Deleting the session failed
//
//
// use: CAAAuiModifyOptions
//
//============================================================================================

// System Framework
//#include "CATBaseUnknown.h"
//#include "CATUnicodeString.h" 
//#include "CATLISTV_CATBaseUnknown.h"
#include "CATSettingInfo.h"
#include "CATString.h"

// ObjectModelerBase Framework
//#include "CATDocumentServices.h"   // to open and close document
#include "CATSession.h"
#include "CATSessionServices.h"    // to open and close session
//#include "CATIDocRoots.h"          // to identify the root of a document
//#include "CATDocument.h"           // to work with documents
 
// CATAssemblyInterfaces Framework
#include "CATAsmGeneralSettingServices.h"
#include "CATIAsmGeneralSettingAtt.h"
#include "CATAsmConstraintSettingServices.h"
#include "CATIAsmConstraintSettingAtt.h"

// ProductStructure Framework
//#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{
  /* --------------------------------------------------------- */
  /*  1. Open the CATIA session                                */
  /* --------------------------------------------------------- */

  printf("1 - opening a Session\n");
  CATSession * pSession = NULL;
  HRESULT rc = ::Create_Session("CAA2_Sample_Session", pSession );
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 2;
  }
  printf("     -> done\n");
  
  /* --------------------------------------------------------- */
  /*  2. Search for the setting controller (Assembly/General)  */
  /* --------------------------------------------------------- */

  printf("2 - searching \'General\' setting controller\n");

  CATIAsmGeneralSettingAtt * piGnrlSettingAtt = NULL;
  rc = GetCATAsmGeneralSettingCtrl( IID_CATIAsmGeneralSettingAtt, (void **) & piGnrlSettingAtt );
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 3;
  }
  printf("     -> done\n");

  /*-------------------------------------------------------------*/
  /*  3. Modify options (Assembly/General)                       */
  /*-------------------------------------------------------------*/      
  
  printf("3 - modifying \'General\' options\n");

  // Update options
  CATIAsmGeneralSettingAtt::UpdateMode mode = CATIAsmGeneralSettingAtt::ManualUpdate;
  HRESULT rc1 = piGnrlSettingAtt->GetAutoUpdateMode( mode );
  printf("  Update mode = %d (0: manual - 1: automatic)\n", (int) mode);
  HRESULT rc2 = piGnrlSettingAtt->SetAutoUpdateMode( CATIAsmGeneralSettingAtt::AutomaticUpdate );
  rc = piGnrlSettingAtt->SetAutoUpdateModeLock( TRUE );
  if ( FAILED(rc) )
  {
    printf("  SetAutoUpdateModeLock( TRUE ) failed");
    printf(": as you aren\'t in administrator mode this is normal\n");
  }

  // implicit switch to design mode option
  CATSettingInfo info;
  HRESULT rc3 = piGnrlSettingAtt->GetAutoSwitchToDesignModeInfo( & info );
  CATString * origin = NULL;
  if ( SUCCEEDED( info.GetOrigineValue( origin ) ) && NULL != origin )
  {
    printf("  Autoswitch option origin : %s\n", origin->CastToCharPtr() );
    delete origin;
    origin = NULL;
  }

  // Move Fix Together options
  CATIAsmGeneralSettingAtt::ExtendMoveToFixT fixTMode = CATIAsmGeneralSettingAtt::NeverExtendMove;
  HRESULT rc4 = piGnrlSettingAtt->GetMoveWithFixTExtendMode( fixTMode );
  printf("  Move Fix Together option = %d (0: never - 1: ask - 2: always)\n", (int) fixTMode);
  HRESULT rc5 = piGnrlSettingAtt->SetMoveWithFixTExtendMode( CATIAsmGeneralSettingAtt::AskIfExtendMove );

  // cleaning unnecessary data
  piGnrlSettingAtt->Release();
  piGnrlSettingAtt = NULL;

  if ( FAILED(rc1) || FAILED(rc2) || FAILED(rc3) || FAILED(rc4) || FAILED(rc5) ) 
  {
    printf("     -> failed\n");
    return 4;
  }
  printf("     -> done\n");

  /* ------------------------------------------------------------- */
  // 4 - Search for the setting controller (Assembly/Constraints)  */
  /* ------------------------------------------------------------- */

  printf("4 - searching \'Constraints\' setting controller\n");
  CATIAsmConstraintSettingAtt * piCstSettingAtt = NULL;
  rc = GetCATAsmConstraintSettingCtrl( IID_CATIAsmConstraintSettingAtt, (void **) & piCstSettingAtt );
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 5;
  }
  printf("     -> done\n");

  /*-------------------------------------------------------------*/
  /*  5. Modify options (Assembly/Constraints)                */
  /*-------------------------------------------------------------*/      
  
  printf("5 - modifying \'Constraints\' options\n");

  // Paste component mode
  CATIAsmConstraintSettingAtt::PasteComponentMode pasteMode = CATIAsmConstraintSettingAtt::WithoutCsts;
  rc1 = piCstSettingAtt->GetPasteComponentMode( pasteMode );
  printf("  Paste component mode = %d\n", (int) pasteMode);
  rc2 = piCstSettingAtt->SetPasteComponentMode( CATIAsmConstraintSettingAtt::WithCstOnCut );

  // Constraint creation mode
  rc = piCstSettingAtt->SetConstraintCreationModeLock( TRUE );
  if ( FAILED(rc) )
  {
    printf("  SetConstraintCreationModeLock( TRUE ) failed");
    printf(": as you aren\'t in administrator mode this is normal\n");
  }

  // quick constraint options
  CATSettingInfo info2;
  rc3 = piCstSettingAtt->GetQuickConstraintModeInfo( & info2 );
  if ( SUCCEEDED( info2.GetOrigineValue( origin ) ) && NULL != origin )
  {
    printf("  Autoswitch option origin : %s\n", origin->CastToCharPtr() );
    delete origin;
    origin = NULL;
  }

  char ** typesList = NULL;
  int size = 0;
  rc4 = piCstSettingAtt->GetQuickConstraintOrderedList( typesList, size );
  rc5 = E_FAIL;
  if ( SUCCEEDED( rc4 ) && NULL != typesList )
  {
    int i = 0;
    for ( ; i < size; i++ )
    {
      printf("  QuickConstraintOrderedList[%d] = %s\n", i, typesList[i] );
    }
    if ( 2 <= size )
    {
      char * tmp = typesList[0];
      typesList[0] = typesList[1];
      typesList[1] = tmp;
      rc5 = piCstSettingAtt->SetQuickConstraintOrderedList( (const char **) typesList, size );
    }
    
    // cleaning
    for ( i = 0; i < size; i++ )
    {
      delete [] typesList[i];
      typesList[i] = NULL;
    }
    delete [] typesList;
    typesList = NULL;
  }


  // cleaning unnecessary data
  piCstSettingAtt->Release();
  piCstSettingAtt = NULL;

  if ( FAILED(rc1) || FAILED(rc2) || FAILED(rc3) || FAILED(rc4) || FAILED(rc5) ) 
  {
    printf("     -> failed\n");
    return 6;
  }
  printf("     -> done\n");

  /* ----------------------------------------- */
  /*  6 - End the session                        */
  /* ----------------------------------------- */
  
  printf("6 - ending the session\n");
  rc = ::Delete_Session("CAA2_Sample_Session");
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 7;
  }
  printf("     -> done");

  // good bye
  return 0;
}  
