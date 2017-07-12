#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define m 5
#define limit (ceil((m+1)/2))

typedef enum{l,n}ln_type;
typedef struct node_tag
{
    ln_type ln;
    int count;
    int data[m-1];
    struct node_tag* down[m];
    struct node_tag* parent;
    struct node_tag* prev;
    struct node_tag* next;
}node_type;

void SetDownNULL(node_type** ptr)
{
    node_type* temptr=*ptr;
    int i;
    for(i=0;i<m;i++)
    {
        temptr->down[i]=NULL;
    }
}

node_type* MakeNodeBPT()
{
    node_type* nptr=(node_type*)malloc(sizeof(node_type));
    nptr->count=0;
    SetDownNULL(&nptr);
    nptr->next=NULL;
    nptr->prev=NULL;
    nptr->parent=NULL;
    return nptr;
}

void StepRight(node_type**root, int pos)                    //made only for leaf
{
    node_type* ptr=*root;
    int i;
    ptr->down[ptr->count]=ptr->down[ptr->count-1];
    for(i=ptr->count-2;i>=pos;i--)
    {
        ptr->data[i+1]=ptr->data[i];
        ptr->down[i+1]=ptr->down[i];
    }
}

void SortNode(node_type**root)
{
    node_type*ptr=*root;
    int i;
    int val=ptr->data[ptr->count-1];
    node_type* valptr=ptr->down[ptr->count];
    for(i=0;i<ptr->count-1&&val>ptr->data[i];i++)
    {
    }
    StepRight(&ptr,i);
    ptr->data[i]=val;
    ptr->down[i]=valptr;
}

void InsertBPT(node_type** root, int d)
{
    node_type* ptr=*root;
    if(ptr==NULL)
    {
        node_type* nptr=MakeNodeBPT();
        nptr->data[0]=d;
        nptr->count++;
        nptr->ln=l;
        *root=nptr;
    }
    else
    {
        while(ptr->ln!=l)                           //to traverse till leaf
        {
            int i=0;
            while(i<ptr->count)                     //to traverse the array
            {
                if(d<ptr->data[i])
                {
                    ptr=ptr->down[i];
                    break;
                }
                else if(d>=ptr->data[i])
                {
                    i++;
                }
            }
        }
        if(ptr->count<limit)
        {
            ptr->data[ptr->count]=d;
            ptr->count=ptr->count+1;
            SortNode(&ptr);
        }
        else
        {
            node_type* lptr;
            lptr=SplitNode(&ptr,&d)
        }
    }
}

void InitBPT(node_type** root)
{
    int d;
    FILE* fptr=fopen("data.txt","r");
    fseek(fptr,0,SEEK_END);
    unsigned int size=ftell(fptr);
    if(size!=0)
    {
        rewind(fptr);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d",&d);
            //printf("%d, ",d);
            InsertBPT(root,d);
        }
        fclose(fptr);
    }
    else
    {
        printf("\nData is empty or not available\n");
    }
}
void main()
{
    node_type* root;
    InitBPT(&root);
}
