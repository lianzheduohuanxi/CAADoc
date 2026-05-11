#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrApplicativeAttributes.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH = JS0GROUP \
            CAAAdpUtilities \
            CATPLMIdentificationAccess \
            CATPLMComponentInterfaces \
            CATPLMIntegrationUse \
            CATObjectModelerBase \
            CATMecModUseItf \
            CATMecModLiveUseItf \
            CATGMModelInterfaces \
		    KnowledgeItf \
		    CAT3DPhysicalRepItf \
			CAAV5V6MmrUtilities \

#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
            CATObjectModelerBase \
            CATMecModUseItf \
            CATMecModLiveUseItf \
            CATGMModelInterfaces \
		    KnowledgeItf \ 
			CAAV5V6MmrUtilities \
			CATMecModInterfaces \

#endif

	        

