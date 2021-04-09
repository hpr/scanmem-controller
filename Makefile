all: scanmem-controller.so ScanmemController.class

run: ScanmemController.java
	java -Djava.library.path=. ScanmemController

scanmem-controller.so: scanmem-controller.c
	gcc -shared -o scanmem-controller.so scanmem-controller.c -I. -ldl -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC

ScanmemController.class: ScanmemController.java
	javac ScanmemController.java -h .