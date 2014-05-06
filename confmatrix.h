#ifndef _CONF_HEADER_
#define _CONF_HEADER_

/*
 * confmatrix API  
 */


/*
 * Represents the confusion matrix. To be defined by the student.
 */
typedef struct confmatrix ConfMatrix;



/* cm_make:
 *   creates and returns a ConfMatrix, where classes is the number of
 *   classes the confusion matrix will be considering.
 */
ConfMatrix* cm_make(int classes);

/* 
 * cm_validate:
 *   This function takes a table [tbl], a "trained" decision tree [tree],
 *   and attempts to determine how well the tree predicts classes.
 *   It will take each row of the table, and compare the actual class
 *   in the table to the predicted class it finds from the tree.
 *   Each prediction will be recorded in the confusion matrix [cm]. 
 */
void cm_validate(ConfMatrix *cm, Table *tbl, Tree **tree, int trees);

/* 
 * cm_print:
 *   prints ConfMatrix cm with the format:
 *
 *   Confusion matrix: total=X, errors=Y
 *    | 0 1
 *   0|a,b,
 *   1|c,d,
 *
 *   where the X is the number of predictions, Y is the number
 *   of wrong predictions, and a,b,c,d,etc. are the specific numbers
 *   for each class that was predicted. Note that there is a trailing
 *   new line after the last row of text printed.
 */
void cm_print(ConfMatrix* cm);

/*
 * cm_free():
 *   You know the drill!
 */
void cm_free(ConfMatrix* cm);

/* 
 * tbl_classes_count:
 *   returns the number of classes in a table. You will need
 *   this to know how large to make the confusion matrix.
 */
int tbl_classes_count(Table *);

int find_most_voted(int* p, int length);

int find_expected_string_vote(Row* row, Tree** tree, int trees);

int find_expected_double_vote(Row* row, Tree** tree, int trees);

void count_errors(int classes, ConfMatrix* cm);

#endif
