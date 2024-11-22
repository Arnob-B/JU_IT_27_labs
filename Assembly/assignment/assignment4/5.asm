.model small
.code 

main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov cx, [si]

mov dx , 0000h
mov ax , 0001h

looping:
cmp cx, 0000h
jz exit

mul cx ; ax * cx  -> dx, ax

dec cx
jmp looping

exit:
mov si, 0040h
mov [si], ax
mov si, 0042h
mov [si], dx

int 03h
mov ah, 4ch

main endp
end 

