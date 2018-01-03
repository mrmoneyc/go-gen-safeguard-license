erase *.class

xcopy /E/I ..\..\java\com com
copy ..\..\java\psprolibjni_win.dll .

javac Floating.java
javac Nodelocked.java
javac PASfloating.java
javac PASnodelocked.java
javac ShowClient.java
javac ShowServer.java
javac ShowDetail.java
