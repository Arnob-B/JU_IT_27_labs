.MODEL SMALL
.STACK 100H
.CODE
  MAIN PROC
    MOV AX,@DATA
    MOV DS,AX
    MOV CL, 00H
    ; STORING  0030H
    MOV SI , 0030H
    MOV BL, [SI]
    ;STORING 0040H
    MOV SI, 0040H
    MOV AL, [SI]
    ;MAKING 2'S COMPLIMENT OF AL
    ;NEG AL
    NOT BL
    INC BL
    ;ADDITION
    ADD AL, BL

    CMC
    ADC CL, CL

    JNC L1
    ;answer is -ve and res is 2's comp of al 
    NOT AL
    INC AL
    L1:
      MOV SI, 0050H
      MOV [SI],AL
      MOV SI, 0051H
      MOV [SI], CL
    INT 3H
    MOV AH,4CH
    INT 21H
  MAIN ENDP
END
