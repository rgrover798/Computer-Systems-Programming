;
;
;
.ORIG x3000
GETINPUT
			GETC					; Get user input
			OUT						; Output user input
			BRnzp 	EVALUATE		; Unconditionally jump to evaluate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3 - value to print in hexadecimal
PRINT_HEX
			AND 	R1, R1, #0		; Set digit counter to 0
NEXTVAL		ADD 	R1, R1, #-4		; Subtract 4 from digit counter to check if 4 digits printed
			BRz 	DONE			; Branch to DONE if printing complete
			ADD 	R1, R1, #4		; Add 4 back to digit counter
			

NEWHEX		AND 	R2, R2, #0	 	; Set bit counter to 0 
			AND 	R4, R4, #0		; Set digit to 0
			ADD 	R3, R3, #0		; Keep R3 as last updated register

			BRzp 	POSCASE			; Branch to POSCASE if R3 is positive
NEGCASE		ADD 	R4, R4, R4		; Left shift R4
			ADD 	R2, R2, #1		; Increment bit counter for negative case
			ADD 	R4, R4, #1		; Set LSB in R3 to MSB from R3, 1 in the negative case 
			BRnzp 	TESTBITS		; Once done, branch to TESTBITS
POSCASE		ADD 	R4, R4, R4		; Left shift R4 
			ADD 	R2, R2, #1		; Increment bit counter for positive case
			ADD 	R4, R4, #0		; Set LSB in R3 to MSB from R3, 0 in the negative case
			
TESTBITS	ADD 	R3, R3, R3		; Left shift R3 to go to next most significant bit
			ADD 	R2, R2, #-4 	; Subtract 4 from bit counter to check if we have 4 bits
			BRz 	TRANSLATE
			ADD 	R2, R2, #4		; Add 4 back to bit counter
			ADD 	R3, R3, #0		; keep R3 at the last updated register
			BRn 	NEGCASE			; Branch to NEGCASE if R3 is negative
			BRzp 	POSCASE 		; Branch to POSCASE if R3 is positive		
				
TRANSLATE	ADD 	R4, R4, #-9		; Subtract 9 from digit to see if digit less than/equal to 9
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

NCONST		.FILL x0030
LCONST		.FILL x0041

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
			LD 		R1, NOT_EQSIGN	; Load R1 with the negative hex value of equal sign
			ADD 	R1, R0, R1		; Compute R0 - R1
			BRz 	EQSIGNCASE		; If user input is an equal sign, branch to EQSIGNCASE
			LD 		R1, NOT_SPACE	; Load R1 with the negative hex value of space 
			ADD 	R1, R0, R1		; Compute R0-R1
			BRz 	GETINPUT		; If user input is space, branch to GETINPUT

; CHECKING IF USER INPUT IS A VALID OPERATOR

			LD 		R1, NOT_PLUS	;
			ADD 	R1, R0, R1		;
			BRz 	PLUS_OPERAND	;
			LD 		R1, NOT_MINUS	;
			ADD 	R1, R0, R1		;
			BRz 	MINUS_OPERAND	;
			LD 		R1, NOT_MUL		;
			ADD 	R1, R0, R1		;
			BRz 	MUL_OPERAND		;
			LD 		R1, NOT_DIV		;
			ADD 	R1, R0, R1		;
			BRz 	DIV_OPERAND		;
			LD 		R1, NOT_EXP		;
			ADD 	R1, R0, R1		;
			BRz 	EXP_OPERAND		;

; CHECKING IF USER INPUT IS A VALID OPERAND

			LD 		R1, NOT_ZERO	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_ONE		;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_TWO		;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_THREE	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_FOUR	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_FIVE	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_SIX		;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_SEVEN	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_EIGHT	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			LD 		R1, NOT_NINE	;
			ADD 	R1, R0, R1		;
			BRz 	VALIDCHAR		;
			BRnzp	INVALID			; If not valid character, branch to INVALID and halt

VALIDCHAR	
			LD 		R2, NOT_CONST 	; Load R2 with NOT_CONST
			ADD 	R0, R0, R2		; Subtract R2 from R0
			JSR 	PUSH			; Push numerical input to stack
			BRnzp 	GETINPUT		; Get next user input

PLUS_OPERAND
			JSR		POP				; POP first value from stack 
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R4, R0, #0		; If no underflow, add first value from stack into R4
			JSR 	POP				; POP second value from stack
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp 	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R3, R0, #0		; If no underflow, add first value from stack into R3
			JSR 	PLUS			; Jump to PLUS and complete operation
			BRnzp 	GETINPUT		; Get next user input

