			.ORIG 	x3000

			AND 	R1, R1, #0		; Set digit counter to 0
NEXTVAL		ADD 	R1, R1, #-4		; Subtract 4 from digit counter to check if we have 4 digits printed
			BRz 	FINISH			; Branch to FINISH if true
			ADD 	R1, R1, #4		; Add 4 back to digit counter
			

NEWHEX		AND 	R2, R2, #0	 	; Set bit counter to 0 
			AND 	R4, R4, #0		; Set digit to 0
			ADD 	R3, R3, #0		; Keep R3 as last updated register

			BRzp 	POSCASE			; Branch to POSCASE if R3 is positive
NEGCASE		ADD 	R4, R4, R4		; Left shift R4
			ADD 	R2, R2, #1		; Increment bit counter for negative case
			ADD 	R4, R4, #1		; Set LSB in R3 to MSB from R3 which would be 1 in the negative case 
			BRnzp 	TESTBITS		; Once done, branch to TESTBITS
POSCASE		ADD 	R4, R4, R4		; Left shift R4 
			ADD 	R2, R2, #1		; Increment bit counter for positive case
			ADD 	R4, R4, #0		; Set LSB in R3 to MSB from R3 which would be 0 in the negative case
			
TESTBITS	ADD 	R3, R3, R3		; Left shift R3 to go to next most significant bit
			ADD 	R2, R2, #-4 	; Subtract 4 from bit counter to check if we have 4 bits
			BRz 	TRANSLATE
			ADD 	R2, R2, #4		; Add 4 back to bit counter
			ADD 	R3, R3, #0		; keep R3 at the last updated register
			BRn 	NEGCASE			; Branch to NEGCASE if R3 is negative
			BRzp 	POSCASE 		; Branch to POSCASE if R3 is positive		
				
TRANSLATE	ADD 	R4, R4, #-9		; Subtract 9 from digit to see if digit is less than or equal to 9
			BRnz	LESS			; Branch to LESS than 9 case
			ADD 	R4, R4, #9		; Add 9 back to digit 
			ADD 	R4, R4, #-10	; Subtract 10 from R4 if it is a hex value of A-F
			LD	 	R0, LCONST		; Load R0 with the letter hex value for 'A'
			ADD 	R0, R0, R4		; Add R4 to the hex value for 'A' in R0
			OUT
			ADD 	R1, R1, #1		; Increment digit counter
			BRnzp 	NEXTVAL
LESS		ADD 	R4, R4, #9		; Add 9 back to digit
			LD 		R0, NCONST		; Load R0 with the number hex value for '0'
			ADD 	R0, R0, R4		; Add R4 to the hex value for '0' in R0
			OUT
			ADD 	R1, R1, #1		; Increment digit counter
			BRnzp 	NEXTVAL			; Branch to NEXTVAL

FINISH 		HALT

NCONST		.FILL x0030
LCONST		.FILL x0041
			.END


			
	


