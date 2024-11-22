.model small
.code
main proc
mov ax, @data
mov ds, ax
mov si, 0030h

mov ah, [si]
mov al , [si]

mov cl , 04h;
shl al , cl
shr al , cl
add al, 30h ; converting to ascii

;ah
shr ah, cl ;ah is set
add ah, 30h ; converting to ascii


mov si, 0050h
mov [si], al
mov si, 0051h
mov [si], ah

int 03h
mov ah, 4ch


main endp
end main

