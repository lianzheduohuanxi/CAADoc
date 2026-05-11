#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrExtMmrCombinedCurveSample.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
	       CAAV5V6ExtMmrCombinedCurve \ 
	       CAAAdpUtilities \
   	       CAT3DPhysicalRepItf \
           CATPLMIntegrationUse \
           CATPLMIntegrationAccess \
           CATPLMComponentInterfaces \
           CATMecModUseItf \
           CATMecModLiveUseItf \
           ObjectModelerSystem \
           CATObjectModelerBase \
           DataCommonProtocolUse \
           CATGSMUseItf \
           CATProductStructureUseItf \
           KnowledgeItf \
		   PLMDictionaryNavServices \

#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \
	       CAAV5V6ExtMmrCombinedCurve \ 
           CATMecModUseItf \
           CATMecModLiveUseItf \
           ObjectModelerSystem \
           CATObjectModelerBase \
           CATGSMUseItf \
           KnowledgeItf \
		   CATObjectSpecsModeler \
		   CATMecModInterfaces \
#endif
