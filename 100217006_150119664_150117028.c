// Elif Nur Kemiksiz	100217006
// Nesrin Simsek 		150119664
// Reyta Gul Muran 		150117028

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 30

struct vertex
{
    char vertex_name[MAX_LEN];
    struct vertex *vertex_next;
    struct adjacent *adjacent_list;
};
typedef struct vertex VertexNode;
typedef VertexNode *VertexNodePtr;

struct adjacent
{
    char adjacent_name[MAX_LEN];
    struct adjacent *adjacent_next;
    int weight;
};
typedef struct adjacent AdjacentNode;
typedef AdjacentNode *AdjacentNodePtr;

// Prints the menu.
void print_menu()
{
    printf("\n1.Read file\n"
           "2.Show adjacency matrix/list\n"
           "3.Find shortest path\n"
           "4.Exit\n");
}

/* Inserts related vertex from input.txt file to the correct place in the vertex list.
If there is already such a vertex, returns and does not add that vertex. */
void add_vertex(VertexNodePtr *vertex, VertexNodePtr vertexPtr)
{
    VertexNodePtr previousPtr = NULL;
    VertexNodePtr currentPtr = *vertex;

    while (currentPtr != NULL && strcmp(vertexPtr->vertex_name, currentPtr->vertex_name) >= 0)
    {
        if (strcmp(currentPtr->vertex_name, vertexPtr->vertex_name) == 0)
            return;
        previousPtr = currentPtr;
        currentPtr = currentPtr->vertex_next;
    }
    if (previousPtr == NULL)
    {
        vertexPtr->vertex_next = *vertex;
        *vertex = vertexPtr;
    }
    else
    {
        previousPtr->vertex_next = vertexPtr;
        vertexPtr->vertex_next = currentPtr;
    }
}

/* Inserts related adjacent from input.txt file to the correct place in the adjacent list of related vertex. */
void add_adjacent(VertexNodePtr *vertex, char vertex_name[], AdjacentNodePtr newAdjacent)
{
    VertexNodePtr currentPtr = *vertex;
    newAdjacent->adjacent_next = NULL;

    while (currentPtr != NULL && strcmp(currentPtr->vertex_name, vertex_name) != 0)
    {
        currentPtr = currentPtr->vertex_next;
    }

    if (currentPtr->adjacent_list == NULL)
    {
        currentPtr->adjacent_list = newAdjacent;
    }
    else
    {
        AdjacentNodePtr currentAdjacentPtr = currentPtr->adjacent_list;
        while (currentAdjacentPtr != NULL)
        {
            if (currentAdjacentPtr->adjacent_next == NULL)
                break;
            currentAdjacentPtr = currentAdjacentPtr->adjacent_next;
        }
        currentAdjacentPtr->adjacent_next = newAdjacent;
    }
}

// Prints the adjacency list.
void print_adjacent(VertexNodePtr vertex)
{
    printf("\nThe Adjacency List");
    while (vertex != NULL)
    {
        AdjacentNodePtr adjacent = vertex->adjacent_list;
        printf("\n%s :", vertex->vertex_name);
        while (adjacent != NULL)
        {
            printf(" %s,%d", adjacent->adjacent_name, adjacent->weight);
            adjacent = adjacent->adjacent_next;
        }
        vertex = vertex->vertex_next;
    }
    printf("\n");
}


int main()
{
    FILE *file;
    VertexNodePtr vertex_head = NULL;
    char fileName[MAX_LEN];
    int choice;

    while (1)
    {
        print_menu();
        printf("Enter your choice: ");
        scanf(" %d", &choice);

        /* Asks user the file name in order to read, for every iteration reads the file line by line 
        and adds vertices and adjacents bidirectionally. */
        if (choice == 1)
        {
            printf("Enter file name: ");
            scanf(" %s", fileName);
            file = fopen(fileName, "r");
            char line[MAX_LEN];
            while (fgets(line, MAX_LEN, file))
            {
                VertexNodePtr vertex = (VertexNodePtr)malloc(sizeof(struct vertex));
                AdjacentNodePtr newAdjacent = (AdjacentNodePtr)malloc(sizeof(struct adjacent));
                vertex->vertex_next = NULL;
                vertex->adjacent_list = NULL;
                newAdjacent->adjacent_next = NULL;

                // It allows to get rid of commas in lines.
                int i = 0;
                char *tokenPtr, *arr[MAX_LEN];
                tokenPtr = strtok(line, ",");
                while (tokenPtr != NULL)
                {
                    arr[i++] = tokenPtr;
                    tokenPtr = strtok(NULL, ",");
                }
                strcpy(vertex->vertex_name, arr[0]);
                strcpy(newAdjacent->adjacent_name, arr[1]);
                newAdjacent->weight = atoi(arr[2]);

                add_vertex(&vertex_head, vertex);
                add_adjacent(&vertex_head, vertex->vertex_name, newAdjacent);

                // Adding vertices in reverse way
                VertexNodePtr vertex2 = (VertexNodePtr)malloc(sizeof(struct vertex));
                AdjacentNodePtr newAdjacent2 = (AdjacentNodePtr)malloc(sizeof(struct adjacent));
                vertex2->vertex_next = NULL;
                vertex2->adjacent_list = NULL;
                newAdjacent2->adjacent_next = NULL;

                strcpy(vertex2->vertex_name, arr[1]);
                strcpy(newAdjacent2->adjacent_name, arr[0]);
                newAdjacent2->weight = atoi(arr[2]);

                add_vertex(&vertex_head, vertex2);
                add_adjacent(&vertex_head, vertex2->vertex_name, newAdjacent2);
            }
            
            puts("\nThe file has been read.");
        }
        
        // Prints the adjacency list.
        if (choice == 2)
        {
            print_adjacent(vertex_head);
        }
        
        // Exits the program with a message.
        if (choice == 4)
        {
            puts("\nExiting...\nThank you!");
            break;
        }
    }

    fclose(file);
    return 0;
}
