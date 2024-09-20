.model small
.stack 100h
.code
main proc
  mov ax, @data
  mov ds , ax
  mov si, 0030H
  mov ax, 0000H
  mov dl, 00h ; to store the carry

  ;counter
  mov cx, 0005H

  looping:
  add ax, [si]
  jnc exit
  inc dl
  exit:
  add si, 0002h
  LOOP looping ; dec counter by 1 and check
  
  mov si, 0050h
  mov [si], ax
  mov si, 0052h
  mov [si], dl

  int 03h
  mov ah, 04cH
  int 21h
main endp
END
