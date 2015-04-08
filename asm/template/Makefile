#LWTOOLS=/boot/apps/lwtools/bin/
LWTOOLS=/usr/local/bin/
#LWTOOLS=
ASM=$(LWTOOLS)lwasm -9 -b
SAPTOFD=$(LWTOOLS)saptofd
SAPFS=$(LWTOOLS)sapfs
PNG=$(LWTOOLS)png2mo5
F2K5=$(LWTOOLS)f2k5

all: floppy.sap k5
	$(SAPTOFD) floppy.sap
	cp floppy.fd k5 ../../dcmo5/software/
	cd ../../dcmo5 && ./dcmo5
	
run:
	@echo "running"
	@mess mo6 -nomaximize -flop1 floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt

k5: main
	$(F2K5) $^

floppy.sap: main pic
	$(SAPFS) -c floppy.sap
	$(SAPFS) -a floppy.sap AUTO.BIN
	$(SAPFS) -a floppy.sap TEST.PIC

main: main.asm

	$(ASM) -o AUTO.BIN main.asm


pic: test.png
	$(PNG) test.png TEST.PIC
