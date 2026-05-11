
/**
 * @quickReview ZGG 04:09:28
 * @quickReview TPC 03:12:10
 * @quickReview TPC 03:12:10
 * @quickReview TPC 03:11:28
 * @quickReview SVN 02:05:29
 * @quickreview TPC 01:08:20
 */

// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//  Abstract of the sample:
//  ----------------------
//   
//  Batch program
// 
//    Insert a toleranced V4 model in a CATProduct.
//    Browse tolerances, identify their type and read informations.
//    Dump collected informations to a text file.
//
//  Illustrates:
//
//    Using TPS (Technological Product Specifications) interfaces to browse a
//    toleranced model.
//
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAATpiBrowseTolerances <FullPath1\InModel.model> <FullPath2\OutText.txt>
//
//  Input:
//    a model (e.g. CAATpiBrowseInModel1.model)
//
//  Outputs:
//    Return code is 0 if program worked ok, >0 otherwise.
//    A dump text file containing tolerancing informations. Dump file is same
//    that CAATpiBrowseOutText1.txt which is provided as reference.
//
//  Materials for this tutorial (input model and reference dump file) are 
//  located in CAATPSInterfaces.edu/CNext/resources.
//
//=============================================================================
//  Main Methods:
//  ------------
//
//  main
//  CAATpiDumpCATITPSSemanticValidity
//  CAATpiDumpCATITPS
//  CAATpiDumpCATITPSToleranceZone
//  CAATpiDumpCATITPSDimensionLimits
//
//  The methods CAATpiDump<InterfaceName>, illustrate for the considered 
//  interface, how to use it to access tolerancing informations and dump them 
//  to a stream.
//
//=============================================================================

//---------------------------------------------------------------------- System
#include "CATUnicodeString.h" // To manipulate international strings
#include "CATCmpGuid.h"       // To compare IID. 
#include "CATBSTR.h"

//----------------------------------------------------------------- Mathematics
#include "CATMath.h"          // For absolute value on float: CATFabs

//----------------------------------------------------------- ObjectModelerBase
#include "CATSessionServices.h"  // To create and delete object modeler session
#include "CATDocumentServices.h" // To create and remove a product document
#include "CATDocument.h"         // To manipulate document
#include "CATIDocRoots.h"        // To retrieve roots of document
#include "CATSession.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATListOfCATBaseUnknown.h" // Document's roots returned type

//------------------------------------------------------------ ProductStructure
#include "CATIProduct.h" // To add and manipulate products

//-------------------------------------------------- ProductStructureInterfaces
#include "CATIAProduct.h" // To add a V4 model in product

//----------------------------------------------------------- MechModInterfaces
#include "CATITTRS.h"        // Link between tolerances and CAD geometry
#include "CATITTRSList.h"    // TTRS list manipulation interface
#include "CATMmrTTRSClass.h" // TTRS Class enum definition
 
//------------------------------------------------------------ CATTPSInterfaces
#include "CATITPSDocument.h"          // Entry point for tolerancing
#include "CATITPSList.h"              // List of TPS object, Sets and Tolerances
#include "CATITPSComponent.h"         // TPS object manipulated in TPS list.
#include "CATITPSSet.h"               // Tolerancins Set that contains tolerances
#include "CATITPSSemanticValidity.h"  // Access Type and SuperType
#include "CATITPS.h"                  // Retrieve link with surface
#include "CATITPSToleranceZone.h"
#include "CATITPSDimensionLimits.h"
#include "CATITPSMaterialCondition.h"
#include "CATITPSEnvelopCondition.h"
#include "CATITPSAssociatedRefFrame.h"
#include "CATITPSReferenceFrame.h"
#include "CATITPSCompositeTolerance.h"
#include "CATITPSProjectedToleranceZone.h"
#include "CATTPSStatus.h"
#include "CATTPSSingleLimit.h"

// Interfaces used only by their IID that defines SuperType and Type of TPS.

#include "CATITPSForm.h"               // Typing interface
#include "CATITPSStraightness.h"       // Typing interface
#include "CATITPSFlatness.h"           // Typing interface
#include "CATITPSCircularity.h"        // Typing interface
#include "CATITPSCylindricity.h"       // Typing interface
#include "CATITPSProfileOfAnyLine.h"   // Typing interface
#include "CATITPSProfileOfASurface.h"  // Typing interface
#include "CATITPSPatternTruePos.h"     // Typing interface

