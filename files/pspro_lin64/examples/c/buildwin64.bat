cl /c /MT Floating.c
cl /c /MT Nodelocked.c
cl /c /MT PASfloating.c
cl /c /MT PASnodelocked.c
cl /c /MT ShowClient.c
cl /c /MT ShowServer.c
cl /c /MT ShowDetail.c
cl /c /MT Vendorid.c
cl /c /MT sgarc4.c

link Floating.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link Nodelocked.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link PASfloating.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link PASnodelocked.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link ShowClient.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link ShowServer.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link ShowDetail.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link Vendorid.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
link sgarc4.obj ..\..\lib\psprolib_mt.lib kernel32.lib netapi32.lib user32.lib libcmt.lib ws2_32.lib advapi32.lib libcmt.lib
