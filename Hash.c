#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "Math.h"
#include "Hash.h"

/*
static int resize( int );
static void stepHash( char[] );
*/
static int hash( HashTable *, char[] );

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
        hashArr[i].state = 0;                        /* 0 represents free and available */
    }
        
    hash->hashArray = hashArr;                        /* Point created Array to the Array in HashTable struct */
    hash->size = newSize;
    hash->count = 0;

    return hash;
} 

/*
FUNCTION: put
IMPORT: hash (HashTable), inKey (String), data (Void Pointer)
EXPORT: none
PURPOSE: Include the data into the hash table
*/
void put( HashTable* theHash, char inKey[], void *inData )
{
    HashEntry *hashArr = NULL;
    int hashIdx = 0, stop = FALSE; 
    int lastIdx = 0;

    hashIdx = hash( theHash, inKey );           /* Get the hash index from hash function */
    hashArr = theHash->hashArray;               /* Point the hashArray in HashTable to local hashArr pointer */

    /* ASSERTION: Stop when an item is inserted into the table */
    while ( stop == FALSE )
    {
        if ( hashArr[hashIdx].state == 0 || hashArr[hashIdx].state == -1 )
        {
            strcpy( hashArr[hashIdx].key, inKey );
            hashArr[hashIdx].data = inData;
            hashArr[hashIdx].state = 1;              /* Mark this place as occupied */
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
