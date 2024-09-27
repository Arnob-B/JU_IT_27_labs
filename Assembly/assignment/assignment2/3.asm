.model small
.code 
  main proc
  mov ax, @data
  mov DS, ax
  mov ES, ax

  mov si, 0030h
  mov di, 0040h
  mov cl , [si]
  cmp [di], cl ; checking if the string length is equal or not
  jnz failed 
  inc si
  inc di
  mov ch, 00h

  cld;
  looping:
    cmpsb ; es:di and ds:si and inc di and si
    jz l1
  failed:
    ;failed
    mov si, 0050h
    mov bx,1111h
    mov [si], bx
    jmp exit
  l1:
    loop looping
    ;passed
    mov si, 0050h
    mov bx,0ffffh
    mov [si], bx
  exit:
  int 03h
  main endp
end

