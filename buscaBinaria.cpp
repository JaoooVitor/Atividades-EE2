#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool binarySearch(char *arr[], int size, char target[]) {
    int start = 0, end = size - 1;

    while (start <= end) {
        int middle = (start + end) / 2;
        int cmp = strncmp(target, arr[middle], strlen(target));

        if (cmp == 0) {
            return true;
        } else if (cmp < 0) {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }

    return false;
}

int compareStrings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    FILE *file = fopen("nomes.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *names[1000];
    char line[100];

    int numNames = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        strlwr(line);
        names[numNames] = strdup(line);
        numNames++;
    }

    fclose(file);

    qsort(names, numNames, sizeof(names[0]), compareStrings);

    printf("Digite a consulta de busca: ");
    char query[100];
    scanf("%s", query);

    strlwr(query);

    bool found = false;

    printf("Nomes encontrados que começam com '%s':\n", query);
    for (int i = 0; i < numNames; i++) {
        if (binarySearch(names, numNames, query)) {
            if (strncmp(names[i], query, strlen(query)) == 0) {
                printf("%s\n", names[i]);
                found = true;
            }
        }
    }

    if (!found) {
        printf("Nenhum nome encontrado com a consulta '%s'.\n", query);
    }

    for (int i = 0; i < numNames; i++) {
        free(names[i]);
    }

    return 0;
}
