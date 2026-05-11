// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspProperties - This sample illustrates how to use the following
// interfaces to access a part's attributes and ID data:  
// CATIPspAttribute, CATIPspID
//
#include <iostream.h>

// This framework
#include "CAAPspProperties.h"

// CATPlantShipInterfaces
#include "CATIPspAttribute.h"
#include "CATIPspID.h"
#include "CATIPspPhysical.h"

//ObjectModelerBase
#include "CATDocument.h"

// LiteralFeature
#include "CATICkeParm.h"

// System
#include "CATListOfCATUnicodeString.h"
#include "CATListOfDouble.h" 
#include "CATListOfInt.h" 

//=============================================================================
//  Constructor
//=============================================================================
CAAPspProperties::CAAPspProperties() 
{
  cout << "CAAPspProperties::CAAPspProperties()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspProperties::~CAAPspProperties()
{
  cout << "CAAPspProperties::~CAAPspProperties()" << endl;
}

//=============================================================================
//  List and query attributes and ID
//=============================================================================
int CAAPspProperties::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspProperties::DoSample                     ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical        *piPhysical = NULL;
  CATIPspAttribute       *piAttribute = NULL;
  CATIPspID              *piID = NULL;
  
  CATListValCATUnicodeString *pAttrNameList = NULL;
  CATListValCATUnicodeString *pDomainNameList = NULL;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a physical object from the input document
    piPhysical = GetAPhysicalObject();

    if ( NULL != piPhysical )
    {
      //  Find CATIPspAttribute interface
      rc = piPhysical->QueryInterface(IID_CATIPspAttribute,(void**)&piAttribute);
      if( SUCCEEDED( rc) )
      {
        cout << "Succeeded in getting CATIPspAttribute interface pointer" << endl;
        //  Find CATIPspID interface
        rc = piPhysical->QueryInterface(IID_CATIPspID,(void**)&piID);

        if( SUCCEEDED( rc) )
        {
          cout << "Succeeded in getting CATIPspID interface pointer" << endl;
        }
      }
      piPhysical->Release();
      piPhysical = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspAttribute methods
    //-------------------------------------------------------------------------
    if ( NULL != piAttribute )
    {
      int NumOfDomains = 0;

      //----------------------------------------------------------------------
      //  List Domain Names
      //----------------------------------------------------------------------               
      if( SUCCEEDED( piAttribute->ListDomainNames ( &pDomainNameList)) && 
        ( NULL != pDomainNameList ))      
      {
        cout << "Succeeded in getting a list of domains for a part" << endl;
              
        delete pDomainNameList;  
        pDomainNameList = NULL;          
      }

      //----------------------------------------------------------------------
      // List Attributes for CATPIP domain
      //----------------------------------------------------------------------

      if( SUCCEEDED( piAttribute->ListAttributes ( "CATPIP", &pAttrNameList ))
         && ( NULL !=  pAttrNameList) )      
      {
        cout << "Succeeded in getting a list of attributes" << endl;

        //
        // Querying attribute values and discrete values
        //
        QueryAttributeValues( piAttribute, pAttrNameList );                                                 
      }
      if( NULL !=  pAttrNameList )
      {                                       
        delete pAttrNameList;  
        pAttrNameList = NULL;
      }                                  
             
      piAttribute->Release();
      piAttribute = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspID methods
    //-------------------------------------------------------------------------
    if ( NULL != piID )
    {

      //----------------------------------------------------------------------
      //  Generate ID without generating a new sequence number
      //---------------------------------------------------------------------- 
      CATUnicodeString oGeneratedID;
      if( SUCCEEDED( piID->GenIDNoGenSeqNum ( oGeneratedID ) ))
        cout << "ID generated without a sequence number: " 
             << oGeneratedID.ConvertToChar() << endl;

      //----------------------------------------------------------------------
      //  Generate and store ID without a sequence number
      //---------------------------------------------------------------------- 
      if( SUCCEEDED( piID->GenAndPutIDNoGenSeqNum ( oGeneratedID ) ))
        cout << "Succeeded in generating and storing ID without a sequence number" << endl;

      //----------------------------------------------------------------------
      //  Generate and store ID with a sequence number
      //---------------------------------------------------------------------- 
      if( SUCCEEDED( piID->GenAndPutID ( oGeneratedID ) ))
        cout << "Succeeded in generating and storing ID with a sequence number" << endl;

      //----------------------------------------------------------------------
      // GetID
      //---------------------------------------------------------------------- 
      if( SUCCEEDED( piID->GetID ( oGeneratedID ) ))
        cout << "Succeeded in getting ID: " 
             << oGeneratedID.ConvertToChar() << endl;

      //----------------------------------------------------------------------
      // Check if the ID is generated as per the schema
      //----------------------------------------------------------------------
      CATBoolean bIsGeneratedID = FALSE;
      if( SUCCEEDED( piID->IsIDGenerated ( bIsGeneratedID ) ))
        cout << "Succeeded in checking: IsIDGenerated" << endl;

      //----------------------------------------------------------------------
      // GetLocalID
      //---------------------------------------------------------------------- 
      CATUnicodeString oLocalID;
      if( SUCCEEDED( piID->GetLocalID ( oLocalID ) ))
        cout << "Succeeded in getting Local ID" << endl;

      piID->Release();
      piID = NULL;
    }

  } // end CATTry

  CATCatch (CATError, error)
  {
    
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piID ) { piID->Release(); piID = NULL; }
    if ( NULL != piAttribute ) { piAttribute->Release(); piAttribute = NULL; }
    if( NULL != pDomainNameList )
    {          
      delete pDomainNameList;  
      pDomainNameList = NULL;          
    }
    if( NULL != pAttrNameList )
    {          
      delete pAttrNameList;  
      pAttrNameList = NULL;          
    }
    
    cout << "CAAPspProperties::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}

// 
// Private function : Query Discrete type, type of attribute and discrete values
//
int CAAPspProperties::QueryAttributeValues (CATIPspAttribute* piAttribute, CATListValCATUnicodeString *pAttrNameList )
{
  int RetVal = 0;

  if ( NULL == piAttribute )
  {
    cout << "Pointer pAttr is NULL" << endl;
    return 1;
  }
  if( NULL ==  pAttrNameList )
  {
    cout << "pAttrNameList is NULL" << endl;
    return 1;
  }

  int numAttr =  pAttrNameList->Size();
  cout << "Number of attributes is " << numAttr << endl;
  if( numAttr == 0) return 0;

  CATICkeParm* pCkeParm = NULL;
  
  CATTry 
  {
                     
    for( int iAttr =1; iAttr <= numAttr; iAttr++ )
    {

      CATUnicodeString uPropertyName = (*pAttrNameList)[iAttr];
      //
      // Getting type of the attribute
      //
      CATAttrKind eAttrKind;

      if( SUCCEEDED(piAttribute->GetType ( uPropertyName , eAttrKind )) )
        cout << "Succeeded in getting attribute type" << endl;

      //
      // Get Literal interface 
      //
      if( SUCCEEDED(piAttribute->GetLiteral ( uPropertyName, &pCkeParm )) )
        cout << "Succeeded in getting literal" << endl;

      if( NULL != pCkeParm )
      {
        pCkeParm->Release();
        pCkeParm = NULL;
      }
      //
      // Checking if attribute is discrete or not
      // 
      CATBoolean  bDiscrete = FALSE;
      int         iDiscreteType = 0;
      if( FAILED(piAttribute->IsDiscrete ( uPropertyName, bDiscrete, iDiscreteType )) )
        cout << "Failed to get a discrete type status. Attribute is not discrete" << endl;
      else
      {
        //
        // Getting Discrete Values  ( Normal discrete attribute)
        //
        if (  bDiscrete &&  (iDiscreteType == 1) )              
        {                              
          if( eAttrKind == tk_string )
          {                               
            
            CATListOfCATUnicodeString DiscreteValuesList;
            if ( SUCCEEDED(piAttribute->ListStringDiscreteValues( uPropertyName, DiscreteValuesList)) )
            {
              cout << "Succeeded in getting string discrete values." << endl;
            }            
          }
          else if ( eAttrKind == tk_integer)
          {            
            CATListOfInt iListofInt;
            
            if( SUCCEEDED(piAttribute->ListIntegerDiscreteValues( uPropertyName, iListofInt)) )
            {                
              cout << "Succeeded in getting integer discrete values." << endl;
            }
            
          }
          else if (eAttrKind == tk_double )
          {
            CATListOfDouble dListofDouble;
            if( SUCCEEDED(piAttribute->ListDoubleDiscreteValues( uPropertyName, dListofDouble)) )
            {
              cout << "Succeeded in getting double discrete values." << endl;
            }            
          }
        }

        if (  bDiscrete &&  (iDiscreteType == 2) )
        {
          cout << "Discrete type is " <<  iDiscreteType << endl;
          
          CATListOfCATUnicodeString ShortDiscreteValuesList;
          CATListOfCATUnicodeString DiscreteValuesList;

          if ( FAILED(piAttribute->ListDiscreteValues( uPropertyName, ShortDiscreteValuesList, DiscreteValuesList)) )
          {
              cout << "FAILED to get encoded discrete values" <<endl;
          }
          
        }
      }

      //
      // Check if attribute is derived from logical line
      //
      CATBoolean Derived = FALSE;
      if( SUCCEEDED(piAttribute->IsDerived ( uPropertyName, &Derived )) &&
          Derived )
      {
        cout << uPropertyName.ConvertToChar() << " is derived" << endl;
        // Reset derived attribute
        if( SUCCEEDED(piAttribute->ResetDerivedAttr ( uPropertyName)) )
          cout << "Succeeded in resetting derived attribute" << endl;
      }

    } //end for index =iAttr
  } // end CATTry

  CATCatch (CATError, error)
  {
    if( NULL != pCkeParm )
    {
      pCkeParm->Release();
      pCkeParm = NULL;
    }
        
    cout << "CAAPspProperties::QueryAttributeValues *** CATRethrow" << endl;
        
    CATRethrow;
  } 
  CATEndTry;
  
  return RetVal;
                 
}

