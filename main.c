#include <stdio.h>
#include <string.h>
#include "NodeStructure.h"

int main()
{
    FILE* sampleDataPointer = fopen("SampleData.txt", "r");//create pointer to input text file
    char singleLine[120];//where we are storing each line of text when parsing files
    //initialise list
    struct Node* headNodePointer = NULL;//create head node pointer for future initialization
    while(fgets(singleLine,sizeof(singleLine),sampleDataPointer))//takes input from file and stores shape and color into node
    {
        if(strcmp("",singleLine)==0)//if string is empty print error message
        {
            printf("empty input is not accepted");
        }
        else
        {
            char* color = strtok(singleLine,",");
            char* shape = strtok(NULL,"\n");

            if(headNodePointer == NULL)
            {
                headNodePointer = addNode(headNodePointer,shape,color);
            }
            else
            {
                addNode(headNodePointer,shape,color);
            }
        }


    }
    fclose(sampleDataPointer);//closes access to input file
    //delete input given file
    FILE* hitListPointer = fopen("TheHitList.txt", "r");//data to delete
    while(fgets(singleLine,sizeof(singleLine),hitListPointer))
    {
        char* inputColor = strtok(singleLine,",");//extracts shape from SampleDataSingleLine
        char* inputShape = strtok(NULL,"\n");//extracts remaining text from SampleDataSingleLine
        struct Node* nodeSeacherPointer = findNode(headNodePointer,inputShape,inputColor);

        if(findNode(headNodePointer,inputShape,inputColor)!=NULL)//if target is found we send target to delete node
        {
            if(findNode(headNodePointer,inputShape,inputColor)==headNodePointer)//if deleting headNode resassign its pointer to new node
            {
                headNodePointer = deleteNode(nodeSeacherPointer,headNodePointer);
            }
            else//deletes target node if not headNode
            {
                deleteNode(nodeSeacherPointer,headNodePointer);

            }
        }

    }
    fclose(hitListPointer);//closes access to hit list file
    printList(headNodePointer);//prints list for debugging
    return 0;

}
