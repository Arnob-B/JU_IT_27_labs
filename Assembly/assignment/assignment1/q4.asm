.model small
.stack 100h
.code
main proc
  mov ax, @data
  mov ds , ax
  mov si, 0030H
  mov ax, 0000H
  
  ;counter
  mov cx, 0007H

  looping:
  add al, [si]
  jnc exit
  inc ah
  exit:
  inc si
  LOOP looping ; dec counter by 1 and check
  
  mov si, 0050h
  mov [si], ax

  int 03h
  mov ah, 04cH
  int 21h
main endp
END
