# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAMmrCCDataExtensionUI.m
#======================================================================
#  Jan 2007  Creation:
#======================================================================
#
#ifdef LOCAL_DEFINITION_FOR_IID
#
#else
#
#endif
BUILT_OBJECT_TYPE = SHARED LIBRARY
#
LINK_WITH = CAAMmrCCDataExtension \
            CATObjectSpecsModeler \
            CATMechanicalModelerUI \
            MecModItfCPP\
            JS0FM \
            CATDialogEngine \
            CATViz \
            DI0PANV2\
            ON0MAIN CD0FRAME \
            JS0GROUP       
#
LOCAL_CCFLAGS= -DSPECDEBUG
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX


#
OS = SunOS
#
OS = Windows_NT

