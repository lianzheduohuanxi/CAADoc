// COPYRIGHT DASSAULT SYSTEMES 2001+
//=============================================================================
//
// CAASchAppClassNames
//
//=============================================================================
#ifndef CAASchAppClassNames_H
#define CAASchAppClassNames_H

//-----------------------------------------------------------------------------
// Application reference name labeled for testing instantiation
//-----------------------------------------------------------------------------
#define SCHEDUPart_TestRef                  "CAASch_Component"

//-----------------------------------------------------------------------------
// Application name
//-----------------------------------------------------------------------------
#define SCHEDUApplication_Name              "CAASCHEDU_SamplePID"

//-----------------------------------------------------------------------------
// ".feat" file name
//-----------------------------------------------------------------------------
#define SCHEDUAppFeat_Name                  "CAASCHEDUApp.CATfct"

#define SCHEDUAppClientID                   "CAASCHEDUApp_ClientId"
//-----------------------------------------------------------------------------
// application object container name
//-----------------------------------------------------------------------------
#define SCHEDUAppCont_Name                  "CAASCHEDUAppObjCont"

//-----------------------------------------------------------------------------
// SU classes
//-----------------------------------------------------------------------------
#define SCHEDUClass_ASMPRODUCT              "ASMPRODUCT"
#define SCHEDUClass_CONNECTION              "CONNECTION"
#define SCHEDUClass_CONNECTOR               "CONNECTOR"
#define SCHEDUClass_Part                    "CAASCHEDUPart"
#define SCHEDUClass_FuncPart                "CAASCHEDUFunctionalPart"
#define SCHEDUClass_PhysPart                "CAASCHEDUPhysicalPart"
#define SCHEDUClass_String                  "CAASCHEDUString"
#define SCHEDUClass_FuncString              "CAASCHEDUFuncString"

// sub-classes of SCHEDUClass_FuncPart
#define SCHEDUClass_Compressor              "CAASCHEDUCompressFunc"
#define SCHEDUClass_Pump                    "CAASCHEDUPumpFunc"
#define SCHEDUClass_Vessel                  "CAASCHEDUVesselFunc"
#define SCHEDUClass_BlockValve              "CAASCHEDUBlockValveFunc"
#define SCHEDUClass_CheckValve              "CAASCHEDUCheckValveFunc"
#define SCHEDUClass_ControlValve            "CAASCHEDUControlValveFunc"
#define SCHEDUClass_Reducer                 "CAASCHEDUReducerFunc"
#define SCHEDUClass_Nozzle                  "CAASCHEDUNozzleFunc"

#define SCHEDUClass_PhysString              "CAASCHEDUPhysicalString"
#define SCHEDUClass_Connector               "CAASCHEDUConnector"
#define SCHEDUClass_Connection              "CAASCHEDUConnection"

//-----------------------------------------------------------------------------
// SU Names
//-----------------------------------------------------------------------------
#define SCHEDUName_ASMPRODUCT              "ASMPRODUCT"
#define SCHEDUName_Part                    "Sample Application Part"
#define SCHEDUName_FuncPart                "Sample Application Functional Part"
#define SCHEDUName_PhysPart                "Sample Application Physical Part"
#define SCHEDUName_String                  "Sample Application String"
#define SCHEDUName_FuncString              "Sample Application Functional String"

// sub-classes of SCHEDUClass_FuncPart
#define SCHEDUName_Compressor              "Sample Application Compressor Function"
#define SCHEDUName_Pump                    "Sample Application Pump Function"
#define SCHEDUName_Vessel                  "Sample Application Vessel Function"
#define SCHEDUName_BlockValve              "Sample Application Blocking Valve Function"  
#define SCHEDUName_CheckValve              "Sample Application Check Valve Function"
#define SCHEDUName_ControlValve            "Sample Application Control Valve Function"
#define SCHEDUName_Reducer                 "Sample Application Reducer Function"
#define SCHEDUName_Nozzle                  "Sample Application Nozzle Function"
#define SCHEDUName_PhysString              "Sample Application Physical String"
#define SCHEDUName_Connector               "Sample Application Connector"
#define SCHEDUName_Connection              "Sample Application Connection"

//-----------------------------------------------------------------------------
// SU Attributes
//-----------------------------------------------------------------------------
// Connector
#define SCHEDUATTR_Connector_FlowCapacity  "CAASCHEDUConnectorFlowCapacity"
#define SCHEDUATTR_Connector_FlowReality   "CAASCHEDUConnectorFlowReality"
#define SCHEDUATTR_Connector_ToOtherCntr   "CAASCHEDUConnectorToOtherCntr"

//-----------------------------------------------------------------------------
// Others
//-----------------------------------------------------------------------------
#define SCHEDUATTRConnectorFamily_Name     "CAASCHEDUConnectorFamily"
#define SCHEDUAppDiscipline_Name           "CAASCHEDUAppDiscipline"

#define SCHEDUAppClass_ConnectionVisu      "CAASCHEDUAppClass_ConnectionVisu"
#endif
