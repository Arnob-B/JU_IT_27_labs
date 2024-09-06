.model small
.code
main proc
  mov ax, 3000h
  mov ds, ax

  mov ax, 0088h
  mov bl, 33h

  div bl; q in al , r in ah

  mov si, 0060h
  mov [si], ax

  mov ah, 03h
  mov ah, 4ch
  int 21h
main endp
end

