// 1️ Stack using Array (push, pop, peek, isEmpty, isFull, size)
#include <stdio.h>
#define MAX 5

int stack[MAX];
int top = -1;

// Function prototypes
void push(int value);
void pop();
int peek();
int isEmpty();
int isFull();
int size();
void display();

int main() {
    push(10);
    push(20);
    push(30);
    display();
    printf("Top element: %d\n", peek());
    pop();
    display();
    printf("Stack size: %d\n", size());
    return 0;
}

void push(int value) {
    if (isFull()) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = value;
    printf("Pushed %d\n", value);
}

void pop() {
    if (isEmpty()) {
        printf("Stack Underflow!\n");
        return;
    }
    printf("Popped %d\n", stack[top--]);
}

int peek() {
    if (isEmpty()) {
        printf("Stack Empty!\n");
        return -1;
    }
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == MAX - 1;
}

int size() {
    return top + 1;
}

void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack: ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

// Convert Infix to Postfix Expression

#include <stdio.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infixToPostfix(char* expr) {
    char postfix[MAX];
    int i, k = 0;
    char c;
    for (i = 0; expr[i] != '\0'; i++) {
        c = expr[i];
        if (isalnum(c))
            postfix[k++] = c;
        else if (c == '(')
            push(c);
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

int main() {
    char expr[] = "A+(B*C-(D/E^F)*G)*H";
    infixToPostfix(expr);
    return 0;

    
// Evaluate Postfix Expression

#include <stdio.h>
#include <ctype.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int v) { stack[++top] = v; }
int pop() { return stack[top--]; }

int evaluate(char* exp) {
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];
        if (isdigit(c)) {
            push(c - '0');
        } else {
            int b = pop();
            int a = pop();
            switch (c) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
    }
    return pop();
}

int main() {
    char exp[] = "231*+9-";
    printf("Result = %d\n", evaluate(exp));
    return 0;
}



// Singly Linked List (Insertion at beginning, end, specific position)


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insertAtBegin(int v);
void insertAtEnd(int v);
void insertAtPos(int v, int pos);
void display();

int main() {
    insertAtBegin(10);
    insertAtEnd(20);
    insertAtPos(15, 2);
    display();
    return 0;
}

void insertAtBegin(int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v;
    n->next = head;
    head = n;
}

void insertAtEnd(int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v;
    n->next = NULL;
    if (head == NULL) head = n;
    else {
        struct Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }
}

void insertAtPos(int v, int pos) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v;
    if (pos == 1) {
        n->next = head;
        head = n;
        return;
    }
    struct Node* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;
    n->next = temp->next;
    temp->next = n;
}

void display() {
    struct Node* t = head;
    while (t) {
        printf("%d -> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}


// Singly Linked List (Deletion from beginning, end, specific node)

void deleteBegin() {
    if (head == NULL) return;
    struct Node* temp = head;
    head = head->next;
    free(temp);
}

void deleteEnd() {
    if (head == NULL) return;
    if (head->next == NULL) { free(head); head = NULL; return; }
    struct Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void deletePos(int pos) {
    if (head == NULL) return;
    if (pos == 1) { deleteBegin(); return; }
    struct Node* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;
    struct Node* del = temp->next;
    temp->next = del->next;
    free(del);
}


// Doubly Linked List (Add & Delete)


#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;

void insertEnd(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = val;
    n->next = NULL;
    n->prev = NULL;
    if (head == NULL) head = n;
    else {
        struct Node* t = head;
        while (t->next) t = t->next;
        t->next = n;
        n->prev = t;
    }
}

void deleteEnd() {
    if (head == NULL) return;
    struct Node* t = head;
    while (t->next != NULL)
        t = t->next;
    if (t->prev) t->prev->next = NULL;
    else head = NULL;
    free(t);
}

void display() {
    struct Node* t = head;
    printf("List: ");
    while (t) {
        printf("%d <-> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}

int main() {
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);
    display();
    deleteEnd();
    display();
    return 0;
}


// Binary Tree (Inorder, Preorder, Postorder)

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v; n->left = n->right = NULL;
    return n;
}

void inorder(struct Node* r) {
    if (r) {
        inorder(r->left);
        printf("%d ", r->data);
        inorder(r->right);
    }
}

void preorder(struct Node* r) {
    if (r) {
        printf("%d ", r->data);
        preorder(r->left);
        preorder(r->right);
    }
}

void postorder(struct Node* r) {
    if (r) {
        postorder(r->left);
        postorder(r->right);
        printf("%d ", r->data);
    }
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Inorder: "); inorder(root);
    printf("\nPreorder: "); preorder(root);
    printf("\nPostorder: "); postorder(root);
    return 0;
}


// Binary Search Tree (Insert & Search)

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int v) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = v; n->left = n->right = NULL;
    return n;
}

struct Node* insert(struct Node* root, int v) {
    if (root == NULL) return newNode(v);
    if (v < root->data)
        root->left = insert(root->left, v);
    else if (v > root->data)
        root->right = insert(root->right, v);
    return root;
}

int search(struct Node* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search(root->left, key);
    else return search(root->right, key);
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 20);
    printf("Search 15: %s\n", search(root, 15) ? "Found" : "Not Found");
    printf("Search 7: %s\n", search(root, 7) ? "Found" : "Not Found");
    return 0;
}


//all sorting techniques

#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void bubbleSort(int a[], int n) {
    for (int i=0; i<n-1; i++)
        for (int j=0; j<n-i-1; j++)
            if (a[j] > a[j+1])
                swap(&a[j], &a[j+1]);
}

void selectionSort(int a[], int n) {
    for (int i=0; i<n-1; i++) {
        int min=i;
        for (int j=i+1; j<n; j++)
            if (a[j]<a[min]) min=j;
        swap(&a[min], &a[i]);
    }
}

void insertionSort(int a[], int n) {
    for (int i=1; i<n; i++) {
        int key=a[i], j=i-1;
        while (j>=0 && a[j]>key)
            a[j+1]=a[j--];
        a[j+1]=key;
    }
}

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void printArray(int a[], int n) {
    for (int i=0; i<n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {5, 2, 9, 1, 5, 6};
    int n = 6;
    printf("Original array: ");
    printArray(a, n);

    quickSort(a, 0, n - 1);
    printf("Sorted array: ");
    printArray(a, n);
    return 0;
}
