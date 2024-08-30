# MOV instructions
```asm
mov <source operand > <dest operand>
```
operand :-> memory variable,registers, constants
1. both source and dest cannot be memory var at the same time 
2. size of both operand should be same

> in masm mov [si], 00h gives operand must hv same size error
so its better to use memory and register ie mov [si] , bl


## moving in memory
mov memvar, 23h;



# Exchange instruction
```asm
xch <operand1> <operand2>
```
operand :-> memory variable,registers, constants
1. both source and dest cannot be memory var at the same time 
2. size of both operand should be same
