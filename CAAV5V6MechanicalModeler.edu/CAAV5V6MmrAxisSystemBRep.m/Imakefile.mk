#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrAxisSystemBRep.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH =JS0GROUP \
           CATObjectModelerBase \
           CATMathematics \
           DataCommonProtocolUse \
           CAAAdpUtilities \
           CATMecModUseItf \
		   CATMecModLiveUseItf \
           CATSketcherUseItf \
           CATPLMComponentInterfaces \
           CATPLMIntegrationUse \
           CATPLMIntegrationAccess \
           CAT3DPhysicalRepItf \
           CATProductStructureUseItf \
           KnowledgeItf \
		   PLMDictionaryNavServices \

#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
           CATObjectModelerBase \
		   CATMathematics \
           CATObjectSpecsModeler \
           CATMechanicalModeler \
		   CATMecModInterfaces \
           KnowledgeItf \
		   CATSketcherInterfaces \
           CATGeometricObjects \
		   CATCGMGeoMath \
		   CATMecModUseItf \
		   CATMecModLiveUseItf \
#endif
