
#*******************************************************************************************
#*
##* Check for a node-locked "monitor" license, version "5.0"
#*
#*******************************************************************************************/


import sys
import PSProlibProxy

# make this application use an external license file
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_EXTERNAL);

# !!!!!!!!!!!!!!!!!!!!!!!! EXTREMELY IMPORTANT !!!!!!!!!!!!!!!!!!!!!!
# If you look at Nodelocked.c in examples/c you will notice that the license filename
# begins with @  in the sgAuthorized() call.   This tells the SafeGuard software the 
# license file "monitor.lic" is side-by-side to the executable accessing it.  For the 
# C example, this works great so you dont have to build a pathname to the license file 
# in your software.  However this does not work well for Java, Python and other language 
# interfaces, because the executable is actually the "java" binary which is typically 
# /usr/bin/java.  Or for Python, /usr/local/bin/python.  So if you use the @ sign to 
# find your license file in a java app, it will expect the monitor.lic license file is 
# /usr/bin/monitor.lic or /usr/local/bin/monitor.lic (NOT GOOD!)
# So you will have to find your license file some other way. In the case below, it will look
# in the current working directory.

if PSProlibProxy.sgAuthorized("monitor.lic","monitor","5.0") != PSProlibProxy.SG_AUTHORIZED:
   # tell the user they are not licensed for the application and exit gracefully
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit();

retVal,daysRemaining = PSProlibProxy.sgExpireDays("monitor.lic","monitor","5.0")

print 'Enabling the monitor functionality for',daysRemaining,'days....'

print 'Running the monitor application....'
