#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_LEN 64

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char local_msg[MSG_LEN];
    memset(local_msg, 0, MSG_LEN);

    if (rank == 0) {
        snprintf(local_msg, MSG_LEN, "Rank %d comunicador", rank);
    } else {
        snprintf(local_msg, MSG_LEN, "Rank %d con size %d", rank, size);
    }

    char *all_msgs = NULL;
    if (rank == 0) {
        all_msgs = (char *) malloc(size * MSG_LEN);
    }

    /* Recoleccion ordenada: cada proceso envia MSG_LEN bytes, el root
     * los concatena en orden de rank en 'all_msgs'. */
    MPI_Gather(local_msg, MSG_LEN, MPI_CHAR,
               all_msgs, MSG_LEN, MPI_CHAR,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("%s\n", all_msgs + i * MSG_LEN);
        }
        free(all_msgs);
    }

    MPI_Finalize();
    return 0;
}