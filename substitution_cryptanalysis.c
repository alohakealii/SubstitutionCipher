#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000
#define MAX_CHAR_TYPES 30

char *readFile(char *filename);
void charCount(char ct[]);
void decrypt(char *ct, char *keyFile);

void main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Ciphertext file required.\n");
		return;
	}

	// read a file
	char *ct = readFile(argv[1]);
	printf("CT: %s\n\n", ct);

	// display numbers of each character
	charCount(ct);

	// if chosen, attempt decrypt with a key
	if (argc > 2)
		decrypt(ct, argv[2]);
}

char *readFile(char *filename)
{
    FILE *file;
    char *ciphertext;
    size_t n = 0;
    int c;

    // if cannot open file
    if ((file = fopen(filename, "r")) == NULL)
        return NULL;

    ciphertext = malloc(MAX_LENGTH);

    while ((c = fgetc(file)) != EOF)
    {
        ciphertext[n++] = (char) c;
    }

    // terminate with the null character
    ciphertext[n] = '\0';        

    return ciphertext;
}

void charCount(char ct[]) {
    char chars[MAX_CHAR_TYPES];
    int count[MAX_CHAR_TYPES];
    int i = 0;
    // initialize arrays
    for (i = 0; i < MAX_CHAR_TYPES; i++) {
        chars[i] = '\0';
        count[i] = 0;
    }
    i = 0;
    // loop through cipher text
    while (ct[i] != '\0') {
        int j = 0;
        // loop through char frequency arrays
        for (j = 0; j < MAX_CHAR_TYPES; j++) {
            // if char has not been seen yet
            if (chars[j] == '\0') {
                chars[j] = ct[i];
                count[j]++;
                j = MAX_CHAR_TYPES;
            }
            // if char matches and has been seen
            else if (chars[j] == ct[i]) {
                count[j]++;
                j = MAX_CHAR_TYPES;
            }
        }
        i++;
    }
    // print char count
    printf("Char Count:\n\n");
    for (i = 0; i < MAX_CHAR_TYPES; i++) {
        if (chars[i] != '\0')
            printf("%c: %2d\n", chars[i], count[i]);
    }
    printf("\n");
}

void decrypt(char *ct, char *keyFile) {
    // go through file to read key
    char *key = readFile(keyFile);
    char cipherchar[MAX_CHAR_TYPES];
    char plainchar[MAX_CHAR_TYPES];
    int i = 0;
    while (key[i] != '\n') {
        cipherchar[i] = key[i];
        i++;
    }
    int numOfDifChars = i;
    i++;
    int j;
    for (j = 0; j < numOfDifChars; j++) {
        plainchar[j] = key[i];
        i++;
    }

    /*// test section
    for (i = 0; i < numOfDifChars; i++) {
        printf("%c = %c\n", cipherchar[i], plainchar[i]);
    }
    printf("\n");*/

    // go through ciphertext changing with key
    i = 0;
    while (ct[i] != '\0') {
        for (j = 0; j < numOfDifChars; j++) {
            if (ct[i] == cipherchar[j]) {
                ct[i] = plainchar[j];
                j = numOfDifChars;
            }
        }
        i++;
    }
    printf("PT: %s\n\n", ct);
}