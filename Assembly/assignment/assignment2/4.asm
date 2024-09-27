; modified the question
;the 0030h will contain the size of the string

.model small
.code 
  main proc
  mov ax, @data
  mov DS, ax
  mov ES, ax

  mov si, 0030h
  mov ch, 00h
  mov cl , [si]
  inc si
  mov di, si
  add di, cx
  dec di; di pointing to last byte
  ; setting up the counter
  mov ah, 00h
  mov al, cl
  mov bl , 02h
  div bl
  mov cl, al


  looping:
    mov bl, [di] ; bl acting as temp variable
    cmp [si], bl ; es:di and ds:si
    jz l1
  failed:
    ;failed
    mov si, 0050h
    mov bx,1111h
    mov [si], bx
    jmp exit
  l1:
    inc si
    dec di
    loop looping
    ;passed
    mov si, 0050h
    mov bx,0ffffh
    mov [si], bx
  exit:
  int 03h
  main endp
end

