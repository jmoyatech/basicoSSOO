#include <stdio.h>
#include <sys/signal.h>

//contador de control-c

int contador=0;
int veces=0;

void rutina_SIGALARM();
void rutina_SIGINT();

main(){

	signal(SIGALRM,rutina_SIGALARM);
	signal(SIGINT,rutina_SIGINT);
	alarm(15);
	printf("ya puedes pulsar controlc\n");
	for(;;);
}
void rutina_SIGINT(){
	contador++;
}
void rutina_SIGALARM(){
	printf("has pulsado %d veces controlc\n",contador);
	contador=0;
	veces++;
	if(veces==4) exit(0);
	else alarm(15);
}
