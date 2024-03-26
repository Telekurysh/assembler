PUBLIC input_proc
EXTRN X: byte

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
input_proc proc near
	mov ah, 1
	int 21h
	mov X, al
	ret
input_proc endp
CSEG ENDS
END