#include "CATITPSOrientation.h"        // Typing interface
#include "CATITPSParallelism.h"        // Typing interface
#include "CATITPSPerpendicularity.h"   // Typing interface
#include "CATITPSAngularity.h"         // Typing interface

#include "CATITPSPosition.h"           // Typing interface
#include "CATITPSTruePosition.h"       // Typing interface
#include "CATITPSConcentricity.h"      // Typing interface
#include "CATITPSSymmetry.h"           // Typing interface
#include "CATITPSPositionOfAnyLine.h"  // Typing interface
#include "CATITPSPositionOfASurface.h" // Typing interface

#include "CATITPSRunOut.h"             // Typing interface
#include "CATITPSTotalRunOut.h"        // Typing interface
#include "CATITPSCircularRunOut.h"     // Typing interface

#include "CATITPSDimension.h"          // Typing interface
#include "CATITPSLinearDimension.h"    // Typing interface
#include "CATITPSAngularDimension.h"   // Typing interface
#include "CATITPSChamferDimension.h"   // Typing interface

#include "CATITPSDatum.h"              // Typing interface
#include "CATITPSDatumSimple.h"        // Typing interface
#include "CATITPSDatumTarget.h"        // Typing interface
#include "CATITPSDatumSystem.h"        // Typing interface

#include "CATITPSNonSemantic.h"        // Typing interface
#include "CATITPSText.h"               // Typing interface
#include "CATITPSFlagNote.h"           // Typing interface

//------------------------------------------------------ Functions Declarations

// Dumps informations accessible with CATITPSSemanticValidity interface.
// Theses informations are SuperType, Type and behavioral interfaces that can 
// be taken on a tolerance.
// ipiTole: input tolerance.
// ipStream: dump stream.

void CAATpiDumpCATITPSSemanticValidity (CATITPSComponent * ipiTole,
                                        FILE * ipStream);

// Dumps information accessible with CATITPS interface
// This information is surface class where tolerance is applyed.
// ipiTole: input tolerance.
// ipStream: dump stream.

void CAATpiDumpCATITPS (CATITPSComponent * ipiTole,
                        FILE * ipStream);

// Dumps information accessible with CATITPSToleranceZone interface.
// This information is tolerance zone value, dumped only  if tolerance adhere
// to CATITPSToleranceZone.
// ipiTole: input tolerance.
// ipStream: dump stream.

void CAATpiDumpCATITPSToleranceZone (CATITPSComponent * ipiTole,
                                     FILE * ipStream);

// Dumps informations accessible with CATITPSDimensionLimits interface.
// Theses informations are dimensions limits values, dumped only 
// if tolerance adhere to CATITPSDimensionLimits.
// ipiTole: input tolerance.
// ipStream: dump stream.

void CAATpiDumpCATITPSDimensionLimits (CATITPSComponent * ipiTole,
                                       FILE * ipStream);

// Corrects some OS differences in displaying floats.
// opString: generated output string.
// ipFormat: required format, same that the printf C standard style.
// iFl: input float to be formatted.

void CAATpiSprintf (char * opString, char * ipFormat, float iFl);


