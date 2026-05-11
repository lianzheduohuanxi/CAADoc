
// COPYRIGHT DASSAULT SYSTEMES 2000

// CAA 
#include "CAAGsiServices.h"

//ObjectModelerBase Framework
#include "CATIDescendants.h"           
#include "CATIContainer.h"             
#include "CATIAlias.h"                
#include "CATISpecObject.h"           

// MechanicalModeler Framework 
#include "CATIPrtContainer.h"         
#include "CATIPrtPart.h"               
#include "CATIBasicTool.h"               
#include "CATIGSMTool.h"               


#include "CATIMechanicalRootFactory.h" 
#include "CATIMechanicalTool.h"          
#include "CATIMmiOrderedGeometricalSet.h"          
#include "CATIMmiNonOrderedGeometricalSet.h"          
#include "CATIMfBRep.h"
#include "CATMfErrUpdate.h"           
#include "CATMmrLinearBodyServices.h"  

// LiteralFeatures Framework
#include "CATICkeParmFactory.h"       
#include "CATICkeParm.h"             

// GSMInterfaces 
#include "CATIGSMFactory.h"           
#include "CATIGSMProceduralView.h"

//Visu / Model 
#include "CATModify.h"
#include "CATDelete.h"
#include "LifeCycleObject.h"
#include "CATIModelEvents.h"

//System 
#include "CATError.h"                  
#include "CATBoolean.h"                   
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"


// =====================================
// Defines 
// =====================================
#define GS        0  
#define OGS       1 
#define HBody     2 

#define UNDER_Current  0
#define UNDER_Part     1

// =====================================
// Debug
// =====================================

// #define DEBUG_CAASERVICES    
#ifdef DEBUG_CAASERVICES 
#include "iostream.h"
#endif 



// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / GeometricalSets ==============
// ----------------------------------------------------------------------------------------------

