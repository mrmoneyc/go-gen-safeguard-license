import sys
import PSProlibProxy

#********************************************************************
#*
#* This sample demonstrates a real life scenario of using the Product
#* Activation Server for a typical client application.  It first checks
#* whether there is a paid license available, if there is, it will 
#* retrieve it.  If not, then it will attempt to obtain a demo license.
#* available and all criteria are met, then a demo license will be 
#* installed on the client computer next to this running executable.
#*
#* This example checks for a license called 'monitor' '5.0'.
#*
#* If you are testing this on your local host you won't need to change
#* the hostname in the two locations below.  If not, you will need to
#* change 'localhost' to either an IP address or Domain name.
#*
#* MySQL and the Prodcut Activation Server will need to be running,
#* and either of the 'paid_node' or 'demo_node' table records
#* will need to be updated to add the above component name, version, and
#* other information to enable this client app to get a license.  If you
#* use bin/create.sql to create the database and tables, these will be
#* populated for you.
#*
#********************************************************************/

email =       "bob@example.com"
component =   "monitor"
version =     "5.0"
licensefile = "pas-nodelocked.lic"
company =     "localhost"


# make this application use an external license file
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_EXTERNAL)

print 'Checking for a license to run',component,'.'

# Are we already licensed?  
retVal = PSProlibProxy.sgAuthorized(licensefile,component,version)
if retVal != PSProlibProxy.SG_AUTHORIZED:
   print 'Checking for a paid license to run',component,'.'

   # we are going to use the email address as the unique paid customer identifier
   # it can be anything.  But the email address "bob@example.com" must be in the
   # cust column of the paid_node table to identify the customer.

   retVal,serverline,componentline = PSProlibProxy.sgPaActivate(company, 29775, PSProlibProxy.SG_ACTIVATE_PAID_NODE, email, component, version, email)

   if retVal != PSProlibProxy.SG_SUCCESS & retVal != PSProlibProxy.SG_AUTHORIZED:
       print 'Checking for a demo license to run',component,'.'
       retVal,serverline,componentline = PSProlibProxy.sgPaActivate(company, 29775, PSProlibProxy.SG_ACTIVATE_DEMO_NODE, '', component, version, email)
 
       if retVal != PSProlibProxy.SG_SUCCESS & retVal != PSProlibProxy.SG_AUTHORIZED:
          retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
          print 'Problem with the activation server:',szMessage
          sys.exit();
       else:
          # create the license file
          retVal = PSProlibProxy.sgEnableComponentLine(licensefile,componentline)
          if retVal != PSProlibProxy.SG_SUCCESS:
             retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
             print 'Problem installing the license:',szMessage
             sys.exit();
   else:
       # create the license file
       retVal = PSProlibProxy.sgEnableComponentLine(licensefile,componentline)
       if retVal != PSProlibProxy.SG_SUCCESS:
          retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
          print 'Problem installing the license:',szMessage
          sys.exit();

# check once again in case the PAS sent us a new license file
retVal = PSProlibProxy.sgAuthorized(licensefile,component,version)
if retVal != PSProlibProxy.SG_SUCCESS:
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit()
    
retVal,daysRemaining = PSProlibProxy.sgExpireDays(licensefile,component,version)

print 'Authorized to run the demo version of',component,'for',daysRemaining,'more days.'

sys.exit();
