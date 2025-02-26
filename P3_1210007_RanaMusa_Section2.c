/**Rana Ali Musa
Section 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char Id[20];
    char name[20];
    char city[20];
    char date[20];
    char class_id[20];
    struct node* left;
    struct node* right;
};
  FILE *input;

struct node* root;

void read_File();
struct node* create_node( char id[20], char name[20], char city[20], char class_id[20], char date[20]);
struct node* insert_node(struct node* student, char id[20], char name[20], char city[20], char class_id[20],char date[20]);
void inOrderTraversal(struct node* root);
struct node* search(struct node* root, char key[20]);
struct node* delete_student(struct node* root, const char* key);
void city_search(struct node* root, char key[20]);
void inOrderTraversal_forFile(struct node* root) ;
int getSize(struct node* root);
void lexicographic_order_helper(struct node* root, struct node* student[], int* index);
void lexicographic_order(struct node* root);
void City_search_helper(struct node* root, struct node* student[], int* index, char key[20]);
void class_list(struct node* root);

int main() {
    int n;

root = NULL;



  read_File();


    char id[20];
    char class_id[20];
    char name[20];
    char city[20];
    char date[20];



        printf("1. Insert a student\n");
        printf("2. Find a student by ID\n");
        printf("3. List all students in lexicographic order of names\n");
        printf("4. Search for students from a city\n");
        printf("5. List all students by class in lexicographic order of names\n");
        printf("6. Delete a student by ID\n");
        printf("7. Save all students to file\n");
        printf("8. print all student's names and ids\n");

        printf("9. Exit\n");

    scanf("%d", &n);

    while(n!=9){

    switch (n) {
        case 1: { //inserthion

            int m = 0;
            while (m != -1) {

                printf("Enter Student's Id: ");
                scanf("%s", id);
                printf("Enter Student's name: ");
                scanf("%s", name);
                printf("Enter Student's city: ");
                scanf("%s", city);
                printf("Enter Student's class_id: ");
                scanf("%s", class_id);
                printf("Enter Student's enrollment date: ");
                scanf("%s", date);

                struct node* student = create_node(id, name, city, class_id, date);
                root = insert_node(root, id, name, city, class_id, date);
                printf("Enter -1 to stop inserting or 1 to continue: ");
                scanf("%d", &m);

            }
            break;
        }
        case 2:{

        printf("\nEnter ID to search for?\n");
        char key[20];
        scanf("%s",key);
       struct node* founded_node =search(root, key);
       if(founded_node==NULL)
       {
           printf("Oops! NOT FOUND!!\n\n");
       }

       if(founded_node!=NULL){
    printf("\nit is found !\n\n");
    printf("ID: %s \n", founded_node->Id);
    printf("Name: %s \n", founded_node->name);
    printf("Class ID: %s\n ", founded_node->class_id);
    printf("City: %s \n", founded_node->city);
    printf("date: %s\n ", founded_node->date);

    printf("Enter 1 if you want to edit data and 0 to continue\n");
        int x;
        scanf("%d",&x);
        if(x==1)
        {

                printf("Enter Student's name: ");
                scanf("%s", name);
                printf("Enter Student's city: ");
                scanf("%s", city);
                printf("Enter Student's class_id: ");
                scanf("%s", class_id);
                printf("Enter Student's enrollment date: ");
                scanf("%d", date);



    strcpy(founded_node->name, name);
    strcpy(founded_node->city, city);
    strcpy(founded_node->class_id, class_id);
    strcpy(founded_node->date, date);

        }


       }

        break;
        }

        case 3:{

   lexicographic_order(root);
            break;
        }
        case 4:{

            printf("Enter the name of the City\n");
            char city[20];
            scanf("%s",&city);
         city_search(root, city) ;


        break;
        }

        case 5:{
            class_list(root);


        break;


        }
        case 6:
            {
                printf("Enter an Id to delete\n");
                char key[20];
                scanf("%s",&key);


                struct node* search_node = search(root,key);


                if (search_node != NULL)
                {
                    root=   delete_student(root, key);
                    printf("\nStudent with Id '%s' has been deleted\n\n", key);
                    // Update the root if necessary
                }
                else
                {
                    printf("\nStudent with Id '%s' was not found\n\n", key);
                }




                break;

            }

        case 7:
            {
                 input=fopen("students.data","w");
        fprintf(input,"************************************Students*************************************************\n\n");
                inOrderTraversal_forFile(root);
                fclose(input);
                printf("\nSAVED!\n\n");

                break;
            }

            case 8:{

    inOrderTraversal(root);
    printf("\n");

            break;
            }
        default:
            {
                printf("\nNO SUCH OPERATION!\n\n");
                break;
            }

    }


        printf("\n\n");
        printf("1. Insert a student\n");
        printf("2. Find a student by ID\n");
        printf("3. List all students in lexicographic order of names\n");
        printf("4. Search for students from a city\n");
        printf("5. List all students by class in lexicographic order of names\n");
        printf("6. Delete a student by ID\n");
        printf("7. Save all students\n");
        printf("8. print all student's names and ids\n");
        printf("9. Exit\n");
        printf("\n");

    scanf("%d", &n);
    }

    return 0;
}
/*this function is to read students from file it reads the file as this:

for the input file
data must be 5 lines for each student
    name
    id
    class id
    city
    date


every five lines represent a studdent*/

