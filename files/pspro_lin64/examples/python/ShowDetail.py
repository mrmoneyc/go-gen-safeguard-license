import sys
import PSProlibProxy

#********************************************************************
#*
#* This demonstrates one way how to query the license server for 
#* specific information about each connected client and what they
#* have checked out, such as:
#*
#* thread ID
#* socket file descriptor
#* IP address
#* Process ID (PID)
#* Process name (pathname to the remote process)
#* Username
#* Hostname
#* Component
#* Version
#* Count
#*
#*
#********************************************************************

servername = "localhost"

# tell this program to use the floating license manager
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_FLOATING)

retVal = PSProlibProxy.sgConnect()

if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit()

while True:

   retVal,thread_id,sockfd,ip,pid,process,user,host,component,version,count = PSProlibProxy.sgShowServerDetail()
      
   if retVal == PSProlibProxy.SG_NO_MORE_SERVER_DETAIL:
      break

   print thread_id,sockfd,ip,pid,process,user,host,component,version,count

retVal = PSProlibProxy.sgDisconnect()

sys.exit()
