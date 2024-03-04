#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print(int *arr, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}

void insert_file(FILE *fp, int *a , int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%d\t",a[i]);
    }
    fprintf(fp,"\n");
}
void swap(int *a, int *b)
{
    int temp=*a ;
    *a=*b;
    *b= temp;
}

int partition_lp(int *arr, int p, int q, double *c)
{
    int x = arr[p], i =p, j;
    for(j=p+1;j<=q;j++)
    {
        (*c)++;
        if(arr[j]<=x)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i],&arr[p]);
    return i;
}

int random_part(int *arr, int p , int r, double*c)
{
    int i = rand()%(r-p+1)+p;
    swap(&arr[r], &arr[i]);
    return partition_lp(arr,p,r,c);
}

void random_qs(int *arr, int p , int r, double *c)
{
    if(p<r)
    {
        int q = random_part(arr,p,r,c);
        random_qs(arr,p,q-1,c);
        random_qs(arr,q+1,r,c);
    }
}

 void permute(FILE *fp, int *a, int n, int index)
 {
    int i;
    if(index==n-1)
    {
       insert_file(fp,a,n);
       return; 
    }
    for(i= index; i<n;i++)
    {
        swap(&a[index],&a[i]);
        permute(fp,a,n,index+1);
        swap(&a[index],&a[i]);
    }
 }

 void quicksort_lp(int *arr, int p, int r, double *c)
 {
    if(p<r)
    {
        int q = random_part(arr,p,r,c);
        quicksort_lp(arr,p,q-1,c);
        quicksort_lp(arr,q+1,r,c);
    }
}

double fact(int n)
{
    int i;
    double r =1;
    for(i=1;i<=n; i++)
    {
        r*=i;
    }
    return r;
}

int main()
{
    srand(time(NULL));
    FILE *fptr1, *fptr2_random, *fptr2_fixed, *fptr3, *fptr4;
    int n, i, *a;
    double r=0, f=0;
    printf("Enter the Number of inputs : \n");
    scanf("%d",&n);
    a = (int *) malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        a[i]=i;
    }
    fptr1 = fopen("p.txt","w");
    if(fptr1!=NULL)
    {
        permute(fptr1, a, n,0);
    }
    else
    {
        printf("File Does not exist");
    }
    fptr2_random = fopen("p.txt", "r");
    fptr2_fixed = fopen("p.txt", "r");
    fptr3 = fopen("or.txt","w");
    fptr4 = fopen("of.txt", "w");
    while(fscanf(fptr2_random, "%d",&a[0])!=EOF)
    {
        for(i=1;i<n;i++)
        {
            fscanf(fptr2_random,"%d",&a[i]);
        }
        random_qs(a,0,n-1,&r);
        insert_file(fptr3, a , n);  
    }
    while(fscanf(fptr2_fixed, "%d",&a[0])!=EOF)
    {
        for(i=1;i<n;i++)
        {
            fscanf(fptr2_fixed,"%d",&a[i]);
        }
        quicksort_lp(a,0,n-1,&f);
        insert_file(fptr4, a , n);  
    }
    fclose(fptr2_random);
    fclose(fptr2_fixed);
    fclose(fptr3);
    fclose(fptr4);
    printf("Average number of comparisons for randomized : %lf\n",r/fact(n));
    printf("Average number of comparisons for fixed : %lf\n",f/fact(n));

    return 0;
    

}

