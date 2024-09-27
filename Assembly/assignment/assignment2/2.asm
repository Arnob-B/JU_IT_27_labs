.model small
.code 
  main proc
  mov ax, @data
  mov DS, ax
  mov ES, ax
  mov di, 0030h
  mov si, 0040h

  mov al , 55h

  mov dl, 00h
  mov cx, 0008h

  cld;
  looping:
    scasb ; comp(ES:DI and al) -> inc di
    jnz l1
      dec di
      mov [si], di
      inc di
      add si, 0002h
  l1:
    loop looping
  mov [si], dl
  int 03h
  main endp
end
