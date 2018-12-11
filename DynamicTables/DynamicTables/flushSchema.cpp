/*
The specified schema will be copied to the filename given.
*/
#include<stdio.h>
#include<string.h>
typedef struct schemas{
	char *nameOfSchema;
	char ***s;
	int rows;
	int cols;
};
schemas * flushSchema(char *str, schemas *tables, int *noOfTables){
	char line[100], token[30];
	FILE *f1;
	int lines = 0, i = 0, cols = 0, j = 0, k = 0, z = -1;
	for (i = i; str[i] != ' '; i++){
		token[i] = str[i];
	}
	token[i] = '\0';
	for (i = i; str[i] == ' '; i++);
	f1 = fopen(token, "w");
	if (f1 == NULL){
		printf("Error in opening file.....\n");
		return tables;
	}
	j = 0;
	for (i = i; !(str[i] == ' ' || str[i] == '\0'); i++, j++){
		token[j] = str[i];
	}
	token[j] = '\0';

	for (k = 0; k < *noOfTables; k++){
		if (strcmp(token, tables[k].nameOfSchema) == 0){
			z = k;
			break;
		}
	}
	if (z != -1){
		for (i = 0; i < tables[z].rows; i++){
			for (j = 0; j < tables[z].cols-1; j++){
				fprintf(f1, "%s", tables[z].s[i][j]);
				fprintf(f1, "%s", ",");
			}
			fprintf(f1, "%s", tables[z].s[i][j]);
			fprintf(f1, "%s", "\n");
		}
		fclose(f1);
		printf("Flush Success!!\n");
		return tables;
	}
	else{
		printf("Invalid schema!!!\n");
		return tables;
	}

	return NULL;
}