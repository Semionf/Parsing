#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)
void PrintAllMoviesForYear(int);
void GetMovieByIndex(int);
void freeList();
void printList();
void add(int, int, char, char*, char*);
void addFromFile(struct OskarActor*);
void switchElements(struct OskarActor*);
void ageBubbleSort();
int getItemCount();
void updatePopularity(int);
void Run();
void LoadFile();
void Save(char*);
void Load(char*);
void mostPopular();

struct OskarActor {
    int index;
    int year;
    int popularity;
    char age;
    char movie[1000];
    char name[1000];
    struct OskarActor* next;
    struct OskarActor* prev;
};

struct OskarActor_Header
{
    int Version;
    int ItemsCount;
    char reserved[1000];
};

struct OskarActor* HEAD = NULL;
struct OskarActor* TAIL = NULL;

int main() 
{
    char fileName[100];
    LoadFile();
    Run();
    Run();
    Run();
    Run();
    printList();
    printf("Enter file name to save: ");
    scanf("%s", fileName);
    Save(fileName);
    freeList();
    Load(fileName);
    printList();
    freeList();
    return 0;
}
void PrintAllMoviesForYear(int Year) {

    struct OskarActor* curr = HEAD;
    while (curr)
    {
        if (curr->year == Year)
        {

            printf("%s %d\n", curr->name, curr->age);

        }
        curr = curr->next;
    }

}

void GetMovieByIndex(int Index) {

    struct OskarActor* curr = HEAD;
    while (curr)
    {
        if (curr->index == Index)
        {

            printf("%s %s %d\n", curr->movie, curr->name, curr->age);
            break;

        }
        curr = curr->next;
    }

}

void freeList() {

    struct OskarActor* curr = HEAD;
    while (HEAD)
    {
        curr = HEAD;
        HEAD = HEAD->next;
        free(curr);
    }
    HEAD = TAIL = NULL;
}

void printList() {
    struct OskarActor* curr = HEAD;
    while (curr)
    {
        printf("%d %d %d %s %s\n", curr->index, curr->year, curr->age, curr->movie, curr->name);
        curr = curr->next;
    }
}

void add(int tokenIndex,int tokenYear,char tokenAge, char* tokenName, char* tokenMovie) {
    struct OskarActor* node_1 = (struct OskarActor*)malloc(sizeof(struct OskarActor));
    node_1->next = node_1->prev = NULL;
    node_1->popularity = 0;
    node_1->index = tokenIndex;
    node_1->year = tokenYear;
    node_1->age = tokenAge;
    strcpy(node_1->name, tokenName);
    strcpy(node_1->movie, tokenMovie);


    if (HEAD == NULL)
    {
        HEAD = TAIL = node_1;
    }
    else
    {
        TAIL->next = node_1;
        node_1->prev = TAIL;
        TAIL = node_1;
    }
}

void addFromFile(struct OskarActor* node) {

    if (HEAD == NULL)
    {
        HEAD = TAIL = node;
    }
    else
    {
        TAIL->next = node;
        node->prev = TAIL;
        TAIL = node;
    }
}


void LoadFile()
{
    FILE* f = fopen("Actress.bin.txt", "r");
    char str[10000] = "";
    if (!f)
    {
        printf("File Error");
        return;
    }
    int index, year;
    char age;
    char* tokenIndex;
    char* tokenYear;
    char* tokenAge;
    char* tokenName;
    char* tokenMovie;
    char* token;

    fgets(str, sizeof(str), f);
    while (fgets(str, sizeof(str), f) != NULL)
    {

        tokenIndex = strtok(str, ",");
        index = atoi(tokenIndex);
        tokenYear = strtok(NULL, ",");
        year = atoi(tokenYear);
        tokenAge = strtok(NULL, ",");
        age = atoi(tokenAge);
        token =  strtok(NULL, "\"");
        tokenName = strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        tokenMovie = strtok(NULL, "\"");


        add(index, year, age, tokenName, tokenMovie);
    }
}

