
ASM=lwasm -9 -b
SAPTOFD=saptofd
SAPFS=sapfs
PNG=png2mo5
F2K5=f2k5

all: floppy.sap #k5
	$(SAPTOFD) floppy.sap
	
run:
	@echo "running"
	@mess mo6 -nomaximize -flop1 floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt

k5: main
	$(F2K5) AUTO.BIN TEST.PIC

floppy.sap: main pic
	$(SAPFS) -c floppy.sap
	$(SAPFS) -a floppy.sap AUTO.BIN
	$(SAPFS) -a floppy.sap TEST.PIC

main: main.asm

	$(ASM) -o AUTO.BIN main.asm


pic: test.png
	$(PNG) test.png TEST.PIC
clean:
	rm floppy.sap
	rm AUTO.BIN
	rm TEST.PIC
	rm floppy.fd
	rm FILE.K5
