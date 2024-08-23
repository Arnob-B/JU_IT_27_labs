

|services|hex|extra|
|---|---|---|
|single char input|01|into al reg|
|single char output|02|from dl reg|
|string display|09|from dx reg|

### string display
mov ah , 09h
will display the string whose offset address is stored in dx regiter
# interruption call
int 21h
