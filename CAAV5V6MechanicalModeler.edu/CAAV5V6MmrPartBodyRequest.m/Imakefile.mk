# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6MmrPartRequest.m
#======================================================================
#
BUILT_OBJECT_TYPE= LOAD MODULE

#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
           CATMecModLiveUseItf \
	       CATMecModUseItf \
           CATObjectModelerBase \
           ObjectModelerSystem \
	       CATGeometricObjects \
	       CATGMModelInterfaces \
	       CAAV5V6MmrUtilities \
		   CATPLMComponentInterfaces \

#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \
           CATMecModLiveUseItf \
	       CATMecModUseItf \
		   CATMecModInterfaces \
           CATObjectModelerBase \
           ObjectModelerSystem \
	       CATGeometricObjects \
	       CATGMModelInterfaces \
	       CATMecModInterfaces \
	       CAAV5V6MmrUtilities \

#endif
