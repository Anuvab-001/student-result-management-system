
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100
#define MAX 100
#define MAXsub 10

typedef struct Student {
    int id;
    char name[50];
    int subCount;
    char subjects[MAXsub][50];
    float marks[MAXsub];
    float credits[MAXsub];
    float total;
    float cgpa;
    char grade[3];
} Student;




float gradePoint(float mark) {
    if(mark>=80)
        return 4.00;
    else if(mark>=75)
        return 3.75;
    else if(mark>=70)
     return 3.50;
    else if(mark>=65)
     return 3.25;
    else if(mark>=60)
     return 3.00;
    else if(mark>=55)
     return 2.75;
    else if(mark>=50)
     return 2.50;
    else if(mark>=45)
     return 2.25;
    else if(mark>=40)
     return 2.00;
    else
    return 0.00;
}

void assignGrade(float cgpa, char grade[]) {
    if(cgpa == 4.00)
     strcpy(grade,"A+");
    else if(cgpa >=3.75)
        strcpy(grade,"A");
    else if(cgpa >=3.50)
     strcpy(grade,"A-");
    else if(cgpa >=3.25)
     strcpy(grade, "B+");
    else if(cgpa >=3.00)
     strcpy(grade, "B");
    else if(cgpa >=2.75)
     strcpy(grade, "B-");
    else if(cgpa >=2.50)
     strcpy(grade, "C+");
    else if(cgpa >=2.25)
     strcpy(grade, "C");
    else if(cgpa >=2.00)
     strcpy(grade, "D");
    else strcpy(grade, "F");
}

float calculateTotal(Student *s) {
    float sum = 0;
    for(int i = 0; i < s->subCount; i++) {
        sum += s->marks[i];
    }
    return sum;
}

float calculateCGPA(Student *s) {
    float num=0,den=0;
    for(int i=0;i<s->subCount;i++) {
        float gp=gradePoint(s->marks[i]);
        num+= gp * s->credits[i];
        den += s->credits[i];
    }
    if(den == 0) return 0;
    return num / den;
}



Student heap[MAX];
int heapSize = 0;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a=*b;
    *b=temp;
}

void heapifyUp(int index) {
    if(index == 0)
        return;
    int parent=(index-1)/2;

    if(heap[parent].cgpa < heap[index].cgpa) {
        swap(&heap[parent], &heap[index]);
        heapifyUp(parent);
    }
}

void insertHeap(Student s) {
    heap[heapSize] = s;
    heapifyUp(heapSize);
    heapSize++;
}

void displayTopper() {
    if(heapSize == 0) {
        printf("No students available\n");
    } else {
        printf("\nTop Student:\n");
        printf("ID:%d Name:%s CGPA:%.2f Grade:%s\n",
               heap[0].id, heap[0].name, heap[0].cgpa, heap[0].grade);
    }
}



void displayRanking() {
    if(heapSize==0) {
        printf("No students available\n");
        return;
    }

    Student temp[MAX];

    for(int i = 0; i < heapSize; i++) {
        temp[i] = heap[i];
    }


    for(int i =0;i<heapSize-1;i++) {
        for(int j = 0; j < heapSize - i - 1; j++) {
            if(temp[j].cgpa < temp[j + 1].cgpa) {
                Student t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    printf("\n=== Student Ranking (By CGPA) ===\n");
    for(int i = 0; i < heapSize; i++) {
        printf("Rank %d -> ID:%d Name:%s CGPA:%.2f Grade:%s\n",
               i + 1,
               temp[i].id,
               temp[i].name,
               temp[i].cgpa,
               temp[i].grade);
    }
}




typedef struct Node {
    Student data;
    struct Node *left, *right;
} Node;

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertBST(Node* root, Student s) {
    if(root == NULL) return createNode(s);

    if(s.id < root->data.id) {
        root->left = insertBST(root->left, s);
    } else {
        root->right = insertBST(root->right, s);
    }
    return root;
}

void inorder(Node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("ID:%d Name:%s CGPA:%.2f Grade:%s\n",
               root->data.id, root->data.name, root->data.cgpa, root->data.grade);
        inorder(root->right);
    }
}




typedef struct HashNode {
    Student data;
    struct HashNode* next;
} HashNode;

HashNode* hashTable[SIZE];

int hashFunction(int id) {
    return id % SIZE;
}

void insertHash(Student s) {
    int index = hashFunction(s.id);

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->data = s;
    newNode->next = hashTable[index];

    hashTable[index] = newNode;
}

Student* searchHash(int id) {
    int index = hashFunction(id);
    HashNode* temp = hashTable[index];

    while(temp != NULL) {
        if(temp->data.id == id) return &temp->data;
        temp = temp->next;
    }
    return NULL;
}




int main() {
    Node* root = NULL;
    int choice;

    while(1) {
        printf("\n===== Student Result Record Management System =====\n");
        printf("1. Add Student\n2. Search\n3. Topper\n4. Display All\n5. Ranking\n6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if(choice==1) {
            Student s;

            printf("Enter ID: ");
            scanf("%d", &s.id);
            getchar();

            printf("Enter Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("How many subjects: ");
            scanf("%d", &s.subCount);
            getchar();

            for(int i = 0; i < s.subCount; i++) {
                printf("Enter subject %d name: ", i + 1);
                fgets(s.subjects[i], sizeof(s.subjects[i]), stdin);
                s.subjects[i][strcspn(s.subjects[i], "\n")] = 0;

                printf("Enter subject %d marks: ", i + 1);
                scanf("%f", &s.marks[i]);
                getchar();

                if(strstr(s.subjects[i], "lab") != NULL||strstr(s.subjects[i], "Lab") != NULL) {
                    s.credits[i] = 1.5;
                } else {
                    s.credits[i] = 3.0;
                }
            }

            s.total = calculateTotal(&s);
            s.cgpa = calculateCGPA(&s);
            assignGrade(s.cgpa, s.grade);

            insertHeap(s);
            root = insertBST(root, s);
            insertHash(s);

            printf("Student Added CGPA = %.2f\n", s.cgpa);
        }

        else if(choice == 2) {
            int id;
            printf("Enter ID: ");
            scanf("%d", &id);

            Student* s = searchHash(id);

            if(s == NULL) {
                printf("Not Found\n");
            } else {
                printf("ID:%d Name:%s CGPA:%.2f Grade:%s\n",
                       s->id, s->name, s->cgpa, s->grade);
            }
        }

        else if(choice == 3) {
            displayTopper();
        }

        else if(choice == 4) {
            inorder(root);
        }

        else if(choice == 5) {
            displayRanking();
        }

        else if(choice == 6) break;

        else printf("Invalid choice\n");
    }

    return 0;
}
