# Frameworks d'interface CGM
cgm_itf_fw="|GMAdvancedOperatorsInterfaces|GMModelInterfaces|GMOperatorsInterfaces|SGMOperatorsInterfaces|CDMOperatorsInterfaces|ICMOperatorTopInterfaces"

# Frameworks utilisables par les partenaires CAA
basic_fw="|AdvancedMathematics|CATMathStream|CATSubdivisionObjects|GeometricObjects|GeometricObjectsCGM|Mathematics|$cgm_itf_fw"

# Frameworks utilisables par les applis DS
partial_itf_fw="|CATSubdivisionOperators|Tessellation|" # -> These frameworks must remain in IdentityCard.h at DS
