.model small
.code
main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov di, 0040h
mov bx, 0050h

mov si, 0030h
mov cx, 0007h

mov dl,00h; contains positive numbers

looper:
mov al, [si]
ror al,1h
jc odd ; if odd
; even
mov ax, [si]
mov [bx], ax
inc bx
inc si

loop looper
jmp exit

odd:
mov ax, [si]
mov [di], ax
inc di
inc si

loop looper

exit: 


int 03h
mov ah, 4ch

main endp
end

