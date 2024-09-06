# services

|services|hex|extra|
|---|---|---|
|single char input|01|into al reg|
|single char output|02|from dl reg|
|string display|09|from dx reg|
|before program terminate|03||
|program terminate|4c||

### char display
reads from dl register
### string display
will display the string whose offset address is stored in dx regiter

# interruption call
interrupts the cpu execution
```asm
int 21h
```
