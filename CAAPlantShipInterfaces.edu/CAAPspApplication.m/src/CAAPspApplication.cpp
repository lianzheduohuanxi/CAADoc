// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspApplication - This sample illustrates how to use the following
// interfaces to query a domain and application:  CATIPspApplication,
// CATIPspDomainEnvironment, CATIPspClass, CATIPspObject, CATIPspResource.
//
#include <iostream.h>

// This framework
#include "CAAPspApplication.h"

// CATPlantShipInterfaces
#include "CATIPspApplication.h"
#include "CATIPspClass.h"
#include "CATIPspDomainEnvironment.h"
#include "CATIPspObject.h"
#include "CATIPspResource.h"
#include "CATIPspPhysical.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATIContainer.h"

// System
#include "CATICStringList.h"
#include "CATBooleanDef.h"
#include "CATString.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspApplication::CAAPspApplication() 
{
  cout << "CAAPspApplication::CAAPspApplication()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspApplication::~CAAPspApplication()
{
  cout << "CAAPspApplication::~CAAPspApplication()" << endl;
}

//=============================================================================
//  DoSample for Piping domain and application
//=============================================================================
int CAAPspApplication::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspApplication::DoSample                    ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspApplication       *piApplication = NULL;
  CATIPspDomainEnvironment *piDomainEnv = NULL;
  CATIPspClass             *piClass = NULL;
  CATIPspObject            *piObject = NULL;
  CATIPspResource          *piResource = NULL;
  CATIContainer            *piRootCont = NULL;

  CATString sDomain;
  CATUnicodeString DomainCont;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);
 
    piRootCont = GetRootContainer();
    if (NULL == piRootCont)
    {
       cout << "CAAPspApplication:"
            << "Cannot find root container"
            << endl;
       return E_FAIL;
    }

    CATObject *piObj = new CATObject("CATPiping");
    if ( NULL != piObj )
    {
       //  Find CATIPspApplication interface 
       rc = piObj->QueryInterface(IID_CATIPspApplication,(void **)&piApplication);
       //  Find CATIPspClass interface
       rc = piObj->QueryInterface(IID_CATIPspClass,(void **)&piClass);
       //  Find CATIPspResource interface
       rc = piObj->QueryInterface(IID_CATIPspResource,(void **)&piResource);

       piObj->Release();
       piObj = NULL;
    }
            
    //-------------------------------------------------------------------------
    //  CATIPspApplication methods
    //-------------------------------------------------------------------------
    if ( NULL != piApplication )
    {
       //----------------------------------------------------------------------
       //  Activate the Piping application
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piApplication->Initialization(piRootCont)) )
          cout << "Piping application initialized" << endl;

       //----------------------------------------------------------------------
       //  List domains supported by this application
       //----------------------------------------------------------------------
       CATICStringList *pListDomains = NULL;
       if ( SUCCEEDED(piApplication->ListDomains(&pListDomains)) &&
             NULL != pListDomains )
       {
          unsigned int size = 0; 
          if ( SUCCEEDED(pListDomains->Count(&size)) )
          {
             int NumOfDomains = (int)size;
             cout << "Number of domains for this application: " << NumOfDomains << endl;
             for (int j = 0; j < NumOfDomains; j++ )
             {
                char *DomainName = NULL;
                pListDomains->Item(j,&DomainName);
                if ( DomainName )
                {
                   cout << DomainName << endl;
                   delete [] DomainName; DomainName = NULL;
                }
             }
          }
          pListDomains->Release();  pListDomains = NULL;
       }

       //----------------------------------------------------------------------
       //  Is application a 3D application?
       //----------------------------------------------------------------------
       CATBoolean Is3D;
       rc = piApplication->Is3DApplication(&Is3D);
       if ( Is3D )
          cout << "Piping is a 3D application" << endl;

       //----------------------------------------------------------------------
       //  Get the application main domain name
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piApplication->GetApplicationDomain(sDomain)) )
          cout << "Application's main domain: " << sDomain << endl;

       piApplication->Release();
       piApplication = NULL;
    }

    //-------------------------------------------------------------------------
    //  Find CATIPspDomainEnvironment interface 
    //-------------------------------------------------------------------------
    if ( sDomain.GetLengthInChar() > 0 )
    {
       CATObject *piDomainObj = new CATObject(sDomain);
       if ( NULL != piDomainObj )
       {
          rc = piDomainObj->QueryInterface(IID_CATIPspDomainEnvironment,(void **)&piDomainEnv);
          piDomainObj->Release();
          piDomainObj = NULL;
       }
    }

    //-------------------------------------------------------------------------
    //  CATIPspDomainEnvironment methods
    //-------------------------------------------------------------------------
    if ( NULL != piDomainEnv )
    {
       //-------------------------------------------------------------------
       //  Get the domain feature catalog name
       //-------------------------------------------------------------------
       CATUnicodeString FeatFileName;
       if ( SUCCEEDED(piDomainEnv->GetFeatFile(FeatFileName)) )
          cout << "Domain feature catalog: "
               << FeatFileName.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the domain user defined feature catalog name
       //-------------------------------------------------------------------
       CATUnicodeString UserFeatFile;
       if ( SUCCEEDED(piDomainEnv->GetUserFeatFile(UserFeatFile)) )
          cout << "Domain user defined feature catalog: "
               << UserFeatFile.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the 3D application name associated to this domain
       //-------------------------------------------------------------------
       CATString ApplName;
       if ( SUCCEEDED(piDomainEnv->Get3DApplication(ApplName)) )
          cout << "3D application name: " << ApplName << endl;

       piDomainEnv->Release();
       piDomainEnv = NULL;
    }

    //-------------------------------------------------------------------------
    //  Get a physical object in the document and find its 
    //  CATIPspObject interface 
    //-------------------------------------------------------------------------
    CATIPspPhysical *piPhysical = GetAPhysicalObject();
    if ( NULL != piPhysical )
    {
       rc = piPhysical->QueryInterface(IID_CATIPspObject,(void**)&piObject);
       piPhysical->Release();
       piPhysical = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspObject methods
    //------------------------------------------------------------------------- 
    if ( NULL != piObject )
    {
       CATString sApplName;
       CATString sDomainName;
       piObject->GetApplicationName(sApplName);
       piObject->GetDomainName(sDomainName);

       piObject->Release();
       piObject = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspClass methods
    //------------------------------------------------------------------------- 
    if ( NULL != piClass )
    {
       CATICStringList *pList = NULL;
       unsigned int ListSize = 0; 

       if ( SUCCEEDED(piClass->ListStartUpPhysicalParts(&pList)) 
            && NULL != pList )
       {
          pList->Count(&ListSize);
          cout << "Number of physical part classes found: " << (int)ListSize << endl;
          pList->Release();  pList = NULL; ListSize = 0;
       }

       if ( SUCCEEDED(piClass->ListStartUpFunctionParts(&pList))
            && NULL != pList )
       {
          pList->Count(&ListSize);
          cout << "Number of function part classes found: " << (int)ListSize << endl;
          pList->Release();  pList = NULL; ListSize = 0;
       }

       if ( SUCCEEDED(piClass->ListStartUpConnectors(&pList))
            && NULL != pList )
       {
          pList->Count(&ListSize);
          cout << "Number of connector classes found: " << (int)ListSize << endl;
          pList->Release();  pList = NULL; ListSize = 0;
       }

       if ( SUCCEEDED(piClass->ListStartUpConnections(&pList))
            && NULL != pList )
       {
          pList->Count(&ListSize);
          cout << "Number of connection classes found: " << (int)ListSize << endl;
          pList->Release();  pList = NULL; ListSize = 0;
       }

       if ( SUCCEEDED(piClass->ListStartUpLogicalLines(&pList))
            && NULL != pList )
       {
          pList->Count(&ListSize);
          cout << "Number of logical line classes found: " << (int)ListSize << endl;
          pList->Release();  pList = NULL; ListSize = 0;
       }

       piClass->Release();
       piClass = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspResource methods
    //------------------------------------------------------------------------- 
    if ( NULL != piResource )
    {
       CATUnicodeString Blank = "";
       CATUnicodeString ResourceName;
       CATUnicodeString Path, Directory, FileName, Flag;
       CATUnicodeString DomainName = sDomain.CastToCharPtr();

       //-------------------------------------------------------------------
       //  Get the line catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetLineCatalogPath(Blank,Path,ResourceName)) )
       {
          cout << "Line catalog resource name: " << ResourceName.ConvertToChar() << endl;
          //----------------------------------------------------------------
          //  Get a resource's path given a resource name
          //----------------------------------------------------------------
          if ( SUCCEEDED(piResource->GetResourcePath(ResourceName,Path)) )
             cout << "Line catalog path: " << Path.ConvertToChar() << endl;
       }

       //-------------------------------------------------------------------
       //  Get the zone catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetZoneCatalogPath(Blank,Path,ResourceName)) )
          cout << "Zone catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the ID schema directory
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetIDSchemaDir(DomainName,Directory,ResourceName)) )
          cout << "ID Schema directory: " << Directory.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the user dictionary file name
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetUserDictFileName(DomainName,FileName,ResourceName)) )
          cout << "User dictionary file name: " << FileName.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the ID Sequence number directory
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetIDSequenceNumberDir(Directory,ResourceName)) )
          cout << "ID Sequence number directory: " << Directory.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the discrete values directory
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetDiscreteValuesDir(Directory,ResourceName)) )
          cout << "Discrete values directory: " << Directory.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the standards catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetStandardsCatalogPath(Path,ResourceName)) )
          cout << "Standards catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the design rules catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetDesignRulesCatalogPath(Path,ResourceName)) )
          cout << "Design rules catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the Specification catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetSpecificationCatalogPath(Path,ResourceName)) )
          cout << "Specification catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the Insulation Specification catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetInsulationSpecCatalogPath(Path,ResourceName)) )
          cout << "Insulation Specification catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the part catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetPartCatalogPath(Path,ResourceName)) )
          cout << "Part catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the On/Off sheet catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetOffsheetCatalogPath(Path,ResourceName)) )
          cout << "On/Off sheet catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the resolved part catalog directory path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetResolvedPartCatalogDir(Directory,ResourceName)) )
          cout << "Resolved part catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the graphic representation filename
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetGraphicRepFileName(FileName,ResourceName)) )
          cout << "Graphic representation filename: " << FileName.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the file containing a list of valid classes for the
       //  active discipline
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetDisciplineClassesFileName(FileName,ResourceName)) )
          cout << "Discipline classes filename: " << FileName.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the connector attribute filename.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetCntrAttrFileName(FileName,ResourceName)) )
          cout << "Connector attribute filename: " << FileName.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the report definition directory.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetReportDefinitionDir(Directory,ResourceName)) )
          cout << "Report definition directory: " << Directory.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the annotation catalog path
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetAnnotationCatalogPath(Path,ResourceName)) )
          cout << "Annotation catalog path: " << Path.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the graphic names directory used in a schematics application.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetGraphicNamesDir(Directory,ResourceName)) )
          cout << "Graphic names directory: " << Directory.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the flag that indicates if 3D application placement
       //  is schematic driven.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetSchematicDrivenFlag(Flag,ResourceName)) )
       {
          cout << "Schematic driven flag resource name: " << ResourceName.ConvertToChar() << endl;
          //----------------------------------------------------------------
          //  Get a resource's value given a resource name
          //----------------------------------------------------------------
          if ( SUCCEEDED(piResource->GetResourceValue(ResourceName,Flag)) )
             cout << "Schematic driven flag: " << Flag.ConvertToChar() << endl;
       }

       //-------------------------------------------------------------------
       //  Get the flag that indicates if 3D application placement
       //  is function driven.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetFunctionDrivenFlag(Flag)) )
          cout << "Function driven flag: " << Flag.ConvertToChar() << endl;

       //-------------------------------------------------------------------
       //  Get the growth factor value.
       //-------------------------------------------------------------------
       double Value;
       if ( SUCCEEDED(piResource->GetGrowthFactorValue(Value)) )
          cout << "Growth factor value: " << Value << endl;

       //-------------------------------------------------------------------
       //  Get the cable clearance value.
       //-------------------------------------------------------------------
       if ( SUCCEEDED(piResource->GetCableClearanceValue(Value)) )
          cout << "Cable clearance value: " << Value << endl;

       piResource->Release();
       piResource = NULL;
    }
  } // end CATTry


  CATCatch (CATError, error)
  {
    if ( NULL != piApplication ) { piApplication->Release(); piApplication = NULL; }
    if ( NULL != piDomainEnv ) { piDomainEnv->Release(); piDomainEnv = NULL; }
    if ( NULL != piClass ) { piClass->Release(); piClass = NULL; }
    if ( NULL != piObject ) { piObject->Release(); piObject = NULL; }
    if ( NULL != piResource ) { piResource->Release(); piResource = NULL; }
    cout << "CAAPspApplication::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
