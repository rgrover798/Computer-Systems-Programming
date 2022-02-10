.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.
NEWCHAR 
		IN							; Take user input into R0
		LD 		R1, NEW_LINE	 	; Load R1 with the value of NEW_LINE
		NOT 	R1, R1				;
		ADD 	R1, R1, #1			;
		ADD 	R2, R1, R0 			; 
		BRz 	FINISH				; Branch to HALT if newline is reached
		LD 		R1, SPACE			; Load R1 with the value of SPACE
		NOT 	R1, R1				;
		ADD 	R1, R1, #1			;
		ADD 	R2, R1, R0			;
		BRz 	NEWCHAR				; Branch to NEWCHAR is inputted value is a space

 
SPACE   		.FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
		LD 		R1, NEG_OPEN		;
		ADD 	R2, R1, R0			;
		BRnp 	OUTER				; 
		JSR 	PUSH				;
		BRnzp 	NEWCHAR				;
OUTER	JSR 	POP					;
		AND 	R5, R5, #1			;
		BRnz 	CONTINUE			;			
		ADD 	R5, R5, #-2			;
		BRnzp 	CONTINUE			;
CONTINUE
		LD 		R2, STACK_START		;
		LD 		R1, STACK_START		;
		NOT 	R1, R1				;
		ADD 	R1, R1, #1			;
		ADD 	R2, R2, R1			;
	 	BRz		CLEAN				;
		AND 	R5, R5, #0			;
		ADD 	R5, R5, #-1			;
		BRnzp   NEWCHAR				;
CLEAN
		AND 	R5, R5, #0			;
		ADD 	R5, R5, #1			;
		BRnzp 	NEWCHAR				;
		

NEG_OPEN 		.FILL xFFD8
NEG_CLOSED		.FILL xFFD7

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;

PUSH	
		ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;

OVERFLOW
        ADD R5, R5, #1          ;

DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;

POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

FINISH 	HALT	
		.END

