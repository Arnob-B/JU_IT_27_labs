.model small
.code
main proc
  mov ax, @data
  mov ds , ax
  ; used to store the source address
  mov si, 0030H
  ; used to store the destination address
  mov di, 0050H; bl register will be used for holding the data
  mov bl , 00h;
  mov [di],bl; making their initial values 0
  inc di
  mov [di],bl
  dec di
  
  ;counter
  mov cx, 7 

  looping:
    mov bl , [si]
    add [di], bl
    mov bl,00h;
    adc bl,bl
    inc di
    add [di],bl
    dec di
    ;moving the source address one bit ahead
    inc si
  LOOP looping ; dec counter by 1 and check

  mov ah, 04cH
  int 21h
main endp
END
