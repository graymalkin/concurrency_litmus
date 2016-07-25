CC = musl-gcc
CC_FLAGS = -c -g -Wall -pedantic -std=c11
CC_FLAGS += $(CPU) -fno-common

LD = musl-gcc
LD_FLAGS =
LIBRARY_PATHS =
LIBRARIES = -lc -lpthread

BINARY_NAME = c_litmus

FILES = src/main.o src/sb.o
INCLUDE = -I./lib

COLOR_GREEN =
COLOR_RESET =

all: $(FILES) $(BINARY_NAME) clean

.c.o: $(FILES)
	@$(CC) $(CC_FLAGS) $(INCLUDE) -o $@ $<
	@echo "[$(COLOR_GREEN)CC$(COLOR_RESET)]  $@"

$(BINARY_NAME): $(FILES)
	@echo "[$(COLOR_GREEN)LD$(COLOR_RESET)]  $@"
	@$(LD) $(LD_FLAGS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

clean:
	rm -f $(FILES)

.PHONY: all
