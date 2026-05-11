# COPYRIGHT DASSAULT SYSTEMES  2001
BUILT_OBJECT_TYPE = LOAD MODULE
#
LINK_WITH = JS0GROUP                \ 
		    CATProductStructure1    \
	     	CATLiteralFeatures      \
            CATObjectModelerBase    \
            CATObjectSpecsModeler   \
            CATGitInterfaces        \
            CATEhiInterfaces        \
            CATElectricalInterfaces \
			KnowledgeItf            \
			CATMecModInterfaces
#
OS = COMMON

