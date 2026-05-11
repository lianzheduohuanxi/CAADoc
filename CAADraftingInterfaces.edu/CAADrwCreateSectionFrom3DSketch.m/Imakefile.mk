#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
CATDfiUUID \
DraftingItfCPP
SketcherInterfacesUUID \
#else
LINK_WITH_FOR_IID = SystemUUID
#endif
# COPYRIGHT DASSAULT SYSTEMES 2000
BUILT_OBJECT_TYPE = LOAD MODULE

LINK_WITH = $(LINK_WITH_FOR_IID)  JS0GROUP JS0CORBA CATObjectModelerBase CATTPSUUID\
			CATObjectSpecsModeler DraftingItfCPP CATDraftingInterfaces CATNewTopologicalObjects \
			CATProductStructure1 CATGeometricObjects CATMecModInterfaces CATMathematics\
			CATVisualization  CATViz CATSketcherInterfaces
