#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#define CLAVE (key_t)(23452352 + 234345223 ) // Reemplazar
struct MENSAJE{
long tipo;
pid_t pid;
unsigned char ok;
unsigned long offset;
unsigned char c;
};
int msgid; /* identificador de la cola de mensajes */
main(){
struct MENSAJE msg;
int e;
pid_t mi_pid;
void ControlC();
mi_pid=getpid();
msgid = msgget(CLAVE, IPC_CREAT | 0600);
if (msgid < 0){
printf("Error en obtencion de la cola de mensajes\n");
exit(1);
}
printf("Cliente iniciado, para terminar pulsa Control-C\n");
for(;;){ /* Prepara una peticion de servicio */
msg.pid=mi_pid;
msg.tipo=1L;
printf("Introduce valor de offset:\n");
scanf("%ld", &msg.offset);
e=msgsnd(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), 0);
if (e<0){
printf("Error en envio de mensaje\n");
exit(1);
}
/* Espera respuesta: */
e=msgrcv(msgid, &msg, sizeof(struct MENSAJE) - \
sizeof(long), (long)mi_pid, 0);
if (e<0){
printf("Error en recepcion de mensaje\n");
exit(1);
}
if (msg.ok)
printf("Valor devuelto en mensaje: c = %c\n", msg.c);
else
printf("El servidor informa de un error\n");
}
}


