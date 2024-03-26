EXTRN sum: near
STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	X db ?
	Y db ?
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
main:
	mov ax, DSEG
	mov ds, ax
	
	mov ah, 1
	int 21h
	mov X, al

	mov dl, 10
	mov ah, 2
	int 21h
	
	mov ah, 1
	int 21h
	mov Y, al

	mov dl, 10
	mov ah, 2
	int 21h	

	call sum
	sub BH, 48
	mov dl, BH
	mov ah, 2
	int 21h
	mov ax, 4c00h
	int 21h
CSEG ENDS
PUBLIC X
PUBLIC Y
END main
