
.SUFFIXES:

ifeq ($(strip $(DEVKITPPC)),)
$(error "DEVKITPPC is not configured")
endif

include $(DEVKITPPC)/wii_rules

TARGET := boot

.PHONY: all clean

all: $(TARGET).dol

$(TARGET).elf: source/main.c
	$(CC) -O2 -Wall $(MACHDEP) -I$(LIBOGC_INC) $< -L$(LIBOGC_LIB) -lwiiuse -lbte -logc -lm -o $@

clean:
	rm -f $(TARGET).elf $(TARGET).dol $(TARGET).elf.map
