# copyright dassault systemes 2008
#======================================================================
# iMAKEFILE FOR MODULE CATPVRUserExit.m
#======================================================================
#
#  Sept 2009  CREATION: 
#======================================================================
#
# shared  library module 
#
BUILT_OBJECT_TYPE=SHARED  LIBRARY    
    
OS  =  COMMON  
LINK_WITH  =  JS0GROUP  JS0CRYPTEXIT  SystemUUID \
                       AD0XXBAS \
                       AS0STARTUP \
                       TstCATPDMBase\
                       ProductStructureItf \
                       CATPDMReconcileItfCPP \
		       CATPDMBaseItf

