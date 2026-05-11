# COPYRIGHT DASSAULT SYSTEMES 2001
#======================================================================
# Imakefile for module CAAEPstBFContInit.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH = CATObjectModelerBase  \
            CATObjectSpecsModeler \
            CATProductStructure1  \
            JS0GROUP              \
            CAAPstEduNavigFeatProv\
            CAAPstEduNavigExtProv \
	    CAAPstEduCtxMenuProv
