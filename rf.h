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
void build_tree(Table* org_tbl,Table* tbl, Tree* t);

/*
 * Returns a newly allocated node;
 */
Node* n_make();

/*
 * Returns a char** where the index of the char* is the mapped value.
 * Calls classes_str and find_diff_classes_str in one function to
 * limit clutter.
 * Prints out the class mapping to the terminal
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
 * Does not have duplicates and frees list
 * Length is the length of the list. (number of elements)
 */
char** find_diff_classes_str(char** list, int length);

/*
 * Returns an array of doubles where each index is the mapped class.
 * Calls classes_double and find_diff_classes_double into one function.
 * limits clutter
 * Prints out the class mapping to the terminal
 */
double* class_mapping_double(Table* tbl);

/*
 * Returns an array of doubles in ascending order from the table tbl.
 */
double* classes_double(Table* tbl);

/*
 * Returns an array of all the different classes in ascending order.
 * Does not have duplicate and frees list
 * Length is the length of the list. (number of elements)
 */
double* find_diff_classes_double(double* list, int length);

/*
 * Used to compare strings for qsort.
 */
int double_compare(const void* a, const void* b);

/*
 * Returns an array of integers that is in table order and each string 
 * is replaced with its mapped class.
 */
unsigned int* classes_for_entropy_str(char** key, Table* tbl);

/*
 * Returns the integer class of the mapped value of a given string
 */
int find_val_str(char** list, int length, char* key);

/*
 * Prints the class mapping.
 */
void print_class_mapping_str(char** list, int length);

/*
 * Returns the number of different strings in ordered_list
 */
int number_of_class_str(char** ordered_list, int length);

/*
 * Returns an array of integers that is in table order and each double
 * is replaced with its mapped class
 */
unsigned int* classes_for_entropy_double(double* key, Table* tbl);

/*
 * Returns the integer class of the mapped value of a given double
 */
int find_val_double(double* list, int length, double key);

/*
 * Prints the class mapping.
 */
void print_class_mapping_double(double* list, int length);

/*
 * Returns the number of different doubles in ordered_list
 */
int number_of_class_double(double* ordered_list, int length);

/*
 * Prints put the class mapping
 */
void class_mapping_double_print(Table* tbl);

/*
 * Prints put the class mapping
 */
void class_mapping_string_print(Table* tbl);

/*
 * Returns an array of integers of columns to check amounting to 2/3's of cols
 */
int* two_thirds_columns(int cols);

/*
 * Checks that check is not in the array loc.
 * Returns 1 if no match is found.
 */
int checker(int* loc, int length, int check);

/*
 * Moves the file stream past the column names so you can get to the raw data
 */
void skip_first_row();

int find_value(Table* tbl, int row);

char find_class_type(Table* tbl);

int majority_class(Table* tbl);

int find_most(int* loc, int length);
