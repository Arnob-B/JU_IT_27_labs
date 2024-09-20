.model small
.stack 100h
.data
.code
main proc
mov ax,@data
mov ds,ax
mov ax,0000h
mov si,0040h
mov al,[si]
mov si,0050h
sub al,[si]
das
mov dl,00h

jnc exit
mov bl,al ; temporary register
mov al,99h
sub al,bl ; 99 - result
add al,01h ; 100 - result
daa ; adjustments
mov dl,01h ; shows the number is negative
exit:
mov si,0060h
mov [si],al
inc si
mov [si],dl
int 03h
main endp
end main

