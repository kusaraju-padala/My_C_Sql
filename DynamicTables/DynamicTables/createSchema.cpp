#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct schemas{
	char *nameOfSchema;
	char ***s;
	int rows;
	int cols;
};
schemas * createSchema(char *str, schemas *tables, int *noOfTables){
	char token[30];
	int i = 0, j = 0,k=0;
	for (i = 0; str[i] != ' '; i++);
	for (i = i; str[i] == ' '; i++);
	j = i;
	for (i = i; !(str[i] == ' ' || str[i] == '\0'); i++, k++){
		token[k] = str[i];
	}
	token[k] = '\0';
	for (int k = 0; k < *noOfTables; k++){
		if (strcmp(token, tables[k].nameOfSchema) == 0){
			printf("Already schema existed\n");
			return tables;
		}
	}
	if (*noOfTables == 0){
		tables = (schemas*)malloc(sizeof(schemas));
		tables[0].nameOfSchema = (char*)malloc((i-j)*sizeof(char));
		strcpy(tables[0].nameOfSchema, token);
		tables[0].s = NULL;
		tables[0].rows = 0;
		tables[0].cols = 0;
		*noOfTables = *noOfTables + 1;
		printf("Shema Created!!\n");
		return tables;
	}
	else if (*noOfTables > 0){
		tables = (schemas*)realloc(tables, (*noOfTables + 1)*sizeof(schemas));
		tables[*noOfTables].nameOfSchema = (char*)malloc((i - j)*sizeof(char));
		strcpy(tables[*noOfTables].nameOfSchema, token);
		tables[*noOfTables].s = NULL;
		tables[*noOfTables].rows = 0;
		tables[*noOfTables].cols = 0;
		*noOfTables = *noOfTables + 1;
		printf("Schema Created!!\n");
		return tables;
	}
	
	
	return NULL;
}