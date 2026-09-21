#include <mpi.h>
#include <stdio.h>

#ifndef VALOR_INICIAL
#define VALOR_INICIAL 42
#endif

int main(int argc, char** argv) {
    int rank, size;
    int valor; /* buffer que se transmite; el root lo inicializa, los
                  demas lo reciben aqui mismo */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int ROOT = 0;

    if (rank == ROOT) {
        valor = VALOR_INICIAL;
        printf("Rank %d (coordinador): voy a difundir el valor %d a %d procesos\n",
               rank, valor, size);
        fflush(stdout);
    }

    /* Barrera opcional solo para que el mensaje del coordinador se
     * imprima antes que los de recepcion (efecto visual, no es
     * necesaria para la correctitud de MPI_Bcast). */
    MPI_Barrier(MPI_COMM_WORLD);

    /* Difusion colectiva: el root envia, el resto recibe, en una sola
     * llamada identica para todos. */
    MPI_Bcast(&valor, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    printf("Rank %d: recibi el valor %d\n", rank, valor);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}