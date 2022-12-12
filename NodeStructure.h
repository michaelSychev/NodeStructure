//
// Created by michael on 6/14/2022.
//

#ifndef UNTITLED_NODESTRUCTURE_H
#define UNTITLED_NODESTRUCTURE_H

#endif //UNTITLED_NODESTRUCTURE_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 implement node structure that contains shape and color,
then implement functions to add a node,
find a node,
and delete a node.
*/
//list will not have duplicates(n1 and n2 cant have same shape and same color)
struct Node
{
    char shape[20];
    char color[20];
    struct Node* next;

}node;
//default values
const char DEFAULT_COLOR[] = "white";
const char DEFAULT_SHAPE[] = "circle";
//constant defentitions
const int COLOR_SIZE = 20;
const int SHAPE_SIZE = 20;

//function prototypes
struct Node* addNode(struct Node* head, char* shape, char* color);
struct Node* findNode(struct Node* headNode, char* targetShape, char* targetColor);
struct Node* deleteNode(struct Node* targetNode, struct Node* headNode);
int nodeCount(struct Node* nodeHead);
void printList(struct Node* headNode);

//pre:node structure must exist
//post:returns the length of the structure
int nodeCount(struct Node* nodeHead)
{
    struct Node* curr = nodeHead;
    int count = 0;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

//pre:Init must be called
//post:creates node and returns pointer
struct Node* addNode(struct Node* headNodePointer, char* shape, char* color)
{
    if(headNodePointer==NULL)//initializing linekd list
    {
        headNodePointer = (struct Node*)malloc(sizeof(struct Node));
        strncpy(headNodePointer->color, (char*)color,COLOR_SIZE);
        strncpy(headNodePointer->shape, (char*)shape,SHAPE_SIZE);
        headNodePointer->next=NULL;
        printf("List is initialised with shape:%s and color:%s\n",headNodePointer->shape,headNodePointer->color);

    }
    else//creating normal node that is not head node
    {
        //find the tail
        struct Node* curr = headNodePointer;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        //create new element
        struct Node* newNodePointer = (struct Node*)malloc(sizeof(struct Node));
        strncpy(newNodePointer->color, color,COLOR_SIZE);
        strncpy(newNodePointer->shape, shape,SHAPE_SIZE);
        //append new element to tail
        curr->next = newNodePointer;
        // new tail point to NULL
        newNodePointer->next = NULL;
    }
    return headNodePointer;
}
//pre:takes a shape and color and pointer to headNode
//post:returns pointer to desired node or returns null
struct Node* findNode(struct Node* headNode, char* targetShape, char* targetColor)
{
    //iterate through each node and compare color and shape
    struct Node* curr = headNode;
    struct Node* rv;
    do
    {
        if(strcmp(curr->shape, targetShape)==0 && strcmp(curr->color,targetColor)==0)//found the node
        {
            rv = curr;
            curr =NULL;//kill the loop
        }
        else//curr did not find node
        {
            if(curr->next==NULL)//at the end of the list
            {
                printf("Could not find node that contains shape:%s  color:%s \n",targetShape,targetColor);
                curr= NULL;//if at end of list kill the loop
            }
            else//iterate to next node if not at end of list
            {
                curr=curr->next;

            }
        }
    } while (curr != NULL);

    return rv;
}
//pre:target node must exist
//post: deletes desired node and restructures list
struct Node* deleteNode(struct Node* targetNode, struct Node* headNode)
{
    if (nodeCount(headNode) == 0)//no nodes
    {
        printf("The structure is empty\n");
    }
    else if (nodeCount(headNode) == 1)//one node
    {
        if(targetNode==headNode)
        {
            free(headNode);
            printf("structure has been deleted, call Init to start new structure\n");
        }
        else
        {
            printf("target node is not present1\n");
        }
    }

    else //more than one node
    {
        struct Node* prev = NULL;
        struct Node* curr = headNode;
        do
        {
            //found target
            if(curr == targetNode)
            {
                //check if headNode is targetNode
                if(targetNode==headNode)
                {
                    headNode = curr->next;
                    free(curr);
                    printf("deleted headNode and new node is %s , %s\n", headNode->shape, headNode->color);
                    curr=NULL;
                }
                    //check if at last node
                else if(curr->next == NULL)
                {
                    printf("deleting last node in list\n");
                    prev->next=NULL;
                    free(curr);
                    curr=NULL;
                }
                    //normal case(delete node that is not first or last in structure)
                else
                {
                    printf("deleting node with contents %s,%s\n",curr->shape,curr->color);
                    prev->next = curr->next;//point previous node to node after current
                    free(curr);//free target node
                    curr=NULL;
                }
            }

            else//keep looking for targetNode
            {
                if(curr->next==NULL)//if curr->next is null we are at the end
                {
                    printf("Node was not found, no changes where made to list");
                }
                prev = curr;
                curr = curr->next;
            }
        }while (curr !=NULL);//checks if current points to next, else we exit the loop
    }
    return headNode;
}
void printList(struct Node* headNode)
{
    //printf("the list contains %d entries, head is at %x \n",nodeCount(headNode), headNode);
    struct Node* curr = headNode;
    do
    {
        printf("%s,%s\n",curr->color,curr->shape);
        curr=curr->next;
    }
    while(curr!=NULL);
}
/*sample input
 *  struct Node* headPointer = InitHead();//creates head with default attributes and assigns pointer to head
    struct Node* curr = headPointer;//create reference pointer that starts at head
    addNode(headPointer, "rectangle", "blue");
    addNode(headPointer, "undecagon", "green");
    curr = findNode("rectangle","blue",headPointer);
    printf("%s, %s\n",curr->shape,curr->color);
    return 0;
 */