# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAADegGeoCommands.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH=  CATApplicationFrame  \
            DI0PANV2             \
            CATDialogEngine      \
            JS0GROUP JS0FM       \
            CATVisualization  CATViz   \
            CAASysGeoModelInf  CAAVisModelForRep CAAAfrCustCommandHdrModel \
            CAAVisWireBoxComp CATObjectModelerBase CATMathematics

