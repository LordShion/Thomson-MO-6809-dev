PREFIX=m6809-unknown
CC=$(PREFIX)-gcc
AS=$(PREFIX)-as

SAPTOFD=saptofd
SAPFS=sapfs

F2K5=f2k5
BUILDPATH=build



all: floppy.sap k5
	$(SAPTOFD) $(BUILDPATH)/floppy.sap

run:
	@echo "running"
	@mess mo6 -nomaximize ${ARGS} -flop1 $(BUILDPATH)/floppy.sap -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt
	@echo "mess ended"

runK5:
	@echo "running"
	@mess mo6 -nomaximize ${ARGS} -cass FILE.K5 -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt
	@echo "mess ended"


k5: main
	@echo "creating mo5 cassette file..."
	$(F2K5) $(BUILDPATH)/AUTO.BIN
	@echo "mo5 casette created"
	
floppy.sap: main
	@echo "Creating mo/to floppy..."
	$(SAPFS) -c $(BUILDPATH)/floppy.sap
	$(SAPFS) -a $(BUILDPATH)/floppy.sap $(BUILDPATH)/AUTO.BIN
	@echo "mo/to floppy created!"

main: main.c

	mkdir $(BUILDPATH)
	@echo "compiling..."
	$(CC) -S main.c
	@echo "assembling..."
	$(AS) -o $(BUILDPATH)/AUTO.BIN main.s
	@echo "code assembled!"


%.o: %.c
	$(CC) $(CFLAGS) -S $< 

%.o: %.s
	$(AS) $< -o $@.bin

clean:
	@echo "cleaning..."
	@rm -rf $(BUILDPATH)
	@echo "build cleaned!"
