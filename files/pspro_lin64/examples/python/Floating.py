
#*******************************************************************************************
#*
#* Check out a 'monitor' license, version '5.0' from the license server
#*
#* The server will have to be running and serving this license.
#*
#*******************************************************************************************

import sys
import PSProlibProxy

#*********************************************************************
#*
#* These functions deal with the condition when the connection to the 
#* LM has been lost.  If you don't define these, then default handlers 
#* are instaled which look just like these !!
#*
#* To see this in action...
#*
#* Start the license manager (first run generatelicenses.sh/bat)
#*
#* ../../bin/sglmserver float.lic (or for Windows) ..\..\bin\sglmserver float.lic
#*
#* from another Terminal window or CMD prompt run Floating.py
#*
#* python Floating.py
#*
#* Leave it running (don't press return to end the program)
#*
#* Then CTL-C the license server (stop it).  And wait 1 minute or two minutes.
#* After you see the 'Lost...' messages, restart the license server again and
#* wait another minute to see 'Floating.py' 'Reconnect....'
#*
#* In real life, you will probably want to do more with these routines. But it 
#* is a good start.
#*
#*********************************************************************


def recon(server,retries,count):
        print
	print 'Lost connection with server',server,'attempting to reconnect',retries,'of',count,'...'

def recon_complete(server,retries):
        print
	print 'Reconnected with server',server,'after',retries,'attempts ...'

def recon_checkout_fail(server,component,version):
        print
        print 'Unable to check out license',component,', version',version,'from server',server,'...'

def recon_exit(server,retries):
        print
        print 'Maximum reconnect attempts of',retries,'to server',server,'...'

#*********************************************************************

# beginning of the main application

# make this application use a floating license server
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_LICENSETYPE,PSProlibProxy.SG_LICENSETYPE_FLOATING)

# set the LM callbacks for when the connection to the license server
# is lost for any reason.

# check every 1 minute (default is every 2 minutes)
PSProlibProxy.sgSetAttrInt(PSProlibProxy.SG_ATTR_RETRY_INTERVAL,1)

PSProlibProxy.sgSetAttrFnP(PSProlibProxy.SG_ATTR_VENDOR_RECONNECT,recon)
PSProlibProxy.sgSetAttrFnP(PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_COMPLETE,recon_complete)
PSProlibProxy.sgSetAttrFnP(PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL,recon_checkout_fail)
PSProlibProxy.sgSetAttrFnP(PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_EXIT,recon_exit)

if PSProlibProxy.sgCheckout('monitor','5.0') != PSProlibProxy.SG_SUCCESS:
   # tell the user they are not licensed for the application and exit gracefully
   retVal,szMessage = PSProlibProxy.sgGetLastErrorString()
   print szMessage
   sys.exit()

print 'Running the monitor application....'

print
nb = raw_input('Press return to release the license....')

# app is finished, check in the license.  NOTE:  it is not necessary to do this
# as the license server will detect the process terminating and do it for you.

PSProlibProxy.sgCheckin('monitor','5.0')

sys.exit()
