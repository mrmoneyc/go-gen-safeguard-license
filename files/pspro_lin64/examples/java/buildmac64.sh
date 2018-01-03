rm -f *.class

cp -r ../../java/com .
cp ../../java/libpsprolibjni_mac.jnilib .

javac Floating.java
javac Nodelocked.java
javac PASfloating.java
javac PASnodelocked.java
javac ShowClient.java
javac ShowServer.java
javac ShowDetail.java
