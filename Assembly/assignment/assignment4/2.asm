.model small
.code 

main proc

mov ax, @data
mov ds, ax

mov si, 0030h
mov ch, 00h
mov cl, [si]
mov al , 00h
mov ah , 00h


looper:
add al , 01h
daa
adc ah, 00h

loop looper


mov si, 0040h
mov [si], ax

int 03h
mov ah, 4ch

main endp
end 

