import sys
import PSProlibProxy

#********************************************************************
#*
#* This example demonstrates the sgShowClient() function.
#* It retrieves information about what the current process
#* has checked out.
#*
#********************************************************************

# tell this program to use the floating license manager
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_FLOATING)

retVal = PSProlibProxy.sgCheckout('monitor','5.0');
if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit()

# IMPORTANT:  Even thought the version for 'widget' is 6.0 in the license file
# if we check out an earlier version and only a 6.0 license is available it will
# consume one of the 6.0 licenses

retVal = PSProlibProxy.sgCheckout('widget','5.0');
if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit();

# IMPORTANT!!  if you check out the same component again, the count will increment
retVal = PSProlibProxy.sgCheckout('widget','5.0');
if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString(szMessage)
   print szMessage
   sys.exit()

      
while True:

   retVal,serverhost,clienthost,user,component,version,count = PSProlibProxy.sgShowClient()
   if retVal == PSProlibProxy.SG_NO_MORE_CLIENT_COMPONENTS: 
      break

   print serverhost,clienthost,user,component,version,count

retVal = PSProlibProxy.sgCheckin('monitor','5.0')

# NOTE:  Even if you don't check-in the second 'widget', it will be
# returned to the license pool when the process exits.

retVal = PSProlibProxy.sgCheckin('widget','5.0')

sys.exit()