// =========================================================================================================
// Create GeometricFeaturesSets
// =========================================================================================================
ExportedByCAAGsiServices HRESULT  
CAAGsiCreateGeometricFeatureSets (const CATIContainer_var &ispCont, const CATUnicodeString& iName, 
                                  const CATISpecObject_var & spInputParentTool , CATISpecObject_var & spSpecTool,  
                                  int & oDiag, int iTopLevel, int iType  )
{
    
    HRESULT rc = S_OK ; 
#ifdef DEBUG_CAASERVICES 
    cout  << "(CAAGsiServices) CAAGsiCreateSurfacicFeatureSet "  << endl;
#endif 
    
    oDiag = -1; 
    // Create a new GSM Tool  
    // Warning:   father of New GSMTool can be an objet or the root PartBody tool  
    
    // Phase 1: Retrieve the current Part container
    // --------------------------------------------- 
    CATIPrtContainer_var          spPartCont   = ispCont;
    CATIPrtPart_var               spPart       = spPartCont -> GetPart();
    
    
    if (NULL_var != spPart )
    {
        int Position = 0;
        // Note: iTopLevel allow to create the tools directly under the root of the graph  
        // iTopLevel = 0 : Create under current feature  
        // iTopLevel = 1 : Create directly under Part 
        
        // Phase 1: Reterieve ParentForTool ito be insert Part or another Tool 
        // --------------------------------------------- 
        
        // Reference Part 
        CATISpecObject_var spSpecPart      = spPart;
        CATISpecObject_var spParentForTool ;
        
        // Tool is about to create under the Part 
        if (iTopLevel==1 ) {
            //cout << " (CAAGsiCreateGeometricFeatureSets)Case 1"<<endl ;
            
            spParentForTool = spPart ; 
        }
        // Tool is about to create under a defined Parent Tool 
        else   if (iTopLevel==0 &&  spInputParentTool  != NULL_var ) { 
            
            CATIBasicTool_var spSpecBasicTool = spInputParentTool ;  // Check it is a tool 
            if ( NULL_var != spSpecBasicTool ) { 
                spParentForTool = spInputParentTool   ;
                // cout << " (CAAGsiCreateGeometricFeatureSets)Case 2 / Tool =" << spParentForTool->GetName() <<endl  ;
                
            } 
            else { 
                // cout << " (CAAGsiCreateGeometricFeatureSets) ERROR , input Parent for tool is not a GS, OGS or Body "<<endl; 
                oDiag =3 ; // Parent for tool is not a Valid object 
            }

        }            
        // Tool is about to create after current object in the Part 
        else if (iTopLevel==0 &&  spInputParentTool  == NULL_var ) { 
            
            // Read Current Tool
            // Note: Current Tool is 
            // either a PartBody (  Necessary: spCurrentFeat == spCurrentTool)
            // either a OpenBody (  Necessary: spCurrentFeat == spCurrentTool)
            CATIBasicTool_var spCurrentTool = spPart -> GetCurrentTool();
            
            // Read Current feature 
            // A  tool can be insert after an already defined part feature  
            CATISpecObject_var spCurrentFeat = spPart->GetCurrentFeature();
            
            // Note: Current Feature is 
            // either a PartBody, GS  or OGS 
            //    Not Necessary: spCurrentFeat == spCurrentTool 
            //    Position = 0 : The tool is created under Part 
            // either a Feature under a PartBody  
            //    The Tools is created after the current feature which position is set below
            
            spParentForTool  = spCurrentTool;
         
            if ( spCurrentFeat != spCurrentTool)  {
                // The Tool Parent will be the Current Tool
                // Read position of Current Feature in Tool
                CATIDescendants_var spRoot = spCurrentTool;
                Position = spRoot -> GetPosition( spCurrentFeat);
            }
            // cout << " (CAAGsiCreateGeometricFeatureSets)Case 3 / Tool =" << spParentForTool ->GetName() << " /Position ="<<Position<<  endl ;
            
        }
        
        // Phase 2: Check rules for creation of Tools 
        // --------------------------------------------- 
        // Toplevel ==0 
        // Need to check the tool to inseert is consistant with is Parent destination tool 
        if (iTopLevel==0) {
            
            CATIMmiNonOrderedGeometricalSet_var spNonOrderedGeomSet = spParentForTool  ; 
            CATIMmiOrderedGeometricalSet_var    spOrderedGeomSet    = spParentForTool ; 
            CATIMechanicalTool_var              spMechanicalSet     = spParentForTool ; 
            if (iType == 0 ) { 
                if ( NULL_var != spNonOrderedGeomSet ) { 
                    oDiag = 0;    // GS a inserer dans un GS ou sous un feature d'un GS 
                }
                else {
#ifdef DEBUG_CAASERVICES 
                    cout << " (CAAGsiCreateGeometricFeatureSets) ERROR , a GS  can only be inserted under another GS or directly under the part"<< endl; 
#endif 
                     oDiag =1 ; // GS que l'on veut inserer dans un Body ou OGS 
                }
            }
            else if (iType == 1 ) { 
                if ( NULL_var != spOrderedGeomSet || NULL_var !=  spMechanicalSet  ) { 
                    oDiag = 0;    //  OGS a inserer dans un Body or OGS 
                }
                else {
#ifdef DEBUG_CAASERVICES 
                    cout << " (CAAGsiCreateGeometricFeatureSets) ERROR , an OGS can only be inserted under another Body or OGS  or directly under the part"<< endl; 
#endif 
                     oDiag =2 ; // Body or GS  que l'on veut inserer dans un GS 
                }
            }    
            else if (iType ==2 ) { 
                if ( NULL_var != spOrderedGeomSet ) {
                    oDiag = 0;    // Body a inserer sous la Part ou un OGS 
                }
                else {
#ifdef DEBUG_CAASERVICES 
                    cout << " (CAAGsiCreateGeometricFeatureSets) ERROR , a body can only be inserted under an OGS  or directly under the part"<< endl; 
#endif 
                    oDiag =4 ; // Body  que l'on veut inserer dans un GS ou dans un Body existant  
                }
            }    
        }
            
        // Phase 2: Create the tool as whished 
        // --------------------------------------------- 
        // Create of the Tool 

        if (oDiag < 1) { 
            // Phase 3: Create a GSMTool
            // --------------------------------------------- 
            if (NULL_var != spParentForTool)
            {
                CATIMechanicalRootFactory_var spMechRoot = ispCont ;
                if (NULL_var != spMechRoot) {  
                    
                    if (0 == iType ) { 
                        
                        //  cout << " (CAAGsiCreateGeometricFeatureSets) Create GS  "<< iName << endl; 
                        rc = spMechRoot -> CreateGeometricalSet(iName,spParentForTool,spSpecTool,Position);
                        
                    }
                    else  if (1 == iType ) { 
                        
                        // cout << " (CAAGsiCreateGeometricFeatureSets)Create OGS  "<< iName << endl; 
                        rc = spMechRoot -> CreateOrderedGeometricalSet(iName,spParentForTool,spSpecTool,Position);
                        }
                    else  if (2 == iType ) { 
                        
                        // cout << " (CAAGsiCreateGeometricFeatureSets) Create Body   "<< iName << endl; 
                        spSpecTool  = spMechRoot -> CreatePRTTool(iName,spParentForTool,Position);
                    }
                    
                }
            }      
            
            // Phase 4: Set  the tool as current 
            // --------------------------------------------- 
            if (NULL_var != spSpecTool )
            {
                if (NULL_var != spPart) { 
                    //    cout << " (CAAGsiCreateGeometricFeatureSets) Set As Current the tool "<<  endl; 
                    spPart -> SetCurrentFeature(spSpecTool);
                }
                
            }
        }
        else {
            rc = E_FAIL ; 
        }
        
        
        
   }
   
#ifdef DEBUG_CAASERVICES 
   if (SUCCEEDED(rc) && NULL_var !=spSpecTool ) { 
       cout << " (CAAGsiCreateGeometricFeatureSets) Set created  ="<< spSpecTool  -> GetName() <<endl ;
   } 
   else { 
       cout << " (CAAGsiCreateGeometricFeatureSets) ERROR Failed create Geometric Features set "<<endl ;
   } 
#endif 
   return rc ;
}  

