#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/signal.h>
#include <unistd.h>
#define CLAVE (key_t)( 23452352 + 234345223 ) // Reemplazar.
struct MENSAJE{
long tipo;
pid_t pid;
unsigned char ok;
unsigned long offset;
unsigned char c;
};
int msgid; /* identificador de la cola de mensajes */
FILE *fp; /* Descriptor de fichero */
main(){
struct MENSAJE msg;
int e;
void ControlC();
fp = fopen("datos", "r");
if (fp == NULL){
printf("Error en apertura del fichero\n");
exit(1);
}
msgid = msgget(CLAVE, IPC_CREAT | 0600);
if (msgid < 0){
printf("Error en obtencion de la cola de mensajes\n");
exit(1);
}
signal(SIGINT, ControlC);
printf("Iniciado servidor, para terminar pulsa ControlC\n");
for(;;){ /* Espera peticion de servicio: */
e=msgrcv(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), 1L, 0);
if (e<=0){ /* Numero de bytes leidos o negativo si error */
printf("Error en recepcion de mensaje\n");
msgctl(msgid, IPC_RMID, 0);
exit(1);
}
e=fseek(fp, msg.offset, SEEK_SET);
if (e<0){ /* Error en posicionamiento */
msg.ok=0; /* Error */
msg.tipo=(long)msg.pid;
e=msgsnd(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), 0);
if (e<0){
printf("Error en envio de mensaje\n");
msgctl(msgid, IPC_RMID, 0);
exit(1);
}
}
else{
e=fread(&msg.c, 1, 1, fp);
if (e<=0){ /* Error o no leido nada */
msg.ok=0; /* Error */
msg.tipo=(long)msg.pid;
e=msgsnd(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), 0);
if (e<0){
printf("Error en envio de mensaje\n");
msgctl(msgid, IPC_RMID, 0);
exit(1);
}
}
else{
msg.ok=1; /* OK */
msg.tipo=msg.pid;
e=msgsnd(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), 0);
if (e<0){
printf("Error en envio de mensaje\n");
msgctl(msgid, IPC_RMID, 0);
exit(1);
}
}
}
}
}
void ControlC(){
msgctl(msgid, IPC_RMID, 0);
fclose(fp);
exit(0);
}

