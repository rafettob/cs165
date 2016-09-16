#ifndef HASH_TABLE_GUARD
#define HASH_TABLE_GUARD

#define BUCKETS 7

typedef int keyType;
typedef int valType;

typedef struct _hashnode {
    keyType key;
    valType val;
    struct _hashnode* next;
} hashnode;

typedef struct _hashtable {
    hashnode** values;
    int* bucketCount;
} hashtable;



void init(hashtable** ht);
void put(hashtable* ht, keyType key, valType value);
int get(hashtable* ht, keyType key, valType *values, int num_values);
void erase(hashtable* ht, keyType key);
int getHashCode(keyType key);

#endif
