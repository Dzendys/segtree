#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

//STRUCTS
typedef struct
{
    int* data;
    int length, capacity;
}IntArray;

typedef struct Node
{
    int min, max;
    Node *left, *right;
}Node;

typedef struct
{
    int interval;
    Node* root;
}Segtree;


//HELPING FUNCS
int max(int a, int b)
{
    #ifdef MAX
    printf("[MAX] %d-%d\n", a, b);
    #endif
    if (a >= b)
        return a;
    return b;
}

int min(int a, int b)
{
    #ifdef MIN
    printf("[MIN] %d-%d\n", a, b);
    #endif
    if (a<=b)
        return a;
    return b;
}


//ARRAY
bool resizeIntArray(IntArray* array, int newCapacity)
{
    #ifdef RESIZE
    printf("[RESIZE] Resizing from %d to %d\n", array->capacity, newCapacity);
    #endif
    array->capacity = newCapacity;
    int* tmp = (int*)realloc(array->data, array->capacity * sizeof(*(array->data)));
    if (!tmp)
        return false;
    array->data = tmp;
    if (array->length > array->capacity)
        array->length = array->capacity;
    return true;
}

bool appendIntArray(IntArray* array, int value)
{
    #ifdef ARRAY_APPEND
    printf("[ARRAY_APPEND] Appending %d to array\n", value);
    #endif
    if (array->length >= array->capacity)
    {
        #ifdef ARRAY_APPEND
        puts("[ARRAY_APPEND] Needs to realloc");
        #endif
        array->capacity = (array->capacity + 1) * 2;
        int* tmp = (int*)realloc(array->data, array->capacity*sizeof(*(array->data)));
        if (!tmp)
            return false;
        array->data = tmp;
    }
    array->data[(array->length)++] = value;
    return true;
}

IntArray makeIntArray()
{
    IntArray i;
    i.capacity = 0;
    i.length = 0;
    i.data = NULL;
    return i;
}

void destroyIntArray(IntArray* array)
{
    array->capacity = 0;
    array->length = 0;
    free(array->data);
    array->data = NULL;
}


//NODE
Node* makeNode()
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->left = NULL;
    n->right = NULL;
    n->max = INT_MIN;
    n->min = INT_MAX;
    return n;
}

void destroyNodeRec(Node* node)
{
    if (node == NULL)
        return;
    destroyNodeRec(node->right);
    destroyNodeRec(node->left);
    free(node);
}


//SEGTREE
bool overlapsCompletly(int Qfrom, int Qto, int from, int to)
{
    if (Qfrom <= from && Qto >= to)
    {
        #ifdef OVERLAP_COMPLETLY
        printf("[OVERLAP_COMPLETLY] true %d-%d %d-%d\n", Qfrom, Qto, from, to);
        #endif
        return true;
    }
    #ifdef OVERLAP_COMPLETLY
    printf("[OVERLAP_COMPLETLY] false %d-%d %d-%d\n", Qfrom, Qto, from, to);
    #endif
    return false;
}

bool overlapsPartly(int Qfrom, int Qto, int from, int to)
{
    if (Qfrom <= to && Qto >= from)
    {
        #ifdef OVERLAP_PARTLY
        printf("[OVERLAP_PARTLY] true %d-%d %d-%d\n", Qfrom, Qto, from, to);
        #endif
        return true;
    }
    #ifdef OVERLAP_PARTLY
    printf("[OVERLAP PARTLY] false %d-%d %d-%d\n", Qfrom, Qto, from, to);
    #endif
    return false;
}

Node* buildSegtree(Segtree* tree, IntArray* array, int from, int to)
{
    if (from == to)
    {
        Node* node = makeNode();
        node->min = array->data[from];
        node->max = array->data[from];
        return node;
    }

    int mid = from + (to - from)/2;
    Node* node = makeNode();
    node->left = buildSegtree(tree, array, from, mid);
    node->right = buildSegtree(tree, array, mid + 1, to);
    node->min = min(node->left->min, node->right->min);
    node->max = max(node->left->max, node->right->max);
    return node;
}

int queryMaxRec(Node* node, int Qfrom, int Qto, int from, int to)
{
    if (overlapsCompletly(Qfrom, Qto, from, to))
        return node->max;
    
    int mid = from + (to - from) / 2;

    //left subtree
    int left = INT_MIN;
    if (overlapsCompletly(Qfrom, Qto, from, mid))
        left = node->left->max;
    else if (overlapsPartly(Qfrom, Qto, from, mid))
        left = queryMaxRec(node->left, Qfrom, Qto, from, mid);
    
    //right subtree
    int right = INT_MIN;
    if (overlapsCompletly(Qfrom, Qto, mid + 1, to))
        right = node->right->max;
    else if (overlapsPartly(Qfrom, Qto, mid + 1, to))
        right = queryMaxRec(node->right, Qfrom, Qto, mid + 1, to);
    
    return max(left, right);
}

