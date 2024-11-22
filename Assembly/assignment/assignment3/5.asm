.model small
.code
main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov bh, 00h
mov bl  , [si]
add bl, 40h

mov si, 0050h
mov al, [bx]
mov [si], al

int 03h
mov ah, 4ch

main endp
end
