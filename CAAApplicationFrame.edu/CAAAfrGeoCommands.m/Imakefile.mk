# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeoCommands.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \
            CATVisualization CATViz  \
            CATMathematics        \
            JS0FM JS0GROUP        \
            DI0PANV2              \
            CAAAfrCustCommandHdrModel CAASysGeoModelInf
