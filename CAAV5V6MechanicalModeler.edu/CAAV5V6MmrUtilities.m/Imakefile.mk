# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6MmrUtilities.m
#====================================================================== 
#
BUILT_OBJECT_TYPE= SHARED LIBRARY

#if defined (CATIAR214) 
LINK_WITH=  JS0GROUP \
            CATMecModLiveUseItf \
            CATObjectModelerBase \
            KnowledgeItf \
            CATMecModUseItf \
            CATProductStructureInterfaces \
			CATPLMIdentificationAccess \
	        ObjectModelerSystem \ 
			CAT3DPhysicalRepItf\
			CATPLMComponentInterfaces \
			CAAAdpUtilities \
#elif defined (CATIAV5R23) 
LINK_WITH=  JS0GROUP \
            CATMecModLiveUseItf \
            CATObjectModelerBase \
            KnowledgeItf \
            CATMecModUseItf \
            CATInteractiveInterfaces \
	        ObjectModelerSystem \ 
			CATMecModInterfaces \
			CATObjectSpecsModeler  \
			CATInteractiveInterfaces \
#endif
