#############################################
##  Processor: S32K144
##  Author: Saurabh Kumar
##  GCC Version: 12.3
##  $(info [${ROOT}])
##  Makefile for S32K144 Bootloader
#############################################

#RootDirectory with the Project paths
ROOT = ./../..


APP_DIR = $(ROOT)/20_App
BSW_DIR = $(ROOT)/30_Bsw

APPSUB_DIR += $(APP_DIR)/Main

SRC_DIR += $(BSW_DIR)/gpio/src
SRC_DIR += $(BSW_DIR)/startup/src
SRC_DIR += $(BSW_DIR)/clock/src
SRC_DIR += $(BSW_DIR)/can/src
SRC_DIR += $(BSW_DIR)/adc/src
SRC_DIR += $(BSW_DIR)/flash/src
SRC_DIR += $(BSW_DIR)/hwExtDrv/src
SRC_DIR += $(BSW_DIR)/interrupt/src
SRC_DIR += $(BSW_DIR)/wdog/src
SRC_DIR += $(BSW_DIR)/spi/src
SRC_DIR += $(BSW_DIR)/port/src

INC_DIR += $(patsubst %/src,%/inc,$(SRC_DIR))
INC_DIR += $(ROOT)/30_Bsw/common
INC_DIR += $(APPSUB_DIR)

BIN_DIR = $(ROOT)/10_Build/bin
OBJ_DIR = $(ROOT)/10_Build/obj

#Compiler Directories
CC_DIR = $(ROOT)/40_Tools/20_Compiler/gcc-10.3
CC_BIN = $(CC_DIR)/bin
CC_INC = $(CC_DIR)/include
CC_LIB = $(CC_DIR)/lib

#Compilar Path
CC = $(CC_BIN)/arm-none-eabi-gcc
OBJSIZE = $(CC_BIN)/arm-none-eabi-size
OBJDUMP = $(CC_BIN)/arm-none-eabi-objdump
OBJCOPY = $(CC_BIN)/arm-none-eabi-objcopy

#Project Name
PROJECT = S32_BL

SRC += $(wildcard $(ROOT)/*/*/*/*.c)
INC = $(wildcard $(INC_DIR)/*.h)
OBJ += $(patsubst $(BSW_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ += $(patsubst $(APPSUB_DIR)/%.c,$(OBJ_DIR)/%.o,$(APPSUB_DIR)/main.c)

#Compiler and Linker flags

CFLAGS = -c -march=armv7e-m -mthumb -g3 -mcpu=cortex-m4 -Wall -std=gnu11 $(addprefix -I ,$(INC_DIR)) -ggdb
LDFLAGS = -T S32_BL.ld -g3 -ggdb -Wl,-Map=$(BIN_DIR)/S32_BL.map -nostdlib -mcpu=cortex-m4 -Wall -Werror -Wshadow $(addprefix -L ,$(CC_LIB))

#Target name with path
TARGET = $(ROOT)/10_build/bin/$(PROJECT)

############################# Makefile rules to build the project ###############################
all: $(TARGET).elf

$(TARGET).elf:$(OBJ)
	@echo Linking: $@
	@$(CC) $(LDFLAGS) $^ -o $@

###################################### For Compiling the BSW #####################################
$(OBJ_DIR)/%.o:$(BSW_DIR)$(*)/%.c
	@mkdir -p $(@D)
	@echo Compiling: $@
	@$(CC) $(CFLAGS) $^ -o $@

################################## For Compiling the Application #################################
$(OBJ_DIR)/%.o:$(APPSUB_DIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling: $@
	@$(CC) $(CFLAGS) $^ -o $@

objsize: 
	@echo Size of output file is:
	@$(OBJSIZE) $(TARGET).elf

objcopytohex:
	@echo Generating .bin file....
	@$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

objcopytobin:
	@echo Generating .bin file....
	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

clean:
	@echo Removing build files
	@rm -rf $(ROOT)/10_Build/bin/* $(OBJ_DIR)/*
	@echo Done...

.PHONY: all clean