.model small

.code
main proc             
    mov ax, 1000h
    mov ds, ax
    mov [0001h],7h ;num1
    mov [0002h],4h ;num2
    mov [0003h],0h ; to store the sum
    
    mov bl, 00h
    add bl, [0001h]  ;taking the first num
    add bl, [0002h]  ;taking the second num
        
                                                           
    mov [0003h], bl                       
                                  
    ;;output                              
    add bl, 30h ;convet into character    
    mov dl, bl
    mov ah, 02h
    int 21h
    
    mov ah, 4ch
    int 21h
    
main endp
