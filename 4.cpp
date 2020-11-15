#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <random>
#include <iostream>
#include <chrono>

using namespace std::chrono;
int main(int argc, char **argv)
{
    int rank, np;
    int a[1000];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int n = atoi(argv[1]);
    int flag = atoi(argv[2]);
    int n1,d;
    if (flag == 1)
    {
        n1=n/np;
        if (rank == np - 1)
        {
            n1 += (n % np);
        }
        int i = 0;
        while (i < n1)
        {
            if (rank == np - 1)
                a[i] = rank * (n1 - (n % np)) + i;
            else
                a[i] = rank * n1 + i;
            i++;
        }
    }
    else if(flag==2)
    {
        n1=n/np;
        if(rank<n%np&&n%np!=0)
            n1++;
        int i=0;
        while(i*np+rank<n)
        {
            a[i]=i*np+rank;
            i++;
        }
    }
    else
    {
        d=2;
        n1=n/(d*np);
        
        
    }
    MPI_Barrier(MPI_COMM_WORLD);
    auto start = high_resolution_clock::now();

    int local_sum = 0,i;
    for (i = 0; i < n1; i++)
        local_sum += a[i];
    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Total Sum:%d\n", total_sum);
    }
    MPI_Finalize();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    //std::cout << duration.count() << std::endl;
}