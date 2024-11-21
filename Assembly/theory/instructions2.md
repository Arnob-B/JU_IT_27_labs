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
> in each rotation CF gets effected
> ie if rot with 3h then each rotation will have their own CF states

## ROL 
> [!IMPORTANT]
> MSB wraps -> LSB
> CF takes -> MSB

## ROR 
> [!IMPORTANT]
> LSB wraps -> MSB
> CF takes -> LSB

# Rotation with carry 
## RCL
> [!IMPORTANT]
> LSB wraps -> PREVIOUS CF
> MSB moves to -> CF

## RCR 
> [!IMPORTANT]
> MSB wraps -> previous CF
> LSB moves -> CF


# shifts
> Bit shifting only
> no wraping 
> carry flag gets affected

