#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* IPC can be used to enforce the order of the execution of processes.
*/

int main ()
{
    char *s, buf[1024];
    int fds[2]; //el kernel se encarga de hacer la asociacion para que pasandole un arreglo depende de cual posicion se tenga lee o escribe

    pipe(fds);

    if (fork() == 0) { 
    //aca solo entra el hijo, mientras que el padre tranquilamente puede estar ejecutandose concurrentemente
    //con el codigo fuera de este if
        printf("child\n");
        
        s = "hello world\n";
        write(fds[1], s, strlen(s));
        
        exit(0);
    }

    printf("father will block until read\n");

    //el read es bloqueante hasta que se termine de escribir entonces hasta que el proceso hijo
    //termine de escribir el proceso padre estara bloqueado 
    read(fds[0], buf, 12);
    printf("father continues..\n");

    // write to std out
    write(1, buf, 12);

    return 1;
}
