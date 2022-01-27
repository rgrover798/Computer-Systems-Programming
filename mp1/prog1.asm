;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string and as the loop count during histogram 
;    initialization
;    R2 holds the current character being counted and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

			LD  R0,HIST_ADDR      	; point R0 to the start of the histogram
	
									; fill the histogram with zeroes 

			AND R6,R6,#0			; put a zero into R6
			LD  R1,NUM_BINS			; initialize loop count to 27
			ADD R2,R0,#0			; copy start of histogram into R2

									; loop to fill histogram starts here

HFLOOP		STR R6,R2,#0			; write a zero into histogram
			ADD R2,R2,#1			; point to next histogram entry
			ADD R1,R1,#-1			; decrement loop count
			BRp HFLOOP				; continue until loop count reaches zero

									; initialize R1, R3, R4, and R5 from memory

			LD R3,NEG_AT			; set R3 to additive inverse of ASCII '@'
			LD R4,AT_MIN_Z			; set R4 to difference between ASCII '@' and 'Z'
			LD R5,AT_MIN_BQ			; set R5 to difference between ASCII '@' and '`'
			LD R1,STR_START			; point R1 to start of string

									; the counting loop starts here
COUNTLOOP
			LDR R2,R1,#0			; read the next character from the string
			BRz PRINT_HIST			; found the end of the string
			ADD R2,R2,R3			; subtract '@' from the character
			BRp AT_LEAST_A			; branch if > '@', i.e., >= 'A'

NON_ALPHA
			LDR R6,R0,#0			; load the non-alpha count
			ADD R6,R6,#1			; add one to it
			STR R6,R0,#0			; store the new non-alpha count
			BRnzp GET_NEXT			; branch to end of conditional structure

AT_LEAST_A
			ADD R6,R2,R4			; compare with 'Z'
			BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing

ALPHA		ADD R2,R2,R0			; point to correct histogram entry
			LDR R6,R2,#0			; load the count
			ADD R6,R6,#1			; add one to it
			STR R6,R2,#0			; store the new count
			BRnzp GET_NEXT			; branch to end of conditional structure

									; subtracting as below yields the original character minus '`'

MORE_THAN_Z
			ADD R2,R2,R5			; subtract '`' - '@' from the character
			BRnz NON_ALPHA			; if <= '`', i.e., < 'a', go increment non-alpha
			ADD R6,R2,R4			; compare with 'z'
			BRnz ALPHA				; if <= 'z', go increment alpha count
			BRnzp NON_ALPHA			; otherwise, go increment non-alpha
	
GET_NEXT
			ADD R1,R1,#1			; point to next character in string
			BRnzp COUNTLOOP			; go to start of counting loop



PRINT_HIST

; This algorithm prints the histogram specified by values from HIST_ADDR located at x3F00 which
; hold the number of times character have appeared in the string specified at x4000. The program
; does this by looping through each histogram bin, starting at x3F00, and loading the value
; specified by each bin into R3 in order to print the specified value being stored. (The value
; being stored is calculated by the histogram code above which parses a string to calculate  
; how many letters or other characters are in a string). The algorithm works by converting each
; group of four binary digits into their corresponding ASCII value, and then shifting the four
; bits over and then printing again the next four bits until the whole hex value is done printing
;
; Registers Used:
; R0 is used to print newline, space, histogram bin labels, and the hex values specified by the 
; histogram bins starting from x3F00
; R1 is used to keep track of the amount of digits of the hex value printed so far. Once it 
; reaches 4, the whole HEX value is printed.
; R2 is used to keep track of the current bit that is a subset of length four of the overall hex
; value. Once it reaches 4, the whole SUBSET OF the HEX value is printed
; R3 is used to hold the hex value that needs to be printed along with the address of where it
; is being printed from
; R4 holds the exact value of the current digit being printed of the SUBSET that is in R2. This 
; digit is then converted to it's corresponding ASCII value to be printed
; R5 is used to keep track of the number of bins that have been printed so far as a counter
; R6 is used to hold the ASCII values of the labels for each histogram bin being printed


			LDI 	R3, HIST_ADDR 	; Load starting histogram value needed to be printed to R3
			LD 		R5, NUM_BINS	; Load number of bins into R5
			LD 		R6, STARTPRINT	; Load starting print value for histogram into R6
			BRnzp	START			; Unconditionally branch to START to start printing process
			
NEXTBIN 	LD 		R3, HIST_ADDR	; Load R3 with the value of HIST_ADDR
			ADD 	R3, R3, #1		; Increment to next histogram address location
			ST	 	R3, HIST_ADDR	; Store next histogram location in HIST_ADDR
			LDI	 	R3, HIST_ADDR	; Load R3 with value that needs to be printed
			ADD 	R5, R5, #-1		; Subtract one from bin counter
			BRz 	DONE			; Branch to DONE if all bins have printed	

			LD 		R0, NEWLINE		; Load R0 with newline ascii value
			OUT						; Print newline	

START		LD 		R0, STARTPRINT 	; Load R0 with starting print value for histogram
			OUT 					; Print ascii value stored in R6 for histogram output
			ADD 	R6, R6, #1 		; Increment ascii value being printed for histogram output
			ST 		R6, STARTPRINT	; Update value to be printed for next histogram bin
			LD 		R0, SPACE		; Load R0 with ASCII value for space
			OUT						; Print space with ASCII value stored in R0

			AND 	R1, R1, #0		; Set digit counter to 0
NEXTVAL		ADD 	R1, R1, #-4		; Subtract 4 from digit counter to check if we have 4 digits printed
			BRz 	NEXTBIN			; Branch to HFLOOP if complete
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


DONE		HALT			; done


; the data needed by the program
NCONST		.FILL x0030		; Number ASCII val 
LCONST		.FILL x0041		; Letter ASCII val 
NEWLINE		.FILL x000A 	; Newline ASCII val
SPACE	 	.FILL x0020		; Space ASCII val
STARTPRINT	.FILL x0040		; Starting printing val
NUM_BINS	.FILL #27		; 27 loop iterations
NEG_AT		.FILL xFFC0		; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6		; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0		; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 	; histogram starting address
STR_START	.FILL x4000		; string starting address

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
