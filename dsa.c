#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    char parent_name[50];
    char mobile[15];
    char address[100];
    struct Student* next;
};

struct StudentLinkedList {
    struct Student* head;
};

struct stackNode {
    struct StudentLinkedList data;
    struct stackNode* next;
};

struct Stack {
    struct stackNode* top;
};


// FUNCTION TO CREATE A NEW STUDENT NODE
struct Student* createStudent(char name[], char parent_name[], char mobile[], char address[]) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    strcpy(newStudent->parent_name, parent_name);
    strcpy(newStudent->mobile, mobile);
    strcpy(newStudent->address, address);
    newStudent->next = NULL;
    return newStudent;
}

// FUNCTION TO CREATE newStudent LINKED LIST
struct StudentLinkedList createStudentLinkedList() {
    struct StudentLinkedList newList;
    newList.head = NULL;
    return newList;
}

// FUNCTION TO ADD A STUDENT TO LINKED LIST
void addStudent(struct StudentLinkedList* list, struct Student* student) {
    student->next = list->head;
    list->head = student;
}

// FUNCTION TO DISPLAY THE LIST OF STUDENTS
void displayStudents(struct StudentLinkedList* list) {
    struct Student* current = list->head;
    if (current == NULL) {
        printf("No students in the list.\n");
    } else {
        printf("Student information: \n");

        while (current != NULL) {
            printf("Name: %s\n", current->name);
            printf("Parent Name: %s\n", current->parent_name);
            printf("Mobile: %s\n", current->mobile);
            printf("Address: %s\n", current->address);
            printf("\n");
            current = current->next;
        }
    }
}

// FUNCTION TO PUSH THE STUDENT LINKED LIST ONTO THE STACK
void pushStack(struct Stack* stack, struct StudentLinkedList list) {
    struct stackNode* newNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    newNode->data = list;
    newNode->next = stack->top;
    stack->top = newNode;
}

// FUNCTION TO POP THE STUDENT LINKED LIST FROM STACK
struct StudentLinkedList popstack(struct Stack* stack) {
    if (stack->top == NULL) {
        struct StudentLinkedList emptyList = createStudentLinkedList();
        return emptyList;
    }

    struct stackNode* temp = stack->top;
    stack->top = stack->top->next;
    struct StudentLinkedList poppedList = temp->data;
    free(temp); // Free the popped stack node to prevent memory leak
    return poppedList;
}

// FUNCTION TO DELETE A STUDENT BY NAME
void deleteStudent(struct StudentLinkedList* list, char name[]) {
    struct Student* current = list->head;
    struct Student* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Student with name %s not found.\n", name);
}

