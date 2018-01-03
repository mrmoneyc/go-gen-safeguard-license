import sys
import PSProlibProxy

#********************************************************************
#*
#* This example demonstrates the sgShowServer() function.
#* It retrieves information from the license server about
#* components that the server is serving up.
#*
#********************************************************************

# tell this program to use the floating license manager
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_FLOATING)

retVal = PSProlibProxy.sgConnect()

if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit()

while True:

   retVal,component,version,id,idtype,count,current,expires,certificate = PSProlibProxy.sgShowServer()
      
   if retVal == PSProlibProxy.SG_NO_MORE_SERVER_COMPONENTS:
      break

   print component,version,id,idtype,count,current,expires,certificate

retVal = PSProlibProxy.sgDisconnect()

sys.exit()
