# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAMmrCCDataExtension.m
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
LINK_WITH = \
            JS0GROUP \
            \
            CATMechanicalModeler\
            CATObjectModelerBase\          
            \
            ObjectModeler\
            SpecsModeler \
            \
            CATTopologicalObjects BODYNOPE\
            KnowledgeItf\
            \
            CATVisualization\
            CATMathematics
                      
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


#INSERTION ZONE NOT FOUND, MOVE AND APPEND THIS VARIABLE IN YOUR LINK STATEMENT
#LINK_WITH = ... $(WIZARD_LINK_MODULES) ...
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =  \
JS0GROUP JS0FM JS0GROUP CATMmrApplicativeFeaturesUUID 
# END WIZARD EDITION ZONE
