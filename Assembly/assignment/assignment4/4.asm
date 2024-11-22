.model small
.code 

main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov ah, [si]
mov al, [si]

shr al , 1
xor ah, al

mov si, 0040h
mov [si], ah

int 03h
mov ah, 4ch

main endp
end 
