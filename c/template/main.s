
;;; gcc for m6809 : May 15 2016 00:37:20
;;; 4.6.4 (gcc6809lw pl6)
;;; ABI version 1
;;; -mint16
	.module	main.c
	.area .text
	.globl _myputs
_myputs:
	pshs	u
	leas	-2,s
	leau	,s
	stx	,u
	bra	L2
L3:
	ldb	[,u]
;----- asm -----
;  11 "main.c" 1
	 SWI 
 FCB 2
;  0 "" 2
;--- end asm ---
	ldd	,u
	addd	#1
	std	,u
L2:
	ldb	[,u]
	tstb	;cmpqi:(ZERO)
	bne	L3
	leas	2,s
	puls	u,pc
LC0:
	.ascii "Hello, World !\r\n\0"
	.globl _main
_main:
	pshs	u
	leau	,s
	ldx	#LC0
	jsr	_myputs
	puls	u,pc