int main() {
    struct StudentLinkedList studentList = createStudentLinkedList();
    struct Stack stack;
    stack.top = NULL;

    int choice;

    while (1) {
        printf("----------------------------\n");
        printf("Student Information Portal\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Delete Student\n");
        printf("4. Undo\n");
        printf("5. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Add student
                char name[50];
                char parent_name[50];
                char mobile[15];
                char address[100];

                printf("Enter student's name: ");
                scanf(" %49[^\n]", name);  // To allow spaces in input
                printf("Enter parent's name: ");
                scanf(" %49[^\n]", parent_name);
                printf("Enter mobile number: ");
                scanf(" %14[^\n]", mobile);
                printf("Enter student's address: ");
                scanf(" %99[^\n]", address);

                // PUSH THE CURRENT LIST ONTO THE STACK
                pushStack(&stack, studentList);

                // CREATE A NEW STUDENT AND ADD THEM TO THE LIST
                addStudent(&studentList, createStudent(name, parent_name, mobile, address));
                break;
            }
            case 2: // Display students
                displayStudents(&studentList);
                break;

            case 3: { // Delete student
                char deleteName[50];
                printf("Enter the name of the student to delete: ");
                scanf(" %49[^\n]", deleteName);
                pushStack(&stack, studentList); // Push before deletion
                deleteStudent(&studentList, deleteName);
                break;
            }
            case 4: // Undo
                studentList = popstack(&stack);
                break;

            case 5: // Exit
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}








































/*This program implements a student information system using linked lists and a stack. Here's an explanation of each part of the code:

Struct Definitions:
struct Student:
This structure holds information about a student. It contains:

name: the student's name.
parent_name: the parent's name.
mobile: the student's mobile number.
address: the student's address.
next: a pointer to the next Student in the linked list, making it a part of a singly linked list.
struct StudentLinkedList:
This structure represents a linked list of students. It has:

head: a pointer to the first Student node in the list.
struct stackNode:
This structure is a node for a stack. Each node contains:

data: a StudentLinkedList, representing the student list at a given point.
next: a pointer to the next stackNode (i.e., the previous state of the student list).
struct Stack:
This represents the stack used for undo operations. It has:

top: a pointer to the topmost stackNode.
Function Definitions:
createStudent():
This function creates and returns a new Student node.

Takes in name, parent_name, mobile, and address as parameters.
Allocates memory for a new Student using malloc.
Copies the passed values into the newly allocated student using strcpy.
Initializes the next pointer to NULL, since this is a new node.
Returns the pointer to the newly created Student.
createStudentLinkedList():
Initializes an empty StudentLinkedList.

Sets head to NULL, representing an empty list.
Returns the initialized list.
addStudent():
Adds a student to the beginning of the linked list.

The function takes in a pointer to the list and a Student.
Sets the next pointer of the new student to the current head of the list.
Updates the head to point to this new student, making it the first element of the list.
displayStudents():
Displays all the students in the linked list.

If the list is empty (i.e., head == NULL), it prints that there are no students.
Otherwise, it iterates through each student node using a loop, printing the student's information (name, parent_name, mobile, and address).
pushStack():
Pushes the current state of the student list onto the stack.

Takes in a pointer to the Stack and a StudentLinkedList.
Allocates memory for a new stackNode.
Sets the data of this node to the current StudentLinkedList.
Updates the next pointer of this node to the current top of the stack.
Updates the top of the stack to this new node.
popstack():
Pops the topmost list from the stack (i.e., restores the previous state).

If the stack is empty (top == NULL), it returns an empty list.
Otherwise, it stores the topmost node in a temporary pointer, updates the top pointer to the next node, retrieves the student list (data) from the top node, frees the memory of the popped node, and returns the student list.
deleteStudent():
Deletes a student by name from the linked list.

Takes in a pointer to the list and the student's name.
Iterates through the list, comparing each node's name with the given name.
If the name matches, it updates the previous node's next pointer to skip the current node and frees the memory of the deleted student.
If the student is not found, it prints an error message.
Main Function:
struct StudentLinkedList studentList = createStudentLinkedList();
Initializes the student list as an empty list.

struct Stack stack; stack.top = NULL;
Initializes an empty stack, setting top to NULL.

The main loop:

Continuously runs an interactive menu with options to add, display, delete, undo, or exit.

scanf("%d", &choice);
Reads the user's choice.

case 1: Add Student

Prompts the user to enter the student's name, parent_name, mobile, and address.
Before modifying the list, pushes the current list onto the stack using pushStack().
Calls addStudent() to add the new student to the list.
case 2: Display Students

Calls displayStudents() to show all the students in the list.
case 3: Delete Student

Prompts the user for the name of the student to delete.
Pushes the current state of the list onto the stack for undo purposes.
Calls deleteStudent() to remove the student from the list.
case 4: Undo

Calls popstack() to restore the list to its previous state.
case 5: Exit

Exits the program.
default:

Prints an error message if the user enters an invalid choice.
Summary:
Linked List: Stores student records.
Stack: Supports undo by storing previous states of the student list.
Operations: Add, delete, display, and undo student records.*/










