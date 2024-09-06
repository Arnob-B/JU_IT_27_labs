.model small
.code
main proc
  mov ax, 3000h
  mov ds, ax

  mov si,0040h
  mov al, [si]; storing 0040 in al register

  mov si, 0050h;
  mov bl, [si]; storing 0050 in bl register

  mul bl

  mov si, 0060h
  mov [si], ax

  mov ah, 03h
  mov ah, 4ch
  int 21h
main endp
end