//-----------------------------------------------------------------------------
int main (int iArgc,        // Argument count (3)
          char * iapArgv[]) // iapArgv[1]: path of toleranced model to browse
                            // iapArgv[2]: path of output dump text file
{
  // Check argument count
  if( iArgc != 3 ) return (1);

  // Open a session
  CATSession * pSession = NULL;
  Create_Session("SampleSession", pSession);

  //---------------------------------------------------------------------------
  // Insert a V4 model in a product document
  //---------------------------------------------------------------------------

  // Create a new product document
  CATDocument* pDoc = NULL;
  CATUnicodeString DocType("CATProduct");
  CATDocumentServices::New (DocType, pDoc);

  // Retrieve root product
  CATIDocRoots_var spDocRootOnDoc (pDoc);
  if ( spDocRootOnDoc == NULL_var ) return (2);

  CATListValCATBaseUnknown_var* RootsList = spDocRootOnDoc->GiveDocRoots();
  if ( RootsList == NULL )
  {
    return (3);
  }
  else
  {
    if ( RootsList->Size() < 1 )
    {
      delete RootsList;
      RootsList = NULL;
      return (3);
    }
  }

  CATIProduct_var spProductOnDocRoot ((*RootsList)[1]);
  delete RootsList;
  RootsList = NULL;

  if (spProductOnDocRoot == NULL_var) return (4);

  // Add a receipt Product
  CATUnicodeString Name("TolerancedModel");
  CATIProduct_var spChildProduct = spProductOnDocRoot -> AddProduct(Name);

  // Transform command line argument in a path with correct string type
  CATUnicodeString ModelPath(iapArgv[1]);
  CATBSTR ModelPathAsBSTR;
  ModelPath.ConvertToBSTR(&ModelPathAsBSTR);

  // Add model in receipt Product
  CATIAProduct_var spChildProductJnl( spChildProduct );

  if ( spChildProductJnl == NULL_var ) return (5);

  int ier = spChildProductJnl -> AddMasterShapeRepresentation(ModelPathAsBSTR);
  if ( ier != 0 ) return (6);

  //---------------------------------------------------------------------------
  // Browse and dump tolerances to text file
  //---------------------------------------------------------------------------

  // Open stream for output text file
  FILE * pStream = fopen(iapArgv[2], "w");
  if ( pStream == NULL ) return (7);

  // Write copyright in stream
  fprintf(pStream, "%s\n","COPYRIGHT DASSAULT SYSTEMES 2000");

  HRESULT rc = E_FAIL;

  // Retrieve TPS entry point interface on document
  CATITPSDocument * piTPSDoc = NULL;
  if ( pDoc )
  {
    rc = pDoc -> QueryInterface (IID_CATITPSDocument, (void**) &piTPSDoc);
  }
  if ( FAILED(rc) ) return (8);

  // Retrieve list of tolerancing sets in document as a CATITPSList
  CATITPSList * piSetList = NULL;
  rc = piTPSDoc -> GetSets(&piSetList);
  piTPSDoc -> Release();
  piTPSDoc = NULL;

  if ( SUCCEEDED(rc) )
  {
    // Retrieve set count
    unsigned int SetCount = 0;
    piSetList -> Count(&SetCount);

    // Iterate on list of set and for each set analyze tolerances
    CATITPSSet* piSet = NULL;
    for( unsigned int SetIdx = 0; SetIdx < SetCount; SetIdx++ )
    {
      // Retrieve set in the list
      CATITPSComponent* piCompOnSet = NULL;
      rc = piSetList->Item (SetIdx, &piCompOnSet);
      if ( SUCCEEDED(rc) )
      {
        // Analyze sets of piTPSDoc
        rc = piCompOnSet ->QueryInterface(IID_CATITPSSet, (void **)&piSet);
        if ( SUCCEEDED(rc) )
        {
          // Retrieve tolerances that belong to set as a CATITPSList
          CATITPSList* piToleList = NULL;
          rc = piSet -> GetTPSs(&piToleList);
          if ( SUCCEEDED(rc) )
          {
            // Retrieve tolerances count in set
            unsigned int ToleCount = 0;
            piToleList  -> Count(&ToleCount);
            
            // Analyze tolerances of set
            for ( unsigned int ToleIdx = 0; ToleIdx < ToleCount; ToleIdx ++ )
            {
              // Get ToleIdx tolerance in set
              CATITPSComponent * piCompOnTole = NULL;
              rc = piToleList -> Item (ToleIdx, &piCompOnTole);
              if ( SUCCEEDED(rc) )
              {
                
                fprintf (pStream,"%s%s%i%s%i%s\n",
                                 "------------------------ ", 
                                 " Set.", SetIdx,".Tolerance.",ToleIdx,
                                 " -----------------------");
                
                // Dump tolerance informations
                CAATpiDumpCATITPSSemanticValidity (piCompOnTole, pStream);
                CAATpiDumpCATITPS                 (piCompOnTole, pStream);
                CAATpiDumpCATITPSToleranceZone    (piCompOnTole, pStream);
                CAATpiDumpCATITPSDimensionLimits  (piCompOnTole, pStream);
                
                piCompOnTole -> Release();
              }
            }
            piToleList -> Release();
          }
          piSet -> Release();
        }
        piCompOnSet -> Release();
      }
    }
    piSetList -> Release();
  }
  // Close output dump file
  fclose(pStream);

  // Close document
  CATDocumentServices::Remove(*pDoc);

  // Close the session
  Delete_Session("SampleSession");

  return (0);
};


