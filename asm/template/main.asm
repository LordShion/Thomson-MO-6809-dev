; MO5 Test stuff

	ORG $3000
		; Could be a little lower ?

main
	; Disable interrupts
	ORCC #$50
;	SWI

	; Paint screen with 0xAA pattern in FORME
	LDA #$AA
	LDX #$1F40
boucle
	STA ,-X
	CMPX #0
	BNE boucle

	; Set the border (also to 0xAA)
	STA $A7C0

	; COLOR memory to 0xCF
	LDA #$AD
	LDX #$1F40
boucle2
	STA ,-X
	CMPX #0
	BNE boucle2

	; Sync on VBL
mainloop

	; ... do effects !
	; Twister
	; Plasma
	; Scroll
	; Dots
	; Draw squares
	; ...
	; Sprites
	; Wireframe 3D

	; MEA8000 Music

;	JMP mainloop

; DATAS
; Location for framecounter to decide when to switch effects

	END main
;	RTI