int queryMinRec(Node* node, int Qfrom, int Qto, int from, int to)
{
    if (overlapsCompletly(Qfrom, Qto, from, to))
        return node->min;
    
    int mid = from + (to - from) / 2;

    //left subtree
    int left = INT_MAX;
    if (overlapsCompletly(Qfrom, Qto, from, mid))
        left = node->left->min;
    else if (overlapsPartly(Qfrom, Qto, from, mid))
        left = queryMinRec(node->left, Qfrom, Qto, from, mid);
    
    //right subtree
    int right = INT_MAX;
    if (overlapsCompletly(Qfrom, Qto, mid + 1, to))
        right = node->right->min;
    else if (overlapsPartly(Qfrom, Qto, mid + 1, to))
        right = queryMinRec(node->right, Qfrom, Qto, mid + 1, to);
    
    return min(left, right);
}

int queryMax(Segtree* tree, int Qfrom, int Qto)
{
    #ifdef QUERY
    printf("[QUERY] Max query %d-%d\n", Qfrom, Qto);
    #endif
    if (tree->root == NULL)
        return INT_MIN;
    return queryMaxRec(tree->root, Qfrom, Qto, 0, tree->interval);
}

int queryMin(Segtree* tree, int Qfrom, int Qto)
{
    #ifdef QUERY
    printf("[QUERY] Min query %d-%d\n", Qfrom, Qto);
    #endif
    if (tree->root == NULL)
        return INT_MAX;
    return queryMinRec(tree->root, Qfrom, Qto, 0, tree->interval);
}

Segtree makeSegtree(IntArray* array)
{
    Segtree tree;
    tree.interval = array->length - 1;
    tree.root = buildSegtree(&tree, array, 0, tree.interval);
    return tree;
}

void destroySegtree(Segtree* tree)
{
    destroyNodeRec(tree->root);
    tree->root = NULL;
    tree->interval = -1;
}


//LOADING
bool loadArray(IntArray* array)
{
    puts("Napište čísla oddělená mezerou:");
    int number;
    while (scanf("%d", &number) == 1)
    {
        //append to int array
        if (!appendIntArray(array, number))
            return false;

        //end of input (on one line)
        char c = getchar();
        if (c == '\n' || c == EOF)
            return (array->length != 0);
        
        //unudentifiable character
        if (c != ' ')
            return false;
    }
    return false;
}

enum {BAD_INPUT, END_OF_INPUT, MIN_QUERY, MAX_QUERY};

int loadQuery(int* from, int* to, int maxInterval)
{
    char q = '\0';
    if (scanf(" %c %d %d", &q, from, to) != 3)
    {
        //check for end of input
        char c = EOF;
        scanf(" %c", &c);
        if (c == EOF || c == '\n')
        {
            #ifdef LOAD_QUERY
            puts("[LOAD_QUERY] No more input, exiting...");
            #endif
            return END_OF_INPUT;
        }
        #ifdef LOAD_QUERY
        puts("[LOAD_QUERY] Bad input, exiting...");
        #endif
        return BAD_INPUT;
    }
    if (*from < 0 || *to > maxInterval || *to < *from || (q != 'm' && q != 'M'))
    {
        #ifdef LOAD_QUERY
        puts("[LOAD_QUERY] Bad interval or query identifier, exiting...");
        #endif
        return BAD_INPUT;
    }
    if (q == 'm')
        return MIN_QUERY;
    return MAX_QUERY;
}

//PRINTING
void printIntArray(IntArray* array)
{
    for (int i = 0; i < array->length; i++)
        printf("|%d", array->data[i]);
    printf("|\n");
}


int main()
{
    IntArray array = makeIntArray();
    if (!loadArray(&array))
    {
        puts("Nesprávný vstup!");
        destroyIntArray(&array);
        return EXIT_FAILURE;
    }

    #ifdef PRINT_ARRAY
    printIntArray(&array);
    #endif

    Segtree tree = makeSegtree(&array);

    //queries
    int from, to;
    puts("Napište dotaz:");
    while (!feof(stdin))
    {
        int code = loadQuery(&from, &to, tree.interval);
        if (code == BAD_INPUT)
        {
            puts("Nesprávný dotaz!");
            destroySegtree(&tree);
            destroyIntArray(&array);
            return EXIT_FAILURE;
        }
        else if (code == END_OF_INPUT)
            break;
        else if (code == MIN_QUERY)
            printf("Minimum v intervalu %d-%d je: %d\n", from, to, queryMin(&tree, from, to));
        else if (code == MAX_QUERY)
            printf("Maximum v intervalu %d-%d je: %d\n", from, to, queryMax(&tree, from, to));
    }
    
    //cleanup
    destroySegtree(&tree);
    destroyIntArray(&array);
    return EXIT_SUCCESS;
}