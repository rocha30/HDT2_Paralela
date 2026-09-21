#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* ---------- Etapa 1: antes de la barrera ---------- */
    printf("Rank %d: [Etapa 1] iniciando trabajo previo...\n", rank);
    fflush(stdout);

    sleep(rank % 3); /* simula tiempos de trabajo distintos por proceso */

    printf("Rank %d: [Etapa 1] trabajo previo terminado, esperando en la barrera\n", rank);
    fflush(stdout);

    /* ---------- Punto de sincronizacion ---------- */
    MPI_Barrier(MPI_COMM_WORLD);

    /* ---------- Etapa 2: despues de la barrera ---------- */
    /* Al llegar aqui, TODOS los procesos ya terminaron la Etapa 1,
     * sin importar cuanto tardo cada uno. */
    printf("Rank %d: [Etapa 2] todos sincronizados, continuando con la siguiente fase\n", rank);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}