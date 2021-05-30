UNAME_S = $(shell uname -s)
$(info $Building for [${UNAME_S}])

CC=clang
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
CFLAGS += -isystem lib/glfw/include -isystem lib/glad/include -isystem lib/cglm/include
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a lib/cglm/libcglm.a -lm

ifeq ($(UNAME_S), Darwin)
	CFLAGS += -F /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread
endif

SRC = $(wildcard src/*.c src/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs libs main

libs:
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/glfw && cmake . && make

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/main

main: $(OBJ)
	$(CC) -o $(BIN)/main $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
