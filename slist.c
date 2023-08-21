
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"



void dbllist_init(dbllist_t * a){    // initilaize the double link list with head pointer and tail pointer to NULL and the size of the list is zero
    dbllist_head(a) = NULL;
    dbllist_size(a) = 0;
    dbllist_tail(a) = NULL;

}

void dbllist_destroy(dbllist_t * a,dbllist_destroy_t b){
    if (dbllist_head(a)!=NULL){  // if the list wasnt null
        dbllist_node_t *tn1;
        dbllist_node_t *tn ;

   for(tn=dbllist_head(a);tn!=NULL;) {// loop on the dbllist and make free to the data andto the node
       if (b == DBLLIST_FREE_DATA) {
           free(dbllist_data(tn));
       }

       tn1 = dbllist_next(tn);
       free(tn);
       tn = tn1;
   }
     a->size=0;
    //free(a);//free to the dbllist
}

}


int dbllist_append(dbllist_t * a,void *b){// insert node in the first of the list

    dbllist_node_t * tm = (dbllist_node_t *)malloc(sizeof(dbllist_node_t));
    if (a==NULL||tm==NULL||b==NULL)// if malloc failed or da
        return -1;

    dbllist_data(tm) = b;
    dbllist_prev(tm)=NULL;// insert the data in the node
    dbllist_next(tm)=NULL;// make the next of the node point to null

    if(dbllist_head(a)==NULL) {// if the dbllist was NULL
        dbllist_head(a) = tm;
        dbllist_tail(a)=tm;
        dbllist_size(a)+=1;
        return 0;
    }

    else
    {// if it wasnt NULL then insert to first of the list
        dbllist_next(dbllist_tail(a))=tm;
        dbllist_prev(tm) = dbllist_tail(a);
        dbllist_tail(a) = tm;
        dbllist_size(a)+=1;
    }

    return 0;
}

int dbllist_prepend(dbllist_t * a,void * b){
    dbllist_node_t * tm = (dbllist_node_t *)malloc(sizeof(dbllist_node_t));
    if (tm==NULL)// if malloc failed
        return -1;

    dbllist_data(tm) = b;
    dbllist_prev(tm)=NULL;// insert the data in the node
    dbllist_next(tm)=NULL;// make the next of the node point to null

    if(dbllist_head(a)==NULL) {// if the dbllist was NULL
        dbllist_head(a) = tm;
        dbllist_tail(a)=tm;
        dbllist_size(a)+=1;
        return 0;
    }

    else
    {// if it wasnt NULL then insert to first of the list
        dbllist_prev(dbllist_head(a))=tm;
        dbllist_next(tm) = dbllist_head(a);
        dbllist_head(a) = tm;
        dbllist_size(a)+=1;
    }

    return 0;
}

int dbllist_remove(dbllist_t * a, dbllist_node_t* b ,dbllist_destroy_t c){
    if(a==NULL)
        return -1;

    if(b==dbllist_head(a))
    {
        dbllist_node_t * tm=dbllist_head(a);// the head of list a
        tm=dbllist_next(tm);// making swap func and free the data
        dbllist_head(a)=tm;
        if(c==DBLLIST_FREE_DATA)
        free(dbllist_data(b));
        free(b);

        dbllist_prev(tm)=NULL;
        dbllist_size(a)-=1;
        return 0;
    }

   else if(b==dbllist_tail(a)){// if the node was the tail of the list then remove the data according to the bit and free the node
        dbllist_node_t * tm=dbllist_tail(a);
        tm=dbllist_prev(tm);
        if(c==DBLLIST_FREE_DATA)
            free(dbllist_data(dbllist_tail(a)));
        free(dbllist_tail(a));
        dbllist_tail(a)=tm;// making swap function
        dbllist_next(tm)=NULL;
        dbllist_size(a)-=1;
        return 0;
   }

   else{
     // the node was not the head or the tail


               dbllist_node_t * tm;
               dbllist_node_t * tm1;

               tm1=dbllist_next(b);
               tm=dbllist_prev(b);
               if(c==DBLLIST_FREE_DATA)
                   free(dbllist_data(b));
               free(b);
               dbllist_prev(tm1)=tm;
               dbllist_next(tm)=tm1;
               dbllist_size(a)-=1;
               return 0;


       }
   }


