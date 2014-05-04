#include "defs_itf.h"

#define ERROR .001

char** colnames;
char buffer[9999];
int* err;

int main(int argc, char *argv[]){
    ca_init(argc, argv);
    char* train;
    char* valid;
    int trees = 0;
    char type;
    srand(13);
    
    //Get -train and -validate files and number of trees
    if(ca_defined("train"))
        train = ca_str_value("train");
    else if(ca_defined("t"))
        train = ca_str_value("t");
    if(ca_defined("validate"))
        valid = ca_str_value("validate");
    else if(ca_defined("v"))
        valid = ca_str_value("v");
    if(ca_defined("trees"))
        trees = ca_int_value("trees");
    
    //open file
    rd_open(train);
    
    //get first row and set to global variable colnames
    colnames = first_row(); //when freeing colnames, also free colnames[i]
    
    //get the rest of the table
    Table* tbl = tbl_make();
    buffering(tbl);
    
    //set type of class to 
    
    double* list = class_mapping_double(tbl);
    
    
	
    
/*	for(int i = 0; i < tbl_column_count(tbl); i++){
		free(colnames[i]);
	}
tbl_free(tbl);
rd_close(train);
free(colnames); */
	
    //create multiple random trees!!!!
 /*   Tree* ret = t_make();
    build_tree(tbl, ret);
    int space = 0;
    t_print(ret, space, dt_print);*/
    //double* test = class_mapping_double(tbl);
    //for(int i = 0; i < 13; i++){
    //printf("%f\n", test[i]);
   // }
    
}


Table* resample(Table* src){
    Table* ret = tbl_make();
    int rows = tbl_row_count(src);
    Row* rt;
    
    for(int i = 0; i < rows; i++){
        rt = tbl_copy_row(tbl_row_at(src, rand() % rows));
        tbl_add_row(ret, rt);
    }
    tbl_done_building(ret);
    return ret;
}

char** first_row(){
    int c, i = 0, from = 0, to = 0;
    char** columns;
   
    while((c = rd_getchar()) != '\n'){
        buffer[i] = c;
        i++;
    }
    buffer[i+1] = '\0';
    columns = calloc(rd_num_fields(buffer, i), sizeof(char*));
   
    for(int k = 0;  k < rd_num_fields(buffer, i); k++){
        to = rd_field_length(buffer, from+1, i);
        columns[k] = rd_parse_string(buffer, from, to);
        from = rd_field_length(buffer, from+1, i);

    }
    return columns;
}

void buffering(Table *tbl){
    int i = 0, c, fields = 0, prev = 0, curr = 0, count = 0;
    char* hold = '\0';
    double dub;
	char* free_me;
    for(int j = 0; j < 1500; j++){
        buffer[j] = '\0';
    }
    
    err = calloc(1, sizeof(int));
    if(ca_defined("train") || ca_defined("t") || ca_defined("v") || ca_defined("validate")){
        
        while((c = rd_getchar()) != EOF){
            i=0;
            while(c != '\n'){
                if(c == EOF) break;
                buffer[i] = c;
                c = rd_getchar();
                i++;
            }
            buffer[i] = '\0';
            curr = 0;
            count = 0;
            prev = 0;
            fields = rd_num_fields(buffer, i+1);
            tbl_start_row(tbl, fields);
            curr = rd_field_length(buffer, curr, i+1);
            rd_parse_number(buffer, 0, curr-1, err);
            
            if(*err == 1) {
		free_me = rd_parse_string(buffer, 0, curr);
                tbl_add_string_to_row(tbl, free_me);
		free(free_me);

            }
            else{
                tbl_add_double_to_row(tbl, rd_parse_number(buffer, 0, curr, err));
            }
            count++;
            prev = curr+1;
            
            while(count < fields){
                
                curr = rd_field_length(buffer, prev, i);
                rd_parse_number(buffer, prev, (curr-1), err);
                
                if(*err == 1) {
			free_me = rd_parse_string(buffer, prev, curr);
                    tbl_add_string_to_row(tbl, free_me);
			free(free_me);
                }
                else{
                    tbl_add_double_to_row(tbl, rd_parse_number(buffer, prev, curr, err));
                }
                prev = curr+1;
                count++;
            }

            for(int j = 0; j < 1500; j++){
                buffer[j] = '\0';
            }
            i = 0;
        }
    }
    tbl_done_building(tbl);
	free(err);
}

