CC        := g++
LD        := g++

MODULES   := ui fonts epd images
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR)) -I /usr/include

CORE_PCH_NAME := core.h
CORE_PCH  := $(CORE_PCH_NAME).gch

LIBS      := -lwiringPi
CFLAGS    := -Wall -std=c++14

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: CORE_PCH %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/caddypi

build/caddypi: $(OBJ)
	$(LD) $^ $(LIBS) -o $@

$(CORE_PCH):
	$(CC) $(CFLAGS) -x c++-header $(CORE_PCH_FILENAME)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
