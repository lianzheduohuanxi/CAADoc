# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAACafEltToolsOptions.m
#======================================================================
# 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH=JS0FM JS0GROUP \
          DI0PANV2  CATDlgStandard \
          CATIAApplicationFrame \ 
          CAACafCtrlToolsOptions \ 
          CATInteractiveInterfaces \ 
          CATObjectModelerBase 
		
