These examples demonstrate the following:

* (Nodelocked)    Node-locked licensing
* (Floating)      Floating (Concurrent) licensing
* (PASnodelocked) Product Activation Server (Activation over the Internet)
* (PASfloating)   Product Activation Server (Activation over the Internet)
* (Vendorid)      Vendor defined Host ID (Advanced) (only for C examples)
* (ShowClient)    Querying the license server for client license information.
* (ShowServer)    Querying the license server for server license information.
* (ShowDetail)    Querying the license server for detailed license information.

==========================================================

REQUIREMENTS:

The examples are pre-built for each SafeGuard LM version

You will need to run the generatelicenses.sh or generatelicenses.bat
scripts to generate the approproate licenses for your computer.

To rebuild the examples, you will need the following:

For Linux / OS X, you need the gcc compiler installed

For Windows, you need Visual Studio C/C++ installed, but MOST
importantly, you will need to run the vcvars.bat file
found in the Visual Studio installation folder.  This
batch file sets up the environment for you to be able
to compile and link from a CMD command prompt.

==========================================================

If you wish to test the Floating example which uses
the floating license manager, you will need to start the 
license manager on the machine you ran the scripts on.

To start the license manager quickly, you can just open 
another terminal/cmd window and from this directory and
type:

Linux / OS X:

../../bin/sglmserver float.lic

Windows:

..\..\bin\sglmserver float.lic

Then from the original window, you can run the floating example

Linux / OS X, UNIX:

./Floating

Windows:

.\Floating

You will see output from the license server such as:

2016/01/07 17:48:02 CONNECT: USER: joe HOST: xyz  IP: 192.168.1.111
2016/01/07 17:48:02 OUT: monitor VERSION: 5.0 USER: joe HOST: xyz REMAINING: 9
2016/01/07 17:48:07 IN: monitor VERSION: 5.0 USER: joe HOST: xyz REMAINING: 10
2016/01/07 17:48:07 DISCONNECT: USER: joe HOST: xyz IP: 192.168.1.111

==========================================================

While you have the floating license server running you might want
to run the three ShowClient, ShowServer and ShowDetail examples.  
They show information about various client and license server status.
See the source code for details on what is displayed.

You will want to run the Floating example in a separate window and
keep the license checked out while you run these.

==========================================================

To demonstrate either the PASfloating or PASnodelocked apps that
get a license from the Product Activation Server (PAS), you need
to have followed the install instructions in doc/PASInstallGuide.pdf

Don't change anything in the bin/control.txt file.  Just follow 
the instructions from start to finish.  It should only take about 
20 - 30 minutes.

Once MySQL is installed, start it only after following the instructions
to source the bin/create.sql script which creates the Database and
inserts some sample records for these example programs.

Once MySQL is running you then can start the PAS by running it in
a separate terminal windows just like the license server.  In real
life, you would install it as a Windows Service or Daemon on Linux / 
OS X.

Linux / OS X:

../../bin/sgpaserver ../../bin/control.txt

Windows:

..\..\bin\sgpaserver ..\..\bin\control.txt

Then run the example PASfloating and PASnodelocked applications.
You will see that it first attempts to acqure a paid license then
when that doesn't exist, it requests a demo license.  This logic
is controlled in the example code only.  You can implement your
logic however you wish.

You will see output from the PAS such as:

 2016/01/07 18:03:24 Server starting on localhost port 29775
 Ready...
 2016/01/07 18:03:44 CONNECT: USER: joe HOST: xyz IP: 127.0.0.1
 2016/01/07 18:03:44 REQUESTING: paid-node component 'monitor', version '5.0', os 'mac64'
 2016/01/07 18:03:44 MySQL: Connecting...
 2016/01/07 18:03:44 MySQL: Connected...
 2016/01/07 18:03:44 NONEXIST: request for component 'monitor', version '5.0', os 'mac64'
 2016/01/07 18:03:44 DISCONNECT: USER: joe HOST: xyz
 2016/01/07 18:03:44 CONNECT: USER: joe HOST: xyz IP: 127.0.0.1
 2016/01/07 18:03:44 REQUESTING: demo-node component 'monitor', version '5.0', os 'mac64'
 2016/01/07 18:03:44 MySQL: Connecting...
 2016/01/07 18:03:44 MySQL: Connected...
 2016/01/07 18:03:44 ISSUING: demo-node license(s) for component 'monitor', version '5.0', os 'mac64'
 2016/01/07 18:03:44 LICENSE: NAME=monitor VERS=5.0 ID=any-id IDTYPE=any EXPIRES=3-feb-2016 CERT=06aa45f1282df0b2039f0861c1
 2016/01/07 18:03:44 DISCONNECT: USER: joe HOST: xyz


