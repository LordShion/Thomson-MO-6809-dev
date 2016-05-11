; MO5 Test stuff

	ORG $3000
		; Could be a little lower ?

main
	; Disable interrupts
;	ORCC #$50

;-----------------------------------------------------
; Color Computer with 6809
;-------------------------------------------------------

START   LDX     #MESG   POINT TO MESSAGE
        BSR     PRINT   PRINT MESSAGE
        RTS

PRN10   JSR     [$A002] PRINT CHARACTER IN A
PRINT   LDA     ,X+     GET NEXT CHARACTER
        BNE     PRN10   IF NOT 0, PRINT IT
        RTS

MESG    FCC     'HELLO WORLD!'
        FCB     0

		END main
		RTI