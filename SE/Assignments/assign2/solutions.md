# Assignment 2
```bash
gcc -g d.c
```
```bash
gdb a.out
```
a.
```bash
(gdb) list
1       #include <stdio.h>
2
3       int main() {
4         int i, j, k;
5         for (i = 0; i < 10; i++)
6           for (j = 0; j < 200; j++)
7             for (k = 0; k < 3000; k++) {
8               int t1, t2;
9               t1 = i;
10              t2 = j;
(gdb) break 8
Breakpoint 1 at 0x115f: file d.c, line 9.
```
b.
```bash
(gdb) command
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>silent
>continue
>end
(gdb) run
you have reached [0][1][1000]-th iteraion
you have reached [0][1][2000]-th iteraion
you have reached [0][2][1000]-th iteraion
you have reached [0][2][2000]-th iteraion
you have reached [0][3][1000]-th iteraion
you have reached [0][3][2000]-th iteraion
...
...
...
you have reached [9][195][2000]-th iteraion
you have reached [9][196][1000]-th iteraion
you have reached [9][196][2000]-th iteraion
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 1172475) exited normally]
(gdb) info breakpoints
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555515f in main at d.c:9
        breakpoint already hit 6000000 times
        silent
        continue

(gdb) quit
```
c. 
```bash
(gdb) l
1       #include <stdio.h>
2
3       int main() {
4         int i, j, k;
5         for (i = 0; i < 10; i++)
6           for (j = 0; j < 200; j++)
7             for (k = 0; k < 3000; k++) {
8               int t1, t2;
9               t1 = i;
10              t2 = j;
(gdb) break d.c:8 if k==1000
Breakpoint 1 at 0x115f: file d.c, line 9.
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>continue
>end
(gdb) run 
...
...
Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [0][4][1000]-th iteraion
you have reached [0][4][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [0][5][1000]-th iteraion
you have reached [0][5][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [0][6][1000]-th iteraion
you have reached [0][6][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
...
...
...
you have reached [9][195][1000]-th iteraion
you have reached [9][195][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][196][1000]-th iteraion
you have reached [9][196][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 1278027) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555515f in main at d.c:9
        stop only if k==1000
        breakpoint already hit 2000 times
        continue
(gdb) quit
```
d.
```bash
(gdb) l
1       #include <stdio.h>
2
3       int main() {
4         int i, j, k;
5         for (i = 0; i < 10; i++)
6           for (j = 0; j < 200; j++)
7             for (k = 0; k < 3000; k++) {
8               int t1, t2;
9               t1 = i;
10              t2 = j;
(gdb) break 8 if k%1000==0
Breakpoint 1 at 0x115f: file d.c, line 9.
(gdb) command
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>silent
>continue
>end
(gdb) run
you have reached [0][0][1000]-th iteraion
you have reached [0][0][2000]-th iteraion
you have reached [0][1][1000]-th iteraion
you have reached [0][1][2000]-th iteraion
you have reached [0][2][1000]-th iteraion
you have reached [0][2][2000]-th iteraion
you have reached [0][3][1000]-th iteraion
you have reached [0][3][2000]-th iteraion
you have reached [0][4][1000]-th iteraion
you have reached [0][4][2000]-th iteraion
you have reached [0][5][1000]-th iteraion
you have reached [0][5][2000]-th iteraion
you have reached [0][6][1000]-th iteraion
you have reached [0][6][2000]-th iteraion
you have reached [0][7][1000]-th iteraion
...
...
...
you have reached [9][195][2000]-th iteraion
you have reached [9][196][1000]-th iteraion
you have reached [9][196][2000]-th iteraion
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 1307790) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555515f in main at d.c:9
        stop only if k%1000==0
        breakpoint already hit 6000 times
        silent
        continue
(gdb) quit
```
