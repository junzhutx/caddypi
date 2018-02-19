CC        := g++
LD        := g++

MODULES   := ui fonts epd images
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

CORE_PCH_NAME := core.h
CORE_PCH  := $(CORE_PCH_NAME).gch

LIBS      := -lboost_system -lpthread -lboost_thread -lwiringPi
CFLAGS    := -Wall -std=c++14

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp $(CORE_PCH)
	$(CC) $(CFLAGS) -I. $(INCLUDES) -include $(CORE_PCH_NAME) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/caddypi

build/caddypi: $(OBJ)
	$(LD) $^ $(LIBS) -o $@

$(CORE_PCH):
	$(CC) $(CFLAGS) -I /usr/include -x c++-header $(CORE_PCH_NAME)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
