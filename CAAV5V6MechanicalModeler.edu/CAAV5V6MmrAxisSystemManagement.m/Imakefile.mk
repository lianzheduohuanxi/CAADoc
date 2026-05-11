#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrAxisSystemManagement.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
          CATMecModLiveUseItf \
	      CAAAdpUtilities \
	      CATPLMComponentInterfaces \
	      CATPLMIntegrationUse \
          CATObjectModelerBase \
          CATMathematics \
          CATMecModUseItf \
          KnowledgeItf \
	      CATPLMIdentificationAccess \
	      ObjectModelerSystem \ 
	      CAT3DPhysicalRepItf \
		  CAAV5V6MmrUtilities \
	      
#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \  
           CATMecModLiveUseItf \
           CATObjectModelerBase \ 
		   CATObjectSpecsModeler \
           CATMathematics \
           CATMecModUseItf \
           KnowledgeItf \
           CATGSMUseItf \
           CAAV5V6MmrUtilities \
		   CATGMModelInterfaces \ 
		   CATMecModInterfaces \
#endif
