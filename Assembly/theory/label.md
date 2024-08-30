# label
```asm
LABEL:
;CODE
```
> put colon right after the name

```asm
startingpoint : ; this is illegal
```


# Looping
```asm
LOOP <labelname>
```

> decreases the cx register by 1 and checks if not equal to 0
