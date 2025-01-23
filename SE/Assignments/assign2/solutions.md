# prerequisite
> **command \<breakpoint no\>** -> allows us to add automatically execute gdb commands on breakpoint hits

> break \<no\> \<condition\> -> allows us to perform a condition check at that break point hit and if the condition is true , the program gets hault

# Assignment 2
#### compile and debugging
```bash
gcc -g d.c
```
```bash
gdb a.out
```
#### a.
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
#### b.
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
#### c. 
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
#### d.
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

#### e. 
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
(gdb) break 6
Breakpoint 2 at 0x114d: file d.c, line 6.
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>continue
>end
(gdb) command 2
Type commands for breakpoint(s) 2, one per line.
End with a line saying just "end".
>continue
>end
(gdb) run
...
...
...
you have reached [9][197][1000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][197][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][198][1000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][198][2000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][199][1000]-th iteraion

Breakpoint 1, main () at d.c:9
9               t1 = i;
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 144167) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555515f in main at d.c:9
        stop only if k%1000==0
        breakpoint already hit 6000 times
        continue
2       breakpoint     keep y   0x000055555555514d in main at d.c:6
        breakpoint already hit 10 times
        continue
(gdb) quit
```
#### f.
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
(gdb) break 6
Breakpoint 2 at 0x114d: file d.c, line 6.
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>continue
>end
(gdb) command 2
Type commands for breakpoint(s) 2, one per line.
End with a line saying just "end".
>continue
>end
(gdb) disable 1
(gdb) run
...
...
you have reached [9][191][1000]-th iteraion
you have reached [9][191][2000]-th iteraion
you have reached [9][192][1000]-th iteraion
you have reached [9][192][2000]-th iteraion
you have reached [9][193][1000]-th iteraion
you have reached [9][193][2000]-th iteraion
you have reached [9][194][1000]-th iteraion
you have reached [9][194][2000]-th iteraion
you have reached [9][195][1000]-th iteraion
you have reached [9][195][2000]-th iteraion
you have reached [9][196][1000]-th iteraion
you have reached [9][196][2000]-th iteraion
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 170146) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep n   0x000055555555515f in main at d.c:9
        stop only if k%1000==0
        continue
2       breakpoint     keep y   0x000055555555514d in main at d.c:6
        breakpoint already hit 10 times
        continue
(gdb) quit
```

#### g.
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
(gdb) break 8 if k%1000 ==0
Breakpoint 1 at 0x115f: file d.c, line 9.
(gdb) break 6
Breakpoint 2 at 0x114d: file d.c, line 6.
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>continue
>end
(gdb) command 2
Type commands for breakpoint(s) 2, one per line.
End with a line saying just "end".
>print i
>continue
>end
(gdb) disable 1
...
...
you have reached [7][199][2000]-th iteraion

Breakpoint 2, main () at d.c:6
6           for (j = 0; j < 200; j++)
$10 = 8
you have reached [8][0][1000]-th iteraion
you have reached [8][0][2000]-th iteraion
you have reached [8][1][1000]-th iteraion
...
...
you have reached [8][199][2000]-th iteraion

Breakpoint 2, main () at d.c:6
6           for (j = 0; j < 200; j++)
$10 = 9
you have reached [9][0][1000]-th iteraion
you have reached [9][0][2000]-th iteraion
you have reached [9][1][1000]-th iteraion
...
...
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 289107) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep n   0x000055555555515f in main at d.c:9
        stop only if k%1000 ==0
        continue
2       breakpoint     keep y   0x000055555555514d in main at d.c:6
        breakpoint already hit 10 times
        print i
        continue
(gdb) quit
```
> [!IMPORTANT]
> another variation of the command

```bash
>printf "value of i -> %d\n",i
>continue
>end
(gdb) run
...
...
you have reached [8][199][1000]-th iteraion
you have reached [8][199][2000]-th iteraion

Breakpoint 1, main () at d.c:6
6           for (j = 0; j < 200; j++)
value of i -> 9
you have reached [9][0][1000]-th iteraion
you have reached [9][0][2000]-th iteraion
...
...
```
#### h.
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
(gdb) break 6
Breakpoint 2 at 0x114d: file d.c, line 6.
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>continue
>end
(gdb) command 2
Type commands for breakpoint(s) 2, one per line.
End with a line saying just "end".
>print i
>continue
>end
(gdb) disable 1
(gdb) delete 2
(gdb) run
...
...
...
you have reached [9][191][1000]-th iteraion
you have reached [9][191][2000]-th iteraion
you have reached [9][192][1000]-th iteraion
you have reached [9][192][2000]-th iteraion
you have reached [9][193][1000]-th iteraion
you have reached [9][193][2000]-th iteraion
you have reached [9][194][1000]-th iteraion
you have reached [9][194][2000]-th iteraion
you have reached [9][195][1000]-th iteraion
you have reached [9][195][2000]-th iteraion
you have reached [9][196][1000]-th iteraion
you have reached [9][196][2000]-th iteraion
you have reached [9][197][1000]-th iteraion
you have reached [9][197][2000]-th iteraion
you have reached [9][198][1000]-th iteraion
you have reached [9][198][2000]-th iteraion
you have reached [9][199][1000]-th iteraion
you have reached [9][199][2000]-th iteraion
[Inferior 1 (process 373909) exited normally]
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep n   0x000055555555515f in main at d.c:9
        stop only if k%1000==0
        continue
(gdb) quit
```
