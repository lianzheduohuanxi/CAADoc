# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAMmrMultiMeasureAndMeasureSetUI.m
#======================================================================
#  Jan 2007  Creation:
#======================================================================
BUILT_OBJECT_TYPE = SHARED LIBRARY
#
LINK_WITH = CAAMmrMultiMeasureAndMeasureSet \
            CATObjectSpecsModeler \
            CATMechanicalModelerUI \
            MecModItfCPP\
            JS0FM \
            CD0SHOW \
            CATDialogEngine \
            CATViz \
            CATVisualization \
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