void switchElements(struct OskarActor* element)
{
    struct OskarActor* curr = element;
    if (!curr)
    {
        printf("The list is empty");
        return;
    }
    if (HEAD == TAIL)
    {
        printf("The list has one element");
        return;
    }
    else if (HEAD->next == TAIL) // 4 5
    {
        curr->next = NULL;
        curr->prev = TAIL;
        TAIL->prev = NULL;
        TAIL->next = curr;
        HEAD = curr->prev;
        TAIL = curr;
        printf("The list has two element");
        return;
    }
    else if (curr->next && !curr->prev) // 4 5 6  NULL-5 -4 - 6
    {
        curr->next->prev = NULL;
        curr->prev = curr->next;
        curr->next = curr->next->next;
        curr->prev->next = curr;
        curr->next->prev = curr;
        HEAD = curr->prev;
        return;
    }
    else if (curr->next && curr->next->next) // 4 6 5 7
    {
        curr->next->prev = curr->prev; //5 - 4
        curr->prev->next = curr->next; //4 - 5
        curr->next->next->prev = curr; //7 - 6
        curr->prev = curr->next;       //6 - 5
        curr->next = curr->next->next; //6 - 7
        curr->prev->next = curr;       //5 - 6
        return;
    }
    else {// 4 5 7 6
        curr->next->prev = curr->prev; // 6 - 5
        curr->prev->next = curr->next; // 5 - 6
        curr->prev = curr->next; // 7 - 6
        curr->prev->next = curr; // 6 - 7
        curr->next = NULL; // 7 - NULL
        TAIL = curr;
        return;
    }
}

void ageBubbleSort()
{
    struct OskarActor* curr = HEAD;
    int counter = 1;
    if (!HEAD || !HEAD->next)
    {
        printf("Nothing to sort.");
        return;
    }
    while (counter)
    {
        curr = HEAD;
        counter = 0;
        while (curr && curr->next)
        {
            if (curr->age > curr->next->age)
            {
                switchElements(curr); 
                counter++;
                curr = curr->prev;  
            }
            curr = curr->next;
        }
    }
}

int getItemCount()
{
    struct OskarActor* curr = HEAD;
    int count = 0;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

void updatePopularity(int index)
{
    struct OskarActor* curr = HEAD;
    while (curr)
    {
        if (curr->index == index)
        {
            curr->popularity++;
            return;
        }
        curr = curr->next;
    }
}

void Run()
{
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        updatePopularity(rand()%89 + 1);
    }
}

void Save(char* fileName)
{
    FILE* f = fopen(fileName, "wb");
    if (!f)
    {
        printf("File error.");
        return;
    }
    struct OskarActor_Header header;
    struct OskarActor* curr = HEAD;
    header.Version = 1;
    header.ItemsCount = getItemCount();
    fwrite(&header, sizeof(struct OskarActor_Header), 1, f);
    while(curr)
    { 
        fwrite(curr, sizeof(struct OskarActor), 1, f);
        curr = curr->next;
    }
    fclose(f);
}

void Load(char* fileName)
{
    FILE* f = fopen(fileName, "rb");
    if (!f)
    {
        printf("File error");
        return;
    }
    struct OskarActor_Header header;
    struct OskarActor* element;
    fread(&header, sizeof(struct OskarActor_Header), 1, f);
    for (int i = 0; i < header.ItemsCount; i++)
    {
        element = (struct OskarActor*)malloc(sizeof(struct OskarActor));
        element->next = element->prev = NULL;
        fread(element, sizeof(struct OskarActor), 1, f);
        addFromFile(element);
    }
}

void mostPopular()
{
    struct OskarActor* curr = HEAD->next;
    struct OskarActor* mostPopular = HEAD;
    while (curr)
    {
        if (curr->popularity > mostPopular->popularity)
        {
            mostPopular = curr;
        }
        curr = curr->next;
    }
    printf("The most Actress is: %s", mostPopular->name);
}