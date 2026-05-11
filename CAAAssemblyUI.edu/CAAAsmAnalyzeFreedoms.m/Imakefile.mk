# COPYRIGHT DASSAULT SYSTEMES 2004

BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH = CATObjectSpecsModeler \
            CATObjectModelerBase \
            CATProductStructure1 \
			CATConstraintModeler \
            CATAssemblyInterfaces\
            NS0SI18N \
            CATConstraintModelerItf \
CATMecModInterfaces \
MF0DimInt \


LOCAL_CCFLAGS=  -DSPECDEBUG

