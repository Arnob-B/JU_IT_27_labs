.model small
.code
main proc
  mov ax, 3000h
  mov ds, ax

  mov dx, 0000h
  mov ax, 2222h
  mov bx, 0055h;

  div bx; q in ax , r in dx

  mov si, 0060h
  mov [si], ax; quotient
  add si, 02h
  mov [si], dx; remainder

  int 03h
  mov ah, 4ch
  int 21h
main endp
end

