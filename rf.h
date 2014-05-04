/*
 * Returns a resampled table, in which the rows from src are randomly copied the
 * new table. It should have the same number of rows as src. 
 * It is okay for rows to be copied more than once into the new table.
 */
Table* resample(Table* src);

/*
 * Returns a char** of column names from the first row of the open file.
 * To be run before buffering.
 */
char** first_row();

/*
 * Creates a table made from the information in the current open file.
 * Does not buffer the first row. See above.
 */
void buffering(Table* tbl);

/*
 * Builds a tree from a resampled version of tbl and places the root in tree t.
 */
void build_tree(Table* tbl, Tree* t);

/*
 * Returns a newly allocated node;
 */
Node* n_make();

/*
 * Returns a char** where the index of the char* is the mapped value.
 * Calls classes_str and find_diff_classes_str in one function to
 * limit clutter.
 */
char** class_mapping_string(Table* tbl);

/*
 * Returns an array of strings in lexigraphical order from the table tbl.
 */
char** classes_str(Table* tbl);

/*
 * Used to compare strings for qsort.
 */
int str_compare(const void* a, const void* b);

/*
 * Returns an array of all the different classes in lexigraphical order.
 * Does not have duplicates and fress list
 * Length is the length of the list. (number of elements)
 */
char** find_diff_classes_str(char** list, int length);

double* class_mapping_double(Table* tbl);

double* classes_double(Table* tbl);

double* find_diff_classes_double(double* list, int length);

int double_compare(const void* a, const void* b);


