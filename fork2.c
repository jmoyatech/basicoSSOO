#include <unistd.h>
main(){
pipeline("/usr/bin/yes", "/bin/more");
}
int pipeline(char *proc1, char *proc2){
int fd[2];
pipe(fd);
if (fork()!=0){
close(fd[0]); // No lo necesitamos aqui
close(1); // Cierra la salida estandar
dup(fd[1]);
close(fd[1]); // No lo necesitamos
execl(proc1, proc1, 0);
}
else{
close(fd[1]); // No lo necesitamos
close(0); // Cierra la entrada estandar
dup(fd[0]);
close(fd[0]); // No lo necesitamos
execl(proc2, proc2, 0);
}
}

