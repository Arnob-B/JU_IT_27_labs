.model small
.code
main proc

mov ax, @data
mov ds, ax

mov si,0030h
mov ah,01h
mov al,01h
mov [si], ah
inc si
mov [si], al
mov bl, 00h
mov cx, 0008h

looping:
mov bl, 00h
add bl , ah
add bl, al

inc si
mov [si], bl


mov ah, al
mov al, bl

loop looping

int 03h
mov ah, 4ch


main endp
end

