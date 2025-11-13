#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Q1. Stack using Array

int stack[MAX];
int top = -1;

void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = value;
    printf("Pushed %d\n", value);
}

void pop() {
    if (top == -1) {
        printf("Stack Underflow!\n");
        return;
    }
    printf("Popped %d\n", stack[top--]);
}

int peek() {
    if (top == -1) {
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
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack: ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Size\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                value = peek();
                if (value != -1) printf("Top: %d\n", value);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Size: %d\n", size());
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q2. Convert Infix to Postfix

char stack2[MAX];
int top2 = -1;

void push2(char c) {
    stack2[++top2] = c;
}

char pop2() {
    return stack2[top2--];
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infixToPostfix(char* expr) {
    char postfix[MAX];
    int i, k = 0;
    for (i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (isalnum(c))
            postfix[k++] = c;
        else if (c == '(')
            push2(c);
        else if (c == ')') {
            while (top2 != -1 && stack2[top2] != '(')
                postfix[k++] = pop2();
            pop2();
        } else {
            while (top2 != -1 && precedence(stack2[top2]) >= precedence(c))
                postfix[k++] = pop2();
            push2(c);
        }
    }
    while (top2 != -1)
        postfix[k++] = pop2();
    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

int main() {
    char expr[MAX];
    int choice;
    while (1) {
        printf("\n1. Convert Infix to Postfix\n2. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", expr);
                top2 = -1;
                infixToPostfix(expr);
                break;
            case 2:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q3. Evaluate Postfix Expression

int stack3[MAX];
int top3 = -1;

void push3(int v) {
    stack3[++top3] = v;
}

int pop3() {
    return stack3[top3--];
}

int evaluate(char* exp) {
    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];
        if (isdigit(c)) {
            push3(c - '0');
        } else {
            int b = pop3();
            int a = pop3();
            switch (c) {
                case '+': push3(a + b); break;
                case '-': push3(a - b); break;
                case '*': push3(a * b); break;
                case '/': push3(a / b); break;
            }
        }
    }
    return pop3();
}

int main() {
    char exp[MAX];
    int choice;
    while (1) {
        printf("\n1. Evaluate Postfix\n2. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter postfix expression: ");
                scanf("%s", exp);
                top3 = -1;
                printf("Result = %d\n", evaluate(exp));
                break;
            case 2:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q4. Singly Linked List Insertion

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

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
    if (temp == NULL) {
        printf("Invalid position\n");
        free(n);
        return;
    }
    n->next = temp->next;
    temp->next = n;
}

void displayList() {
    struct Node* t = head;
    if (t == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List: ");
    while (t) {
        printf("%d -> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, value, pos;
    while (1) {
        printf("\n1. Insert at Begin\n2. Insert at End\n3. Insert at Position\n4. Display\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtBegin(value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertAtPos(value, pos);
                break;
            case 4:
                displayList();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q5. Singly Linked List Deletion

void deleteBegin() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = head;
    head = head->next;
    free(temp);
    printf("Deleted from beginning\n");
}

void deleteEnd() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Deleted from end\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    printf("Deleted from end\n");
}

void deletePos(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (pos == 1) {
        deleteBegin();
        return;
    }
    struct Node* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position\n");
        return;
    }
    struct Node* del = temp->next;
    temp->next = del->next;
    free(del);
    printf("Deleted from position %d\n", pos);
}

int main() {
    int choice, pos;
    while (1) {
        printf("\n1. Delete from Begin\n2. Delete from End\n3. Delete from Position\n4. Display\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                deleteBegin();
                break;
            case 2:
                deleteEnd();
                break;
            case 3:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletePos(pos);
                break;
            case 4:
                displayList();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q6. Circular Linked List

struct CNode {
    int data;
    struct CNode* next;
};

struct CNode* chead = NULL;

void insertAtEndC(int value) {
    struct CNode* newnode = (struct CNode*)malloc(sizeof(struct CNode));
    newnode->data = value;
    if (chead == NULL) {
        chead = newnode;
        newnode->next = chead;
    } else {
        struct CNode* temp = chead;
        while (temp->next != chead)
            temp = temp->next;
        temp->next = newnode;
        newnode->next = chead;
    }
    printf("Inserted %d\n", value);
}

void deleteNodeC(int value) {
    if (chead == NULL) {
        printf("List is empty\n");
        return;
    }
    struct CNode *curr = chead, *prev = NULL;
    if (curr->data == value && curr->next == chead) {
        free(curr);
        chead = NULL;
        printf("Deleted %d\n", value);
        return;
    }
    if (curr->data == value) {
        while (curr->next != chead)
            curr = curr->next;
        curr->next = chead->next;
        free(chead);
        chead = curr->next;
        printf("Deleted %d\n", value);
        return;
    }
    do {
        prev = curr;
        curr = curr->next;
        if (curr->data == value) {
            prev->next = curr->next;
            free(curr);
            printf("Deleted %d\n", value);
            return;
        }
    } while (curr != chead);
    printf("Value not found\n");
}

void displayC() {
    if (chead == NULL) {
        printf("List is empty\n");
        return;
    }
    struct CNode* temp = chead;
    printf("Circular LL: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != chead);
    printf("(head)\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Insert at End\n2. Delete Node\n3. Display\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEndC(value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNodeC(value);
                break;
            case 3:
                displayC();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q7. Doubly Linked List

struct DNode {
    int data;
    struct DNode *prev, *next;
};

struct DNode* dhead = NULL;

void insertEndD(int v) {
    struct DNode* n = (struct DNode*)malloc(sizeof(struct DNode));
    n->data = v;
    n->next = NULL;
    n->prev = NULL;
    if (dhead == NULL) dhead = n;
    else {
        struct DNode* t = dhead;
        while (t->next) t = t->next;
        t->next = n;
        n->prev = t;
    }
    printf("Inserted %d\n", v);
}

void deleteEndD() {
    if (dhead == NULL) {
        printf("List is empty\n");
        return;
    }
    struct DNode* t = dhead;
    while (t->next != NULL) t = t->next;
    if (t->prev) t->prev->next = NULL;
    else dhead = NULL;
    printf("Deleted %d\n", t->data);
    free(t);
}

void displayD() {
    struct DNode* t = dhead;
    if (t == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("Doubly LL: ");
    while (t) {
        printf("%d <-> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Insert at End\n2. Delete from End\n3. Display\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertEndD(value);
                break;
            case 2:
                deleteEndD();
                break;
            case 3:
                displayD();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q8. Binary Tree Traversals

struct TNode {
    int data;
    struct TNode *left, *right;
};

struct TNode* newTNode(int v) {
    struct TNode* n = (struct TNode*)malloc(sizeof(struct TNode));
    n->data = v;
    n->left = n->right = NULL;
    return n;
}

void inorder(struct TNode* r) {
    if (r) {
        inorder(r->left);
        printf("%d ", r->data);
        inorder(r->right);
    }
}

void preorder(struct TNode* r) {
    if (r) {
        printf("%d ", r->data);
        preorder(r->left);
        preorder(r->right);
    }
}

void postorder(struct TNode* r) {
    if (r) {
        postorder(r->left);
        postorder(r->right);
        printf("%d ", r->data);
    }
}

int main() {
    struct TNode* root = newTNode(1);
    root->left = newTNode(2);
    root->right = newTNode(3);
    root->left->left = newTNode(4);
    root->left->right = newTNode(5);

    int choice;
    while (1) {
        printf("\n1. Inorder\n2. Preorder\n3. Postorder\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q9. Binary Search Tree

struct BST {
    int data;
    struct BST *left, *right;
};

struct BST* bstroot = NULL;

struct BST* newBSTNode(int v) {
    struct BST* n = (struct BST*)malloc(sizeof(struct BST));
    n->data = v;
    n->left = n->right = NULL;
    return n;
}

struct BST* insert(struct BST* root, int v) {
    if (root == NULL) return newBSTNode(v);
    if (v < root->data)
        root->left = insert(root->left, v);
    else if (v > root->data)
        root->right = insert(root->right, v);
    return root;
}

int search(struct BST* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search(root->left, key);
    else return search(root->right, key);
}

struct BST* minValueNode(struct BST* node) {
    struct BST* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct BST* deleteNode(struct BST* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct BST* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BST* temp = root->left;
            free(root);
            return temp;
        }
        struct BST* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorderBST(struct BST* root) {
    if (root) {
        inorderBST(root->left);
        printf("%d ", root->data);
        inorderBST(root->right);
    }
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display (Inorder)\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                bstroot = insert(bstroot, value);
                printf("Inserted %d\n", value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(bstroot, value))
                    printf("Found\n");
                else
                    printf("Not Found\n");
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                bstroot = deleteNode(bstroot, value);
                printf("Deleted %d\n", value);
                break;
            case 4:
                printf("BST (Inorder): ");
                inorderBST(bstroot);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


// Q10. Sorting Algorithms

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]);
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min]) min = j;
        swap(&a[min], &a[i]);
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
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
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int choice, n;
    int a[MAX];

    while (1) {
        printf("\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Quick Sort\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 4) {
            printf("Enter number of elements: ");
            scanf("%d", &n);
            printf("Enter elements: ");
            for (int i = 0; i < n; i++)
                scanf("%d", &a[i]);
        }

        switch (choice) {
            case 1:
                bubbleSort(a, n);
                printf("Sorted: ");
                printArray(a, n);
                break;
            case 2:
                selectionSort(a, n);
                printf("Sorted: ");
                printArray(a, n);
                break;
            case 3:
                insertionSort(a, n);
                printf("Sorted: ");
                printArray(a, n);
                break;
            case 4:
                quickSort(a, 0, n - 1);
                printf("Sorted: ");
                printArray(a, n);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
