# cmp
> [!IMPORTANT]
> changes flag, sign , carry flag


```asm
cmp ah, al
```
|case|flag|
|---|---|
|ah > al| C -> 0 , Z-> 0 , S-> 0|
|ah = al| C -> 0 , Z-> 1 , S-> 0|
|ah < al| C -> 1 , Z-> 0 , S-> 1|


# rotations
> [!WARNING]
> in each rotation CF gets effected</br>
> ie if rot with 3h then each rotation will have their own CF states

## ROL 
> [!IMPORTANT]
> MSB wraps -> LSB</br>
> CF takes -> MSB

## ROR 
> [!IMPORTANT]
> LSB wraps -> MSB </br>
> CF takes -> LSB

# Rotation with carry 
## RCL
> [!IMPORTANT]
> LSB wraps -> PREVIOUS CF </br>
> MSB moves to -> CF

## RCR 
> [!IMPORTANT]
> MSB wraps -> previous CF</br>
> LSB moves -> CF


# shifts
> Bit shifting only
> no wraping 
> carry flag gets affected



# AAD

ASCII adj after addition in AL
> if CF is 1 after addition 
> AH incremented by 1 
> af flag set to 1 
> af flag set to 1 

> else
> AH incremented by 0 
> af flag set to 0 
> af flag set to 0 

in either of the case 
> 4 to 7(most significant 4 bits) of the AL is set to 0
