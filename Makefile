
OUTPUT=./bin/minestorm
CFLAGS=-Wall -Werror -O0 -g -MMD
LDLIBS=-lSDL2 -lm -lSDL2_ttf
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

all: $(OUTPUT)

-include $(OBJS:.o=.d)

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

$(OUTPUT): $(OBJS)
	gcc $^ $(LDLIBS) -o $@

clean:
	rm -rf $(OBJS) $(OBJS:.o=.d) $(OUTPUT)
