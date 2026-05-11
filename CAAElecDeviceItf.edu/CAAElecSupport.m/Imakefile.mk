# COPYRIGHT DASSAULT SYSTEMES  2001
BUILT_OBJECT_TYPE = LOAD MODULE
#
LINK_WITH = JS0GROUP                \
            CATProductStructure1    \
            CATLiteralFeatures      \
            CATObjectModelerBase    \
            CATElbInterfaces        \
			KnowledgeItf            \
			AC0SPBAS				\
			CATElectricalInterfaces $(LINK_WITH_DEBUG)
            
#
OS = COMMON

#ifdef CATIAV5R9
#if os SunOS
LINK_WITH_DEBUG = CATObjectSpecsModeler
#else
LINK_WITH_DEBUG = 
#endif
#else
LINK_WITH_DEBUG = 
#endif
