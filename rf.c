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

	
    
	for(int i = 0; i < tbl_column_count(tbl); i++){
		free(colnames[i]);
	}
tbl_free(tbl);
rd_close(train);
free(colnames);
	
    //create multiple random trees!!!!
    //build_tree(ret);
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

void build_tree(Table* tbl, Tree* t){
    if(tbl == NULL) return;
    Node* n = n_make();
    
    
    return;
}

char** class_mapping_string(Table* tbl){
    if(tbl == NULL) return NULL;
    char** classes = classes_str(tbl);
    char** ret = find_diff_classes_str(classes, tbl_row_count(tbl));
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

double* class_mapping_double(Table* tbl){
    if(tbl == NULL) return NULL;
    double* classes = classes_double(tbl);
    double* ret = find_diff_classes_double(classes, tbl_row_count(tbl));
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