void read_File(){
    FILE* input = fopen("students.data", "r");
    if (input == NULL) {
        printf("Failed to open the file.\n");
        return;
    }



    char line[20];
    char name[20];
    char id[20];
    char class_id[20];
    char city[20];
    char date[20];

    while (fgets(line, sizeof(line), input)) {
        sscanf(line, "%19[^\n]", name);


        fgets(line, sizeof(line), input);
        sscanf(line, "%19[^\n]", id);

        fgets(line, sizeof(line), input);
        sscanf(line, "%19[^\n]", class_id);

        fgets(line, sizeof(line), input);
        sscanf(line, "%19[^\n]", city);

        fgets(line, sizeof(line), input);
        sscanf(line, "%19[^\n]", date);// when it read 5 lines, they are sent to create and insert function to be added to the tree

        struct node* student = create_node(id, name, city, class_id, date);
        root = insert_node(root, id, name, city, class_id, date);
    }

    fclose(input);
}

struct node* create_node(char id[20], char name[20], char city[20], char class_id[20], char date[20]) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newnode->Id, id);
    strcpy(newnode->name, name);
    strcpy(newnode->city, city);
     strcpy(newnode->class_id, class_id); //copy the information into the new node created.


 strcpy(newnode->date, date);
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct node* insert_node(struct node* student, char id[20], char name[20], char city[20], char class_id[20], char date[20]) {
    if (student == NULL) {
        return create_node(id, name, city, class_id, date);
    }


//implementing BST

    if (strcmp(id, student->Id) <= 0) {
        student->left = insert_node(student->left, id, name, city, class_id, date);
    } else if (strcmp(id, student->Id) > 0) {
        student->right = insert_node(student->right, id, name, city, class_id, date);
    }

    return student;
}


void inOrderTraversal(struct node* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printf("ID: %s\t", root->Id);
    printf("Name: %s \n", root->name);


    printf("\n");
    inOrderTraversal(root->right);
}

void inOrderTraversal_forFile(struct node* root) {
    if (root == NULL) {
        return;
    }



    inOrderTraversal_forFile(root->left);
    fprintf(input,"ID: %s \n", root->Id);
    fprintf(input,"Name: %s \n", root->name);
    fprintf(input,"Class ID: %s\n ", root->class_id);
    fprintf(input,"City: %s \n", root->city);
    fprintf(input,"date: %s\n", root->date);
    fprintf(input,"\n");
    inOrderTraversal_forFile(root->right);


}
struct node* search(struct node* root, char key[20]) {
    if (root == NULL || strcmp(root->Id, key) == 0) {
        return root;
    }

    int compare = strcmp(key, root->Id);

    if (compare < 0) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}


