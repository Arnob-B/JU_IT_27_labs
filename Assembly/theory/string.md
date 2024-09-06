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
