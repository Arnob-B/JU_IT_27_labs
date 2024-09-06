# MOV instructions
```asm
mov <source operand > <dest operand>
```
operand :-> memory variable,registers, constants
1. both source and dest cannot be memory var at the same time 
2. size of both operand should be same

### moving values directly to data segment
mov [si] 1234h;
lower byte is 34 and higher byte is 12
let us say si is pointing to 0030h;
0030h will store 34
0031h will store 12

> what i hv tested is that you can't move 1 byte data direclty into memory without using 8 bit register
ie
```asm
mov [si] , 23h;
mov [si], 0023h;
mov [si], 0000h
```
are all invalid

## moving in memory
mov memvar, 23h;



# Exchange instruction
```asm
xch <operand1> <operand2>
```
operand :-> memory variable,registers, constants
1. both source and dest cannot be memory var at the same time 
2. size of both operand should be same



# Add
while adding two 16 bit register or (register and memory pair)
the carry in the half 8 bit is autmatically addjusted 
for ex :-> if there is carry generated in B7 then it will be added to B8



# MUL
```asm
mul <operand>
```
operand : should be 8bit or 16bit register (memory is not allowed)
#### 8bit register as operand 
mul bl 
bl * al -> stores in AX register

#### 16bit register as operand
mul bx 
bx * ax -> stores in DX,AX register
higherbyte -> DX
lowerbyte -> AX

# Div
```asm
div <source operand>
```
source operand(s) : should be 8bit or 16bit register (memory is not allowed)
#### 8bit register as source operand
> operation = AX/s

quotient -> al
remainder -> ah
#### 16bit register as source operand
> operation =( DX,AX )/ s

quotient -> ax
remainder -> dx