//
// =========================================================================================================
//  Get current GSM Tool and create one if none found 
// =========================================================================================================
ExportedByCAAGsiServices CATIGSMTool_var 
CAAGsiGetCurrentSurfacicFeatureSet(const CATIContainer_var &ispCont, const CATUnicodeString& iName,int iSetAsCurrent)
{
   
    HRESULT rc = S_OK; 
#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiGetCurrentSurfacicFeatureSet"  << endl;
#endif 
   
   // Get Current part 
   CATIPrtContainer_var          spPartCont  = ispCont;
//    CATISpecObject_var            spSpecPart  = spPartCont -> GetPart();
   CATIPrtPart_var               spPart      = spPartCont -> GetPart();
   
   CATIGSMTool_var spTool ;
   if (NULL_var != spPart)
   {    
      // Is-it a GSMTool in current Tool ?
      CATIBasicTool_var spCurrentTool = spPart->GetCurrentTool();
      spTool = spCurrentTool;
      
      //1. GSMTool is the current 
      if (NULL_var != spTool)
      {
         // Retrieve existant tools // DO NOT USE External Reference Tool 
         CATISpecObject_var spExternalRef = spPart->GetBodyForExternalReferences();
         if (NULL_var != spExternalRef && spTool == spExternalRef)
            spTool = NULL_var;
      }
      
      //2. No Pre-existant GSMTool  
      if (NULL_var == spTool)
      {
         CATISpecObject_var spSpecTool; 
         CATISpecObject_var spParent; 
         int iDiag = 0 ; 
         rc  = CAAGsiCreateGeometricFeatureSets (ispCont,iName,spParent, spSpecTool, iDiag , UNDER_Part ,  GS) ; 
         if (SUCCEEDED(rc) ){ 
             spTool = spSpecTool ; 
         }
         //  CAAGsiCreateSurfacicFeatureSet(ispCont,iName,iSetAsCurrent,0);
      }
   }
   
   // Return GSMTool
   return spTool;
}



// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / Object                ==============
// ----------------------------------------------------------------------------------------------

// =========================================================================================================
// Insert a Feature in the procedural view / for feature DERIVING directly from GeometricalElement 
// =========================================================================================================

//-----------------------------------------------------------------------------
// The aim of this method is to allow created and updated feature  to be visible 
// in the standard V5 Graph Edito
// Not: for object derivating from GSMGeom use CAAGsiInsertInProceduralView 
ExportedByCAAGsiServices HRESULT 
CAAGsiInsertGeometricalElement( const CATIContainer_var ispCont, const CATISpecObject_var  ispObjectToAppend,
                        CATISpecObject_var  ispInputParent)
{
#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiInsertInProceduralView "  << endl;
#endif 
   
    HRESULT rc = E_FAIL;
    if (NULL_var == ispObjectToAppend ) return rc; 


   CATIGSMTool_var spTool = ispInputParent;
   // Check Father / Initialize current GSMTool  
   if (NULL_var == spTool)
       spTool = CAAGsiGetCurrentSurfacicFeatureSet(ispCont,"CAAGsmTools",1);
   
   // Append object 
   if ( NULL_var != ispObjectToAppend && NULL_var != spTool)
   {
      CATIDescendants_var spParent = spTool;
      if ( NULL_var != spParent)
         // Add in current GSMTool ispObjectToAppend
         spParent -> Append ( ispObjectToAppend );
      else
         return E_FAIL;
   }
   else  
      return E_FAIL;
   return S_OK;

}

// =========================================================================================================
// Insert a FEature in the procedural view / for feature DERIVING from GSMGeom 
// =========================================================================================================
//-----------------------------------------------------------------------------
// The aim of this method is to allow created and updated feature  to be visible 
// in the standard V5 Graph Editor 
ExportedByCAAGsiServices HRESULT 
CAAGsiInsertInProceduralView( const CATISpecObject_var ispObjectToAppend,
                        CATISpecObject_var ispInputParent)
{
   
      
#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiInsertInProceduralView "  << endl;
#endif 
   
   HRESULT rc = E_FAIL;

   CATIGSMProceduralView_var curobj = ispObjectToAppend;
   if (NULL_var != curobj ) {
         rc = curobj->InsertInProceduralView();
#ifdef DEBUG_CAASERVICES 
        if (FAILED(rc))   cout  << "(CAAGsiServices) ERROR  Failed to insert in procedural view  "  << endl;
#endif 
   }
   return rc ;

}


// =========================================================================================================
// Update 
// =========================================================================================================
// This method encapsulates the standard update, in order to catch if needed update errors 
ExportedByCAAGsiServices HRESULT 
CAAGsiObjectUpdate(const CATISpecObject_var & ispSpec)
{

#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiUpdate "  << endl;
#endif 
   HRESULT rc = S_OK ; 
   int iStat = 0 ;
   if ( NULL_var != ispSpec ) {
      // Declare a bloc where every exceptions will be catch and treated in
      // the CATCatch() block
      CATTry  {	
         iStat = ispSpec -> Update();
#ifdef DEBUG_CAASERVICES 
         cout << " Update iStat = " << iStat <<  endl; 
#endif 
         
         // V5R13   
         // check Linearity / usefull for absorbant feature inserted  in OGS 
         CATISpecObject_var spFather = ispSpec->GetFather();
         if ( NULL_var  != spFather )
         {
            spFather -> Release();
             CATIGSMTool *piGSMToolFather = NULL;
             rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFather);
             if ( SUCCEEDED(rc) ) { 
                 int IsAnAbsorbentSet = -1 ;
                 piGSMToolFather->GetType(IsAnAbsorbentSet) ;
                 if ( 1 == IsAnAbsorbentSet ) {
                     CATBaseUnknown_var spUnkwnSpec = ispSpec;
                     rc = CATMmrLinearBodyServices::Insert(spUnkwnSpec) ; 
                 } 
                 piGSMToolFather->Release() ; piGSMToolFather=NULL; 
             }   
         }
         //
         
         
      }
      // This block is specific for Update Errors
      CATCatch(CATMfErrUpdate,error)	 {
#ifdef DEBUG_CAASERVICES 
         cerr << " Update Error: " << (error-> GetDiagnostic()).ConvertToChar() << endl; 
         Flush(error) ; 
#endif 
         return E_FAIL; 
      }
      // This block treats every other exception
      CATCatch(CATError,error)    {
#ifdef DEBUG_CAASERVICES 
         cerr << " Error: " << error->GetMessageText() <<endl; 
         Flush(error);
#endif 

         return E_FAIL; 
      }
      CATEndTry;
      
   }
   return rc ; 
}


