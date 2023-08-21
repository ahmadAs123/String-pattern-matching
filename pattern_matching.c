#include"pattern_matching.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//322786757 id

int counter=0;
int id=0;
int state=1;

int pm_init(pm_t * a){ // intilizing the zero state with all the feuturs of the state
if(a==NULL)
    return -1;
     a->zerostate=( pm_state_t *)malloc(sizeof(pm_state_t ));// malloc to the zerostate
    if(a->zerostate==NULL)
        return -1;
    a->zerostate->id=id;
    a->zerostate->depth=counter;
    a->zerostate->fail = NULL;
    a->zerostate->output = NULL;
    a->zerostate->_transitions=(dbllist_t*)malloc(sizeof(dbllist_t));
    if(a->zerostate->_transitions==NULL)
        return -1;
    a->newstate = state;
    return 0;
}



int pm_addstring(pm_t * a,unsigned char * b, _size_t n){

if (a==NULL)
    return -1;
if(n<0)
    return -1;

    pm_state_t *nod1;
    int j;
    pm_state_t * new;
    pm_state_t *nod2  =a->zerostate;
    pm_state_t *nod3;
    for(j=0;j<n;j++){
        unsigned char l = b[j];

        nod1 = pm_goto_get(nod2, l);// check if there is sons

        if (nod1==NULL)
        {


           new= malloc(sizeof (pm_state_t));// update all the futures
            id++;
            counter++;
            new->id=id;
            new->fail=NULL;
            new->_transitions=(dbllist_t*)malloc(sizeof(dbllist_t));
            new->output = (dbllist_t*)malloc(sizeof(dbllist_t));
            if (new->output==NULL)// malloc was faild
            {
                // pm_destroy(a);
                return -1;
            }
            new->depth=counter;
            printf("Allocating state %d\n", new->id);// print the state id
            printf("%d -> %c -> %d\n", nod2->id,l,new->id);//print the state is from to
            if(new->_transitions==NULL) {
                return -1;
            }

            nod3=nod2;
            int res=pm_goto_set(nod2, l, new);// add edge that connect between nod2 and new by label l

            if (res==-1)
            {
                return -1;
            }

         nod2=new;
            state++;
        }

        else
        nod2=nod1 ;// work on the next state
    }


   new->output = (dbllist_t*)malloc(sizeof(dbllist_t));
    if (nod2->output==NULL)// malloc was faild
    {
       // pm_destroy(a);
        return -1;
    }
    dbllist_init(nod2->output);//itilize the dbllist
    dbllist_append(nod2->output, b);// update the output of the last state to be the string

    return 0;

}




int pm_goto_set(pm_state_t *from_state ,unsigned char symbol ,pm_state_t *to_state){
   // add edge that connect between two state if there is no coneection
   if(from_state==NULL)
       return -1;
   if(to_state==NULL)
       return -1;
    pm_labeled_edge_t *new = (pm_labeled_edge_t*)malloc(sizeof(pm_labeled_edge_t)); // make a new edge label
    if (new==NULL)
        return -1;

    new->state = to_state;// insrert the data to the new edge label
    new->label = symbol;

  int res= dbllist_append(from_state->_transitions,new);// insert the new edge label in the last of the double list  transition

  if(res==-1){
        free(new);// the isnsert faild
        return -1;}



    return 0; // the prossess succsseid
}


pm_state_t* pm_goto_get(pm_state_t *state,unsigned char symbol){// check if there is a road from this state to another state by the symbol
    if (state!=NULL){// there is state
     pm_labeled_edge_t *res;
    dbllist_node_t * cur ;
   for(cur= dbllist_head(state->_transitions);cur!=NULL;cur=dbllist_next(cur))//loop on the transition list of every each block
    {
        if (((pm_labeled_edge_t *)(dbllist_data(cur)))->label==symbol){//if the label of the edge was the same as symbol then return that state
            res=(pm_labeled_edge_t*)(cur->data);
            return res->state;
    }

    }
   if(cur==NULL)// we didnt find state that we can reach it by this symbol
       return NULL;
    }

    return NULL; // the state was null
}



dbllist_t* pm_fsm_search(pm_state_t * a,unsigned char * b,_size_t c){

    dbllist_t *match_res=(dbllist_t*) malloc(sizeof (dbllist_t));
    if(match_res==NULL)
        return NULL;
    dbllist_init(match_res);// intilize the list

    if(a==NULL)
        return match_res ;
    if(c<0)
        return match_res ;
pm_state_t* first_state=a ;
  for(int i=0;i<c;i++){ // loop on the size of the string
        while(pm_goto_get(first_state,b[i])!=NULL) {// while there is no goto from this node by lable b[i] let the state be the failure of this state
            first_state = first_state->fail;
            if (first_state == NULL)// we arrived to zerostate
                break;
        }
    first_state = pm_goto_get(first_state,b[i]);
    if(dbllist_size(first_state->output) > 0){// if there is output for this state
        dbllist_node_t * first_n=dbllist_head(first_state->output);
     int counter=i;
     while(counter<c){// loop on the num of tj=he letters

     if(strcmp((char*)dbllist_data(first_n),&b[counter])==0) {// the letter equal to the output then push it to the match lest
         int y = dbllist_append(match_res,&b[counter]);
         if (y == -1)
           dbllist_destroy(match_res,1);
            break;
     }
         counter++;

     }
    }
}
  return match_res;
}


