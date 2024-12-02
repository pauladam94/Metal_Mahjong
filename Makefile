CC = clang
BUILD_DIR ?= ./build
NAME = mahjong_agreg

VPATH = ./client:./data:./logic:./visuals:./website:./game:$(BUILD_DIR)

RAYLIB_DIR ?= ./raylib/src/

# This allows the preprocessor to also generate the dependencies in the *.d files
CPPFLAGS += -MP -MD

CFLAGS = -Wall -Wextra -I$(RAYLIB_DIR) -lm
DEBUGFLAGS = -g3 -fsanitize=address
# RELEASEFLAGS = -flto -O3 -DNDEBUG
RELEASEFLAGS = -O3 -DNDEBUG

MODE ?= RELEASE# Default is Release

# Raylib has some warnings that we don’t want to see when compiling in debug
CUSTOM_CFLAGS = -Wno-unused-result -Wno-unused-but-set-variable

# Allow usage of mold linker for faster build time, default to false
USE_MOLD_LINKER ?= FALSE
ifeq ($(USE_MOLD_LINKER), TRUE)
	LDFLAGS += -fuse-ld=mold
endif

ifeq ($(MODE),DEBUG)
	CFLAGS += $(DEBUGFLAGS)
	CUSTOM_CFLAGS += $(DEBUGFLAGS)
else
	CFLAGS += $(RELEASEFLAGS)
	CUSTOM_CFLAGS += $(RELEASEFLAGS)
endif

default: $(NAME)

# for raylib
RAYLIB_RELEASE_PATH = $(CURDIR)/$(BUILD_DIR)
LIBRAYLIB = $(BUILD_DIR)/libraylib.a
export CUSTOM_CFLAGS
export RAYLIB_RELEASE_PATH

SOURCES = $(notdir $(wildcard ./client/*.c ./logic/*.c ./visuals/*.c ./game/*.c))
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.c=%.o))
MAKEFILES = $(OBJECTS:%.o=%.d)

# We include the autogenerated dependencies
-include $(MAKEFILES)

$(NAME): $(OBJECTS) $(LIBRAYLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

raylib: $(LIBRAYLIB)

$(LIBRAYLIB):
	@mkdir -p $(BUILD_DIR)
	$(MAKE) -C $(RAYLIB_DIR)

TEST_SOURCE = $(wildcard test/*.c)
TEST_EXECUTABLE = $(TEST_SOURCE:%.c=%.x)

test: $(TEST_EXECUTABLE)
	@for executable in $(TEST_EXECUTABLE); do \
		./$$executable ;\
	done

test/%.x: test/%.c $(OBJECTS) $(LIBRAYLIB)
	$(CC) $(CFLAGS) -o $@ $(word 1, $^) $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS)) $(LIBRAYLIB)

cleanall : clean clean_raylib

clean:
	$(RM) $(OBJECTS)
	$(RM) $(MAKEFILES)
	$(RM) $(LIBRAYLIB)
	$(RM) --dir $(BUILD_DIR)
	$(RM) $(NAME)
	$(RM) test/*.x

clean_raylib:
	$(MAKE) clean -C $(RAYLIB_DIR)

.PHONY: clean cleanall clean_raylib
