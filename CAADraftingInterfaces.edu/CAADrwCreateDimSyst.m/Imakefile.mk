#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
CATDfiUUID \
SketcherInterfacesUUID
CATMmiUUID
SystemUUID
#else
LINK_WITH_FOR_IID = SystemUUID
#endif
# COPYRIGHT DASSAULT SYSTEMES 2000
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=$(LINK_WITH_FOR_IID) \
            JS0GROUP \
            CATMathematics \
            CATDialogEngine \
            CATDraftingInterfaces  \
            CATSketcherInterfaces  \
            CATObjectModelerBase \
            CATObjectSpecsModeler \
            CATVisualization  CATViz   \
            JS0CORBA JS0FM
