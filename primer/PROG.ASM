EXTRN input_proc: near
STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	X db ?
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG,  SS:STK, DS:DSEG
main:
	mov ax, DSEG
	mov ds, ax
	call input_proc
	mov dl, 13
	mov ah, 2
	int 21h
	mov dl, 10
	int 21h
	mov dl, X
	int 21h
	mov ax, 4c00h
	int 21h
CSEG ENDS
PUBLIC X
END main
