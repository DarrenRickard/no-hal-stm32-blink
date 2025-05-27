TARGET = main
STARTUP = ../Startup/startup_stm32f103c8tx.s

# Include directories
INC_DIRS = -I ../../Drivers/CMSIS/Include -I ../../Drivers/CMSIS/Device

# Compiler and tools
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
STFLASH = st-flash

# Compiler flags
CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -Werror -Wshadow -nostartfiles -nodefaultlibs -nostdlib -ffreestanding $(INC_DIRS)

# Linker script
LDSCRIPT = ../../STM32F103C8TX_FLASH.ld

# Flash start address
FLASH_ADDR = 0x8000000

# Object files
OBJ = $(TARGET).o
STARTUP_OBJ = $(STARTUP:.s=.o)

# Default build target
all: $(TARGET).bin

# Compile main.c
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile startup assembly
$(STARTUP_OBJ): $(STARTUP)
	$(CC) -mcpu=cortex-m3 -mthumb -c $< -o $@

# Link everything using arm-none-eabi-gcc
$(TARGET).elf: $(OBJ) $(STARTUP_OBJ)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) $^ -o $@

# Convert ELF to binary
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	echo "$@ built successfully!" 

# Flash target
flash: $(TARGET).bin
	$(STFLASH) write $< $(FLASH_ADDR)

# Clean build artifacts
clean:
	rm -f $(OBJ) $(STARTUP_OBJ) $(TARGET).elf $(TARGET).bin

