#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "Math.h"
#include "Hash.h"
#include "print.h"

/*
static void stepHash( char[] );
*/
static int hash( HashTable *, char[] );
/*
static int isSizeIncrease( HashTable * );
static int isSizeDecrease( HashTable *);
*/
static void resize( HashTable * );
/*
static void refactor( HashTable * );
*/
/*
FUNCTION: createHash
IMPORT: size (Integer)
EXPORT: hash (HashTable)
PURPOSE: Create a hash entry array of size from IMPORT data
*/
HashTable* createHash( int size )
{
    HashTable *hash = NULL;
    HashEntry *hashArr = NULL;
    int newSize = 0;
    int i;

    hash = malloc(sizeof(HashTable));                 /* Creating HashTable struct */

    newSize = nextPrime( size );
    hashArr = malloc(sizeof(HashEntry) * newSize);    /* Creating the hashEntry array */
    for ( i = 0; i < newSize; i++ )
    {
        strcpy( hashArr[i].key, "" );
        hashArr[i].data = NULL;
        hashArr[i].type = '0';                       /* Set initial value for type first */
        hashArr[i].state = 0;                        /* 0 represents free and available */
    }
 
    hash->hashArray = hashArr;                        /* Point created Array to the Array in HashTable struct */
    hash->size = newSize;
    hash->count = 0;
    hash->lf = 0.0;

    return hash;
}

/*
FUNCTION: put
IMPORT: hash (HashTable), inKey (String), data (Void Pointer), inType (Character)
EXPORT: none
PURPOSE: Include the data into the hash table
*/
void put( HashTable* theHash, char inKey[], void *inData, char inType )
{
    HashEntry *hashArr = NULL;
    int hashIdx = 0, stop = FALSE; 
    int lastIdx = 0;

    hashIdx = hash( theHash, inKey );           /* Get the hash index from hash function */
    hashArr = theHash->hashArray;               /* Point the hashArray in HashTable to local hashArr pointer */

    if ( absolute( theHash->lf - UPPER_BOUND ) <= TOL_LF )
        resize( theHash );
    else
    {
        /* ASSERTION: Stop when an item is inserted into the table */
        while ( stop == FALSE )
        {
            if ( hashArr[hashIdx].state == 0 || hashArr[hashIdx].state == -1 )
            {
                strcpy( hashArr[hashIdx].key, inKey );
                hashArr[hashIdx].data = inData;
                hashArr[hashIdx].type = inType;
                hashArr[hashIdx].state = 1;              /* Mark this place as occupied */
                theHash->lf = getLoadFactor( theHash );
                theHash->count++;
                stop = TRUE;                             /* Stop the loop when data is inserted */
            }
            else if ( hashArr[hashIdx].state == 1 )
            {
                /* Key must always be unique and NEVER REPEATED */
                if ( strcmp( hashArr[hashIdx].key, inKey ) == 0 )
                {
                    printf("Key \'%s\' is existed\n", inKey);
                    stop = TRUE;
                }
                else
                {
                    /* Shuffle back to 0 and find the empty index if hashIdx is at the lastIdx */
                    lastIdx = theHash->size - 1;
                    if ( hashIdx == lastIdx ) 
                        hashIdx = 0;
                    else
                        hashIdx++;
                }
            }
        }
    }    
}

/*
FUNCTION: get
IMPORT: theHash (Hash Table), inKey (String)
EXPORT: data (void Pointer)
PURPOSE: Get the item using the key
*/
void* get( HashTable *theHash, char inKey[] )
{
    int hashIdx = 0;
    void *retData = NULL;
    HashEntry *hashArr = NULL;
    int stop = FALSE, capacity = theHash->size;

    hashArr = theHash->hashArray;
    hashIdx = hash( theHash, inKey );    
 
    /* Iterate until key was found OR when key input does not exist */
    while ( stop == FALSE )
    {
        if ( hashArr[hashIdx].state == 0 || hashArr[hashIdx].state == -1 )
        {
            printf("Key does not exist\n");
            stop = TRUE; 
        }
        else if ( hashArr[hashIdx].state == 1 )
        {
            /* Return the hash if the key is matching */
            if ( strcmp( hashArr[hashIdx].key, inKey ) == 0 )
            {
                retData = hashArr[hashIdx].data;
                stop = TRUE;
            }
            else /* Otherwise, move to the next index to find as it is at the colliding index */
            {
                /* Shuffle to the first index if hashIdx is at the last position */
                if ( hashIdx == (capacity - 1) )
                    hashIdx = 0; 
                else
                    hashIdx++;
                /* Otherwise, move to the next index */
            }
        }
    } 
    return retData;
}