MINUS_OPERAND
			JSR		POP				; POP first value from stack 
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R4, R0, #0		; If no underflow, add first value from stack into R4
			JSR 	POP				; POP second value from stack
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp 	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R3, R0, #0		; If no underflow, add first value from stack into R3
			JSR 	MIN				; Jump to MINUS and complete operation	
			BRnzp 	GETINPUT		; Get next user input					

MUL_OPERAND
			JSR		POP				; POP first value from stack 
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R4, R0, #0		; If no underflow, add first value from stack into R4
			JSR 	POP				; POP second value from stack
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp 	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R3, R0, #0		; If no underflow, add first value from stack into R3
			JSR 	MUL				; Jump to MUL and complete operation
			BRnzp 	GETINPUT		; Get next user input

DIV_OPERAND
			JSR		POP				; POP first value from stack 
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R4, R0, #0		; If no underflow, add first value from stack into R4
			JSR 	POP				; POP second value from stack
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp 	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R3, R0, #0		; If no underflow, add first value from stack into R3
			JSR 	DIV				; Jump to DIV and complete operation
			BRnzp 	GETINPUT		; Get next user input

EXP_OPERAND
			JSR		POP				; POP first value from stack 
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R4, R0, #0		; If no underflow, add first value from stack into R4
			JSR 	POP				; POP second value from stack
			ADD 	R5, R5, #0		; Keep R5 as last updated register
			BRnp 	INVALID			; If R5 is not zero, underflow has occured
			ADD 	R3, R0, #0		; If no underflow, add first value from stack into R3
			JSR 	EXP				; Jump to EXP and complete operation
			BRnzp 	GETINPUT		; Get next user input

EQSIGNCASE	
			LD 		R1, STACK_START	; Load STACK_START into R1	
			LD 		R2, STACK_TOP	; Load STACK_TOP into R2
			NOT 	R2, R2			; Not R2 to make negative
			ADD 	R2, R2, #1		; Add 1 to R2 to make negative
			ADD 	R1, R1, R2		; Compute R1 - R2
			ADD 	R1, R1, #-1		; Subtract 1 to check if only one value in stack
			BRz 	ONLYONE			; Branch to ONLYONE if one value in stack
			BRnzp 	INVALID			; Else, branch to INVALID

ONLYONE
			JSR 	POP				; Jump to POP to take final value out of stack
			ADD 	R3, R0, #0		; Add value from stack in R0 to R3
			ADD 	R5, R0, #0		; Add value from stack in R0 to R5
			BRnzp 	PRINT_HEX		; Print value in R3

INVALID
			LEA 	R0, INVALID_EXP	; Load address of INVALID_EXP into R0
			PUTS					; Output string
			BRnzp 	DONE			; Unconditionally branch to DONE and halt program

NOT_EQSIGN 	.FILL xFFC3				;
NOT_SPACE	.FILL xFFE0				;
NOT_CONST	.FILL xFFD0
			
NOT_PLUS	.FILL xFFD5				;
NOT_MINUS	.FILL xFFD3				;
NOT_MUL		.FILL xFFD6				;
NOT_DIV		.FILL xFFD1				;
NOT_EXP		.FILL xFFA2				;

NOT_ZERO	.FILL xFFD0				;
NOT_ONE		.FILL xFFCF				;
NOT_TWO		.FILL xFFCE				;
NOT_THREE	.FILL xFFCD				;		
NOT_FOUR	.FILL xFFCC				;
NOT_FIVE	.FILL xFFCB				;
NOT_SIX		.FILL xFFCA				;
NOT_SEVEN	.FILL xFFC9				;
NOT_EIGHT	.FILL xFFC8				;
NOT_NINE	.FILL xFFC7				;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
			
			ADD 	R0, R3, R4 		; Add R3 and R4 to each other and store value in R0

			ST 		R7, SAVE_R7		; Save the value of R7 so we don't infintely loop	
			JSR 	PUSH			; Return to previous instruction
			LD 		R7, SAVE_R7		; Load value of R7 to ret back to evaluate 
			RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
			NOT 	R4, R4			; Take two's complement negative inverse of R4
			ADD 	R4, R4, #1		; Add 1 to properly take negative counterpart of R4
			ADD 	R0, R3, R4		; Subtract R4 from R3
	
			ST 		R7, SAVE_R7		; Save the value of R7 so we don't infintely loop
			JSR 	PUSH			; Jump to PUSH to push value in R0 to stack
			LD 		R7, SAVE_R7		; Load value of R7 to ret back to evaluate 
			RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
			ADD 	R3, R3, #0		; Keep R3 as last updated register
			BRp 	CHECKPOS		; If R3 is positive, check other register
			BRn		CHECKNEG		; If R3 is negative, check other register
			BRz 	ZEROOUT			; If R3 is zero, check other register

