#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

# Build from course1/src with PLATFORM=HOST or PLATFORM=MSP432.
# Targets: build/all, compile-all, clean, NAME.i, NAME.asm, NAME.o,
#          and course1.asm (disassembly of the linked executable).
.DEFAULT_GOAL := build
.DELETE_ON_ERROR:

PLATFORM ?= HOST

# Validate the selected platform, except for a standalone clean operation.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),Clean)
ifeq ($(filter $(PLATFORM),HOST MSP432),)
$(error Specify PLATFORM=HOST or PLATFORM=MSP432)
endif
endif
endif

COURSE1 ?= 1
VERBOSE ?= 0
include sources.mk

TARGET = course1
CPU = cortex-m4
ARCH = armv7e-m
SPECS = nosys.specs
CFLAGS = -Wall -Werror -g -O0 -std=c99
CPPFLAGS = $(INCLUDES) -D$(PLATFORM)
ifeq ($(COURSE1),1)
CPPFLAGS += -DCOURSE1
endif
ifeq ($(VERBOSE),1)
CPPFLAGS += -DVERBOSE
endif
LDFLAGS = -Wl,-Map=$(TARGET).map

ifeq ($(PLATFORM),MSP432)
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZE = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump
LINKER_FILE = ../msp432p401r.lds
ARCH_FLAGS = -mcpu=$(CPU) -mthumb -march=$(ARCH) \
             -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += $(ARCH_FLAGS) --specs=$(SPECS)
LDFLAGS += -T $(LINKER_FILE)
# Keep floating-point registers out of exception handlers (modern GCC).
interrupts_msp432p401r_gcc.o interrupts_msp432p401r_gcc.i interrupts_msp432p401r_gcc.asm: CFLAGS += -mgeneral-regs-only
else
CC = gcc
LD = ld
SIZE = size
OBJDUMP = objdump
LINKER_FILE =
endif

OBJS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)
# Rebuild when platform, COURSE1, or VERBOSE changes without make clean.
PLATFORM_STAMP = .config-$(PLATFORM)-$(COURSE1)-$(VERBOSE)
$(PLATFORM_STAMP):
	rm -f .config-*
	touch $@

.PHONY: build all compile-all clean Build Clean
build: $(TARGET).out
	$(SIZE) $(TARGET).out
all Build: build
compile-all: $(OBJS)

$(TARGET).out: $(OBJS) $(LINKER_FILE) Makefile sources.mk $(PLATFORM_STAMP)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c Makefile sources.mk $(PLATFORM_STAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -MT "$*.o $*.i $*.asm" -c $< -o $@

%.i: %.c Makefile sources.mk $(PLATFORM_STAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.i=.d) -MT "$*.o $*.i $*.asm" -E $< -o $@

%.asm: %.c Makefile sources.mk $(PLATFORM_STAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.asm=.d) -MT "$*.o $*.i $*.asm" -S $< -o $@

$(TARGET).asm: $(TARGET).out
	$(OBJDUMP) -d $< > $@


clean:
	rm -f *.o *.d *.dep *.i *.asm *.map *.out .config-*
Clean: clean

-include $(DEPS)
