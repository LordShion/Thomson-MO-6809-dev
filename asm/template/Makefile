
ASM=lwasm -9 -b
SAPTOFD=saptofd
SAPFS=sapfs
PNG=png2mo5
F2K5=f2k5
BUILDPATH=build

all: floppy.sap #k5
	$(SAPTOFD) $(BUILDPATH)/floppy.sap
	
run:
	@echo "running"
	@mess mo6 -nomaximize ${ARGS} -flop1 $(BUILDPATH)/floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt
	@echo "mess ended"

k5: main
	@echo "creating mo5 cassette file..."
	$(F2K5) AUTO.BIN
	@echo "mo5 casette created"

floppy.sap: main pic
	@echo "Creating mo/to floppy..."
	$(SAPFS) -c $(BUILDPATH)/floppy.sap
	$(SAPFS) -a $(BUILDPATH)/floppy.sap $(BUILDPATH)/AUTO.BIN
	$(SAPFS) -a $(BUILDPATH)/floppy.sap $(BUILDPATH)/TEST.PIC
	@echo "mo/to floppy created!"

main: main.asm

	mkdir $(BUILDPATH)
	@echo "assembling..."
	$(ASM) -o $(BUILDPATH)/AUTO.BIN main.asm
	@echo "code assembled!"


pic: test.png
	$(PNG) test.png $(BUILDPATH)/TEST.PIC

clean:
	@echo "cleaning..."
	@rm -rf $(BUILDPATH)
	@echo "build cleaned!"