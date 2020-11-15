#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

void rand_generator(int n,int *a)
{
    for(int i = 0; i < n ; ++i)
    {
        a[i] = rand()%100;
    }
}

int main(int argc, char** argv)
{
    srand(27);

    int n = atoi(argv[1]);
    int a[n];

    rand_generator(n,a);

    int np,rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int start = (n/np)*rank;
    int end = (n/np)*(rank+1);

    if(rank == np-1)
    {
        end = n;
    }

    int sum = 0;

    for(int i = start; i < end; ++i)
    {
        sum += a[i];
    }

    if(rank == 0)
    {
        int total_sum = 0;

        for(int i = 1 ; i < np ; ++i)
        {
            int lsum;

            MPI_Recv(&lsum , 1 , MPI_INT , i , i , MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            total_sum += lsum;
        }

        total_sum += sum;

        printf("The sum is : %d\n",total_sum);
    }

    else
    {
        MPI_Send(&sum , 1 , MPI_INT , 0 , rank , MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
