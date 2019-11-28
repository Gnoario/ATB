# My first makefile
 
all: run

ConsultOracle.class: ConsultOracle.java
	javac \
	-cp ".:./java_files/jars/jpl.jar" \
	ConsultOracle.java

 atb: main.c Ataque.hs player.c monsters.c score.c history.c guilda.c
	ghc -c -O Ataque.hs
	ghc --make -no-hs-main -optc-O main.c -ljvm player.c monsters.c score.c history.c guilda.c Ataque -o atb \
	-I/usr/lib/jvm/java-8-openjdk-amd64/include \
	-I/usr/lib/jvm/java-8-openjdk-amd64/include/linux \
	-L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server \
	-lpthread

run: ConsultOracle.class atb
	./atb

clean:
	rm -rf *.o *~ atb