# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrCombinedCurveUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH= CATCclInterfaces \
           CATVizBase \
           CATVisualization \
           CATObjectModelerBase \
           CATApplicationFrame \
           CATMecModInterfaces \
           CATConstraintModelerItf \
           CATMechanicalModeler \
           JS0FM                       \
           JS0GROUP 