int pm_makeFSM(pm_t * a) {
    dbllist_node_t *curruntly;
    pm_state_t *res;
    pm_state_t *re;
   // dbllist_node_t *on;
    dbllist_node_t *state_on;
    dbllist_node_t *tmp;
    dbllist_node_t *cur;
    pm_labeled_edge_t *son;
    pm_state_t * state_before;
    pm_state_t *result;
    int tot_q;
if(a==NULL)
    return -1;
    dbllist_t *q = (dbllist_t*)malloc(sizeof(dbllist_t));
    if (q == NULL) // if the malloc faild return -1 and destroy the dbllist
    {
        dbllist_destroy(q,1);
        return -1;
    }
    dbllist_init(q);// intiliazation of the dbllist

    for (cur = dbllist_head(a->zerostate->_transitions);cur != NULL; cur = dbllist_next(cur)) { // loop on the tranzitions of the zerostate and insert into queue q
        res = ((pm_labeled_edge_t *) dbllist_data(cur))->state;
        tot_q = dbllist_append(q, res);
        if (tot_q == -1) { // the insertion didnt succsess then return -1
          dbllist_destroy(q,1);
            return -1;

        }
        res->fail = a->zerostate; // make the failir of the states to the zero state
    }


    while (dbllist_size(q)!=0) {
        int si=dbllist_size(q);// loop on the quueue

        re = dbllist_data(dbllist_head(q));// the data of the first node
        int uu=re->id;
        // -1 for the size beacuse we dequeue
        tmp = dbllist_head(q);  //swap code to svae the data and free the node
        dbllist_head(q) = dbllist_next(dbllist_head(q));
        free(tmp);
        dbllist_size(q) -= 1;


        pm_state_t *on = re;
int u=on->id;
        state_on = dbllist_head(on->_transitions);//pointer on the sons of this node that we push it out from the queue
        int ssso=dbllist_size(on->_transitions);

        int j = 0;
        for (; j < dbllist_size(on->_transitions); j++) {// loop on all the sons of this state
           son= dbllist_data(state_on);
           result= son->state;
           int r=result->id;
            int y = dbllist_append(q, result);// ppush in the queue
            if (y < 0) {

                return -1;
            }
            state_before = on->fail;// poin to the failure
            unsigned char b = son->label;
            while (pm_goto_get(   state_before, b) == NULL) {
                if (  pm_goto_get(   state_before, b)  == NULL) {
                    if(state_before==a->zerostate)
                    break;
                    else
                        state_before =    state_before->fail;
                }

            }

            state_before = pm_goto_get(state_before, b);
            if ( state_before== NULL) {
                state_before=a->zerostate;
                result->fail = a->zerostate;
            }
            else {
                result->fail = state_before;
            }
//int op=result->id;
//int hh=state_before->id;
                printf("Setting f(%d)=%d\n",result->id,  state_before->id);// print the failiur with id of state
                pm_state_t * h=result->fail;
            state_on = dbllist_next(state_on);// point to the next state in queue
        }

    }
   dbllist_destroy(q, DBLLIST_LEAVE_DATA);
    return 0;
}



void pm_destroy(pm_t *pm) {
 pm_state_t *first_node;
    dbllist_node_t *sons_node;
    pm_labeled_edge_t *ed;
    dbllist_t *deleted_queue;
    if (pm==NULL)
        return;

   deleted_queue= (dbllist_t*)malloc(sizeof(dbllist_t));
    if (deleted_queue==NULL)
        return;

    dbllist_init(deleted_queue);
    for (sons_node = dbllist_head(pm->zerostate->_transitions);sons_node != NULL; sons_node = dbllist_next(sons_node)) { // loop on the tranzitions of the zerostate and insert into queue q
        ed = ((pm_labeled_edge_t *) dbllist_data(sons_node));
       first_node = ed->state;
       int n= dbllist_append(deleted_queue,first_node);
        if (n == -1) {
            dbllist_destroy(deleted_queue,1);// the insertion didnt succsess then return -1
            return ;
        }

    }

    while (dbllist_head(deleted_queue)!=NULL) { // loop on the quueue

      pm_state_t* data_node = dbllist_data(dbllist_head(deleted_queue));// the data of the first node

        if (dbllist_size(deleted_queue) == 1) {
            dbllist_destroy(deleted_queue,1); // in queue there is a one node so we must free it
            dbllist_size(deleted_queue) -= 1;
            break;
        }

        else{
            dbllist_size(deleted_queue) -= 1;  // -1 for the size beacuse we dequeue
            dbllist_node_t *tmp = dbllist_head(deleted_queue);  //swap code to svae the data and free the node
            dbllist_head(deleted_queue) = dbllist_next(dbllist_head(deleted_queue));

        }

        pm_state_t *on1 = data_node;

       dbllist_node_t *state_on1 = dbllist_head(on1->_transitions);//pointer on the sons of this node that we push it out from the queue

        for (int j = 0; j < dbllist_size(on1->_transitions); j++) {// loop on all the sons of this state
            pm_labeled_edge_t *son= dbllist_data(state_on1);
             pm_state_t *result= son->state;
            int y = dbllist_append(deleted_queue, result);// ppush in the queue
            if(y==-1){
                dbllist_destroy(deleted_queue,1);
            break;}

                state_on1 = dbllist_next(state_on1);
            }
      //  dbllist_destroy(on1->output,1);
        dbllist_destroy(on1->_transitions,1);
        }
    //free(pm);
    }



