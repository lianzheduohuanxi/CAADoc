// COPYRIGHT DASSAULT SYSTEMES 2009-2010
//
// *****************************************************************
//
//   Identification :
//   ---------------
//
//      RESPONSIBLE : Jean-Luc MEDIONI
//      FUNCTION    : PVR
//      USE         : CATIA & ENOVIA
//
// *****************************************************************
//
//   Description :
//   ------------
//
//    Provide one implementation of late type CATUExitPVRCommands to validate
//    CATIUExitPVRCommands usage in PVR commands and utility
//
// *****************************************************************
//
//   Remarks :
//   ---------
//
//
// ****************************************************************
//
//   Story :
//   -------
//
//   Revision 1.0  Sept  2009   (ITW) Initial Revision
//
/**
  * @fullreview  ITW     08:12:10 : new file added
  * @quickreview ITW     09:01:05 : Correction and new implementation for UE
  * @quickreview PPN     10:05:21 : minor chg (traces)
  * @quickreview JLM     10:07:13 : Code review
  * @quickreview JLM     10:08:03 : restore PRC doc test in AfterPRCOpenFromPVR
  */
//
// ****************************************************************

#include  "CATUExitPVRCommand.h"   

// --- List of referenced classes
// --- * System header that need to be referenced

#include <stdlib.h>
#include <stdio.h>
#include "CATStdIO.h"

// --- * User Exit to be implemented

#include  "CATIUExitPVRCommands.h" 

// --- Other classes referenced 
// --- * System framework

#include "CATDocument.h"
#include "CATUnicodeString.h"

//-----------------------------------------------------------------------------
// Define this class has a code Extension
//-----------------------------------------------------------------------------

CATImplementClass( CATUExitPVRCommand , CodeExtension , CATBaseUnknown , CATUExitPVRCommands ) ;  

//  ---------------------------------------------- 
//  Tie  the  implementation  to  its  interface  
//  ---------------------------------------------- 

#include  "TIE_CATIUExitPVRCommands.h"  
TIE_CATIUExitPVRCommands(CATUExitPVRCommand);  

//----------------------------------------------------------------------  
// Constructor 
//----------------------------------------------------------------------

CATUExitPVRCommand::CATUExitPVRCommand()
{  
}  

//----------------------------------------------------------------------  
// Destructors 
//----------------------------------------------------------------------
CATUExitPVRCommand::~CATUExitPVRCommand()  
{  
}  

//----------------------------------------------------------------------
// --- * User Exit called after opening a PRC from PVR specication.
//----------------------------------------------------------------------
HRESULT CATUExitPVRCommand::AfterPRCOpenFromPVR( CATDocument * ixPVRDoc , CATDocument * ixPRCDoc )
{
   HRESULT            nReturnCode = S_OK ;
   CATUnicodeString   cNamePRC           ;
   CATUnicodeString   cNamePVR           ;

   fprintf( stdout , "CATUExitPVRCommand::AfterPRCOpenFromPVR()\n" ) ;

   // --- Validate inputs: PVR Document

   if( ixPVRDoc )
   {
      cNamePVR = ixPVRDoc->displayName() ;
      fprintf( stdout , "    . PVR name is <%s> \n" , cNamePVR.ConvertToChar() ) ;
   }
   else
   {
      //--- Invalid PVR DOC
      fprintf( stdout , "    . No PVR document defined. \n" ) ;
      nReturnCode = E_INVALIDARG ;
   }

   //--- 1-0 Validate i/p PRC Document
   if( ixPRCDoc )
   {
      cNamePRC = ixPRCDoc->displayName() ;
      fprintf( stdout , "    . PRC name is <%s> \n" , cNamePRC.ConvertToChar() ) ;
   }
   else
   {
      //--- Invalid PRC DOC
      fprintf( stdout , "    . No PRC document defined. \n" ) ;
      nReturnCode = E_INVALIDARG ;
   }

   fprintf( stdout , " CATIUExitPVRCommands AfterPRCOpenFromPVR : PVR : %s :  PRC : %s \n ", cNamePVR.ConvertToChar() , cNamePRC.ConvertToChar() ) ;
   fflush( stdout ) ;

   return nReturnCode ;
}

