############################################################
############################################################
#####
#####		Provide Backward Compatibility
#####
#####		%W%	%Y%	%G%
#####
############################################################
############################################################

define(m4COMPAT, %I%)

include(berkhosts.m4)

#####################################################
#  General code to convert back to old style names  #
#####################################################
S5

R$+@$+.LOCAL		$2:$1				u@h.LOCAL => h:u
R$+@$+.CC		$2:$1				u@h.CC => h:u
R$+@$=Z			$@$2:$1				u@bhost => h:u
R$+@$-.UUCP		$2!$1				u@host.UUCP => host!u
R$+@$+.ARPA		$1@$2				u@host.ARPA => u@host
