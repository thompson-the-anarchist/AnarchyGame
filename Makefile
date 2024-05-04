CFLAGS = -std=c99 -ggdb
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
OBJECTS = main.o draw.o init.o shutdown.o update.o

all: anarchy

anarchy: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o anarchy $(LIBS)

clean:
	rm anarchy *.o

run: anarchy
	./anarchy

