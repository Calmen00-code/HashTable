#ifndef HASH
#define HASH

#define LOWER_BOUND 0.4
#define UPPER_BOUND 0.7

typedef struct HashEntry
{
    char key[STR];
    void *data;
    int state;
}HashEntry;

typedef struct HashTable
{
    HashEntry *hashArray;
    int size;
    int count;
}HashTable;

HashTable* createHash( int );
void put( HashTable*, char[], void* );
void* get( HashTable *, char[] );
void* removeHash( HashTable *, char[] );
double getLoadFactor( HashTable * );

#endif
