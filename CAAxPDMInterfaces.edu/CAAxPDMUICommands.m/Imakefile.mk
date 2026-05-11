#COPYRIGHT Dassault Systemes 2006
#======================================================================
# Imakefile for module CAAxPDMUICommands.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 

LINK_WITH= JS0GROUP JS0FM \
         DI0PANV2 \
         CATApplicationFrame CATDialogEngine CATxPDMInterfaces \
		   CATInteractiveInterfaces CATObjectModelerBase CATMathematics CATMathStream \
		   AS0STARTUP CAAxPDMToolbar CATVisualization CATViz CAAxPDMDRMILB
