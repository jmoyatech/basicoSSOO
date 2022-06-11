#include <stdio.h>
//ejemplo FORK
main(){
int i, e, idf;
idf=0;
for (i=0; i< 5; i++){
if (fork() == 0){
/* Hijo */
idf = i+1;
printf("Numero = %d, pid = %d\n", idf, getpid());
sleep(3);
if (idf == 5){
printf("Termina el %d, PID = %d, PPID =%d\n", \
idf, getpid(), getppid());
exit(0);
}
}
else{
wait(&e);
printf("Termina el %d, PID = %d, PPID =%d\n", \
idf, getpid(), getppid());
exit(0);
}
}
}
