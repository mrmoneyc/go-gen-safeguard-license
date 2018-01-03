copy ..\..\lib\psprolib.lib
copy ..\..\lib\psprolib.dll
gfortran -m32 -ffpe-summary=none -I ..\..\h -o Floating Floating.f psprolib.lib
gfortran -m32 -I ..\..\h -o Nodelocked Nodelocked.f psprolib.lib 
gfortran -m32 -I ..\..\h -o PASfloating PASfloating.f psprolib.lib 
gfortran -m32 -I ..\..\h -o PASnodelocked PASnodelocked.f psprolib.lib
gfortran -m32 -I ..\..\h -o ShowClient ShowClient.f psprolib.lib 
gfortran -m32 -I ..\..\h -o ShowServer ShowServer.f psprolib.lib 
gfortran -m32 -I ..\..\h -o ShowDetail ShowDetail.f psprolib.lib 
