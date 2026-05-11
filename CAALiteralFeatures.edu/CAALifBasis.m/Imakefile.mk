#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
CAALiteralFeaturesEduUUID \
LiteralFeaturesUUID \
SystemUUID
#else
LINK_WITH_FOR_IID = SystemUUID
#endif
# COPYRIGHT DASSAULT SYSTEMES  2000

#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH=$(LINK_WITH_FOR_IID) 	CATObjectSpecsModeler\
			CATObjectModelerBase \
			JS0GROUP Collections \
            KnowledgeItf MecModItf
#