//----------------------------------------------------------------------
// --- * Enables to update an attribute value on PVR document.
//----------------------------------------------------------------------
HRESULT CATUExitPVRCommand::UpdateAttributeOnPvrSynchro( CATDocument      * ixPVRDoc
                                                       , int                inIsyncNeeded
                                                       , CATUnicodeString & ocAttrId 
                                                       , CATUnicodeString & ocAttrVal )
{
   HRESULT            nReturnCode = S_OK ;
   CATUnicodeString   cName              ;

   fprintf( stdout , "CATUExitPVRCommand::UpdateAttributeOnPvrSynchro()\n" ) ;

   // --- Validates that a PVR Document is defined

   if( ixPVRDoc )
   {
      // --- Get PVR Name

      cName = ixPVRDoc->displayName() ;
      fprintf( stdout , "    . PVR name is <%s>\n" , cName.ConvertToChar() ) ;

      //--- If PVR sync is needed then set output attribute (e.g. V_description) and its value ("PVR to be updated") 

      if( inIsyncNeeded )
      {
         fprintf( stdout , "    . PVR need to be synchronized.\n" ) ;

         ocAttrId  = "V_description"     ;
         ocAttrVal = "PVR to be updated" ;

         nReturnCode = S_OK ;
      }
      else
      {
         fprintf( stdout , "    . PVR is up to date.\n" ) ;
         nReturnCode = S_FALSE ;
      }
   }
   else
   {
      fprintf( stdout , "    . No PVR document defined.\n" ) ;
      nReturnCode = E_INVALIDARG ;
   }

   fflush( stdout ) ;

   return nReturnCode ;
}

//----------------------------------------------------------------------
// --- * Enables to define default name to be used in Product View Result (PVR) document creation command.
//----------------------------------------------------------------------

HRESULT CATUExitPVRCommand::GetDefaultNamesForPVRCreation( int                                ilNewFrom
                                                          , int                                ilFilteredPVR
                                                          , const CATListValCATUnicodeString & iAttributeIdLst
                                                          , const CATListValCATUnicodeString & iAttributeValueLst
                                                          , CATUnicodeString                 & iocPVRName
                                                          , CATUnicodeString                 & iocPVSName           )
{
   HRESULT nReturnCode = S_OK ;

   fprintf( stdout , "CATUExitPVRCommand::GetDefaultNamesForPVRCreation()\n" ) ;

   //--- Case of PVR to be created using existing PVR.

   if( ilNewFrom )
   {
      fprintf( stdout , "  * Case where PVR will be initialized using an existing one.\n" ) ;
   }

   //--- Case of PVR to be created on filtered assembly.

   if( ilFilteredPVR )
   {
      fprintf( stdout , "  * Case of PVR with an expand capture associated.\n" ) ;
   }

   //--- TraceOut current PVR/PVS name 

   fprintf( stdout , "  * PVR current default name is <%s>.\n" , iocPVRName.ConvertToChar() ) ;
   fprintf( stdout , "  * PVS current default name is <%s>.\n" , iocPVSName.ConvertToChar() ) ;

   int nbAtt = iAttributeIdLst.Size() ;
   if( nbAtt != iAttributeValueLst.Size() )
   {
      nReturnCode = E_FAIL ;
      fprintf( stdout , "  * Attribute name and attribute value list are inconsistent (%d / %d) .\n"
             , iAttributeIdLst.Size() , iAttributeValueLst.Size() ) ;
   }   
   else
   {
      fprintf( stdout , "  * %d attribute defined.\n" , nbAtt ) ;
      for( int nAtt=1 ; nAtt<=nbAtt ; nAtt++ )
      {
         fprintf( stdout , "     %0.3d: %s = <%s>.\n" , nAtt , iAttributeIdLst[nAtt].ConvertToChar() , iAttributeValueLst[nAtt].ConvertToChar() ) ;
      }   
   }

   fflush( stdout ) ;

   return nReturnCode ;
}
