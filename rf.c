#include "defs_itf.h"

//int main(){
    
    
//}


Table* resample(Table* src){
    Table* ret = tbl_make();
    srand(13);
    int rows = tbl_row_count(src);
    Row* rt;
    
    for(int i = 0; i < rows; i++){
        rt = tbl_copy_row(tbl_row_at(src, rand() % rows));
        tbl_add_row(ret, rt);
    }
    tbl_done_building(ret);
    return ret;
}