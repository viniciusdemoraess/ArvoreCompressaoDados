#define DataStructure_LinkedList_h
#define DataStructure_LinkedList_h

enum boolean {
    true = 1, false = 0
};

typedef enum boolean bool;

typedef struct Node {
    void *data;
    int *freq;
    struct Node *next;
    
}Node;

typedef struct LinkedList {
    Node *first;
    int size;
}LinkedList;

typedef bool (*compare)(void*,void*);

void init(LinkedList *list);
int enqueue(LinkedList *list, void *data, int *freq);
bool isEmpty(LinkedList *list);
int indexOf(LinkedList *list, void *data, int *freq, compare equal);
int freq(LinkedList *list);