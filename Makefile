MCU := atmega168
TARGET := TalkyPump

CC := avr-gcc
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
SIZE := avr-size

SRCS := main.c gsm.c usart.c

COMMON_CFLAGS := \
	-mmcu=$(MCU) \
	-fcommon \
	-std=gnu99 \
	-x c \
	-funsigned-char \
	-funsigned-bitfields \
	-ffunction-sections \
	-fdata-sections \
	-fpack-struct \
	-fshort-enums \
	-Wall \
	-MMD \
	-MP

COMMON_LDFLAGS := \
	-mmcu=$(MCU) \
	-Wl,--gc-sections \
	-Wl,--start-group \
	-Wl,-lm \
	-Wl,--end-group

BUILD_DIR := build

.PHONY: all debug release clean size

all: debug release

debug: CFLAGS := $(COMMON_CFLAGS) -DDEBUG -O1 -g2
debug: OUT_DIR := $(BUILD_DIR)/wsl-debug
debug: $(BUILD_DIR)/wsl-debug/$(TARGET).hex $(BUILD_DIR)/wsl-debug/$(TARGET).eep $(BUILD_DIR)/wsl-debug/$(TARGET).srec $(BUILD_DIR)/wsl-debug/$(TARGET).lss
	$(SIZE) $(BUILD_DIR)/wsl-debug/$(TARGET).elf | tee $(BUILD_DIR)/wsl-debug/size.txt

release: CFLAGS := $(COMMON_CFLAGS) -DNDEBUG -Os
release: OUT_DIR := $(BUILD_DIR)/wsl-release
release: $(BUILD_DIR)/wsl-release/$(TARGET).hex $(BUILD_DIR)/wsl-release/$(TARGET).eep $(BUILD_DIR)/wsl-release/$(TARGET).srec $(BUILD_DIR)/wsl-release/$(TARGET).lss
	$(SIZE) $(BUILD_DIR)/wsl-release/$(TARGET).elf | tee $(BUILD_DIR)/wsl-release/size.txt

$(BUILD_DIR)/wsl-debug/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MF "$(@:.o=.d)" -MT "$@" -c -o "$@" "$<"

$(BUILD_DIR)/wsl-release/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MF "$(@:.o=.d)" -MT "$@" -c -o "$@" "$<"

$(BUILD_DIR)/wsl-debug/$(TARGET).elf: $(SRCS:%.c=$(BUILD_DIR)/wsl-debug/%.o)
	$(CC) -o "$@" $^ $(COMMON_LDFLAGS) -Wl,-Map="$(BUILD_DIR)/wsl-debug/$(TARGET).map"

$(BUILD_DIR)/wsl-release/$(TARGET).elf: $(SRCS:%.c=$(BUILD_DIR)/wsl-release/%.o)
	$(CC) -o "$@" $^ $(COMMON_LDFLAGS) -Wl,-Map="$(BUILD_DIR)/wsl-release/$(TARGET).map"

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "$<" "$@"

%.eep: %.elf
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "$<" "$@" || true

%.srec: %.elf
	$(OBJCOPY) -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "$<" "$@"

%.lss: %.elf
	$(OBJDUMP) -h -S "$<" > "$@"

size: all

clean:
	rm -rf $(BUILD_DIR)

-include $(BUILD_DIR)/wsl-debug/*.d
-include $(BUILD_DIR)/wsl-release/*.d