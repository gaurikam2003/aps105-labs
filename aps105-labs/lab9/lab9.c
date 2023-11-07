#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* DO NOT EDIT THE LINES BELOW */
#define STRING_MAX 1024

typedef struct node {
  char *name;
  int lines;
  int runtime;
  int memory_usage;
  struct node *next;
} Node;

typedef struct linked_list {
  Node *head;
} LinkedList;

void readInputString(char *, int);
void readInputNumber(int *);
void readInputChar(char *);
LinkedList *newList();
char getCommand();
void handleInsert(LinkedList *);
void handleDelete(LinkedList *);
void handleSearch(LinkedList *);
void handlePrint(LinkedList *);
void handleQuit(LinkedList *);

int main() {
  LinkedList *list = newList();
  char command = '\0';
  printf("Experimental database entry\n");
  while (command != 'Q') {
    command = getCommand();
    switch (command) {
      case 'I':
        handleInsert(list);
        break;
      case 'D':
        handleDelete(list);
        break;
      case 'S':
        handleSearch(list);
        break;
      case 'P':
        handlePrint(list);
        break;
      case 'Q':
        handleQuit(list);
        break;
    }
  }
  free(list);
  return 0;
}

/* DO NOT EDIT THE LINES ABOVE */
void handleInsert(LinkedList *list) {
  // place your code to handle the insert command here
  int numChar;
  int numLines;
  int runTime;
  int memUsage;

  printf("\nNumber of characters in file name: ");
  readInputNumber(&numChar);
  // new_node->file_name = (char*) malloc(strlen(file_name) + 1);

  printf("File name: ");
  char *fileName = (char *)malloc(sizeof(char) * ((size_t)numChar + 1));
  readInputString(fileName, numChar + 1);

  printf("Number of lines in CSV file: ");
  fflush(stdin);
  readInputNumber(&numLines);

  printf("Experiment runtime (ms): ");
  readInputNumber(&runTime);

  printf("Experiment memory usage (B): ");
  readInputNumber(&memUsage);

  Node *file = malloc(sizeof(Node));
  file->name = fileName;
  file->lines = numLines;
  file->runtime = runTime;
  file->memory_usage = memUsage;
  file->next = NULL;

  if (list->head == NULL || strcmp(file->name, list->head->name) > 0) {
    file->next = list->head;
    list->head = file;
  } else if (strcmp(file->name, list->head->name) == 0) {
    printf("\nAn entry with that file name already exists.\n");
    free(file->name);
    free(file);
  } else {
    Node *currentNode = list->head;
    while (currentNode->next != NULL &&
           strcmp(file->name, currentNode->next->name) < 0) {
      currentNode = currentNode->next;
    }
    if (currentNode->next == NULL ||
        strcmp(file->name, currentNode->next->name) > 0) {
      file->next = currentNode->next;
      currentNode->next = file;
    } else {
      printf("An entry with that file name already exists.\n");
      free(file->name);
      free(file);
    }
  }
}

void handleDelete(LinkedList *list) {
  // place your code to handle the delete command here
  char fileName[STRING_MAX];

  printf("\nEnter file name to delete: ");
  readInputString(fileName, STRING_MAX);

  Node *current = list->head;
  Node *previous = NULL;

  while (current != NULL && strcmp(current->name, fileName) != 0) {
    previous = current;
    current = current->next;
  }
  if (current == NULL) {
    printf("An entry for file <%s> does not exist.\n", fileName);  // not right
  } else {
    if (previous == NULL) {
      list->head = current->next;
    } else {
      previous->next = current->next;
    }
    printf("Deleting entry for CSV file <%s>\n", fileName);
    free(current->name);
    free(current);
    // list->size--;
  }
}

void handleSearch(LinkedList *list) {
  // place your code to handle the search command here
  char fileName[STRING_MAX];
  printf("\nEnter file name to find: ");
  readInputString(fileName, STRING_MAX);

  Node *current = list->head;
  while (current != NULL && strcmp(fileName, current->name) != 0) {
    current = current->next;
  }
  if (current == NULL) {
    printf("An entry for file <%s> does not exist.\n", fileName);
  } else {
    double throughput = 1000 * (double)current->lines / current->runtime;
    printf("File <%s>\n", current->name);  // not right
    printf("Lines: %d\n", current->lines);
    printf("Runtime (ms): %d\n", current->runtime);
    printf("Memory usage (B): %d\n", current->memory_usage);
    printf("Throughput: %.2lf\n", throughput);
  }
}

void handlePrint(LinkedList *list) {
  // place your code to handle the print command here
  printf("\nData entries:\n");
  Node *current = list->head;
  if (current == NULL) {
    printf("There are no data entries.\n");
  } else {
    while (current != NULL) {
      double throughput = 1000 * (double)current->lines / current->runtime;
      printf("\nFile <%s>\n", current->name);
      printf("Lines: %d\n", current->lines);
      printf("Runtime (ms): %d\n", current->runtime);
      printf("Memory usage (B): %d\n", current->memory_usage);
      printf("Throughput: %.2lf\n", throughput);  // not right
      current = current->next;
    }
  }
}

void handleQuit(LinkedList *list) {
  // place your code to handle the quit command here
  Node *current = list->head;
  printf("Deleting entry for CSV file <%s>\n", current->name);
  while (current != NULL) {
    Node *temp = current->next;
    free(current);
    current = temp;
  }
  list->head = NULL;
  exit(0);
}

/* DO NOT EDIT THE LINES BELOW */
void readInputString(char *str, int length) {
  int i = 0;
  char c;
  while (i < length && (c = getchar()) != '\n') {
    str[i++] = c;
  }
  str[i] = '\0';
}

void readInputNumber(int *number) {
  char buf[STRING_MAX];
  readInputString(buf, STRING_MAX);
  *number = (int)strtol(buf, (char **)NULL, 10);
}

void readInputChar(char *character) {
  char buf[2];
  readInputString(buf, 3);
  *character = buf[0];
}

LinkedList *newList() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  return list;
}

char getCommand() {
  char command;
  printf("\nSupported commands are:\n");
  printf(" I - Insert\n");
  printf(" D - Delete\n");
  printf(" S - Search\n");
  printf(" P - Print\n");
  printf(" Q - Quit\n");
  printf("\nPlease select a command: ");
  readInputChar(&command);
  while (command != 'I' && command != 'D' && command != 'S' && command != 'P' &&
         command != 'Q') {
    printf("Invalid command <%c>, please select a command: ", command);
    readInputChar(&command);
  }
  return command;
}
/* DO NOT EDIT THE LINES ABOVE */