void build_tree(Table* tbl, Tree* tree){
    if(tbl == NULL) return;
    Node* n = n_make();
    Column* c;
    int count = 0;
    int cols = tbl_column_count(tbl)-1, index = 0;
    
    //TODO: add randomness. like 2/3 columns
    if(tbl_row_count(tbl) <= 1){
        n->leaf = 1;
        n->class = (unsigned int)tbl_double_at(tbl_row_at(tbl, 0), cols-1);
        t_set_data(tree, n);
        tree->left = NULL;
        tree->right = NULL;
        return;
    }
    
    
    Table* left;
    Table* right;
    
    double prev = 0xFFFFFFFFFFFFFFFF, entropy = 0, split_d = 0;
    char* split_s;
    char type;
    
    
    for(int i = 0; i < cols-1; i++){
        
        c = get_column(tbl, i);
        
        if(tbl_row_type_at(tbl_row_at(tbl, 0), i) == 'S'){
            if(has_single_value(c)) {
                count++;
                free_column(c);
                continue;
            }
            
            entropy = find_string_split_entropy(c);
            
        }
        
        if(tbl_row_type_at(tbl_row_at(tbl, 0), i) == 'D'){
            if(has_single_value(c)) {
                count++;
                free_column(c);
                continue;
            }
            
            entropy = find_double_split_entropy(c);
        }
        
        
        if(entropy < prev){
            
            prev = entropy;
            index = i;
            
            if(tbl_row_type_at(tbl_row_at(tbl, 0), index) == 'D'){
                
                type = 'D';
            }
            
            if(tbl_row_type_at(tbl_row_at(tbl, 0), index) == 'S'){
                
                
                type = 'S';
                
                
            }
        }
        free_column(c);
        
    }
    
    
    if(count == tbl_column_count(tbl) -1){
        n->leaf = 1;
        n->class = (unsigned int)tbl_double_at(tbl_row_at(tbl, 0), cols-1);
        t_set_data(tree, n);
        tree->left = NULL;
        tree->right = NULL;
        return;
    }
    Column* first = get_column(tbl, 0);
    if(is_impossible_split(first) == 1){
        n->leaf = 1;
        n->class = (unsigned int)tbl_double_at(tbl_row_at(tbl, 0), cols-1);
        t_set_data(tree, n);
        tree->left = NULL;
        tree->right = NULL;
        free_column(first);
        return;
    }
	free_column(first);
    
    
    if(type == 'S'){
        c = get_column(tbl, index);
        n->entropy = prev;
        n->field.s = calloc(strlen(find_string_split_value(c))+1, sizeof(char));
        
        strcpy(n->field.s, find_string_split_value(c));
        
        
        n->type = type;
        n->leaf = 0;
        n->column = index;
        t_set_data(tree, n);
        
        //build two seperate tables
        left = build_string_left_table(tbl, find_string_split_value(c), index);
        right = build_string_right_table(tbl, find_string_split_value(c), index);
        free_column(c);
        
        //recursion
        tree->left = t_make();
        tree->right = t_make();
        
        dt_build(left, tree->left);
        dt_build(right, tree->right);
        
        if(left != NULL)
            tbl_free(left);
        if(right != NULL)
            tbl_free(right);
        
        return;
    }
    
    if(type == 'D'){
        c = get_column(tbl, index);
        n->entropy = prev;
        n->field.d = find_double_split_value(c);
        n->type = type;
        n->leaf = 0;
        n->column = index;
        t_set_data(tree, n);
        
        //build two seperate tables
        left = build_double_left_table(tbl, find_double_split_value(c), index);
        right = build_double_right_table(tbl, find_double_split_value(c), index);
        free_column(c);
        
        //recursion
        tree->left = t_make();
        tree->right = t_make();
        dt_build(left, tree->left);
        dt_build(right, tree->right);
        if(left != NULL)
            tbl_free(left);
        if(right != NULL)
            tbl_free(right);
        return;
    }
    
    
    return;

    
    
    
    return;
}

//TODO: make a class mapping that doesnt print.
char** class_mapping_string(Table* tbl){
    if(tbl == NULL) return NULL;
    int class_number;
    char** classes = classes_str(tbl);
    class_number = number_of_class_str(classes, tbl_row_count(tbl));
    char** ret = find_diff_classes_str(classes, tbl_row_count(tbl));
    print_class_mapping_str(ret, class_number);
    return ret;
}

char** find_diff_classes_str(char** list, int length){
    char** classes = calloc(1, sizeof(char*));
    char* prev = NULL;
    int index = 0;
    for(int i = 0; i < length; i++){
       
        if(i == 0){
            classes[index] = calloc(strlen(list[i])+1, sizeof(char));
            strcpy(classes[index], list[i]);
            prev = list[i];
            index++;
            continue;
        }
        if(strcmp(prev, list[i]) == 0) continue;
        
            prev = list[i];
            classes = realloc(classes, sizeof(char*)*(index+1));
            classes[index] = calloc(strlen(list[i])+1, sizeof(char));
            strcpy(classes[index], list[i]);
            index++;
    }
    free(list);
    return classes;
}

