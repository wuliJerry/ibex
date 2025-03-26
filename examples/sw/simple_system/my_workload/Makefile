# Makefile for building my_workload in ibex/examples/sw/simple_system/my_workload
# Based on hello_test and common.mk from Ibex repository

# Program name (source file will be my_workload.c)
PROGRAM = my_workload

# Directory setup
PROGRAM_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
COMMON_DIR := $(PROGRAM_DIR)/../common

# Source files
COMMON_SRCS = $(wildcard $(COMMON_DIR)/*.c)
PROGRAM_C = $(PROGRAM).c
EXTRA_SRCS =  # Add any additional .S or .c files here if needed (e.g., extra.S)
SRCS = $(COMMON_SRCS) $(PROGRAM_C) $(EXTRA_SRCS)

# Architecture (RV32IMC with Zicsr extension for control/status registers)
ARCH = rv32imc_zicsr

# Toolchain setup
CC = riscv32-unknown-elf-gcc
CROSS_COMPILE = $(patsubst %-gcc,%-,$(CC))
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# Paths to linker script and CRT (startup code)
LINKER_SCRIPT = $(COMMON_DIR)/link.ld
CRT = $(COMMON_DIR)/crt0.S

# Compiler flags
CFLAGS = -march=$(ARCH) -mabi=ilp32 -static -mcmodel=medany -Wall -g -Os \
         -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding
INCS = -I$(COMMON_DIR)

# Object files and dependencies
C_SRCS = $(filter %.c, $(SRCS))
ASM_SRCS = $(filter %.S, $(SRCS))
OBJS = $(C_SRCS:.c=.o) $(ASM_SRCS:.S=.o) $(CRT:.S=.o)
DEPS = $(OBJS:.o=.d)

# Output files
OUTFILES = $(PROGRAM).elf $(PROGRAM).vmem $(PROGRAM).bin

# Default target
all: $(OUTFILES)

# Link the ELF file
$(PROGRAM).elf: $(OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) -T $(LINKER_SCRIPT) $(OBJS) -o $@

# Generate disassembly (optional)
.PHONY: disassemble
disassemble: $(PROGRAM).dis

$(PROGRAM).dis: $(PROGRAM).elf
	$(OBJDUMP) -fhSD $< > $@

# Convert binary to Verilog memory format (requires srec_cat)
$(PROGRAM).vmem: $(PROGRAM).bin
	srec_cat $< -binary -offset 0x0000 -byte-swap 4 -o $@ -vmem

# Generate binary from ELF
$(PROGRAM).bin: $(PROGRAM).elf
	$(OBJCOPY) -O binary $< $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $(INCS) -o $@ $<

# Compile assembly files
%.o: %.S
	$(CC) $(CFLAGS) -MMD -c $(INCS) -o $@ $<

# Clean up
clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM).elf $(PROGRAM).vmem $(PROGRAM).bin

distclean: clean
	rm -f $(OUTFILES) $(PROGRAM).dis

# Include dependency files
-include $(DEPS)