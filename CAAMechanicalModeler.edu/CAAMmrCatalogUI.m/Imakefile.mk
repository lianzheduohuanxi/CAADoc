# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrCombinedCurveUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=JS0FM JS0GROUP              \
          CATApplicationFrame         \
          CATDialogEngine             \
          CATMechanicalCommands       \
          CATObjectSpecsModeler       \
          CATVisualization CATViz     \
          CATCclInterfaces            \   
          CATObjectModelerBase        \   
          DI0PANV2  CATInteractiveInterfaces                  
          
