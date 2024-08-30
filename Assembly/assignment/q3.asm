.model small
.code
main proc
  mov ax, 3000H
  mov ds , ax
  ; used to store the source address
  mov si, 0030H
  ; used to store the destination address
  mov di, 0040H
  ; bl register will be used for holding the data
  ;counter
  mov cx, 8 

  looping:
    mov bl , [si]
    mov [di], bl
    ;moving the source and dest address one bit ahead
    inc si
    inc di
  LOOP looping ; dec counter by 1 and check

  mov ah, 04cH
  int 21h
main endp
END
