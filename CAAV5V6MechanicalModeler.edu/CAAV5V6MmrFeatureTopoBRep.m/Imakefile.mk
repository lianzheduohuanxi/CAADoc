#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrFeatureTopoBRep.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \  
       CATMecModLiveUseItf \
	   CAAAdpUtilities \
	   CATObjectModelerBase \
	   CATPLMIntegrationUse \
       CATMecModUseItf \
	   CATPLMIdentificationAccess \
	   CATGMModelInterfaces \
	   CATGMOperatorsInterfaces \
	   CATVisItf \
	   CATPLMComponentInterfaces \
	   CAT3DPhysicalRepItf \
	   CAAV5V6MmrUtilities \
	    
#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \  
       CATMecModLiveUseItf \
	   CATMecModUseItf \
	   CATGMModelInterfaces \
	   CATGMOperatorsInterfaces \
	   CATObjectModelerBase \
	   CATMecModInterfaces \
	   CATVisualization \
	   CAAV5V6MmrUtilities \
#endif
