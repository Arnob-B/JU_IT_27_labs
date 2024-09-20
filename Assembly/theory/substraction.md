# Binary substractions
> 2's compliment :-> 1's compliment + 1
> fun fact 2's compliment is used to denote -ve numbers

code for 2's compliment
```asm
not reg; 1's compliment
inc reg
```
```asm
neg reg
```
## using 2's compliment method
general theory :-> 
 for a-b
 do a + 2'comp(b)
 if(final carry is 1)
 - then it is positive and ignore the carry(due to overflow)
 else 
 - the result is negative and is in 2's compliment form
```asm
mov ax,0000h
mov al, 01h
mov bl, 01h

;al - bl
;2's compliment
not bl
inc bl

add al, bl

jc exit; no is positive
not al
inc al

exit:
  int 03h
```
## using 1's compliment method(derived from 2's compliment)
general theory :-> 
 for a -b
 do a + 1'comp(b)
 if(result has a carry 1)
 - then it is positive and ignore the carry and then finally add 1 to result
 else 
 - the result is negative and is in 1's compliment form
```asm
mov ax,0000h
mov al, 01h
mov bl, 01h

;al - bl
;1's compliment
not bl
add al, bl

jc exit; no is positive
not al
dec al

exit:
  inc al
  int 03h
```

## using sub instruction
uses 2's compliment method
general theory :-> 
 for a-b
 sub a , b; stores in a
 if CF flag is 1 
 then the number is negative and answer is **1's compliment** of the number 
 or simple neg;