/*
FUNCTION: removeHash
IMPORT: theHash (Hash Table), key (String)
EXPORT: data (void Pointer)
PURPOSE: Remove a hash entry from the hash table
*/
void* removeHash( HashTable *theHash, char inKey[] )
{
    int hashIdx = 0;
    void *retData = NULL;
    HashEntry *hashArr = NULL;
    int stop = FALSE, capacity = theHash->size;

    hashArr = theHash->hashArray;
    hashIdx = hash( theHash, inKey ); 
 
    if ( theHash->lf - LOWER_BOUND <= TOL_LF )
        resize( theHash );
    else
    {
        /* Iterate until key was found OR when key input does not exist */
        while ( stop == FALSE )
        {
            if ( hashArr[hashIdx].state == 0 )
            {
                printf("Key does not exist\n");
                stop = TRUE; 
            }
            else if ( hashArr[hashIdx].state == -1 )    /* The entry could be in the next index */
            {
                /* Reset the hashIdx if current hashIdx is at the last index so array will not overflow */ 
                if ( hashIdx == (capacity - 1) )
                    hashIdx = 0;        
                else
                    hashIdx++;          
                /* Otherwise, increment to move to the next index */
            }
            else if ( hashArr[hashIdx].state == 1 )
            {
                /* Remove the hash if the key is matching */
                if ( strcmp( hashArr[hashIdx].key, inKey ) == 0 )
                {
                    hashArr[hashIdx].state = -1;   /* Mark it as removed */
                    retData = hashArr[hashIdx].data;
                    theHash->count--;
                    stop = TRUE;
                }
                else /* Otherwise, move to the next index to find as it is at the colliding index */
                {
                    /* Shuffle to the first index if hashIdx is at the last position */
                    if ( hashIdx == (capacity - 1) )
                        hashIdx = 0; 
                    else
                        hashIdx++;
                    /* Otherwise, move to the next index */
                }
            }
        }
    }
    return retData; 
} 

/*
FUNCTION: getLoadFactor
IMPORT: theHash (HashTable)
EXPORT: factor (Reals)
PURPOSE: Return the load factor by taking count/size
*/
double getLoadFactor( HashTable *theHash )
{
    int theSize = 0, theCount = 0;
    double factor = 0;
    if ( theHash != NULL )
    {
        theSize = theHash->size;
        theCount = theHash->count;

        factor = (double)(theCount) / (double)(theSize);
    }
    return factor;
}

/*
FUNCTION: freeHash
IMPORT: theHash (Hash Table)
EXPORT: none
PURPOSE: Free the hash table
*/
void freeHash( HashTable *theHash )
{
    int i;
    HashEntry *hashArr = theHash->hashArray;

    for( i = 0; i < theHash->size; i++ )
    {
        free(&hashArr[i]);  /* Need '&' to specify the address because hashArr[i] 
                               is dereferencing into Hash Entry struct ONLY */
    }
    free(theHash); theHash = NULL;
}

/*
FUNCTION: printHash
IMPORT: theHash (Hash Table)
EXPORT: none
PURPOSE: Print the Hash Table content
*/
void printHash( HashTable *theHash )
{
    printFunc printData;
    HashEntry *hashArr = NULL;
    int i;

    if ( theHash != NULL )
    {
        hashArr = theHash->hashArray;

        for ( i = 0; i < theHash->size; i++ )
        {
            if ( hashArr[i].state == 1 )
            {
                printf("Key: ");
                printString( hashArr[i].key );
                printf(" \t");
                printData = getFunc( hashArr[i].type );                
                printf("Data: ");    
                (*printData)(hashArr[i].data);
                printf(" \t");
                printf("Index: %d", i);
                printf("\n");
            }
        }
    }
} 

