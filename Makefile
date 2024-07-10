
# compile options (see README.md for descriptions)
# 0 = disable
# 1 = enable

# ---- COMPILER/LINKER OPTIONS ----
ENABLE_CLANG                  ?= 0
ENABLE_OVERLAY                ?= 1
ENABLE_LTO                    ?= 0
ENABLE_CHINESE_FULL 		   = 0
ENABLE_ENGLISH				    =0

#############################################################
PACKED_FILE_SUFFIX = L_BL002




CFLAGS =
OPENOCD = openocd-win/bin/openocd.exe
TARGET =  L_BL



ifeq ($(ENABLE_LTO),1)
	# can't have LTO and OVERLAY enabled at same time
	ENABLE_OVERLAY := 0
endif

BSP_DEFINITIONS := $(wildcard hardware/*/*.def)
BSP_HEADERS     := $(patsubst hardware/%,bsp/%,$(BSP_DEFINITIONS))
BSP_HEADERS     := $(patsubst %.def,%.h,$(BSP_HEADERS))

OBJS =
# Startup files
OBJS += start.o
OBJS += init.o



#	OBJS += sram-overlay.o


ifeq ($(ENABLE_OVERLAY),1)
	OBJS += sram-overlay.o
endif
OBJS += driver/eeprom.o
ifeq ($(ENABLE_OVERLAY),1)
	OBJS += driver/flash.o
endif

OBJS += driver/gpio.o
OBJS += driver/i2c.o
OBJS += driver/keyboard.o
OBJS += driver/spi.o
OBJS += driver/st7565.o
OBJS += driver/system.o
OBJS += driver/systick.o
OBJS += external/printf/printf.o
OBJS += board.o
OBJS += font.o
OBJS += ui/helper.o
OBJS += main.o
OBJS += app/key.o
OBJS += app/display.o
OBJS += app/eeprom.o
OBJS += app/uart.o
OBJS += driver/uart.o
OBJS += driver/aes.o
OBJS += version.o
OBJS += misc.o

ifeq ($(OS), Windows_NT) # windows
    TOP := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
    RM = del /Q
    FixPath = $(subst /,\,$1)
    WHERE = where
    NULL_OUTPUT = nul
else # unix
    TOP := $(shell pwd)
    RM = rm -f
    FixPath = $1
    WHERE = which
    NULL_OUTPUT = /dev/null
endif


AS = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

ifeq ($(ENABLE_CLANG),0)
	CC = arm-none-eabi-gcc
# Use GCC's linker to avoid undefined symbol errors
#	LD += arm-none-eabi-gcc
else
#	May need to adjust this to match your system
	CC = clang --sysroot=/usr/arm-none-eabi --target=arm-none-eabi
#	Bloats binaries to 512MB
#	LD = ld.lld
endif

OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

AUTHOR_STRING ?= LOSEHU
# the user might not have/want git installed
# can set own version string here (max 7 chars)
ifneq (, $(shell $(WHERE) git))
	VERSION_STRING ?= $(shell git describe --tags --exact-match 2>$(NULL_OUTPUT))
	ifeq (, $(VERSION_STRING))
    	VERSION_STRING := $(shell git rev-parse --short HEAD)
	endif
endif
# If there is still no VERSION_STRING we need to make one.
# It is needed for the firmware packing script
ifeq (, $(VERSION_STRING))
	VERSION_STRING := NOGIT
endif
#VERSION_STRING := 230930b


ASFLAGS = -c -mcpu=cortex-m0
ifeq ($(ENABLE_OVERLAY),1)
	ASFLAGS += -DENABLE_OVERLAY
endif

ifeq ($(ENABLE_CLANG),0)
	CFLAGS += -Os -Wall -Wno-error -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=c2x -MMD -w
	#CFLAGS += -Os -Wall -Werror -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=c11 -MMD
	#CFLAGS += -Os -Wall -Werror -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=c99 -MMD
	#CFLAGS += -Os -Wall -Werror -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=gnu99 -MMD
	#CFLAGS += -Os -Wall -Werror -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=gnu11 -MMD
else
	# Oz needed to make it fit on flash
	CFLAGS += -Oz -Wall -Werror -mcpu=cortex-m0 -fno-builtin -fshort-enums -fno-delete-null-pointer-checks -std=c2x -MMD
endif

ifeq ($(ENABLE_LTO),1)
	CFLAGS += -flto=auto
else
	# We get most of the space savings if LTO creates problems
	CFLAGS += -ffunction-sections -fdata-sections
endif

# May cause unhelpful build failures
#CFLAGS += -Wpadded

# catch any and all warnings
CFLAGS += -Wextra
#CFLAGS += -Wpedantic

# 设置PACKED_FILE_SUFFIX，根据ENABLE_CHINESE_FULL的值设置不同的后缀

CFLAGS += -DENABLE_EEPROM_TYPE=$(ENABLE_EEPROM_TYPE)

CFLAGS += -DENABLE_CHINESE_FULL=$(ENABLE_CHINESE_FULL)
CFLAGS += -DPACKED_FILE_SUFFIX=\"$(PACKED_FILE_SUFFIX)\"
CFLAGS += -DPRINTF_INCLUDE_CONFIG_H
CFLAGS += -DAUTHOR_STRING=\"$(AUTHOR_STRING)\" -DVERSION_STRING=\"$(VERSION_STRING)\"


ifeq ($(ENABLE_ENGLISH),1)
    CFLAGS  += -DENABLE_ENGLISH
endif

ifeq ($(ENABLE_OVERLAY),1)
	CFLAGS += -DENABLE_OVERLAY
endif

LDFLAGS =
LDFLAGS += -z noexecstack -mcpu=cortex-m0 -nostartfiles -Wl,-T,firmware.ld -Wl,--gc-sections

# Use newlib-nano instead of newlib
LDFLAGS += --specs=nano.specs

ifeq ($(DEBUG),1)
	ASFLAGS += -g
	CFLAGS  += -g
	LDFLAGS += -g
endif

INC =
INC += -I $(TOP)
INC += -I $(TOP)/external/CMSIS_5/CMSIS/Core/Include/
INC += -I $(TOP)/external/CMSIS_5/Device/ARM/ARMCM0/Include

LIBS =


DEPS = $(OBJS:.o=.d)



ifneq (, $(shell $(WHERE) python))
    MY_PYTHON := python
else ifneq (, $(shell $(WHERE) python3))
    MY_PYTHON := python3
endif

ifdef MY_PYTHON
    HAS_CRCMOD := $(shell $(MY_PYTHON) -c "import crcmod" 2>&1)
endif

test:
	$(RM) *.bin
	$(MAKE) build ENABLE_CHINESE_FULL=0 ENABLE_ENGLISH=1
build:clean $(TARGET)
	$(OBJCOPY) -O binary $(TARGET) $(PACKED_FILE_SUFFIX).bin
	$(SIZE) $(TARGET)

version.o: .FORCE

$(TARGET): $(OBJS)
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

bsp/dp32g030/%.h: hardware/dp32g030/%.def

%.o: %.c | $(BSP_HEADERS)
	@echo "$< >> $@"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o: %.S
	@$(AS) $(ASFLAGS) $< -o $@

.FORCE:

-include $(DEPS)





clean:
	@$(RM) $(call FixPath, $(TARGET).bin $(PACKED_FILE_SUFFIX).bin $(TARGET) )

ifeq ($(OS), Windows_NT) # Windows 系统
	@call del_win.bat
else # 类 Unix 系统（Linux, macOS, 等）
	chmod +x del_linux.sh
	sh ./del_linux.sh
endif

