/*
Given file will be imported to the given schema. 
  -It will create new schema if this is the first time it is encountering the schema
  -Else it will append to the already created schema.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct schemas{
	char *nameOfSchema;
	char ***s;
	int rows;
	int cols;
};
schemas * createSchema(char *str, schemas *tables, int *noOfTables);
schemas * importingToSchema(char *str, schemas *tables, int *noOfTables){
	char line[100], token[60];
	FILE *f1;
	int lines = 0,i = 0,cols = 0, j = 0, k = 0;

	for (i = i; !(str[i] == ' ' || str[i] == '\0'); i++){
		token[i] = str[i];
	}
	token[i] = '\0';
	for (i = i; str[i] == ' '; i++);
	f1 = fopen(token, "r");
	if (f1 == NULL){
		printf("Error in opening file.....\n");
		return tables;
	}
	j = 0;
	for (i = i; !(str[i] == ' '||str[i]=='\0'); i++,j++){
		token[j] = str[i];
	}
	token[j] = '\0';
	if (strlen(token) < 1){
		printf("Schema name Required......\n");
		return tables;
	}

	while (fgets(line, 100, f1)){
		lines++;
	}
	fseek(f1, 0, SEEK_SET);
	fgets(line, 100, f1);	
	for (i = 0; line[i] != '\n'; i++){
		if (line[i] == ',')
			cols++;
	}
	cols++;	
	for (j = 0; j < *noOfTables; j++){
		if (strcmp(tables[j].nameOfSchema, token) == 0)
			break;
	}
	if (j == *noOfTables){
		tables = createSchema(str, tables, noOfTables);	
	}
	int z = j;
	if (tables[z].s == NULL){
		tables[z].s = (char***)malloc(lines*sizeof(char***));
		tables[z].rows = lines;
		tables[z].cols = cols;
		for (i = 0; i < lines; i++){
			tables[z].s[i] = (char**)malloc(cols*sizeof(char**));
		}
		fseek(f1, 0, SEEK_SET);
		i = 0; k = 0; j = 0;
		while (fgets(line, 100, f1)){
			for (int l = 0; l < cols; l++){
				int n = 0;
				for (i = i; !(line[i] == '\0' || line[i] == '\n' || line[i] == ','); i++){
					token[n] = line[i];
					n++;
				}
				token[n] = '\0';
				tables[z].s[k][l] = (char*)malloc((i - j)*sizeof(char*));
				strcpy(tables[z].s[k][l], token);
				j = i;
				i++;
			}
			k++; i = 0; j = 0;

		}
		printf("Import Success!!\n");
		fclose(f1);
		return tables;
	}
	else{
		tables[z].s = (char***)realloc(tables[z].s, (tables[z].rows+lines-1)*sizeof(char***));
		for (i = tables[z].rows; i < lines + tables[z].rows - 1; i++){
			tables[z].s[i] = (char**)malloc(cols*sizeof(char**));
		}
		fseek(f1, 0, SEEK_SET);
		i = 0; k = tables[z].rows; j = 0;
		fgets(line, 100, f1);
		while (fgets(line, 100, f1)){
			for (int l = 0; l < cols; l++){
				int n = 0;
				for (i = i; !(line[i] == '\0' || line[i] == '\n' || line[i] == ','); i++){
					token[n] = line[i];
					n++;
				}
				token[n] = '\0';
				tables[z].s[k][l] = (char*)malloc((i - j)*sizeof(char*));
				strcpy(tables[z].s[k][l], token);
				j = i;
				i++;
			}
			k++; i = 0; j = 0;

		}
		tables[z].rows = lines + tables[z].rows - 1;
		printf("Import Success!!\n");
		fclose(f1);
		return tables;
	}
	return NULL;
}