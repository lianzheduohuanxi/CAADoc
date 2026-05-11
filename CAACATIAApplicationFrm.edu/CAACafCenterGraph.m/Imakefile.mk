# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrSearchUI.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=JS0FM JS0GROUP              \
          CATIAApplicationFrame       \
          CATApplicationFrame         \
          CATDialogEngine             \
          CATVisualization CATViz     \
          CATObjectModelerBase        \     
          DI0PANV2              
          