//-----------------------------------------------------------------------------
// CAATpiDumpCATITPSSemanticValidity
//-----------------------------------------------------------------------------
void CAATpiDumpCATITPSSemanticValidity (CATITPSComponent * ipiTole,
                                        FILE * ipStream)
{

  if ( !ipiTole )
  {
    return;
  }

  // Retrieve CATITPSSemanticValidity interface on input tolerance.
  CATITPSSemanticValidity * piSemantic = NULL;
  HRESULT rc = ipiTole -> QueryInterface (IID_CATITPSSemanticValidity,
                                          (void **)& piSemantic);
  if ( SUCCEEDED(rc) )
  {
    //-------------------------------------------------------------------------
    // Identify SuperType and Type
    //-------------------------------------------------------------------------
  
    // Retrieve tolerance SuperType as an IID
    IID * pSuperTypeAsIID = NULL;
    piSemantic -> GetSuperType (&pSuperTypeAsIID);
  
    // Retrieve tolerance Type as an IID
    IID * pTypeAsIID = NULL;
    piSemantic -> GetType (&pTypeAsIID);
  
    // Transform SuperType and Type IID in strings
    CATUnicodeString Type ("Unknown");
    CATUnicodeString SuperType ("Unknown");
  
    // Form tolerances
    // If SuperType IID is the same that IID of CATITPSForm interface then this
    // tolerance belongs to the Form Super Type.
    if ( CATCmpGuid(&IID_CATITPSForm, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Form";
  
      // If Type IID is the same that IID of CATITPSStraightness interface then
      // this tolerance is a Straightness tolerance.
      if ( CATCmpGuid(&IID_CATITPSStraightness, pTypeAsIID) == TRUE )
        Type = "Straightness";
      else if ( CATCmpGuid(&IID_CATITPSFlatness, pTypeAsIID) == TRUE )
        Type = "Flatness";
      else if ( CATCmpGuid(&IID_CATITPSCircularity, pTypeAsIID) == TRUE )
        Type = "Circularity";
      else if ( CATCmpGuid(&IID_CATITPSCylindricity, pTypeAsIID) == TRUE )
        Type = "Cylindricity";
      else if ( CATCmpGuid(&IID_CATITPSProfileOfAnyLine, pTypeAsIID) == TRUE )
        Type = "Profile tolerance of any line";
      else if ( CATCmpGuid(&IID_CATITPSProfileOfASurface, pTypeAsIID) == TRUE )
        Type = "Profile tolerance of any surface";
      else if ( CATCmpGuid(&IID_CATITPSPatternTruePos, pTypeAsIID) == TRUE )
        Type = "Pattern localization";
    }
    // Orientation tolerances
    else if ( CATCmpGuid(&IID_CATITPSOrientation, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Orientation";
  
      if ( CATCmpGuid(&IID_CATITPSParallelism, pTypeAsIID) == TRUE )
        Type = "Parallelism";
      else if ( CATCmpGuid(&IID_CATITPSPerpendicularity, pTypeAsIID) == TRUE )
        Type = "Perpendicularity";
      else if ( CATCmpGuid(&IID_CATITPSAngularity, pTypeAsIID) == TRUE )
        Type = "Angularity";
    }
    // Position tolerances
    else if ( CATCmpGuid(&IID_CATITPSPosition, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Position";
  
      if ( CATCmpGuid(&IID_CATITPSTruePosition, pTypeAsIID) == TRUE )
        Type = "Positional";
      else if ( CATCmpGuid(&IID_CATITPSConcentricity, pTypeAsIID) == TRUE )
        Type = "Concentricity";
      else if ( CATCmpGuid(&IID_CATITPSSymmetry, pTypeAsIID) == TRUE )
        Type = "Symmetry";
      else if ( CATCmpGuid(&IID_CATITPSPositionOfAnyLine, pTypeAsIID) == TRUE )
        Type = "Position linear profile";
      else if ( CATCmpGuid(&IID_CATITPSPositionOfASurface, pTypeAsIID) == TRUE)
        Type = "Position surfacic profile";
    }
    // RunOut tolerances
    else if ( CATCmpGuid(&IID_CATITPSRunOut, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Run-out";
  
      if ( CATCmpGuid(&IID_CATITPSTotalRunOut, pTypeAsIID) == TRUE )
        Type = "Total run-out";
      else if ( CATCmpGuid(&IID_CATITPSCircularRunOut, pTypeAsIID) == TRUE )
        Type = "Circular run-out";
    }
    // Dimension tolerances
    else if ( CATCmpGuid(&IID_CATITPSDimension, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Size";

      if ( CATCmpGuid(&IID_CATITPSLinearDimension, pTypeAsIID) == TRUE )
        Type = "Linear";
      else if ( CATCmpGuid(&IID_CATITPSAngularDimension, pTypeAsIID) == TRUE )
        Type = "Angular";
      else if ( CATCmpGuid(&IID_CATITPSChamferDimension, pTypeAsIID) == TRUE )
        Type = "Chamfer Dim";
    }
    // Datum tolerances
    else if ( CATCmpGuid(&IID_CATITPSDatum, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Datum";

      if ( CATCmpGuid(&IID_CATITPSDatumSimple, pTypeAsIID) == TRUE )
       Type = "Simple datum";
      else if ( CATCmpGuid(&IID_CATITPSDatumSystem, pTypeAsIID) == TRUE )
        Type = "Complex datum";
    }
    // NonSemantic tolerances
    else if ( CATCmpGuid(&IID_CATITPSNonSemantic, pSuperTypeAsIID) == TRUE )
    {
      SuperType = "Non Semantic";

      if ( CATCmpGuid(&IID_CATITPSText, pTypeAsIID) == TRUE )
        Type = "Text";
      else if ( CATCmpGuid(&IID_CATITPSFlagNote, pTypeAsIID) == TRUE )
        Type = "Flag Note";
    }
    // Dump Type and Super Type in output stream
    fprintf(ipStream, "%-32s%s\n", "  SuperType:", SuperType.ConvertToChar());
    fprintf(ipStream, "%-32s%s\n", "  Type:",      Type.ConvertToChar());

    //-------------------------------------------------------------------------
    // Access list of behavioral interfaces implemented on tolerance
    //-------------------------------------------------------------------------

    // Retrieve list of behavioral interfaces that must be analyzed for a 
    // correct and plenty semantic understanding of this tolerance.
    // List is returned as a pointer on an array of pointers (IID adresses)
    int    SemanticItfCount = 0;
    IID ** ppSemanticItfList = NULL;

    rc = piSemantic -> GetUnderstandingSemanticsItf (&SemanticItfCount,
                                                     &ppSemanticItfList);

    // First and second IID in list (idx 0,1) are SuperType and Type of 
    // tolerance. Here start to iterate directly on index 2.
    // The list of semantic interfaces can contains interface IID that are not 
    // published yet. In order to be protected against misunderstanding, the 
    // client code must assume that, if one or some semantic interfaces are
    // unknown, all the interfaces and thus the whole tolerance must be 
    // ignored.
  
    char aInterfaceName [48];
  
    for (int ItfIdx = 2; ItfIdx < SemanticItfCount; ItfIdx ++ )
    {
      // Initialize interface name
      sprintf(aInterfaceName, "%s", "Unknown"); 

      if ( ItfIdx == 2 )
      {
        fprintf(ipStream, "%-32s", "  Semantic behavioral itfs:");
      }
      else
      {
        fprintf(ipStream, "%-32s", " ");
      }

      // Compare with CATITPSToleranceZone 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx],
                      &IID_CATITPSToleranceZone) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSToleranceZone");
      }

      // Compare with CATITPSDimensionLimits 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSDimensionLimits) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSDimensionLimits");
      }

      // Compare with CATITPSMaterialCondition 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSMaterialCondition) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSMaterialCondition");
      }

      // Compare with CATITPSAssociatedRefFrame 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSAssociatedRefFrame) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSAssociatedRefFrame");
      }

      // Compare with CATITPSReferenceFrame 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSReferenceFrame) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSReferenceFrame");
      }

      // Compare with CATITPSEnvelopCondition 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSEnvelopCondition) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSEnvelopCondition");
      }

      // Compare with CATITPSCompositeTolerance 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSCompositeTolerance) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSCompositeTolerance");
      }

      // Compare with CATITPSProjectedToleranceZone 
      if ( CATCmpGuid(ppSemanticItfList[ItfIdx], 
                      &IID_CATITPSProjectedToleranceZone) == TRUE )
      {
        sprintf(aInterfaceName, "%s", "CATITPSProjectedToleranceZone");
      }

      fprintf(ipStream, "%s\n", aInterfaceName);
    }
    delete [] ppSemanticItfList;

    //-------------------------------------------------------------------------
    // Auto Diagnostic on semantic validity of tolerance
    //-------------------------------------------------------------------------

    // Retrieve check diagnostic for this tolerance
    wchar_t * pDiagnostic = NULL;
    CATTPSStatus Status = CATTPSStatusUnknown;
    rc = piSemantic -> Check(&pDiagnostic, &Status);
  
    if ( SUCCEEDED(rc) ) 
    { // If Status is not OK, problem with this tolerance.
      if ( Status != CATTPSStatusOK )
      {
        // if Check KO dump returned diagnostic
        CATUnicodeString Diag;
        Diag.BuildFromWChar(pDiagnostic);
        fprintf(ipStream, "%-32s%s\n",
                          "  Check Diagnostic:", Diag.ConvertToChar());
      }
      delete [] pDiagnostic;
    }
    piSemantic ->Release();
  }
}

