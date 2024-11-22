.model small
.code
main proc

mov ax, @data
mov ds, ax

mov si, 0040h
mov cx, 0008h

mov dl,00h; contains positive numbers
looper:
mov al, [si]
rol al,1h
jc exit ; if negative
inc dl ; stores count of positive

exit:
inc si

loop looper

mov si,0040h
mov [si], dl
mov dh, 08h
sub dh, dl; dh -> negative count

mov si, 0041h
mov [si], dh

int 03h
mov ah, 4ch

main endp
end

