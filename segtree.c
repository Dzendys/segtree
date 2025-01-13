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
/**
 * @brief Returns the maximum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of a and b.
 */
int max(int a, int b)
{
    #ifdef MAX
    printf("[MAX] %d-%d\n", a, b);
    #endif
    if (a >= b)
        return a;
    return b;
}

/**
 * @brief Returns the minimum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The minimum of a and b.
 */
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
/**
 * @brief Resizes the given array to the given capacity.
 *
 * @param array The array to resize.
 * @param newCapacity The new capacity of the array.
 * @return True if the resizing was successful, false otherwise.
 *
 * If the new capacity is smaller than the current length of the array,
 * the length is set to the new capacity.
 */
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

/**
 * @brief Appends a value to the end of the IntArray.
 *
 * @param array A pointer to the IntArray to which the value should be appended.
 * @param value The integer value to append to the array.
 * @return True if the value is successfully appended, false if memory allocation fails.
 *
 * If the array's length reaches its capacity, the function reallocates memory
 * to expand the capacity before appending the new value.
 */
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

/**
 * @brief Returns an empty IntArray.
 *
 * @return An empty IntArray with capacity and length set to 0 and a NULL data pointer.
 */
IntArray makeIntArray()
{
    IntArray i;
    i.capacity = 0;
    i.length = 0;
    i.data = NULL;
    return i;
}

/**
 * @brief Frees the memory allocated for the IntArray and resets its attributes.
 *
 * @param array A pointer to the IntArray to be destroyed.
 *
 * This function deallocates the memory used by the IntArray's data, sets the
 * data pointer to NULL, and resets the array's capacity and length to zero.
 */
void destroyIntArray(IntArray* array)
{
    array->capacity = 0;
    array->length = 0;
    free(array->data);
    array->data = NULL;
}


//NODE
/**
 * @brief Returns a newly allocated Node with default values.
 *
 * @return A pointer to a newly allocated Node.
 *
 * The returned node has its left and right child pointers set to NULL,
 * and its min and max values set to INT_MAX and INT_MIN, respectively.
 */
Node* makeNode()
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->left = NULL;
    n->right = NULL;
    n->max = INT_MIN;
    n->min = INT_MAX;
    return n;
}

/**
 * @brief Recursively destroys a binary tree node and its children.
 *
 * @param node A pointer to the Node to be destroyed.
 *
 * This function recursively frees the memory allocated for a Node and
 * all of its children in a binary tree. It performs a post-order traversal
 * to ensure that child nodes are destroyed before their parent node.
 */
void destroyNodeRec(Node* node)
{
    if (node == NULL)
        return;
    destroyNodeRec(node->right);
    destroyNodeRec(node->left);
    free(node);
}


//SEGTREE
/**
 * @brief Determines if one interval completely overlaps another.
 *
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @param from The starting index of the interval to compare.
 * @param to The ending index of the interval to compare.
 * @return True if the query interval completely overlaps the given interval, false otherwise.
 *
 * This function checks if the query interval [Qfrom, Qto] completely covers
 * the interval [from, to]. It returns true if Qfrom is less than or equal to
 * from and Qto is greater than or equal to to.
 */
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

/**
 * @brief Determines if one interval partially overlaps another.
 *
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @param from The starting index of the interval to compare.
 * @param to The ending index of the interval to compare.
 * @return True if the query interval overlaps the given interval in any way, false otherwise.
 *
 * This function checks if the query interval [Qfrom, Qto] overlaps the interval
 * [from, to] in any way. It returns true if Qfrom is less than or equal to to and
 * Qto is greater than or equal to from.
 */
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

/**
 * @brief Constructs a segment tree node for the given array interval.
 *
 * @param tree A pointer to the segtree being constructed.
 * @param array A pointer to the IntArray from which the segment tree is built.
 * @param from The starting index of the array interval.
 * @param to The ending index of the array interval.
 * @return A pointer to the root node of the constructed segment tree for the specified interval.
 *
 * This function recursively divides the array interval into two halves and
 * constructs the segment tree node for each half. It sets the min and max
 * values of the node based on its children's values. If the interval
 * consists of a single element, it creates a leaf node with that element's value.
 */
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

/**
 * @brief Recursively queries the maximum value within a specified interval in a segment tree.
 *
 * @param node A pointer to the current Node being queried.
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @param from The starting index of the current node's interval.
 * @param to The ending index of the current node's interval.
 * @return The maximum value within the specified query interval.
 *
 * This function performs a recursive search to find the maximum value
 * within the query interval [Qfrom, Qto] in the segment tree. It considers
 * three cases: complete overlap, partial overlap, and no overlap, and accordingly
 * combines results from the left and right subtrees.
 */
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

