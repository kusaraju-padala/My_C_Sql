/*
Here we should take two schemas and we can assume that the first columns of the schemas are the primary keys and merge them accordingly 
and also we can assume that no other columns will match.
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
schemas * importingToSchema(char *str, schemas *tables, int *noOfTables);
schemas * joiningSchemas(char *str, schemas *tables, int *noOfTables){
	int findex = 0, sindex = 0,i=0,j=0,matches[100],matchcount=0,sizeoft;
	char f[20], s[20],t[20];
	for (i = 0; !(str[i] == ' ' || str[i] == ','); i++)
		f[i] = str[i];
	f[i] = '\0';
	for (i = i; (str[i] == ' ' || str[i] == ','); i++);
	for (i = i; !(str[i] == ' ' || str[i] == ','); i++,j++)
		s[j] = str[i];
	s[j] = '\0';
	for (i = i; str[i] == ' '; i++);
	for (i = i; str[i] != ' '; i++);
	for (i = i; str[i] == ' '; i++);
	j = 0;
	for (i = i; !(str[i] == ' ' || str[i] == '\0'); i++, j++)
		t[j] = str[i];
	t[j] = '\0';
	if (strlen(t) < 1){
		printf("Target Schema name Required......\n");
		return tables;
	}
	
	for (i = 0; i < *noOfTables; i++){
		if (strcmp(tables[i].nameOfSchema, f) == 0){
			findex = i;
			break;
		}
	}
	if (i == *noOfTables){
		printf("Schema invalid...");
		return tables;
	}
	for (i = 0; i < *noOfTables; i++){
		if (strcmp(tables[i].nameOfSchema, s) == 0){
			sindex = i;
			break;
		}
	}
	if (i == *noOfTables){
		printf("Schema invalid...");
		return tables;
	}
	if (strcmp(tables[findex].s[0][0], tables[sindex].s[0][0]) == 0){
		
		FILE *f1;
		f1 = fopen("buffer.txt", "w");
		if (f1 == NULL){
			printf("Error in opening file.....\n");
			return tables;
		}
		for (i = 0; i < tables[findex].cols; i++){
			fprintf(f1, "%s,", tables[findex].s[0][i]);
		}
		for (i = 1; i < tables[sindex].cols; i++){
			fprintf(f1, "%s,", tables[sindex].s[0][i]);
		}
		fprintf(f1, "%s", "\n");
		
		int cols = tables[findex].cols + tables[sindex].cols;
		int lines = 0, *overcols = (int*)malloc(tables[sindex].rows*sizeof(int));
		for (i = 1; i < tables[findex].rows; i++){
			for (j = 1; j < tables[sindex].rows; j++){
				if (strcmp(tables[findex].s[i][0], tables[sindex].s[j][0]) == 0){
					for (int k = 0; k < tables[findex].cols; k++){
						fprintf(f1, "%s,", tables[findex].s[i][k]);
					}
					for (int k = 1; k < tables[sindex].cols; k++){
						fprintf(f1, "%s,", tables[sindex].s[j][k]);
					}
					fprintf(f1, "%s", "\n");
					overcols[j] = 1;
					break;
					
				}
			}
			if (j == tables[sindex].rows){
				for (int k = 0; k < tables[findex].cols; k++){
					fprintf(f1, "%s,", tables[findex].s[i][k]);
				}
				for (int k = 1; k < tables[sindex].cols; k++){
					fprintf(f1, "%s,", NULL);
				}
				fprintf(f1, "%s", "\n");
			}
			
		}
		int m = 0;
		for (j = 1; j < tables[sindex].rows; j++){
			if (overcols[j]!=1){
				fprintf(f1, "%s,", tables[sindex].s[j][0]);
				for (int z = 0; z < 5; z++){
					fprintf(f1, "%s,", NULL);
				}
				for (int k = 1; k < tables[sindex].cols; k++){
					fprintf(f1, "%s,", tables[sindex].s[j][k]);
				}
				fprintf(f1, "%s", "\n");
			}
		}
		fclose(f1);
		char filename[100] = "buffer.txt  ";
		strcat(filename, t);
		tables = importingToSchema(filename, tables, noOfTables);
		
		
	}
	else{
		printf("Both primary keys did not match!!\n");
	}
	
	

	return tables;
}