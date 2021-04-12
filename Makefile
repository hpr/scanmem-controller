all: scanmem-controller libscanmem-pipe.so ScanmemController.class

run: ScanmemController.java
	java -Djava.library.path=. ScanmemController

scanmem-controller: scanmem-controller.c
	gcc -o scanmem-controller scanmem-controller.c -I. -ldl -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC

libscanmem-pipe.so: scanmem-pipe.c
	gcc -shared -o libscanmem-pipe.so scanmem-pipe.c -I. -ldl -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC

ScanmemController.class: ScanmemController.java
	javac ScanmemController.java -h .