/*
FUNCTION: hash
IMPORT: theHash (Hash Table), key (String)
EXPORT: hashIdx (Integer)
PURPOSE: Convert the key into a hash index
*/
static int hash( HashTable *theHash, char key[] )
{
    int hashValue = 0, hashIdx = 0;
    int i;
    for ( i = 0; key[i] != '\0'; i++ )
        hashValue += (int)(key[i]);

    hashIdx = hashValue % theHash->size;
    return hashIdx;
}

/*
FUNCTION: isSizeIncrease
IMPORT: theHash (HashTable)
EXPORT: resize (Integer)
PURPOSE: Check if the hash table load factor is within the threshold or not
*/
/*
static int isSizeIncrease( HashTable *theHash )
{
    int increase = FALSE;
    if ( getLoadFactor( theHash ) - UPPER_BOUND >= TOL )
        increase = TRUE;
    return increase;
}
*/
/*
FUNCTION: isSizeDecrease
IMPORT: theHash (HashTable)
EXPORT: resize (Integer)
PURPOSE: Check if the hash tale needed to shrink by comparing LOWER_BOUND with load factor
static int isSizeDecrease( HashTable *theHash )
{
    int decrease = FALSE;
    if ( absolute( LOWER_BOUND - getLoadFactor( theHash ) ) <= TOL )
        decrease = TRUE;
    return decrease;
}
*/

/*
FUNCTION: resize
IMPORT: oldHash (HashTable)
EXPORT: newHash (HashTable)
PURPOSE: Resize the hash table when Load Factor is greater or smaller than threshold
*/
static void resize( HashTable *oldHash )
{
    printFunc printData;
    HashTable *newHash = NULL;
    HashEntry *oldHashArr = NULL; /*, *newHashArr = NULL;*/
    int i, j, test;
    int newSize = 0, oldSize = 0;
    int factor = 2;     /* The hash size is changed by factor */

    oldSize = oldHash->size;

    /* If load factor is smaller than the LOWER_BOUND, theHash is shrinked */
    if ( oldHash->lf - LOWER_BOUND <= TOL_LF )
        newSize = oldHash->size / factor;               /* Decrease the size of the new array by factor */
    else    /* Otherwise, theHash is expanded */
        newSize = oldHash->size * factor;               /* Increase the size of the new array by factor */ 

    newHash = createHash( newSize );
    oldHashArr = oldHash->hashArray;

    j = 0;
    for( i = 0; i < oldSize; i++ )
    {
        /* Re-hash the existing hash entry because the hashIdx will be diff
           since the hash is now updated in size */
        if ( oldHashArr[i].state == 1 )
        {
            j = hash( newHash, oldHashArr[i].key );
            test = j;
            put( newHash, oldHashArr[i].key, oldHashArr[i].data, oldHashArr[i].type );
        }
    }
    /*oldHashAdrr = &oldHash;*/
    *oldHash = *newHash;
    printData = getFunc( oldHash->hashArray[j].type ); 
    (*printData)(oldHash->hashArray[j].data);

    printData = getFunc( newHash->hashArray[j].type ); 
    (*printData)(newHash->hashArray[test].data);

    printf("\nPointer for oldHashArr: %p\n", (void *)(oldHash->hashArray));
    printf("\nPointer for newHashArr: %p\n", (void *)(newHash->hashArray));
    
    
/*
    printf("OLD HASH size: %d\n", oldHash->size);
*/
/*
    freeHash( *oldHashAdrr ); *oldHashAdrr = NULL;
*/
}

/*
FUNCTION: refactor
IMPORT: theHash (HashTable)
EXPORT: none
PURPOSE: Refactor the hash array
*/
/*
static void refactor( HashTable *theHash )
{
    int newSize = 0;

    newSize = nextPrime( theHash->size );
    hashArr = malloc(sizeof(HashEntry) * newSize);    * Creating the hashEntry array */
/*
    for ( i = 0; i < newSize; i++ )
    {
        strcpy( hashArr[i].key, "" );
        hashArr[i].data = NULL;
        hashArr[i].state = 0;                        * 0 represents free and available */
/*
    }
 
    hash->hashArray = hashArr;                        * Point created Array to the Array in HashTable struct */
    /*hash->size = newSize;
    hash->count = 0;
*/
