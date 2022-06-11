#include <stdio.h>
#include <pthread.h>
#include <string.h>
int vcompartida=0,nescritores=0,nlectores=0;
pthread_mutex_t mutex;
pthread_cond_t oklector,okescritor;
main()
{
void *escritor();
void *lector();
pthread_t escritor1,escritor2,lector1,lector2;
int no_ok[4];
pthread_cond_init(&oklector,NULL);
pthread_cond_init(&okescritor,NULL);
pthread_mutex_init(&mutex,NULL);
no_ok[0]=pthread_create(&escritor1,NULL,escritor,NULL);
no_ok[1]=pthread_create(&escritor2,NULL,escritor,NULL);
no_ok[2]=pthread_create(&lector1,NULL,lector,NULL);
no_ok[3]=pthread_create(&lector2,NULL,lector,NULL);
pthread_join(escritor1,NULL);
pthread_join(escritor2,NULL);
pthread_join(lector1,NULL);
pthread_join(lector2,NULL);
pthread_cond_destroy(&oklector);
pthread_cond_destroy(&okescritor);
pthread_mutex_destroy(&mutex);
}
void *escritor(){
void empieza_escribir();
void termina_escribir();
int i;
for(i=0;i<10;i++){
empieza_escribir();
vcompartida++;
termina_escribir();
}
}
void *lector(){
void empieza_leer();
void termina_leer();
int i;
for(i=0;i<10;i++){
empieza_leer();
printf("%d\n",vcompartida);
termina_leer();
}
}
void empieza_escribir()
{
pthread_mutex_lock(&mutex);
if(nescritores>0 || nlectores>0) pthread_cond_wait(&oklector,&mutex);
nescritores++;
pthread_mutex_unlock(&mutex);
}
void termina_escribir()
{
pthread_mutex_lock(&mutex);
nescritores--;
if(nlectores>0) pthread_cond_broadcast(&oklector);
  else pthread_cond_signal(&okescritor);
pthread_mutex_unlock(&mutex);
}
void empieza_leer()
{
pthread_mutex_lock(&mutex);
if(nescritores>0) pthread_cond_wait(&oklector,&mutex);
nlectores--;
pthread_mutex_unlock(&mutex);
}
void termina_leer()
{
pthread_mutex_lock(&mutex);
if(nescritores>0 && (--nlectores)==0) pthread_cond_signal(&okescritor);
pthread_mutex_unlock(&mutex);
}

