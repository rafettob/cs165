#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>


// initialize the components of the hashtable
void init(hashtable** ht) {
    hashtable* hTable = malloc(sizeof(hashtable));
    //*ht = malloc(sizeof(hashtable));
    *ht = hTable;

    hTable->values = calloc(BUCKETS, sizeof(hashnode *));
    hTable->bucketCount = calloc(BUCKETS, sizeof(int));

    // This should be unnecessary since I'm performing a calloc rather than a malloc.
    // for (int i = 0; i < BUCKETS; ++i) {
    //     //hTable->values[i] = NULL;
    //     hTable->bucketCount[i] = 0;
    // }
}

// insert a key-value pair into the hash table
void put(hashtable* ht, keyType key, valType value) {
    //breakpoint set -f hash_table.c -l 28 //here's how to set a breakpoint
    hashnode *newNode = malloc(sizeof(hashnode));
    newNode->key = key;
    newNode->val = value;
    int hashCode = getHashCode(key);
    
    
     if ((ht->bucketCount[hashCode])++ == 0) {
        ht->values[hashCode] = newNode;
        newNode->next = NULL;
     }
     else {
        //check if this works. Unclear exactly where the allocated memory for the previous node is.
        //Might not make sense to store first in memory - just use a point.
        hashnode *currentNode = (ht->values[hashCode]);
        newNode->next = currentNode;
        ht->values[hashCode] = newNode;
     }
}

// get entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries. If the return value is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call. 
int get(hashtable* ht, keyType key, valType *values, int num_values) {
    int hashCode = getHashCode(key);
    int matchingValues = 0;
    hashnode *checkNode = ht->values[hashCode];
    while (checkNode != NULL) {
        if (checkNode->key == key) {
            if (++matchingValues <= num_values)
                values[matchingValues-1] = checkNode->val;
        }
        checkNode = checkNode->next;
    }
    return matchingValues;
}

// erase a key-value pair from the hash talbe
void erase(hashtable* ht, keyType key) {
    int hashCode = getHashCode(key);
    hashnode *prevNode = NULL;
    hashnode *checkNode = ht->values[hashCode];
    hashnode *nextNode;

    while (checkNode != NULL) {
        if (checkNode->key == key) {
            if (prevNode == NULL) {
                ht->values[hashCode] = checkNode->next;
            }
            else {
                prevNode->next = checkNode->next;
            }
            nextNode = checkNode->next;
            free(checkNode);
            checkNode = nextNode;
            ht->bucketCount[hashCode]--;
        }
        else {
            prevNode = checkNode;
            checkNode = checkNode->next;
        }
    }
}

int getHashCode(keyType key)
{
    return key % BUCKETS;
}
