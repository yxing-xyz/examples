objects := $(patsubst %.c,%.o,$(wildcard *.c))

C_FLAGS += -Wall -g
CC=gcc $(INCLUDES) $(C_FLAGS) -c

all: $(objects)
	cc -o main $(objects)

debug: clean ${objects}
	cc -g -o main $(objects)

.PHONY: clean

clean:
	rm -rf ${objects}
	rm -rf main