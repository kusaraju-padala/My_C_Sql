/*
- This section processes all the select statements that should be applied on the DB for specified schemas
- It will tokenize the whole command step by step and process them heirarchically
-Input:(command ,tables pointer, nooftables)
 output: printed to console according to the specifications

 we can give as many spaces as we want in between the tokens it will ignore the white spaces
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

void printrow(schemas *tables, int tableid, int colNo, int *atts, int attsflag){
	if (attsflag == -1){
		for (int i = 0; i < tables[tableid].cols - 1; i++){
			printf("%20s", tables[tableid].s[colNo][i]);
		}
		printf("%20s\n", tables[tableid].s[colNo][tables[tableid].cols - 1]);
	}
	else if (attsflag == 1){
		for (int i = 0; i < tables[tableid].cols ; i++){
			if (atts[i]==1)
				printf("%20s", tables[tableid].s[colNo][i]);
		}
		printf("\n");
	}
	
}
void printstarequal(char *str, schemas *tables, int *noOfTables, int tableid, int colNo, int *atts, int attsflag){
	int i = 0, j = 0;
	char token[30];
	for (i = 0; !(str[i] == ' ' || str[i] == '\0' || str[i] == '\n'); i++)
		token[i] = str[i];
	token[i] = '\0';
	for (i = 1; i <tables[tableid].rows; i++){
		if (strcmp(token, tables[tableid].s[i][colNo]) == 0){
			printrow(tables, tableid, i,atts,attsflag);
		}
	}
	
	
}
void printstargreater(char *str, schemas *tables, int *noOfTables, int tableid, int colNo, int *atts, int attsflag){
	int i = 0, j = 0;
	char token[30];
	for (i = 0; !(str[i] == ' ' || str[i] == '\0' || str[i] == '\n'); i++)
		token[i] = str[i];
	token[i] = '\0';
	for (i = 1; i <tables[tableid].rows; i++){
		if (strlen(token)<strlen(tables[tableid].s[i][colNo])){
			printrow(tables, tableid, i, atts, attsflag);
		}
		else if (strlen(token) == strlen(tables[tableid].s[i][colNo])){
			if (strcmp(token, tables[tableid].s[i][colNo]) < 0){
				printrow(tables, tableid, i, atts, attsflag);
			}
		}
		
	}
}
void printstarlesser(char *str, schemas *tables, int *noOfTables, int tableid, int colNo, int *atts, int attsflag){
	int i = 0, j = 0;
	char token[30];
	for (i = 0; !(str[i] == ' ' || str[i] == '\0' || str[i] == '\n'); i++)
		token[i] = str[i];
	token[i] = '\0';
	for (i = 1; i <tables[tableid].rows; i++){
		if (strlen(token)>strlen(tables[tableid].s[i][colNo])){
			printrow(tables, tableid, i, atts, attsflag);
		}
		else if (strlen(token) == strlen(tables[tableid].s[i][colNo])){
			if (strcmp(token, tables[tableid].s[i][colNo]) > 0){
				printrow(tables, tableid, i, atts, attsflag);
			}
		}

	}
}

void printstarcontains(char *str, schemas *tables, int *noOfTables, int tableid, int colNo, int *atts, int attsflag){
	int i = 0, j = 0;
	char token[30];
	for (i = 0; !(str[i] == ' ' || str[i] == '\0' || str[i] == '\n'); i++)
		token[i] = str[i];
	token[i] = '\0';
	for (i = 1; i <tables[tableid].rows; i++){
		if (strstr(tables[tableid].s[i][colNo],token)){
			
			printrow(tables, tableid, i, atts, attsflag);
		}
	}
}

void printstar(char *str, schemas *tables, int *noOfTables, int tableid,int *atts,int attsflag){
	int i = 0, j = 0,k = 0,colNo=-1;
	char token[30],attr[30];
	if (str[i] == 'w'&&str[i + 1] == 'h'&&str[i + 2] == 'e'&&str[i + 3] == 'r'&&str[i + 4] == 'e'){
		for (i = i + 5; str[i] == ' '; i++);
		j = 0;
		for (i = i; !(str[i] == ' ' || str[i] == '<' || str[i] == '>' || str[i] == '='); i++, j++)
			token[j] = str[i];
		token[j] = '\0';
		strcpy(attr, token);
		for (k = 0; k < tables[tableid].cols; k++){
			if (strcmp(tables[tableid].s[0][k], attr) == 0){
				colNo = k;
				break;
			}
		}
		if (k == tables[tableid].cols){
			printf("Invalid attribute name!!\n");
			return;
		}
		for (i = i; str[i] == ' '; i++);
		j = 0;
		if (str[i] == '=' || str[i] == '>' || str[i] == '<' ){
			token[0] = str[i];
			token[1] = '\0';
			i++;
		}
		else{
			for (i = i; !(str[i] == ' '); i++, j++)
				token[j] = str[i];
			token[j] = '\0';
		}
		
		for (i = i; str[i] == ' '; i++);
		if (strcmp(token, "=") == 0){
			printstarequal(&str[i], tables, noOfTables, tableid, colNo, atts, attsflag);
		}
		else if (strcmp(token, ">") == 0){
			printstargreater(&str[i], tables, noOfTables, tableid, colNo, atts, attsflag);
		}
		else if (strcmp(token, "<") == 0){
			printstarlesser(&str[i], tables, noOfTables, tableid, colNo, atts, attsflag);
		}
		else if (strcmp(token, "matches") == 0){
			printstarequal(&str[i], tables, noOfTables, tableid, colNo, atts, attsflag);
		}
		else if (strcmp(token, "contains") == 0){
			printstarcontains(&str[i], tables, noOfTables, tableid, colNo, atts, attsflag);
		}
	}
	else{
		printf("Invalid command!!!\n");
		return;
	}
}
schemas * selectFromSchema(char *str, schemas *tables, int *noOfTables){
	int allflag = 0, i = 0, j = 0,tableid=-1;
	char token[30];

	if (str[0] == '*'){
		allflag = 1;
		for (i = 1; str[i] == ' '; i++);
		if (str[i] == 'f'&&str[i + 1] == 'r'&&str[i + 2] == 'o'&&str[i + 3] == 'm'){
			for (i = i + 4; str[i] == ' '; i++);
			j = 0;
			for (i = i; !(str[i] == ' ' || str[i] == '\0');i++,j++){
				token[j] = str[i];
			}
			token[j] = '\0';
			int k = 0;
			for ( k = 0; k < *noOfTables; k++){
				if (strcmp(token, tables[k].nameOfSchema) == 0){
					tableid = k;
					break;
				}
			}
			if (k == *noOfTables){
				printf("Invalid schema!!\n");
				return tables;
			}
			for (i = i; str[i] == ' '; i++);
			if (str[i] == 'w'){
				printstar(&str[i], tables, noOfTables, tableid,NULL,-1);
				return tables;
			}
			else{
				for (i = 0; i < tables[tableid].rows; i++){
					for (j = 0; j < tables[tableid].cols-1; j++){
						printf("%20s", tables[tableid].s[i][j]);
					}
					printf("%20s\n", tables[tableid].s[i][j]);
				}
				return tables;
			}
		}
		else{
			printf("Invalid Select Statement!!!\n");
			return tables;
		}
	}
	else{
		int findex = -1;
		
		while (findex==-1){
			for (i = 0; str[i] != 'f'; i++);
			if (str[i] == 'f'&&str[i + 1] == 'r'&&str[i + 2] == 'o'&&str[i + 3] == 'm')
				findex = i;
		}
		for (i = i + 4; str[i] == ' '; i++);
		j = 0;
		for (i = i; !(str[i] == ' ' || str[i] == '\0'); i++, j++){
			token[j] = str[i];
		}
		token[j] = '\0';
		int k = 0;
		for (k = 0; k < *noOfTables; k++){
			if (strcmp(token, tables[k].nameOfSchema) == 0){
				tableid = k;
				break;
			}
		}
		if (k == *noOfTables){
			printf("Invalid schema!!\n");
			return tables;
		}
		int cols = tables[tableid].cols;
		int *atts = (int*)malloc(tables[tableid].cols*sizeof(int));
		for (i = 0; i < cols; i++)
			atts[i] = -1;
		i = 0;
		while (i != findex){
			j = 0;
			for (i = i; !(str[i] == ' ' || str[i] == ','); i++,j++)
				token[j] = str[i];
			token[j] = '\0';
			for (k = 0; k < cols; k++){
				if (strcmp(token, tables[tableid].s[0][k]) == 0){
					atts[k] = 1;
					break;
				}		
			}
			for (i = i; str[i] == ' ' || str[i] == ','; i++);
		}
		i = i + 4;
		for (i = i; str[i] == ' '; i++);
		for (i = i; str[i] != ' '; i++);
		for (i = i; str[i] == ' '; i++);
		if (str[i] == 'w'){
			printstar(&str[i], tables, noOfTables, tableid, atts, 1);
		}
		else if (str[i] == '\0' || str[i] == '\n'){
			for (i = 0; i < tables[tableid].rows; i++){
				for (j = 0; j < tables[tableid].cols; j++){
					if (atts[j]==1)
					   printf("%s,", tables[tableid].s[i][j]);
				}
				printf("\n");
			}
		}
		

		

	}
		

	return tables;
}