CHECKPOS	
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRp 	POSOUT			; If R4 is positive as well, branch to positive output
			Brn		NEGOUT			; If R4 is negative, branch to negative output

CHECKNEG	
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRp 	NEGOUT			; Branch to negative output
			BRn 	POSOUT			; Branch to positive output		

POSOUT		
			ADD 	R3, R3, #0		; Keep R3 as last updated register
			BRp		CHECKR4			; If R3 is already positive, branch to CHECKR4
			NOT 	R3, R3			; Invert R3 to make positive
			ADD 	R3, R3, #1		; Add 1 to make positive 
CHECKR4		
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRp 	READY			; if R4 is also positive, branch to READY
			NOT 	R4, R4			; Invert R4 to make positive
			ADD 	R4, R4, #1		; Add 1 to make positive

READY								; BEGIN MULTIPLICATION PROCESS HERE	BUT RETURN POSITIVE NUMBER
			ADD 	R6, R3, #0		; Add value in R3 into R6

MULLOOP		
			ADD 	R4, R4, #-1		; Subtract one from R4
			BRz 	TRANSFERVAL		; If R4 (counter) = 0, multplication process is done
			ADD 	R3, R3, R6		; Add R3 to R6 (original value of R3) and store in R3
			BRnzp 	MULLOOP			; Unconditionally go back to MULLOOP


NEGOUT
			ADD 	R3, R3, #0		; Keep R3 as last updated register
			BRp		CHECKR4D		; If R3 is already positive, branch to CHECKR4
			NOT 	R3, R3			; Invert R3 to make positive
			ADD 	R3, R3, #1		; Add 1 to make positive 

CHECKR4D		
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRp 	READYD			; if R4 is also positive, branch to READY
			NOT 	R4, R4			; Invert R4 to make positive
			ADD 	R4, R4, #1		; Add 1 to make positive

READYD								; BEGIN MULTPLICATION PROCESS HERE BUT RETURN NEGATIVE NUMBER
			ADD 	R6, R3, #0		; Load value in R3 into R6

MULLOOPD		
			ADD 	R4, R4, #-1		; Subtract one from R4
			BRz 	TURNNEGATIVE	; If R4 (counter) = 0, multplication process is done
			ADD 	R3, R3, R6		; Add R3 to R6 (original value of R3) and store in R3
			BRnzp 	MULLOOPD		; Unconditionally go back to MULLOOPD

TURNNEGATIVE
			NOT 	R3, R3			; Invert R3 to make negative
			ADD 	R3, R3, #1		; Add 1 to make negative
			BRnzp 	TRANSFERVAL		; Uncondtionally branch to TRANSFERVAL  

ZEROOUT		
			AND 	R0, R0, #0		; Set output register, R0, to 0
			BRnzp 	MULDONE			; Unconditionally branch to MULDONE

TRANSFERVAL
			ADD 	R0, R3, #0		; Transfer value of R3 to R0
			BRnzp 	MULDONE			; Unconditionally branch to MULDONE
			
MULDONE		
			ST 		R7, SAVE_R7		; Save the value of R7 so we don't infintely loop
			JSR 	PUSH			; Jump to PUSH to push value in R0 to stack
			LD 		R7, SAVE_R7		; Load value of R7 to ret back to evaluate 
			RET	

DONE		HALT					; done
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRz		DNECASE			; Branch to DNECASE if R4 is 0
			ADD 	R3, R3, #0		; Keep R3 as last updated register
			BRz		DIVZERO			; Branch to DIVZERO if R3 is 0

			NOT 	R1, R4			; Invert R4 and store in R1 by using NOT
			ADD 	R1, R1, #1		; Invert R1 by adding 1
			ADD		R1, R3, R1		; Store the difference of R1 and R4 in R2
			BRn		DIVZERO			; If R3 < R1, return zero by default
			BRnzp 	STANDARD		; If not a special case, branch to standard

DIVZERO		
			AND 	R0, R0, #0		; Set R0 to 0
			BRnzp 	DIVDONE

DNECASE		
			LEA 	R0, UNDEFINED	; Load address of UNDEFINED string into R0
			PUTS					; Output "Undefined" message
			BRnzp 	DONE			; Jump to HALT	
			
STANDARD							; BEGIN STANDARD DIVISON HERE (NO SPECIAL CASES)
			AND 	R1, R1, #0		; Set R1 to 0
			NOT 	R4, R4			; Invert R4 with NOT
			ADD 	R4, R4, #1		; Add 1 to make R4 negative
			ADD 	R3, R3, R4		; Subtract R4 from R3 to initially begin divison process

