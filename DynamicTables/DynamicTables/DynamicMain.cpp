#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "RequiredHeaders.h";


int main(){
	char command[500], line[100], token[100], filename[100];
	int noOfTables = 0;
	struct schemas *tables=NULL;
	while (1){
		printf("MRND_DB>>>");
		gets(command);
		int i = 0, j = 0;
		for (i = 0; !(command[i] == ' ' || command[i] == '\0'); i++)
			token[i] = command[i];
		token[i] = '\0';
		i++;
		for (i = i; command[i] == ' '; i++);
		
		if (strcmp(token, "create") == 0){
			tables = createSchema(&command[i], tables, &noOfTables);

			/* 
			 Ex syntax:  create schema s1 RollNo:int , Name:string , M1:int , M2:int , M3:int , M4:int
			  schema command will take us to create a schema with name s1 with specified attribute names and its corresponding datatypes.

			*/

		}
		else if (strcmp(token, "import") == 0){
			tables = importingToSchema(&command[i], tables, &noOfTables);
			/*
			Ex syntax:  import filename shemaname
			*/
		}
		else if (strcmp(token, "join") == 0){
			tables = joiningSchemas(&command[i], tables, &noOfTables);

			/*
			Ex syntax:  join shemaname1 , schemaname2 as shemaname3
			*/
		}
		else if (strcmp(token, "flush") == 0){
			tables = flushSchema(&command[i], tables, &noOfTables);

			/*
			Ex syntax:  flush filename source_schema_name

			*/
		}
		else if (strcmp(token, "select") == 0){
			tables = selectFromSchema(&command[i], tables, &noOfTables);
			/*
			Ex syntax:  
			            select * from schemaname where Name matches Raju
			            select RollNo , Name from schemaname where M1>90
						select *from schemaname
			*/
		}
		else if (strcmp(token, "exit") == 0){
			printf("Exiting.........");
			/*
			  exit is a single token it terminate and exit the terminal
			*/
			exit(0);
		}
		else{
			printf("Invalid Input!!");
		}
		printf("\n");
		fflush(stdin);
	}
}