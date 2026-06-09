BUILD_X32 = build/cX32
BUILD_X64 = build/cX64
SOURCES := $(shell find . -name "*.c" -not -path "./build/*")

CFLAGS = -ffreestanding -O2 -Iinclude -integrated-as

all: x32 x64

x32: $(BUILD_X32) $(addprefix $(BUILD_X32)/, $(notdir $(SOURCES:.c=_x32.o)))
x64: $(BUILD_X64) $(addprefix $(BUILD_X64)/, $(notdir $(SOURCES:.c=_x64.o)))

$(BUILD_X32) $(BUILD_X64):
	mkdir -p $@

$(BUILD_X32)/%_x32.o: 
	@src=$$(find . -name "$$(basename $@ _x32.o).c"); \
	echo "Building (32-bit): $$src -> $@"; \
	clang --target=i686-elf -march=i686 -m32 $(CFLAGS) -c $$src -o $@

$(BUILD_X64)/%_x64.o: 
	@src=$$(find . -name "$$(basename $@ _x64.o).c"); \
	echo "Building (64-bit): $$src -> $@"; \
	clang --target=x86_64-elf -march=x86-64 -m64 $(CFLAGS) -c $$src -o $@


