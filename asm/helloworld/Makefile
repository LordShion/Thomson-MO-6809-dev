
ASM=lwasm -9 -b
SAPTOFD=saptofd
SAPFS=sapfs
PNG=png2mo5
F2K5=f2k5
BUILDPATH=build
EMULATOR=mame
# EMULATOR=mess

all: floppy.sap #k5
	$(SAPTOFD) $(BUILDPATH)/floppy.sap
	
run:
	@echo "running"
	@$(EMULATOR) mo6 -window -nomaximize -flop1 $(BUILDPATH)/floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt
	@echo "$(EMULATOR) ended"

k5: main
	@echo "creating mo5 cassette file..."
	$(F2K5) AUTO.BIN
	@echo "mo5 casette created"

floppy.sap: main 
	@echo "Creating mo/to floppy..."
	$(SAPFS) -c $(BUILDPATH)/floppy.sap
	$(SAPFS) -a $(BUILDPATH)/floppy.sap $(BUILDPATH)/AUTO.BIN
	@echo "mo/to floppy created!"

main: main.asm

	mkdir $(BUILDPATH)
	@echo "assembling..."
	$(ASM) -o $(BUILDPATH)/AUTO.BIN main.asm
	@echo "code assembled!"



clean:
	@echo "cleaning..."
	@rm -rf $(BUILDPATH)
	@echo "build cleaned!"