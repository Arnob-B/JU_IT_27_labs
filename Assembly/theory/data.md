# defination
contains the data

```asm
.data
 ; variables
 <variable name> <size> <initialvalue>
```

# naming convention rules
1. variable name withing 8 characters
2. alphabets and digits are used 
3. no spaces available
4. only under score as speccial character allowed



# size or variable types
- strings take 1 char/byte
- signed numbers take -(2<sup>n-1</sup>-1) to (2<sup>n-1</sup>-1) 
- unsigned numbers take 0 to (2<sup>n</sup>-1) where n is the no of bits

1. DB(define byte) :-> 1 byte
2. DW(define byte) :-> 2 byte
3. DD(define double word) :-> 4 byte
4. DQ(define quad word) :-> 8 byte
5. DT(define ten bytes) :-> 10 byte

