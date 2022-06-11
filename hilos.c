#include <stdio.h>
#include <pthread.h>
#include <string.h>

struct PARAMETRO{
    char texto[10];
    pthread_t hilo;
};

main(){
    void rutina();
    pthread_t hilo1, hilo2;
    int no_ok;
    struct PARAMETRO p1, p2;
    strcpy(p1.texto, "HOLA ");
    strcpy(p2.texto, "MUNDO");
    p1.hilo=0;
    no_ok=pthread_create(&hilo1, NULL, (void *)rutina, &p1);
    
if (no_ok){
    printf("Error creando hilo = %d\n", no_ok);
    exit(1);
}

p2.hilo=hilo1;
no_ok=pthread_create(&hilo2, NULL, (void *)rutina, &p2);
pthread_join(hilo2, NULL);
printf("\n");
}

void rutina(struct PARAMETRO *p){
if (p->hilo != 0){
pthread_join(p->hilo, NULL);
}
printf("%s", p->texto);
pthread_exit(0);
}

