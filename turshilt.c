#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 // size of shared memory segment

int main()
{
    int shmid;
    char *shmaddr;
    char buffer[SHM_SIZE];

    // generate key for shared memory segment
    key_t key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach to shared memory segment
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // write data to shared memory segment
    strncpy(shmaddr, "Hello, shared memory!", SHM_SIZE);

    // read data from shared memory segment
    strncpy(buffer, shmaddr, SHM_SIZE);
    printf("Received message: %s\n", buffer);

    // detach from shared memory segment
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // remove shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
