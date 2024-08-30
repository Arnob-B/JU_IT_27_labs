.model small
.code
main proc
  mov ax, @data
  mov ds , ax
  ; used to store the source address
  mov si, 0030H
  ; used to store the destination address
  mov di, 0050h
  mov bx, 0000h
  mov [di],bx;
  add di, 0002h;
  mov [di], bl;
  sub di, 0002h;
  
  ;counter
  mov cx, 5 
  looping:
    mov bx , [si]
    add [di], bx
    mov bl,00h;
    adc bl,bl
    add di,0002h
    add [di],bl; [di] = [di] + bl + cf
    sub di, 0002h
    add si,02h
  LOOP looping ; dec counter by 1 and check

  mov ah, 04cH
  int 21h
main endp
END

