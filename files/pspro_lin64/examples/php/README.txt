These examples demonstrate the following:

* (Nodelocked)    Node-locked licensing
* (Floating)      Floating (Concurrent) licensing
* (PASnodelocked) Product Activation Server (Activation over the Internet)
* (PASfloating)   Product Activation Server (Activation over the Internet)
* (Vendorid)      Vendor defined Host ID (Advanced) (Only for C examples)
* (ShowClient)    Querying the license server for client license information.
* (ShowServer)    Querying the license server for server license information.
* (ShowDetail)    Querying the license server for detailed license information.

==========================================================

REQUIREMENTS:

You will need to run the generatelicenses.sh script to generate 
the approproate licenses for your computer.

For Linux / OS X , you need php installed.  We suggest you
install version 5.6 from one of these mirror sites if you
do not already have php installed.  To see what you have
installed from a terminal window, type:

php -v

Here is where to get php if you do not have it installed

http://php.net/get/php-5.6.17.tar.gz/from/a/mirror

Download the .gz version.  Then once downlaoded run gunzip
to unzip it, and then tar xvf on the resulting .tar file.
cd to the php folder and type:

./configure

When that is done, type:

make

then after building it, type:

sudo make install

Once that is complete, type:

php -v

and you should get something like:

PHP 5.6.17 (cli) (built: Jan 14 2016 15:17:57) 
Copyright (c) 1997-2015 The PHP Group
Zend Engine v2.6.0, Copyright (c) 1998-2015 Zend Technologies


Before running php from a terminal window you must first copy 
the PHP version of psprolib.so to the /usr/lib/php/extensions
directory after installing php on your system.

run examples/php/phpinfo.php with the following commands to find
out where the extensions directory is located on your system
the psprolib.so is found under pspro_xxxnn/php/psprolib.so

php phpinfo.php | grep extension_dir
php phpinfo.php | grep enable_dl

to find the php.ini file to edit if you need to change enable_dl = Off
to enable_dl = On

php phpinfo.php | grep php.ini

The line:

enable_dl = Off

should be changed to:

enable_dl = On



==========================================================

If you wish to test the Floating example which uses
the floating license manager, you will need to start the 
license manager on the machine you ran the scripts on.

To start the license manager quickly, you can just open 
another terminal/cmd window and from this directory and
type:

Linux / OS X:

../../bin/sglmserver float.lic

Then from the original window, you can run the floating example

Linux / OS X:

php Floating.php

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
life, you would install it as a Daemon on Linux / OS X.

Linux / OS X:

../../bin/sgpaserver ../../bin/control.txt

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


