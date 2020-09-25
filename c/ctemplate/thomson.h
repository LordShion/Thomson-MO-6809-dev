// 5 : MO5 / 8: TO8

#ifndef PLATFORM
	#error "make TARGET=TO8 or make TARGET=MO5"
#endif

///////////////////////////////////////
// THOMSON.H
///////////////////////////////////////

/* MONITOR ZERO-PAGE */
#define TERMIN	(*(volatile unsigned char*)(MONBASE + 0x00)) // 0x18 bytes
#define STATUS	(*(volatile unsigned char*)(MONBASE + 0x19))
#define TABPT	(*(volatile unsigned int*)(MONBASE + 0x1A))
#define RANG	(*(volatile unsigned char*)(MONBASE + 0x1B)) // Part of TABPT?
#define COLN	(*(volatile unsigned char*)(MONBASE + 0x1C))
#define TOPTAB	(*(volatile unsigned char*)(MONBASE + 0x1D))
#define TOPRAN	(*(volatile unsigned char*)(MONBASE + 0x1E))
#define BOTTAB	(*(volatile unsigned char*)(MONBASE + 0x1F))
#define BOTRAN	(*(volatile unsigned char*)(MONBASE + 0x20))

#define PLOTX	(*(volatile unsigned int*)(MONBASE + 0x32))
#define PLOTY	(*(volatile unsigned int*)(MONBASE + 0x34))
#define CHDRAW	(*(volatile unsigned char*)(MONBASE + 0x36))
#define KEY		(*(volatile unsigned char*)(MONBASE + 0x37))
#define DKOPC	(*(volatile unsigned char*)(MONBASE + 0x48))
#define DKDRV	(*(volatile unsigned char*)(MONBASE + 0x49))
/* 204A is unused */
#define DKTRK	(*(volatile unsigned char*)(MONBASE + 0x4B))
#define DKSEC	(*(volatile unsigned char*)(MONBASE + 0x4C))
#define DKSTA	(*(volatile unsigned char*)(MONBASE + 0x4E))
#define DKBUF	(*(volatile unsigned int*)(MONBASE + 0x4F))

#define DKint1 (*(volatile unsigned int*)(MONBASE + 0x52))

void printhex(unsigned char i);
extern unsigned char mark[];

/* HARDWARE */
#define FDC_STATUS (*(volatile unsigned char*)(FDCBASE))

////////////////////////////////////////
// MO5.H
////////////////////////////////////////

#if PLATFORM == 5
/*****************************************************************************
 * MOx CODE
 ****************************************************************************/
	#define MONBASE 0x2000
	#define FDCBASE	0xA7D0

	/* MONITOR ENTRY POINTS */

	static inline void MENU() {
		asm(" SWI	\n"
			" FCB	0"
			);
	}

	static inline void PUTC(unsigned char car) {
    	asm(" swi \n"
		    " fcb 2"
			::"B" (car)
		);
	}

	static inline void FRM0() {
		asm(" SWI	\n"
			" FCB	4"
			);
	}

	static inline void FRM1() {
		asm(" SWI	\n"
			" FCB	6"
			);
	}

	static inline void BEEP() {
		asm(" SWI	\n"
			" FCB	8"
			);
	}

	// TODO GETC and KTST return values in B,A and Z-flag. How to get these
	// back in C ?

	static inline void DRAW(int x, int y) {
		asm(" SWI	\n"
			" FCB	0xE"
			:: "X" (x), "Y" (y)
		);
	}

	static inline void PLOT(int x, int y) {
		asm(" SWI	\n"
			" FCB	0x10"
			:: "X" (x), "Y" (y)
		);
	}

	static inline void CHPL(int x, int y) {
		asm(" SWI	\n"
			" FCB	0x12"
			:: "X" (x), "Y" (y)
		);
	}

	// TODO GETP returns in B, LPIN in flag C, GETL flag C and regs XY
	// GETS and JOYS in A
	
	enum Note {
		DO  = 0,
		DOs = 1,
		RE  = 2,
		REs = 3,
		MI  = 4,
		FA  = 5,
		FAs = 6,
		SO  = 7,
		SOs = 8,
		LA  = 9,
		LAs = 9,
		SI  = 10,
		UT  = 11,
		// TODO what happens with other values ?
	};

	static inline void NOTE(enum Note note)
	{
		asm(" SWI	\n"
			" FCB	0x1E"
			:: "B" (note)
		);
	}


	/* FLOPPY DRIVE MONITOR ROM */
	// NOTE DKOPC was split into several commands to make it easier to use from
	// C code.
	static inline void write(unsigned char track, unsigned char sector, unsigned char* buffer) {
		DKTRK = (unsigned char)track;
		DKSEC = (unsigned char)sector;
		DKOPC = 8;
		DKBUF = (unsigned int)buffer;

    	asm(" swi \n"
		    " fcb 0x26"
			);
	}

static inline void read(unsigned char track, unsigned char sector, unsigned char* output)
{
	for(;;)
	{
		DKTRK = (unsigned char)track;
		DKSEC = (unsigned char)sector;
		DKOPC = 2;
		DKBUF = (unsigned int)output;

    	asm(" swi \n"
		    " fcb 0x26"
			);

		if (DKSTA == 0x44 || DKSTA == 0) return; // Sector read ok!
		printhex(DKSTA);
	}
}

	static inline void BOOT() {
		asm(" SWI	\n"
			" FCB	0x28"
		);
	}

#else
/*****************************************************************************
 * TOx CODE
 ****************************************************************************/
	/* MONITOR ENTRY POINTS */
	#define mon_putc(car) { \
    	asm("JSR \t0xE803  \t; TO8 PUTC\n"\
			::"B" ((unsigned char) (car))\
		); \
	}

	#define MONBASE 0x6000

#define write(track, sector, buffer) {\
		DKTRK = (unsigned char)track;\
		DKSEC = (unsigned char)sector;\
		DKOPC = 8;\
		DKBUF = (unsigned int)buffer;\
\
    	asm("JSR \t 0xE004 \t; TO8 DKCONT\n"\
		); \
	}

	/* FLOPPY DRIVE MONITOR ROM */
inline void read(unsigned char track, unsigned char sector,
	unsigned char* output)
{
	for(;;)
	{
		DKTRK = (unsigned char)track;
		DKSEC = (unsigned char)sector;
		DKOPC = 2;
		DKBUF = (unsigned int)output;

    	asm("JSR \t 0xE004 \t \n"); \

		if (DKSTA == 0x44 || DKSTA == 0) return; // Sector read ok!
		printhex(DKSTA);
	}
}
#endif

