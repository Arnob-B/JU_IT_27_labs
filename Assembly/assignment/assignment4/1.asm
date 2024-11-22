.model small
.code 

main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov di, 0040h
mov bx, 0050h
mov cx, 0009h


looping:
mov dl, 00h
add dl, [si]
add dl, [di]
mov [bx] , dl 
inc si
inc di 
inc dl

looping looping

int 03h
mov ah, 4ch

main endp
end 

