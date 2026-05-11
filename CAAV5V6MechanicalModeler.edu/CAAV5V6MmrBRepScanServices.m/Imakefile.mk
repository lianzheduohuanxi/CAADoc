#
# COPYRIGHT DASSAULT SYSTEMES 2012
#
#======================================================================
# Imakefile for module CAAV5V6MmrBRepScanServices.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
           CAAAdpUtilities \
           ObjectModelerSystem \ 
           CATObjectModelerBase \
           CATProductStructureInterfaces \
           CATMecModLiveUseItf \
           CATMecModUseItf \
           CATPLMIntegrationAccess \
           PLMPSISessionInterfaces \
           CATPLMComponentInterfaces \
           CAAV5V6MmrUtilities \
           
#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
            CATObjectModelerBase \
			CATObjectSpecsModeler \
            CATMecModUseItf \
            CATMecModLiveUseItf \
			CAAV5V6MmrUtilities \
			CATMecModInterfaces \ 
			CATMechanicalModeler \
			CATProductStructure1 \          
           
#endif          
           

