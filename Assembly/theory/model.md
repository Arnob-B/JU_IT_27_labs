# defination
specifies total amnt of memory the program needs

```asm
.model <spec>
```

# specs
each segment :-> 64kb
## 1. small
    code: one segment 
    data: one segment
## 2. medium
    code: more than 1 segment 
    data: one segment
## 3. compact
    code: in one segment 
    data: more than one segment
## 4. large
    code & data: in one segment 
## 5. huge
    all memory available
