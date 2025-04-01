# Assignment 2
1. Write a program to create two threads. Print “In main thread” in main thread and “In child thread” in child thread.[sol](./Sol1.java)

2. Create two threads and call them EvenThread and OddThread. EvenThread will print number as 2 4 6 8 10... and Odd Thread will print number as 1 3 5.... Now, synchronize these two threads to get the output as: 1 2 3 4 5 6 7 8. [sol](./Sol2.java)

3. Consider the following series x = 1+1/1! +1/2! + 1/3! + .........1/10! . Create two threads t1 & t2. t1 will generate the denominators and t2 will form the term and add them up. Finally print the result.[Sol](./Sol3.java)

4. Consider a file that contains a number of integers. Create two threads. Call them ‘producer’ and ‘consumer’ thread. Producer thread will be reading the integers from the file continuously while consumer thread will add them up. Use proper synchronization mechanism if needed.[sol](./Sol4.java)

5. Consider the series 1+2+3+...+100. This can be considered as (1+3+5+...+99)+(2+4+6+...+100). Create two threads to compute two series in parallel (do not use simplified equation). Finally print the final sum.[Sol](./Sol5.java)

6. Consider the following parallel binary search algorithm for series a1, a2...an sorted in increasing order such that n mod 10 = 0. Element to be searched is e.
    1. Create n/10 threads t1, t2,..,tn/10.
    2. Distribute the numbers among threads such that ti will have numbers ai, ai+1, ....a2i-1.
    3. Distribute the element e to all threads.
    4. Each thread searches the element e in its sub-array using binary search algorithm.
[Sol](./Sol6.java)

7. Write a Java program using threading technology and print the thread index and location where the element has been found.[sol](./Sol7.java)

> again this question is same as question 6  
