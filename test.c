#include "defs_itf.h"





char** colnames;

int main(){
    colnames = calloc(5, sizeof(char*));
    
    
    
    char* c1 = "outlook";
    char* c2 = "temperature";
    char* c3 = "humidity";
    char* c4 = "wind";
    char* c5 = "play";
    colnames[0] = c1;
    colnames[1] = c2;
    colnames[2] = c3;
    colnames[3] = c4;
    colnames[4] = c5;
    //********0.txt********
    char* p1 = "rainy";
    char* p2 = "overcast";
    char* p3 = "sunny";
    
    char* t1 = "cool";
    char* t2 = "mild";
    char* t3 = "hot";
    
    char* h1 = "normal";
    char* h2 = "high";
    char* h3 = "low";
    
    char* w1 = "true";
    char* w2 = "false";
    
    //************1.txt************
    char* x1 = "cat";
    char* x2 = "dog";
    char* x3 = "person";
    char* x4 = "emu";
    char* x5 = "rat";
    char* x6 = "orange";
    char* x7 = "plug";
    
    Table* tbl = tbl_make();
    /*
     
     tbl_start_row(tbl, 5);
     tbl_add_string_to_row(tbl, p1);
     tbl_add_string_to_row(tbl, t1);
     tbl_add_string_to_row(tbl, h1);
     tbl_add_string_to_row(tbl, w2);
     tbl_add_double_to_row(tbl, 0.0);
     tbl_start_row(tbl, 5);
     tbl_add_string_to_row(tbl, p1);
     tbl_add_string_to_row(tbl, t1);
     tbl_add_string_to_row(tbl, h1);
     tbl_add_string_to_row(tbl, w2);
     tbl_add_double_to_row(tbl, 1.0);
     tbl_done_building(tbl);
     
     *//*
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x1);
        tbl_add_double_to_row(tbl, 15);
        tbl_add_double_to_row(tbl, 1);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x2);
        tbl_add_double_to_row(tbl, 50);
        tbl_add_double_to_row(tbl, 0);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x3);
        tbl_add_double_to_row(tbl, 30);
        tbl_add_double_to_row(tbl, 0);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x4);
        tbl_add_double_to_row(tbl, 12);
        tbl_add_double_to_row(tbl, 0);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x5);
        tbl_add_double_to_row(tbl, 12);
        tbl_add_double_to_row(tbl, 1);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x6);
        tbl_add_double_to_row(tbl, 12);
        tbl_add_double_to_row(tbl, 0);
        tbl_start_row(tbl, 3);
        tbl_add_string_to_row(tbl, x7);
        tbl_add_double_to_row(tbl, 15);
        tbl_add_double_to_row(tbl, 1);
        tbl_done_building(tbl);
        */
    
    //*******0.txt*********
  /*  tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p1);
    tbl_add_string_to_row(tbl, t1);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p1);
    tbl_add_string_to_row(tbl, t1);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w1);
    tbl_add_double_to_row(tbl, 0.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p2);
    tbl_add_string_to_row(tbl, t3);
    tbl_add_string_to_row(tbl, h2);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p3);
    tbl_add_string_to_row(tbl, t2);
    tbl_add_string_to_row(tbl, h2);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 0.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p1);
    tbl_add_string_to_row(tbl, t1);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p3);
    tbl_add_string_to_row(tbl, t1);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p1);
    tbl_add_string_to_row(tbl, t1);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p3);
    tbl_add_string_to_row(tbl, t3);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p2);
    tbl_add_string_to_row(tbl, t2);
    tbl_add_string_to_row(tbl, h2);
    tbl_add_string_to_row(tbl, w1);
    tbl_add_double_to_row(tbl, 1.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p3);
    tbl_add_string_to_row(tbl, t2);
    tbl_add_string_to_row(tbl, h2);
    tbl_add_string_to_row(tbl, w1);
    tbl_add_double_to_row(tbl, 0.0);
    tbl_start_row(tbl, 5);
    tbl_add_string_to_row(tbl, p2);
    tbl_add_string_to_row(tbl, t3);
    tbl_add_string_to_row(tbl, h1);
    tbl_add_string_to_row(tbl, w2);
    tbl_add_double_to_row(tbl, 0.0);
    tbl_done_building(tbl);*/
    //tbl_print(tbl);
    Table* ret = tbl_make();
    tbl_start_row(ret, 5);
    tbl_add_string_to_row(ret, p2);
    tbl_add_string_to_row(ret, t1);
    tbl_add_string_to_row(ret, h3);
    tbl_add_string_to_row(ret, w1);
    tbl_add_double_to_row(ret, 1.0);
    tbl_start_row(ret, 5);
    tbl_add_string_to_row(ret, p3);
    tbl_add_string_to_row(ret, t3);
    tbl_add_string_to_row(ret, h2);
    tbl_add_string_to_row(ret, w2);
    tbl_add_double_to_row(ret, 0.0);
    tbl_start_row(ret, 5);
    tbl_add_string_to_row(ret, p1);
    tbl_add_string_to_row(ret, t1);
    tbl_add_string_to_row(ret, h1);
    tbl_add_string_to_row(ret, w2);
    tbl_add_double_to_row(ret, 1.0);
    tbl_start_row(ret, 5);
    tbl_add_string_to_row(ret, p1);
    tbl_add_string_to_row(ret, t1);
    tbl_add_string_to_row(ret, h1);
    tbl_add_string_to_row(ret, w1);
    tbl_add_double_to_row(ret, 0.0);
    tbl_done_building(ret);
    char* split = "mild";

    
    
   
   // tbl_print_row(tbl_row_at(ret, 0));
    
    
   // tbl_print_row(rt);
    
   
    
    tbl = resample(ret);
   // tbl = resample(ret);
    tbl_print(tbl);
    //tbl_print(ret);
    
    
}