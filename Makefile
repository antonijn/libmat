CC = cc
CFLAGS = -c -Iinclude -std=c90 -pedantic-errors

TARGET = libmat.a

OBJECTS = src/mat.o src/vec.o src/misc.o

release: CFLAGS += -DNDEBUG -O2
debug: CFLAGS += -g

release debug: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