int getSize(struct node* root) {
    if (root == NULL) {
        return 0;  // empty tree
    } else {

        int leftSize = getSize(root->left);
        int rightSize = getSize(root->right);

        // Add 1 for the current node and return the total size
        return leftSize + rightSize + 1;
    }
}
/*this idea is to put the tree content in array of struct then implement sorting on the array */
void lexicographic_order_helper(struct node* root, struct node* student[], int* index) {
    if (root == NULL) {
        return; // empty tree
    }

    lexicographic_order_helper(root->left, student, index);

    student[(*index)] = (struct node*)malloc(sizeof(struct node));
    strcpy(student[(*index)]->Id, root->Id);

    strcpy(student[(*index)]->name, root->name);
    strcpy(student[(*index)]->city, root->city);
    strcpy(student[(*index)]->class_id, root->class_id);

    strcpy(student[(*index)]->date, root->date);
    (*index)++;

    lexicographic_order_helper(root->right, student, index);
}


void lexicographic_order(struct node* root) {
    struct node* student[getSize(root)]; // Array to store the nodes
    int n = getSize(root);
    int index = 0; // Current index in the student array

    lexicographic_order_helper(root, student, &index);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcasecmp(student[j]->name, student[j + 1]->name) > 0) {
                // Swap the elements
                struct node* temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("\n");
        printf("ID: %s \n", student[i]->Id);
        printf("Name: %s \n", student[i]->name);
        printf("Class ID: %s\n ", student[i]->class_id);
        printf("City: %s \n", student[i]->city);
        printf("Date: %s\n", student[i]->date);
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(student[i]);
    }
}
void City_search_helper(struct node* root, struct node* student[], int* index, char key[20]) {
    if (root == NULL) {
        return; // Base case: empty tree
    }

    City_search_helper(root->left, student, index, key);

    if (strcmp(root->city, key) == 0) {
        student[(*index)] = (struct node*)malloc(sizeof(struct node));
        strcpy(student[(*index)]->Id, root->Id);
        strcpy(student[(*index)]->name, root->name);
        strcpy(student[(*index)]->city, root->city);
        strcpy(student[(*index)]->class_id, root->class_id);

       strcpy(student[(*index)]->date, root->date);
        (*index)++;
    }

    City_search_helper(root->right, student, index, key);
}

void city_search(struct node* root, char key[20]) {
    struct node* student[100]; // Array to store the nodes (assuming a maximum of 100 matches)
    int index = 0; // Current index in the student array

    City_search_helper(root, student, &index, key);

    if(index==0)
        {
            printf("\nCant find city!\n\n");
           return;
        }

    // Sort the student array based on names
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (strcasecmp(student[j]->name, student[j + 1]->name) > 0) {
                // Swap the elements
                struct node* temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }

    // Print the sorted array
    for (int i = 0; i < index; i++) {
        printf("\n");
        printf("ID: %s \n", student[i]->Id);
        printf("Name: %s \n", student[i]->name);
        printf("Class ID: %s\n", student[i]->class_id);
        printf("City: %s \n", student[i]->city);
        printf("Date: %s\n", student[i]->date);
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < index; i++) {
        free(student[i]);
    }

}
void class_list(struct node* root)
{
        struct node* student[getSize(root)]; // Array to store the nodes
    int n = getSize(root);
    int index = 0; // Current index in the student array

    lexicographic_order_helper(root, student, &index);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcasecmp(student[j]->name, student[j + 1]->name) > 0) {
                // Swap the elements
                struct node* temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("\n");
        printf("Name: %s \t", student[i]->name);
        printf("Class:%s\n\n ", student[i]->class_id);

    }

    // Free the dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(student[i]);
    }
}
struct node* delete_student(struct node* root, const char* key) {
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    int compare = strcmp(root->Id, key);
    if (compare > 0) {
        root->left = delete_student(root->left, key);
        return root;
    } else if (compare < 0) {
        root->right = delete_student(root->right, key);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        struct node* temp = root->right;
        free(root);
        return temp;
    } else if (root->right == NULL) {
        struct node* temp = root->left;
        free(root);
        return temp;
    }

    // If both children exist
    else {
        struct node* succParent = root;

        // Find successor
        struct node* succ = root->right; //succ is successor
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }


        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        strcpy(root->Id, succ->Id);
        strcpy(root->name, succ->name);
        strcpy(root->city, succ->city);
         strcpy(root->class_id, succ->class_id);

        strcpy(root->date, succ->date);

        // Delete Successor and return root
        free(succ);
        return root;
    }
}
