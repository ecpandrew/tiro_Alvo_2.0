CPP = g++
OPTS = -I "irrklang/include" -L "/usr/lib" irrklang/bin/linux-gcc-64/libIrrKlang.so -pthread

all:
	$(CPP) main.cpp -o example -lGL -lGLU -lGLEW -lglut 





clean:
	rm example
