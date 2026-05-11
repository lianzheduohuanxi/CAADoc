# COPYRIGHT DASSAULT SYSTEMES  2001
BUILT_OBJECT_TYPE = LOAD MODULE
#
LINK_WITH =  JS0CORBA \               # IUnknown, CATIUnknownList, CATICStringList
             NS0S3STR \               # CATUnicodeString
             CATObjectModelerBase \   # CATSession, CATDocument, CATDocumentServices
             CATObjectSpecsModeler \  # CATISpecObject
             DraftingItfCPP \         # CATIDftDocumentServices, CATIDrawing, CATIDrwFactory, CATIDftViewMakeUp, CATIView, CATISheet, CATIDrwAnnotationFactory, CATIDrwText
             CATSketcherInterfaces \  # CATI2DWFFactory
             CATSchUUID \             # IIDs of the Schematic Interfaces
             CATSchItfCPP \           # CATSchListServices, CATISchBaseFactory, CATISchAppObjectFactory, CATISchAppConnector, CATISchAppConnectable, CATISchCompConnector, CATISchComponent, CATISchRoute, CATISchGRRComp, CATISchGRR, CATISchCntrLocation, CATISchAppConnection, CATISchSession
             CATMathematics
#
OS = COMMON