char** classes_str(Table* tbl){
    int rows = tbl_row_count(tbl);
    int cols = tbl_column_count(tbl) -1;
    char** classes = calloc(rows, sizeof(char*));
    for(int i = 0; i < rows; i++){
        classes[i] = tbl_string_at(tbl_row_at(tbl, i), cols);
    }
    qsort(classes, rows, sizeof(char*), str_compare);
    
    return classes;
}

int str_compare(const void* a, const void* b){
    const char** a_ = (const char**)a;
    const char** b_ = (const char**)b;
    return strcmp(*a_, *b_);
}

//TODO: make a class mapping that doesnt print.
double* class_mapping_double(Table* tbl){
    if(tbl == NULL) return NULL;
    int class_number;
    double* classes = classes_double(tbl);
    class_number = number_of_class_double(classes, tbl_row_count(tbl));
    double* ret = find_diff_classes_double(classes, tbl_row_count(tbl));
    print_class_mapping_double(ret, class_number);
    return ret;
}

double* find_diff_classes_double(double* list, int length){
    double* classes = calloc(1, sizeof(double));
    double prev;
    int index = 0;
    for(int i = 0; i < length; i++){
        
        if(i == 0){
            classes[index] = list[i];
            prev = list[i];
            index++;
            continue;
        }
        if(fabs(prev - list[i]) < ERROR) continue;
        
        prev = list[i];
        classes = realloc(classes, sizeof(double)*(index+1));
        classes[index] = list[i];
        index++;
    }
    free(list);
    return classes;
}

double* classes_double(Table* tbl){
    int rows = tbl_row_count(tbl);
    int cols = tbl_column_count(tbl) -1;
    double* classes = calloc(rows, sizeof(double));
    for(int i = 0; i < rows; i++){
        classes[i] = tbl_double_at(tbl_row_at(tbl, i), cols);
    }
    qsort(classes, rows, sizeof(double), double_compare);
  
    return classes;
}

int double_compare(const void* a, const void* b){
    if(fabs(*(double*)a - *(double*)b) < ERROR) return 0;
    else
        return *(double*)a - *(double*)b;
}

int* classes_for_entropy_str(char** key, Table* tbl){
    int rows = tbl_row_count(tbl);
    int* ret = calloc(rows, sizeof(int));
    int cols = tbl_column_count(tbl)-1;
    for(int i = 0; i < rows; ++i){
        ret[i] = find_val_str(key, rows, tbl_string_at(tbl_row_at(tbl, i), cols));
    }
    return ret;
}

int find_val_str(char** list, int length, char* key){
    for(int i = 0; i < length; ++i){
        if(strcmp(list[i], key) == 0) return i;
    }
    return -1;
}

void print_class_mapping_str(char** list, int length){
    printf("Class mapping:\n");
    int count = 0, j = 0;
    
    for(int i = 0; i < length; ++i){
        printf("%d = %s\n", i, list[i]);
    }
}

int number_of_class_str(char** ordered_list, int length){
    int index = 0;
    char* prev;
    for(int i = 0; i < length; ++i){
        if(i == 0){
            prev = ordered_list[i];
            ++index;
            continue;
        }
        if(strcmp(prev, ordered_list[i]) == 0) continue;
        
        prev = ordered_list[i];
        ++index;
    }
    
return index;
}

int* classes_for_entropy_double(double* key, Table* tbl){
    int rows = tbl_row_count(tbl);
    int* ret = calloc(rows, sizeof(int));
    int cols = tbl_column_count(tbl)-1;
    for(int i = 0; i < rows; ++i){
        ret[i] = find_val_double(key, rows, tbl_double_at(tbl_row_at(tbl, i), cols));
    }
    return ret;
}

int find_val_double(double* list, int length, double key){
    for(int i = 0; i < length; ++i){
        if(fabs(list[i] - key) < ERROR) return i;
    }
    return -1;
}

void print_class_mapping_double(double* list, int length){
    printf("Class mapping:\n");
    int count = 0, j = 0;
    
    for(int i = 0; i < length; ++i){
        printf("%d = %.2f\n", i, list[i]);
    }
}

int number_of_class_double(double* ordered_list, int length){
    int index = 0;
    double prev;
    for(int i = 0; i < length; ++i){
        if(i == 0){
            prev = ordered_list[i];
            ++index;
            continue;
        }
        if(fabs(prev - ordered_list[i]) < ERROR) continue;
        
        prev = ordered_list[i];
        ++index;
    }
    
    return index;
}



