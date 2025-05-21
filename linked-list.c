#include <stdio.h>
#include <stdlib.h>


#include "malloc.h"
#include "linked-list.h"

struct point{
    int x;
    int y;
};


//Take note of the type casting
static int cmp(const void *aa, const void *bb, void *pp)
{
    struct point *a = (struct point *) aa;
    struct point *b = (struct point *) bb;
    struct point *p = (struct point *) pp;
    double dx, dy, d1, d2;

    dx = a->x - p->x;
    dy = a->x - p->y;
    d1 = dx*dx + dy*dy;
    dx = b->x - p->x;
    dy = b->x - p->y;
    d2 = dx*dx + dy*dy;

    if(d1 < d2)
        return -1;
    else if(d2 < d1)
        return 1;
    else
        return 0;
}


//Implementing a simple filter function
int catch_the_odds(void *aa)
{
    int a = *(int *)aa;
    return a%2;
}


//This is applying a stack for the our case
Conscell *ll_push(Conscell *newList, void *data)
{
    Conscell *newCell = xmalloc(sizeof newCell);
    newCell->data = data;
    newCell->next = list;
    return new;
}

Conscell *ll_pop(Conscell *listToPop)
{
    Conscell *popedList = (*listToPop)->next;
    free(listToPop);
    return popedList;
}

Conscell *ll_free(Conscell *listTofree)
{
    while(listTofree != NULL)
    {
        Conscell *p = listTofree->next;
        free(listTofree);
        listTofree = p;
    }
}

Conscell *ll_reverse(Conscell *listToReverse)
{
    Conscell *reversedList = xmalloc(sizeof reversedList);
    for(Conscell *p = listToReverse; p != NULL; p = p->next)
    {
        ll_push(reversedList, * p->data)
    }
    ll_free(listToReverse);
    return reversedList;
}

Conscell *ll_sort(Conscell *listToSort, int(* cmp)(const void *aa, const *bb, void *params), void *params)
{
    Conscell *list1 = xmalloc(sizeof list1);
    Conscell *list2 = xmalloc(sizeof list2);
    Conscell *p, *q, *head;

    if(listToSort == NULL)
    {
        return listToSort;
    }
    head = listToSort;
    p = listToSort->next;
    while(p != NULL)
    {
        q = p->next;
        if(cmp(p->data, head->data, params) < 0){
            p->next = list1;
            list1 = p
        }
        else
        {
            p-next = list2;
            list2 = p
        }
        p = q;//Updating the value of p
    }

    //Doing recursion for both lists
    list1 = ll_sort(list1, cmp, params);
    list1 = ll_sort(list2, cmp, params);
    head->next = list2

    if(list1 == NULL)
        return head;

    for(p = list1; p->next != NULL; p = p->next)
        ;
    p->next = head;
    return list1;

}

Conscell *ll_filter(Conscell *listToFilter, int(* filter)(void *a), Conscell **removed)
{
    if(listToFilter == NULL)
        return listToFilter;

    while(listToFilter != NULL)
    {
        Conscell *p = listToFilter->next;
        if(filter(listToFilter->data))
        {
            listToFilter->next = *removed;
            *removed = listToFilter;//Making sure that removed always points to the beginning of the first conscell
            return ll_filter(p, filter, removed)
        }
        else
        {
            listToFilter = ll_filter(listToFilter->next, filter, removed);
            return listToFilter;
        }
    }
}

int ll_length(Conscell *longList)
{
    int length = 0;
    for(Conscell *p = longList; p != NULL; p = p->next)
        length++;
}





