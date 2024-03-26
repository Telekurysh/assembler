PUBLIC sum
EXTRN X: byte
EXTRN Y: byte

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
sum proc near
	mov BH, X
	add BH, Y
	ret
sum endp
CSEG ENDS
END