//-----------------------------------------------------------------------------
// CAATpiDumpCATITPS
//-----------------------------------------------------------------------------
void CAATpiDumpCATITPS (CATITPSComponent * ipiTole,
                        FILE * ipStream)
{

  if ( !ipiTole )
  {
    return;
  }

  // Retrieve CATITPS interface on input tolerance
  CATITPS * piTPS = NULL;
  HRESULT rc = ipiTole -> QueryInterface (IID_CATITPS, (void **)&piTPS );
  if ( SUCCEEDED(rc) )
  {
    // Links to toleranced surfaces is retrieved as a TTRS list
    unsigned int Count = 0;
    CATITTRSList * piTTRSList = NULL;
    CATITTRS * piTTRS = NULL;
    CATMmrTTRSClass TTRSClass = CATMmrUnknownTTRSClass;
    // Type CATMmrTTRSClass is an enum that describe functional surface class.
    // It can take values such as spherical, cylindrical, planar...
    // Unknown is a default value used for initialization purpose.

    fprintf(ipStream, "%-32s", "  Link to surface:");

    rc = piTPS -> GetTTRS (&piTTRSList);

    if ( SUCCEEDED(rc) )
    {
      // Dump TTRS count
      piTTRSList -> Count (&Count);
      fprintf(ipStream, "%d%s", Count, " TTRS");

      // Iterate on TTRS list, and for each of them read 
      // and dump his surface class
      for ( unsigned int i = 0; i < Count; i++ )
      {
        // Retrieve TTRS number i in the list as a CATITTRS
        piTTRS = NULL;
        rc = piTTRSList -> Item (i, &piTTRS);
        if ( SUCCEEDED(rc) )
        {
          // Read TTRS class
          TTRSClass = CATMmrUnknownTTRSClass;
          piTTRS -> GetTTRSClass(TTRSClass);
 
          // Dump TTRS class
          fprintf(ipStream, ", ");
          switch ( TTRSClass )
          {
          case CATMmrSphericalTTRSClass:  fprintf(ipStream, "Spherical");break;
          case CATMmrCylindricalTTRSClass:fprintf(ipStream, "Cylindrical");
                                                                         break;
          case CATMmrPlanarTTRSClass:     fprintf(ipStream, "Planar");   break;
          case CATMmrPrismaticTTRSClass:  fprintf(ipStream, "Prismatic");break;
          case CATMmrRevoluteTTRSClass:   fprintf(ipStream, "Revolute"); break;
          case CATMmrComplexTTRSClass:    fprintf(ipStream, "Complex");  break;
          case CATMmrUnknownTTRSClass:    fprintf(ipStream, "UnknownKO");break;
          }
          piTTRS -> Release();
        }
      }
      piTTRSList -> Release();
    }
    fprintf(ipStream, "\n");

    piTPS ->Release();
  }
}

