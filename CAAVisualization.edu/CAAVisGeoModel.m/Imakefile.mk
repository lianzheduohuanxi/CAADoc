# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAVisGeoModel.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=CATVisualization CATViz CATMathematics JS0GROUP CAASysGeoModelInf\
            CAAVisGeoModelInt
