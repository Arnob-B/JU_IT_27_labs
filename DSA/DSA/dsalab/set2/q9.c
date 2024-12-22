#include <stdio.h>
#include <stdlib.h>

// Define the stack structure
typedef struct Stack {
    int top;
    unsigned capacity;
    int *array;
} Stack;

// Function to create a stack of given initial capacity
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is -1
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to add an item to stack
void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// Function to get the top item from stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->array[stack->top];
}

// Define the queue structure
typedef struct Queue {
    Stack* stack1;
    Stack* stack2;
} Queue;

// Function to create a queue using two stacks
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->stack1 = createStack(capacity);
    queue->stack2 = createStack(capacity);
    return queue;
}

// Function to enqueue an item to queue
void enqueue(Queue* queue, int item) {
    push(queue->stack1, item);
    printf("%d enqueued to queue\n", item);
}

// Function to dequeue an item from queue
int dequeue(Queue* queue) {
    if (isEmpty(queue->stack2)) {
        while (!isEmpty(queue->stack1)) {
            push(queue->stack2, pop(queue->stack1));
        }
    }

    if (isEmpty(queue->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }
    return pop(queue->stack2);
}

// Main function to test the queue implementation
int main() {
    Queue* queue = createQueue(100);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("%d dequeued from queue\n", dequeue(queue));
    printf("%d dequeued from queue\n", dequeue(queue));
    printf("%d dequeued from queue\n", dequeue(queue));

    return 0;
}
