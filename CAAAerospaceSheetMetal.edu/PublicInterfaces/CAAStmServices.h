#ifndef CAAStmServices_h_
#define CAAStmServices_h_
//============================================================================================
// COPYRIGHT Dassault Systemes 2004
//============================================================================================
/**
 * Class CAAStmServices.
 *
 * <b>Role</b>: Provides services to manage Aerospace Sheet Metal Features in CAA context
 */
#include "CAAStmExportedBy.h"

#include "CAAStmInputData.h"                 // To describe CAA Aerospace Sheet Metal Features Input Data

#include "CATDocument.h"                     // To handle Document
#include "CATISpecObject.h"                  // To handle Features
#include "CATListPtrCATISpecObject.h"        // To handle List of Features
#include "CATTopDefine.h"                    // To Topological definitions

#include "CATUnicodeString.h"                // To manage strings
#include "CATListOfCATUnicodeString.h"       // To manage a List of strings

class ExportedByCAAStmServices CAAStmServices
  {
  public:
    
    CAAStmServices();
    virtual ~CAAStmServices();
     
    /**
     * <b>Role</b>: Method to read the input data ".txt" File of the sample.
     *
     *   @param iFilePath 
     *      Path to the ".txt" File to read.
     *   @param oLines 
     *      contents of the lines read on the File.
     *
     */
    HRESULT ReadInputFile (const CATUnicodeString &    iFilePath, 
                           CATListOfCATUnicodeString & oLines);    
    
    /**
     * <b>Role</b>: Method to retrieve and analyse Web input data.
     *
     *   @param iInputDataFilePath 
     *      Path to the ".txt" File including the Web input data.
     *   @param ioCAAInputWeb 
     *      Structure representing the Surfacic Flange input data.
     */
    HRESULT AnalyseWebInputData (const CATUnicodeString &  iInputDataFilePath,
                                 CAAStmInputData &         ioCAAInputFlg);

    /**
     * <b>Role</b>: Method to retrieve and analyse Surfacic Flange input data.
     *
     *   @param iInputDataFilePath 
     *      Path to the ".txt" File including the Surfacic Flange input data.
     *   @param ioCAAInputFlg 
     *      Structure representing the Surfacic Flange input data.
     */ 
    HRESULT AnalyseSurfacicFlangeInputData (const CATUnicodeString &  iInputDataFilePath,
                                            CAAStmInputData &         ioCAAInputFlg);
    /**
     * <b>Role</b>: Method to retrieve and analyse Joggle input data.
     *
     *   @param iInputDataFilePath 
     *      Path to the ".txt" File including the Joggle input data.
     *   @param ioCAAInputFlg 
     *      Structure representing the Joggle input data.
     */ 
    HRESULT AnalyseJoggleInputData (const CATUnicodeString &  iInputDataFilePath,
                                    CAAStmInputData &         ioCAAInputJoggle);

    /**
     * <br><b>Role</b>: Method to retrieve a Web Feature in the Part.
     *
     * @param ispPrtPartSpec 
     *   Part Feature
     * @param opiWebSpec 
     *   Specification of the Web feature.
     */ 
    HRESULT FindWeb (const CATISpecObject_var & ispPrtPartSpec,
                     CATISpecObject **          opiWebSpec);

    /**
     * <b>Role</b>: Method to retrieve a feature in the Specifications tree.
     *
     * @param ispPrtPartSpec 
     *   Part Feature
     * @param iSpecName 
     *    Name of the Feature to retrieve : "Sketch.1", ...
     * @param opiSpec 
     *    Retrieved spec.
     */ 
    HRESULT FindFeatureInSpecTree (const CATISpecObject_var & ispPrtPartSpec,
                                   const CATUnicodeString &   iSpecName, 
                                   CATISpecObject **          opiSpec);    
    
    /**    
     * <b>Role</b>: Method to retrieve some Features in the current Part Specs tree.
     *
     * @param ispPrtPartSpec 
     *   Part Feature
     * @param iSpecNamesList 
     *   List of the names of the Features to retrieve : "Sketch.1", "Fill.2", ...
     * @param oSpecsList 
     *   List of the retrieved specs.
     */ 
    HRESULT FindFeaturesInSpecTree (const CATISpecObject_var &        ispPrtPartSpec,
                                    const CATListOfCATUnicodeString & iSpecNamesList,
                                    CATLISTP(CATISpecObject) &        oSpecsList);
   
    /**
     * <b>Role</b>: Method to update an Aerospace Sheet Metal Feature.
     *              
     *              This method encapsulates the standard update mechanism to manage errors.
     *
     *   @param ipiSpec 
     *      Spec to update.
     */
    HRESULT Update (CATISpecObject * ipiSpec);
    
    /**
     * <b>Role</b>: Method to return a Length value converted in meter.
     *
     *   @param iLengthUnitName 
     *      Length Unit.
     *   @param iValueToConvert 
     *      Value To Convert.
     */
    double ConvertLengthToMKS (const CATUnicodeString & iLengthUnitName,
                               const double &           iValueToConvert);
    
    /**    
     * <b>Role</b>: Method to display an Aerospace Sheet Metal Feature current entries.
     *
     * @param ipiSpec 
     *   Feature to display : a Web, a Surfacic Flange or a Joggle.
     */
    HRESULT Display (CATISpecObject * ipiSpec);

  };

#endif 