// =========================================================================================================
// Format name for Panel display 
// =========================================================================================================

// Retrieve Standard Name  
// -----------------------------------------------------------
CATUnicodeString CAAGsiGetSpecBasicName(const CATBaseUnknown_var & CurrentSpec)
{

    CATUnicodeString BasicName;
    // Nom Std simple 
    CATIAlias_var aliasftr  = CurrentSpec ;
    CATISpecObject_var Spec = CurrentSpec  ;
    if (!!aliasftr){
        BasicName.Append(aliasftr->GetAlias()) ;
    }
    else if (!!Spec) {
        BasicName.Append(Spec->GetDisplayName());
    }
   
    //cout << "(CAASewSkinCmd::GetSpecCompleteDisplayName) Basic Name of the feature = " <<BasicName  <<endl;
    return BasicName ;
    
}

//
// Retrieve more explicit name for panel fields
// -----------------------------------------------------------
CATUnicodeString CAAGsiGetSpecDisplayName(const CATBaseUnknown_var& CurrentSpec)
{
   if (CurrentSpec==NULL_var) return "no spec";

   CATUnicodeString DisplayName;
 
   // Spec is a feature Brep 
   // --------------------------------------------------------------------------

   CATIMfBRep_var brep = CurrentSpec;
   if (brep!=NULL_var)
   {
      //on complete le nom du feature Brep avec son support
      CATISpecObject_var support = brep->GetSupport();
      if (support!=NULL_var)
      {
         DisplayName = CAAGsiGetSpecBasicName(support);
         DisplayName.Append("\\");
      }
   }


   /*
     // ==== DS Code Only (Not CAA) 
   // Spec is a solid feature 
   // --------------------------------------------------------------------------
   CATISpecObject_var Spec(CurrentSpec);
   if (Spec!=NULL_var)
   {
      if (Spec->IsSubTypeOf("Solid"))
      {
         //pour les solides, on remonte au shapefeature s'il existe
         CATISlaveGeometry_var slave = Spec;
         if (slave!=NULL_var)
         {
            CATISpecObject_var master = slave->IsSlaveTo();
            if (master!=NULL_var)
            {
               DisplayName = CAAGsiGetSpecBasicName(master);
               return DisplayName;
            }
         }
      }
   }
     // ==== DS Code Only (Not CAA)  
   */
   
   // Spec is standard 
   // --------------------------------------------------------------------------
   DisplayName.Append(CAAGsiGetSpecBasicName(CurrentSpec));
   return DisplayName;

}

// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / FeatureSearch   ==============
// ----------------------------------------------------------------------------------------------

