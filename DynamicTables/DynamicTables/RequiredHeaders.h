/*
-
-
-
-
-
*/
typedef struct schemas{
	char *nameOfSchema;
	char ***s;
	int rows;
	int cols;
};

schemas * createSchema(char *str, schemas *tables,int *noOfTables);
schemas * importingToSchema(char *str, schemas *tables,int *noOfTables);
schemas * joiningSchemas(char *str, schemas *tables, int *noOfTables);
schemas * flushSchema(char *str, schemas *tables, int *noOfTables);
schemas * selectFromSchema(char *str, schemas *tables, int *noOfTables);

