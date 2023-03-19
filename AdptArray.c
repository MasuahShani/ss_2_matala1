#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int size;
    PElement* arr;
    COPY_FUNC cf;
    DEL_FUNC df;
    PRINT_FUNC pf;
}AdptArray_, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf)
{
    PAdptArray arr_AD =(PAdptArray)malloc(sizeof(AdptArray_));
    if(!arr_AD)
    {
        return NULL;
    }

    arr_AD->cf=cf;
    arr_AD->df=df;
    arr_AD->pf=pf;
    arr_AD->size=0;
    arr_AD->arr=NULL;

    return arr_AD;

}

void DeleteAdptArray(PAdptArray arr_AD)
{
    if(!arr_AD)
    {
        return;
    }
    
    PElement* p_arr = arr_AD->arr;

    if(!p_arr)
    {   
        free(arr_AD);
        return;
    }

    for (int i=0; i<(arr_AD->size); i++)
    {
        if(*(p_arr+i))
        {
            (arr_AD->df)(*(p_arr+i));
        }
    }
    if((arr_AD->arr))
    {
        free(arr_AD->arr);
    }

    free(arr_AD);
    
}

Result SetAdptArrayAt(PAdptArray arr_AD, int inx, PElement pe)
{
    if(!arr_AD || inx<0)
    {
        return FAIL;
    }
    if((arr_AD->size)==0)
    {
        PElement* arr=(PElement*)calloc(1,sizeof(PElement));

        if(!arr)
        {
            return FAIL;
        }

    }

    if(inx >= (arr_AD->size))
    {
        PElement* new_arr=(PElement*)calloc(inx+1,sizeof(PElement));

        if(!new_arr)
        {
            return FAIL;
        }

        for(int i=0; i<(arr_AD->size); i++)
        {
            if(*((arr_AD->arr)+i))
            {
                new_arr[i]=(*((arr_AD->arr)+i));
            }
        }
        PElement temp=arr_AD->arr;
        arr_AD->arr=new_arr;
        free(temp);
        arr_AD->size=inx+1;

    }
     
    if(*((arr_AD->arr)+inx))
    {
        (arr_AD->df)(*((arr_AD->arr)+inx));
    }

    PElement copy_pe=(arr_AD->cf)(pe);
    *((arr_AD->arr)+inx)=copy_pe;

    if(!(*((arr_AD->arr)+inx)))
    {
        return FAIL;
    }
    return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray arr_AD, int inx)
{
    if(!arr_AD || (arr_AD->size)<=inx || !(*((arr_AD->arr)+inx)))
    {
        return NULL;
    }

    return (arr_AD->cf)(*((arr_AD->arr)+inx));
}

int GetAdptArraySize(PAdptArray arr_AD)
{
    if(!arr_AD)
    {
        return -1;
    }
    return (arr_AD->size);
}

void PrintDB(PAdptArray arr_AD)
{
    if(!arr_AD)
    {
        printf("The AdaptArray is NULL");
        return;
    }

    if((arr_AD->size)==0)
    {
        printf("The Array is empty");
        return;
    }

    for(int i=0; i<(arr_AD->size); i++)
    {
        if(*((arr_AD->arr)+i))
        {
            (arr_AD->pf)(*((arr_AD->arr)+i));
        }
    }

}