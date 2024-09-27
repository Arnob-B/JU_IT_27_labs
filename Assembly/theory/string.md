10 is newline feed
13 is carriage return
```asm
newline db 10,13,"$"
```



# movsb
move string byte 
    moves each 1 byte at a time from si to di
ds -> source data segment
si -> starting index
es -> destination data segment
di -> destination index
cld -> clear the direction flag
std -> set direction flag
cx -> counter register to store the no of repitition


```asm
  mov ax, 3000h
  mov ds, ax
  mov es, ax
  mov si, 0030h
  mov di, 0050h
  mov cx,0005h
  cld
  rep movsb
```

# scas
compare string with regiters and increases the index register (depending on the direction flag)
> data should be present in ES:DI
scasb :-> AL
scasw :-> AX

# cmps
compare string in memory with another string in memory and increases the index registers (depending on the flags)
> data should be present in ES:DI and DS:SI
cmpsb : byte comparison
cmpsw : word comparison