/**
 * @brief Recursively queries the minimum value within a specified interval in a segment tree.
 *
 * @param node A pointer to the current Node being queried.
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @param from The starting index of the current node's interval.
 * @param to The ending index of the current node's interval.
 * @return The minimum value within the specified query interval.
 *
 * This function performs a recursive search to find the minimum value
 * within the query interval [Qfrom, Qto] in the segment tree. It considers
 * three cases: complete overlap, partial overlap, and no overlap, and accordingly
 * combines results from the left and right subtrees.
 */
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

/**
 * @brief Queries the maximum value within a specified interval in a segment tree.
 *
 * @param tree A pointer to the Segtree being queried.
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @return The maximum value within the specified query interval.
 *
 * This function is a wrapper for queryMaxRec and provides a more convenient
 * interface for querying the maximum value in a segment tree. It takes
 * care of the base case when the tree is empty.
 */
int queryMax(Segtree* tree, int Qfrom, int Qto)
{
    #ifdef QUERY
    printf("[QUERY] Max query %d-%d\n", Qfrom, Qto);
    #endif
    if (tree->root == NULL)
        return INT_MIN;
    return queryMaxRec(tree->root, Qfrom, Qto, 0, tree->interval);
}

/**
 * @brief Queries the minimum value within a specified interval in a segment tree.
 *
 * @param tree A pointer to the Segtree being queried.
 * @param Qfrom The starting index of the query interval.
 * @param Qto The ending index of the query interval.
 * @return The minimum value within the specified query interval.
 *
 * This function is a wrapper for queryMinRec and provides a more convenient
 * interface for querying the minimum value in a segment tree. It takes
 * care of the base case when the tree is empty.
 */
int queryMin(Segtree* tree, int Qfrom, int Qto)
{
    #ifdef QUERY
    printf("[QUERY] Min query %d-%d\n", Qfrom, Qto);
    #endif
    if (tree->root == NULL)
        return INT_MAX;
    return queryMinRec(tree->root, Qfrom, Qto, 0, tree->interval);
}

/**
 * @brief Constructs a segment tree from the given integer array.
 *
 * @param array A pointer to the IntArray from which the segment tree is built.
 * @return A Segtree structure containing the root node of the constructed 
 * segment tree and the interval representing the range of indices in the array.
 *
 * This function initializes a segment tree by setting the interval to the 
 * length of the array minus one and calls buildSegtree to construct the 
 * tree nodes. It returns the constructed segment tree.
 */
Segtree makeSegtree(IntArray* array)
{
    Segtree tree;
    tree.interval = array->length - 1;
    tree.root = buildSegtree(&tree, array, 0, tree.interval);
    return tree;
}

/**
 * @brief Destroys a segment tree by deallocating all of its nodes.
 *
 * @param tree A pointer to the Segtree to be destroyed.
 *
 * This function recursively frees the memory allocated for each node
 * in the segment tree using destroyNodeRec. Afterwards, it resets the
 * tree's root pointer to NULL and sets the interval to -1.
 */
void destroySegtree(Segtree* tree)
{
    destroyNodeRec(tree->root);
    tree->root = NULL;
    tree->interval = -1;
}


//LOADING
/**
 * @brief Loads integers from standard input into an IntArray.
 *
 * @param array A pointer to the IntArray to be loaded with integers.
 * @return True if at least one integer is successfully loaded and appended, false otherwise.
 *
 * This function reads integers from standard input, appending each to the given
 * IntArray. Input is terminated by a newline or EOF. The function returns false
 * if memory allocation fails or if a non-integer character (other than space) is encountered.
 */
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

/**
 * @brief Loads a query from standard input.
 *
 * @param from A pointer to an int to store the starting index of the query interval.
 * @param to A pointer to an int to store the ending index of the query interval.
 * @param maxInterval The ending index of the array interval.
 * @return BAD_INPUT if the input is invalid, END_OF_INPUT if there is no more input, MIN_QUERY or MAX_QUERY depending on the type of query.
 *
 * This function reads a query from standard input, which consists of a single
 * character (either 'm' or 'M') followed by two integers representing the
 * starting and ending indices of the query interval. It appends the loaded
 * query to the given IntArray. Input is terminated by a newline or EOF.
 * The function returns BAD_INPUT if memory allocation fails or if a non-integer
 * character (other than space) is encountered, END_OF_INPUT if there is no more
 * input, MIN_QUERY or MAX_QUERY depending on the type of query.
 */
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
/**
 * @brief Prints the contents of an IntArray.
 *
 * @param array A pointer to the IntArray to be printed.
 *
 * This function prints each element of the IntArray, with each element 
 * separated by a '|' character and enclosed within '|' characters.
 */
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