// =========================================================================================================
// Recursive Scan of mechanical Tool and GSM Tool 
// =========================================================================================================
void LocalScanTool (const CATUnicodeString ToolCurrent, const CATUnicodeString SearchedFeatName, const CATISpecObject_var spSpecTool, CATISpecObject_var & spSpecFound , int  & iFound ) 
{

    
#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) LocalScanTool "  << endl;
#endif 

    CATIDescendants_var spDescendants=  spSpecTool;
    
    int childrenNb= spDescendants->GetNumberOfChildren();
    CATIAlias_var aliasOnCurBody = spSpecTool ;
    // cout << " ObjectCurrent = " <<aliasOnCurBody->GetAlias().ConvertToChar() << "/ NbChildren = " << childrenNb  <<endl; 
 
    CATISpecObject_var TheFoundedSpec ; 
    for ( int i= 1; i<= childrenNb ; i++)
    {
        
        CATISpecObject_var spChild= spDescendants->GetChildAtPosition(i);
        
        CATIGSMTool_var          spGsmTool  = spChild ; 
        CATIMechanicalTool_var   spMechTool = spChild ; 
        
        if ( spGsmTool != NULL_var || spMechTool  != NULL_var ) { 
            
            //              cout << " / "<<ToolName.ConvertToChar()    
            CATIAlias_var aliasOnCurBody = spChild ;
            CATUnicodeString ToolName = aliasOnCurBody->GetAlias(); 
            
            CATUnicodeString TheTool = ToolCurrent;
            TheTool.Append("/"); 
            TheTool.Append(ToolName) ; 
            
#ifdef DEBUG_CAASERVICES            
            cout << " Appel LocalScanTool "<< TheTool.ConvertToChar()<<endl; 
#endif 
            LocalScanTool (TheTool ,  SearchedFeatName, spChild , spSpecFound, iFound ) ;
            
        }
        else { 
            CATISpecObject_var  Feature = spChild ;
            if (NULL_var  != Feature ) { 
                CATUnicodeString Test(Feature->GetName());
                CATIAlias_var aliasOnChild =  spChild ;
                CATUnicodeString FeatName = aliasOnChild ->GetAlias(); 
                //if (SearchedFeatName == Test) {
                if (SearchedFeatName == FeatName) {
#ifdef DEBUG_CAASERVICES            
                    cout << " --------------Object Found " << Test << " / "  << FeatName << endl; 
#endif 
                    TheFoundedSpec = Feature ;
                    iFound =1 ;     
                    break ; 
                }
            }
        }           
    }
    if (iFound ==1 ) {  
        if (NULL_var  != TheFoundedSpec) spSpecFound = TheFoundedSpec; 
    }
}

// =========================================================================================================
// Retrieve a Part or GSD Feature from its name 
// =========================================================================================================
CATISpecObject_var 
CAAGsiSearchFeatureFromName(CATIPrtPart_var & spPrtPart, CATUnicodeString  SearchedFeatName)
{

#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiSearchFeatureFromName "  << endl;
#endif 
    HRESULT rc = S_OK; 
    CATISpecObject_var  spSpecFound  ; 
    int iFound = 0 ; 
    
    CATIDescendants_var spDescendants=  spPrtPart;
    int childrenNb= spDescendants->GetNumberOfChildren();
    CATIAlias_var aliasOnPart = spPrtPart ;
#ifdef DEBUG_CAASERVICES            
    cout << endl ; 
    cout << "Part name  = " <<aliasOnPart ->GetAlias().ConvertToChar() << endl;
#endif 
    int i=0;     
    for (i= 1; i<= childrenNb; i++)
    {
        
        CATISpecObject_var spChild= spDescendants->GetChildAtPosition(i);
        
        CATIGSMTool_var spGsmTool = spChild ; 
        CATIMechanicalTool_var   spMechTool = spChild ; 
        
        if ( spGsmTool != NULL_var || spMechTool  != NULL_var ) { 
            CATIAlias_var aliasOnCurBody = spChild ;
            CATUnicodeString ToolCurrent  = aliasOnCurBody->GetAlias(); 
            // Scan /Update   
            LocalScanTool (ToolCurrent ,  SearchedFeatName, spChild , spSpecFound, iFound ) ;
        }
        
    }
#ifdef DEBUG_CAASERVICES            
    cout << "     / Search result : " << iFound ;
    if (iFound ==1 ) cout << " / -->  "<< (spSpecFound->GetName()).ConvertToChar();   
    cout << endl ;
#endif 
    
    return spSpecFound ; 
}


// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / Knowledge       ==============
// ----------------------------------------------------------------------------------------------


// =========================================================================================================
// Litteral 
// =========================================================================================================

CATICkeParm_var
LocalInstLitteral (void * Value, int IsValuate, CATUnicodeString NomLitteral, CATIContainer_var  Cont, CATUnicodeString Name)
{
#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) LocalInstLitteral "  << endl;
#endif 

    int				Ipipo = 0;
   double			Rpipo = 0.0;
   double         *dist;
   int            *idist;
   
   CATICkeParmFactory_var		fact = Cont;
   CATICkeParm_var				Litteral = NULL_var;
   
   if (Cont == NULL_var)
      return Litteral;
   
//   if (NomLitteral == "Longueur")
   if (NomLitteral == "Length")
   {
      
      if (IsValuate)
	    dist = (double *)Value;
      else
	    dist = &Rpipo;
      
      Litteral = fact -> CreateLength (Name, *dist);
      
   }
   else if (NomLitteral == "Angle")
   {
      if (IsValuate)
	    dist = (double *)Value;
      else
	    dist = &Rpipo;
      
      Litteral = fact -> CreateAngle (Name, *dist);
      
   }
   else if (NomLitteral == "Real")
   {
      if (IsValuate)
	    dist = (double *)Value;
      else
	    dist = &Rpipo;
      
      Litteral = fact -> CreateReal (Name, *dist);
      
   }
   else if (NomLitteral == "Integer")
   {
      if (IsValuate)
	    idist = (int *)Value;
      else
	    idist = &Ipipo;
      
      Litteral = fact -> CreateInteger (Name, *idist);
   }
   else if (NomLitteral == "Boolean")
   {
      if (CATPtrToINT32(Value))
	    Litteral = fact->CreateBoolean(Name,CATCke::True);
      else
	    Litteral = fact->CreateBoolean(Name,CATCke::False);
   }
   else 
   {
      if (IsValuate)
	    dist = (double *)Value;
      else
	    dist = &Rpipo;
      Litteral = fact -> CreateReal (Name, *dist);
   }
   return Litteral;
}

// =========================================================================================================
// Remove of a spec element 
// =========================================================================================================
ExportedByCAAGsiServices
HRESULT CAAGsiRemove ( CATISpecObject_var SpecToRemove) 
{
    HRESULT rc = E_FAIL; 
    if (!!SpecToRemove) { 
        //evenement de remise a jour de la visu
        CATIModelEvents_var IME(SpecToRemove);
        if(!!IME) 
        {
            CATDelete info(SpecToRemove->GetImpl());
            IME->Dispatch(info);
        }
        
        //destruction
        CATISpecObject_var father = SpecToRemove->GetFather();
        if (father!=NULL_var)
        {
            father->Release();
            CATIDescendants_var IDes = father;
            IDes->RemoveChild (SpecToRemove);
        }
        else
        {
            LifeCycleObject_var LCO = SpecToRemove;
            LCO -> remove();
        }
        rc = S_OK ; 
    }
    return rc ;
}

// =========================================================================================================
// Instanciate litteral 
// =========================================================================================================

ExportedByCAAGsiServices CATICkeParm_var
CAAGsiInstanciateLitteral (CATUnicodeString  NomLitteral, CATIContainer_var  Cont,CATUnicodeString Name)
{

#ifdef DEBUG_CAASERVICES 
   cout << "(CAAGsiServices) CAAGsiInstanciateLitteral "  << endl;
#endif 
   	double		pipo = 0.0;
	return LocalInstLitteral (&pipo, 0, NomLitteral, Cont, Name);
}
