#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
CATDfiUUID \
SketcherInterfacesUUID
#else
LINK_WITH_FOR_IID =
#endif
# COPYRIGHT DASSAULT SYSTEMES 2000
BUILT_OBJECT_TYPE = LOAD MODULE

LINK_WITH = $(LINK_WITH_FOR_IID)  JS0CORBA CATObjectModelerBase \
            CATObjectSpecsModeler CATDraftingInterfaces \
            CATSketcherInterfaces 