RETURNDIV	
			ADD 	R1, R1, #1		; Increment division counter to check how many times divided
			ADD 	R3, R3, R4		; Subtract R4 from R3 and continue to loop
			BRzp 	RETURNDIV		; Stop looping when R4 becomes negative
			ADD 	R0, R1, #0		; Load the counter into R0 to put quotient in R0
			BRnzp 	DIVDONE			; Unconditionally branch to DIVDONE
			
DIVDONE		
			ST 		R7, SAVE_R7		; Save the value of R7 so we don't infintely loop
			JSR 	PUSH			; Jump to PUSH to push value in R0 to stack
			LD 		R7, SAVE_R7		; Load value of R7 to ret back to evaluate 
			RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
			ADD 	R4, R4, #0		; Keep R4 as last updated register
			BRz 	EXPZERO			; Branch to EXPZERO if R4 is 0
			BRnzp 	REGEXP			; Unconditionally branch to REGEXP otherwise

EXPZERO		
			AND 	R0, R0, #0		; Set R0 to 0
			ADD 	R0, R0, #1		; Add 1 to R0
			BRnzp 	EXPDONE			; Unconditonally branch to EXPDONE

REGEXP		
			ADD 	R1, R3, #0		; Use R1 to temporarily hold initial value of R3
			ADD 	R6, R3, #0		; Load value of R3 into R6 as an outer counter

TOPLOOP
			ADD 	R4, R4, #-1		; Subtract one from R4
			BRz 	TRANSFEREXP		; If R4 (counter) = 0, exponent process is done
			ADD 	R2, R1, #0		; Repeatedly set R0 to initial value of R3
			ADD 	R6, R3, #0		; Update value of R6 to be added to self
INNERLOOP	
			ADD 	R2, R2, #-1		; Subtract one from R2
			BRz 	TOPLOOP			; Branch to top loop once first iteration of R3*R3 is done
			ADD 	R3, R3, R6		; Add R3 to R6 (original value of R3) and store in R3
			BRnzp 	INNERLOOP		; Unconditionally go back to REGEXP

TRANSFEREXP 
			ADD 	R0, R3, #0		; Transfer value from R3 to R0
			
EXPDONE		
			ST 		R7, SAVE_R7		; Save the value of R7 so we don't infintely loop
			JSR 	PUSH			; Jump to PUSH to push value in R0 to stack
			LD 		R7, SAVE_R7		; Load value of R7 to ret back to evaluate 
			RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
			ST R3, PUSH_SaveR3		; save R3
			ST R4, PUSH_SaveR4		; save R4
			AND R5, R5, #0			;
			LD R3, STACK_END		;
			LD R4, STACk_TOP		;
			ADD R3, R3, #-1			;
			NOT R3, R3				;
			ADD R3, R3, #1			;
			ADD R3, R3, R4			;
			BRz OVERFLOW			; stack is full
			STR R0, R4, #0			; no overflow, store value in the stack
			ADD R4, R4, #-1			; move top of the stack
			ST R4, STACK_TOP		; store top of stack pointer
			BRnzp DONE_PUSH			;

OVERFLOW
			ADD R5, R5, #1			;

DONE_PUSH
			LD R3, PUSH_SaveR3		;
			LD R4, PUSH_SaveR4		;
			RET


PUSH_SaveR3	.BLKW #1				;
PUSH_SaveR4	.BLKW #1				;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
			ST R3, POP_SaveR3		; save R3
			ST R4, POP_SaveR4		; save R3
			AND R5, R5, #0			; clear R5
			LD R3, STACK_START		;
			LD R4, STACK_TOP		;
			NOT R3, R3				;
			ADD R3, R3, #1			;
			ADD R3, R3, R4			;
			BRz UNDERFLOW			;
			ADD R4, R4, #1			;
			LDR R0, R4, #0			;
			ST R4, STACK_TOP		;
			BRnzp DONE_POP			;
UNDERFLOW
			ADD R5, R5, #1			;
DONE_POP
			LD R3, POP_SaveR3		;
			LD R4, POP_SaveR4		;
			RET						;


POP_SaveR3	.BLKW #1				;
POP_SaveR4	.BLKW #1				;
SAVE_R7 	.BLKW #1				;
STACK_END	.FILL x3FF0				;
STACK_START	.FILL x4000				;
STACK_TOP	.FILL x4000				;


UNDEFINED 	.STRINGZ "Undefined"			; Undefined case for division
INVALID_EXP	.STRINGZ "Invalid Expression" 	; Invalid expression for incorrect input


	 		.END