//-----------------------------------------------------------------------------
// CAATpiDumpCATITPSToleranceZone
//-----------------------------------------------------------------------------
void CAATpiDumpCATITPSToleranceZone (CATITPSComponent * ipiTole,
                                     FILE * ipStream)
{

  if ( !ipiTole )
  {
    return;
  }
  // Retrieve tolerance zone interface on input tolerance
  CATITPSToleranceZone * piToleZoneOnTPS = NULL;
  HRESULT rc = ipiTole -> QueryInterface (IID_CATITPSToleranceZone, 
                                          (void **)&piToleZoneOnTPS);

  // QueryInterface succeeded only if CATITPSToleranceZone is a behavioral
  // interface of tolerance
  if ( SUCCEEDED(rc) )
  {
    // Read tolerance zone value
    double ToleZoneValue = 0.0;
    rc = piToleZoneOnTPS -> GetValue (&ToleZoneValue);
    piToleZoneOnTPS ->Release();

    // Dump value to stream
    fprintf(ipStream, "%-32s", "  Tolerance zone value:");
    char aTolZoneAsString[24];
    CAATpiSprintf(aTolZoneAsString,"%.3f", (float) ToleZoneValue);
    fprintf(ipStream, "%s%s\n", aTolZoneAsString, " mm");
  }
}


