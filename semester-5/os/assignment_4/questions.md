# ASSIGNMENT – 4
### mmap and page fault
> totla marks - 10 \[co2\]


## Objective
The objective of this programming assignment is to use the `mmap()` system call and observe **page faults** using the `sar` command.

---

## Steps

1. **Create a Big File**
   - Use the `fallocate` command to create a big file of about **8GB**.

2. **Write a Random Byte**
   - Write a single byte value (**X**) at a specific offset (**F**) in the file.
   - Generate values using a random function:
     - **F**: anywhere between `0` and `8GB`.
     - **X**: anywhere between `0–255`.

3. **Map File into Memory**
   - Use `mmap()` to map the file into the virtual address space.

4. **Read from the Offset**
   - Read data from the same offset (**F**) from the mapped memory.
   - Let the read value be `X'`.

5. **Verify Data**
   - If `X == X'`, continue.
   - If verification fails (`X != X'`), print an error message and terminate the program.
   - Display the offset value **F** in **hexadecimal format**.

6. **Loop Execution**
   - Repeat the sequence of:
     - Writing a random byte.
     - Reading from the offset.
     - Verifying correctness.
   - Run this inside a `while` loop **forever**.

7. **Observe Page Faults**
   - In another terminal, execute:
     ```bash
     sar -B 1
     ```
   - This command should be started **before** running the above program.
   - Observe that **page faults increase** once the program starts executing.

---

## Expected Output

1. **Program Output**
   - Should print verification steps and offset values (in hex).
   - Print an error and terminate if verification fails.

2. **`sar` Command Output**
   - Should display page fault statistics increasing as the program runs.

---

## Submission Guidelines
- Paste the output of the program and the `sar` command as a **comment at the beginning of the program file**.
