.model small
.code
main proc
  mov ax, 3000h
  mov ds, ax
  mov es, ax
  mov si, 0030h
  mov di, 0050h
  mov cx,0005h
  cld
  rep movsb
  mov ah, 03h
  mov ah, 4ch
  int 21h
main endp
end

