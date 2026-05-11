# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrSearchUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=JS0FM JS0GROUP              \
          CATApplicationFrame         \
          CATDialogEngine             \
          CATVisualization CATViz     \
          CATObjectModelerBase        \   
          KnowledgeItf        \   
          DI0PANV2  CATInteractiveInterfaces                  
          
