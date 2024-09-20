.model small
.stack 100h
.code
main proc
  mov ax, 3000h
  mov ds, ax

  mov dx, 0000h
  mov si,0040h
  mov ax, [si]; storing 0040,0041 in ax register

  mov si, 0050h
  mov bx, [si]; storing 0050,0051 in bx register

  mul bx; result gets stored in ax and dx

  mov si,0060h
  mov [si],ax ; lower 16 bits
  add si,0002h
  mov [si],dx; higher 16 bits

  int 03h
  mov ah, 4ch
  int 21h
main endp
end
