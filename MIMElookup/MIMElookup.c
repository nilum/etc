#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
#define MAX_N 16384 // using a power of 2 for the hash table size
 #define MAX_FILE_EXT_LENGTH 11
 #define MAX_MIME_TYPE_LENGTH 51
 
unsigned int hashString(char* str, int len) // should definitely look into a better hash function
{
    unsigned int hashValue = 349;
    for (int i = 0; i < len; i++)
    {
        hashValue += *(str + i);
        hashValue *= *(str + i) + i;
        hashValue >> i;
    }
    return hashValue & MAX_N-1; // mask out unnecessary bits
}
char* movePointerToLastPeriod(char* P, int len)
{
    int periodPos = 0;
    for (int i = 0; i < len; i++)
    {
        if (*(P + i) == '.')
            periodPos = i;
    }
    return (P + periodPos);
}
 
int main()
{
    int N; // Number of elements which make up the association table.
    scanf("%d", &N); fgetc(stdin);
    int Q; // Number Q of file names to be analyzed.
    scanf("%d", &Q); fgetc(stdin);
    
    char mimeTable[MAX_N][MAX_FILE_EXT_LENGTH + MAX_MIME_TYPE_LENGTH] = {0};
    for (int i = 0; i < N; i++)
    {
        char EXT[MAX_FILE_EXT_LENGTH]; // file extension
        char MT[MAX_MIME_TYPE_LENGTH]; // MIME type.
        scanf("%s%s", EXT, MT); fgetc(stdin);
        for (int j = 0; j < strlen(EXT); j++) EXT[j] = tolower(EXT[j]); // convert the extension to lowercase before hashing
        unsigned int hash = hashString(EXT, strlen(EXT));
        while (mimeTable[hash][0] != 0) // while there's a collision, increment the index
        {
            if (hash != MAX_N - 1) // make sure it wraps around instead of overflowing
                hash++;
            else
                hash = 0;
        }
        strcpy(mimeTable[hash], EXT);
        strcpy(mimeTable[hash] + MAX_FILE_EXT_LENGTH, MT);
    }
    for (int i = 0; i < Q; i++)
    {
        int foundValid = 0;
        char FNAME[500]; // One file name per line.
        fgets(FNAME,500,stdin); // One file name per line.
        char* P = FNAME;
        P = movePointerToLastPeriod(P, strlen(P));
        
        if(*P == '.')
        {
            for (int i = 0; i < strlen(P); i++)
            {
                if (*(P + i) == '\n')
                    *(P + i) = '\0';
            }
            char EXT[MAX_FILE_EXT_LENGTH];
            strcpy(EXT, ++P); // advance the pointer one past the period
            for (int j = 0; j < strlen(EXT); j++) EXT[j] = tolower(EXT[j]); // convert the extension to lowercase
            unsigned int hash = hashString(EXT, strlen(EXT)); // hash it
            while (mimeTable[hash][0] && foundValid == 0) // while there's a valid entry in the hash table
            {
                if (strcmp(mimeTable[hash], EXT) == 0) // if it matches
                {
                    printf("%s\n", mimeTable[hash]+MAX_FILE_EXT_LENGTH);
                    foundValid = 1;
                }
                else if (hash == MAX_N - 1) // make sure the hash doesn't overflow the table
                    hash = 0;
                else
                    hash++;
            }
            
        }
        if (foundValid != 1)
            printf("UNKNOWN\n");
        foundValid = 0;                
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    return 0;
}
