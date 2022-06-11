#include <stdio.h>
#include <pthread.h>
#include <string.h>
struct DATOS
  {
  int c1;
  int c2;
  };
pthread_mutex_t m;
main()
{
void *rutina();
void *rutina2();
int no_ok,mutex;
struct DATOS shared_data;
pthread_t hilo1,hilo2;
mutex=pthread_mutex_init(&m,NULL);
no_ok=pthread_create(&hilo1,NULL,rutina,&shared_data);
no_ok=pthread_create(&hilo2,NULL,rutina2,&shared_data);
pthread_join(hilo1,NULL);
pthread_join(hilo2,NULL);
pthread_mutex_destroy(&m);
}
void *rutina(struct DATOS *p)
  {
  int o,k;
  o=pthread_mutex_lock(&m);
  p->c1=69;
  p->c2=96;
  printf("para el primer hilo c1=%d c2=%d\n",p->c1,p->c2);
  k=pthread_mutex_unlock(&m);
  pthread_exit(0);
  }
void *rutina2(struct DATOS *p)
  {
  int o,k;
  o=pthread_mutex_lock(&m);
  p->c1=101;
  p->c2=1010;
  printf("para el segundo hilo c1=%d c2=%d\n",p->c1,p->c2);
  k=pthread_mutex_unlock(&m);
  pthread_exit(0);
  }

