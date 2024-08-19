#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
} Node;


//-----------Insertion of New Node-------------

void insert_node(Node** head,int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value= value;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
    }
    else{
        Node* current= *head;
        while(current->next != NULL){
            current= current->next;
        }
        current->next = new_node;
    }
}

//-------Deletion of Node at a given position-----------------
void deletion_node(Node** head, int position){
    if(*head == NULL || position <0) return;
    Node* temp = *head;

    if(position ==0){
        *head = temp->next;
        free(temp);
        return;
    }
    for(int i=0; temp != NULL && i <position-1; i++){
        temp= temp->next;
    }
    if(temp == NULL || temp->next == NULL)return;

    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

//----------Search  of Node in Linklist------------------

int search_node(Node* head,int value){
    Node* current = head;
    int position=0;

    while(current != NULL){
        if(current->value == value){
            return position;
        }
        position++;
        current = current->next;
    }
    return -1;
}

//------------Sort of Node in Linklist-------------------

void sort_node(Node** head){
    if(*head == NULL)return ;
    Node* current = *head;
    Node* index = NULL;
    int temp;
    
    while(current != NULL){
        index = current->next;
        while(index != NULL){
            if(current->value > index->value){
                temp = current->value;
                current->value = index->value;
                index->value = temp;
            }
            index = index->next;
        }
        current= current->next;
    }
}

//----------Print the Linklist----------------------------------

void display_node(Node* head){
    Node* current = head;
    while(current != NULL){
        printf("%d ->",current->value);
        current = current->next;
    }
    printf("NULL\n");
}


//-------------------Display the menu , what will do---------------------

void display_menu(){

    printf(
        "\nWhich opertions will you do:\n"
        "------------------------------------------\n"
        "[1] Insert a Node \n"
        "[2] Deletion of Node at position"
        "[3] Search  a Node in given Linklist \n"
        "[4] Sort a Node in given Linklist  \n"
        "[5] Display a Node \n"
        "[6] Exit \n"
        "---------------------------------------------\n"
        "Select an opertions :"

    );
}

//-----------Main function-------------------------------

int main(){
    Node* head = NULL;
    int count_show =1;
    while(count_show){
        display_menu();
        int option ;
        scanf("%d",&option);

        switch(option){
            case 1: {
                int value;
                printf("Enter Node of value to insert : ");
                scanf("%d",&value);
                insert_node(&head,value);
            }
            break;

            case 2: {
                int position;
                printf("Enter postion to delete node  ");
                scanf("%d",&position);
                deletion_node(&head,position);
            }
            break;
            case 3 :{
                int value;
                printf("Enter Node to search");
                scanf("%d",&value);
                int position = search_node(head,value);
                if(position == -1){
                    printf("value of node not found .\n");

                }
                else{
                    printf(" value of node %d is found at %d .\n",value,position);
                }
            }
            break;
            case 4:
            sort_node(&head);
            break;

            case 5:
            display_node(head);
            break;

            default:
            printf("choose correct opertion--.\n");
            printf("Invalid opertion");
        }
    }

    printf("-----Exition------\n");
    printf("Thank You");
}
