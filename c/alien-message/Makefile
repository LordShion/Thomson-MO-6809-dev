# Project settings ----------------------------------------------
OBJECTS=obj/$(TARGET)/main.o obj/$(TARGET)/thomson.o
CFLAGS=-Os -std=gnu99 -Wall

ifeq ($(TARGET),TO8)
  CFLAGS += -DPLATFORM=8
else
ifeq ($(TARGET),MO5)
  CFLAGS += -DPLATFORM=5
else
# No target defined. Fail.
all: 
	echo "make TARGET=MO5 or make TARGET=TO8"
endif
endif

# System settings -----------------------------------------------
PREFIX=~/coco/bin/m6809-unknown
CC=$(PREFIX)-gcc
AS=$(PREFIX)-as

# Generic rules -------------------------------------------------
# HFE  disk image (for HxC FE)
#out_sap.hfe: out.sap
#	hxcfloppyemulator_convert out.sap -HFE
#	cp out_sap.hfe /mo5/MO5/
#	unmount /mo5
#	rm -r /mo5
#
# Disk Image
floppy.sap: TEST.BIN TEST.PIC AUTO.BAT
	#cp DOS-MO.SAP $@ # Using this floppy directly results in files going above the 40th track, which MO5 DOS doesn't like.
	sapfs -c $@ 40 2
	sapfs -a $@ $^

# Linking
TEST.BIN TEST.map: $(OBJECTS) TEST.script
	#$(CC) -v -Os $(OBJECTS) -o TEST.BIN -Wl,--map -Wl,-m -Wl,-Ttext,0x6100 -nostdlib -lgcc
	lwlink --decb $(OBJECTS) --output=TEST.BIN --map=TEST.map --script=TEST.script --library-path=/boot/common/lib/gcc/$(PREFIX)/4.6.1 --library-path=/boot/common/$(PREFIX)/lib #-lgcc

#Compiling
obj/$(TARGET)/%.o: %.c obj/$(TARGET)
	$(CC) $(CFLAGS) -c $< -o $@

obj/$(TARGET)/%.o: pff/%.c obj/$(TARGET)
	$(CC) $(CFLAGS) -c $< -o $@

obj/$(TARGET)/%.o: %.s obj/$(TARGET)
	$(AS) $< -o $@

obj/$(TARGET):
	mkdir -p $@

TEST.PIC: ForeverXIII.png
	png2mo5 $^ $@

clean:
	rm -rf *.o
	rm -rf *.sap
	rm -rf *.BIN
#	rm -rf *.fd
	rm -rf *.K5
	rm -rf *.hfe
	rm -rf *.PIC
	rm -rf obj

run:
	@echo "running"
	@mess mo6 -nomaximize -flop1 floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt


	
	
