#
# COPYRIGHT DASSAULT SYSTEMES 2002
#
BUILT_OBJECT_TYPE=SHARED LIBRARY
#
LINK_WITH= JS0GROUP \
           CATProductStructure1 \
		   CATObjectModelerBase \
           CATElectricalInterfaces \
           CATEwrInterfaces \
		   CATObjectSpecsModeler \
		   KnowledgeItf \
		   CATProductStructureInterfaces \
		   ProductStructurePubIDL
#
OS = COMMON