//-----------------------------------------------------------------------------
// CAATpiDumpCATITPSDimensionLimits
//-----------------------------------------------------------------------------
void CAATpiDumpCATITPSDimensionLimits (CATITPSComponent * ipiTole,
                                       FILE * ipStream)
{

  if ( !ipiTole )
  {
    return;
  }

  // Retrieve dimension limits interface on input tolerance
  CATITPSDimensionLimits * piDimLimitsOnTPS = NULL;
  HRESULT rc = ipiTole -> QueryInterface (IID_CATITPSDimensionLimits,
                                          (void **)&piDimLimitsOnTPS);

  // QueryInterface succeeded only if CATITPSDimensionLimits is a behavioral
  // interface of tolerance. (Tolerance is a dimension)
  if ( SUCCEEDED(rc) )
  {
    // Try to read up and bottom limits of the dimension
    double UpLimit     = 0.0;
    double BottomLimit = 0.0;
    rc = piDimLimitsOnTPS -> GetLimits (&BottomLimit, &UpLimit);

    // HRESULT returned by GetLimits must be tested, because E_FAIL is returned
    // when, for instance, dimension is defined as "10 max". In that case, it
    // is a single limit dimension. Modifier on this dimension can be read by 
    // using GetModifier method.
    if ( SUCCEEDED(rc) )
    {
      // Dump up and bottom dimensions limits values
      char aOneLimit[24];
      CAATpiSprintf(aOneLimit,"%.3f", (float) UpLimit);
      fprintf(ipStream, "%-32s%s%s\n", "  Up limit:", aOneLimit, " mm");
      CAATpiSprintf(aOneLimit,"%.3f", (float) BottomLimit);
      fprintf(ipStream, "%-32s%s%s\n", "  Bottom limit:", aOneLimit, " mm");
    }
    else
    {
      // Read modifier on single limit dimension 
      CATTPSSingleLimit Modifier = CATTPSSLNotDefined;
      rc = piDimLimitsOnTPS -> GetModifier (&Modifier);
      fprintf(ipStream, "%-32s", "  Single Limit:");

      // Dump modifier
      switch ( Modifier )
      {
      case CATTPSSLUnsupported:
        fprintf(ipStream, "Unsupported");
        break;
      case CATTPSSLNotDefined:
        fprintf(ipStream, "Not Defined");
        break;
      case CATTPSSLMaximum:
        fprintf(ipStream, "Maximum");
        break;
      case CATTPSSLMinimum:
        fprintf(ipStream, "Minimum");
        break;
      case CATTPSSLAsInformation:
        fprintf(ipStream, "AsInformation");
        break;
      }
      fprintf(ipStream, "\n");
    }
    piDimLimitsOnTPS -> Release();
    piDimLimitsOnTPS = NULL;
  }
}

//-----------------------------------------------------------------------------
// CAATpiSprintf
//-----------------------------------------------------------------------------
// This function correct some minor OS differences in displaying float.
// With this traitment all OS generate exactly the same dump file.

void CAATpiSprintf (char * opString, char * ipFormat, float iFl)
{
  // Prevent displaying "-0.0" instead of  "0.0"
  float fl = iFl;
  if ( CATFabs(iFl) < 1.e-6 )
  {
    fl = +0.0;
  }
  sprintf (opString, ipFormat, fl);

  // Prevent displaying "0,2" instead of "0.2"
  // We have to check if no ',' has been introduced instead of a '.' character
  char * pStringStartingWithAComma = strchr(opString, ',');
  if ( pStringStartingWithAComma != NULL)
  {
    pStringStartingWithAComma[0] = '.';
  }
}

