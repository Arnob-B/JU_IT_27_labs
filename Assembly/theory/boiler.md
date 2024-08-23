# Boiler Plate code

There are different methods to write the boiler Plate
> It generaly depends on the assembler

> all the codes will be for masm


### One of the Easiest ways
```asm
.dosseg
.model small

.code
        main proc
        ; write you code here
        main endp
end main
```

### masm 6.0 or above
```asm
.model small
.stack ;use default 1-kb stack
.data 
.code 
.startup
; all codes here
.exit
end

```
# dosseg
this command enables the segment to be called in any random order
