.model small
.code
main proc
  mov ax, 3000h
  mov ds,ax
  mov cx, 0005h
  mov ax, 0000h
  mov si, 0030h
  looping:
    add al,[si]
    daa
    adc ah,00h
    inc si
  LOOP looping

  mov si,0040h;
  mov [si],ax;
  int 03h
  mov ah,4ch
  int 21h
main endp
end
