.model small
.stack 100h
.data
.code

main proc
mov ax, @data
mov ds, ax

mov si, 0050h
mov al, [si]
mov si, 0040h

mov ah, 00h

sub al, [si]
das
jnc l2
adc ah, 00h

l2: mov si, 0060h
mov [si], ax

int 03h
mov ah, 4ch
int 21h

main endp
end main
