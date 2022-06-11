/* Implementacion de las primitivas sobre semaforos */

/* Se proporcionan las primitivas siguientes:
 *    SEMAFORO sem_create(valor_inicial)
 *    int sem_wait(SEMAFORO s) 
 *    int sem_signal(SEMAFORO s)
 *    int sem_delete(SEMAFORO s)
*/

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <errno.h>
# include "semaforo.h"

SEMAFORO sem_create(int v){
  /* crea un semaforo, con valor inicial v. Retorna el identificador   */
  static int obten_sem();  /* Rutina para obtener id. de semaforo nuevo */
  union semun arg;         /* Para inicializarlo                        */
  int semid;               /* ID de semaforo                            */

  semid = obten_sem(); 
  if (semid < 0){ return semid; } /* ERROR, no pudo obtenerse el semaforo */

  /* La asigna el valor inicial */
  arg.val = v; /* valor inicial */
  if (semctl(semid, 0, SETVAL, arg) <0){ return -1; }
                                /* No pudo inicializarse */
  return semid;
}

int sem_wait(SEMAFORO s){
  /* Ejecuta un wait sobre el semaforo s */

  struct sembuf sembuf; /* Para indicar la operacion */

  sembuf.sem_op = WAIT;
  sembuf.sem_flg = 0;
  sembuf.sem_num = 0;
  if (semop(s, &sembuf, 1) < 0){ return -1;} /* ERROR */
  return 1;
}


int sem_signal(SEMAFORO s){
  /* Ejecuta un signal sobre el semaforo s */

  struct sembuf sembuf;

  sembuf.sem_op = SIGNAL;
  sembuf.sem_flg = 0;
  sembuf.sem_num = 0;
  if (semop(s, &sembuf, 1) < 0){ return -1; } /* ERROR */
  return 1;
}

int sem_delete(SEMAFORO s){
  /* Borra el semaforo s */

  union semun arg; /* No usado */
  semctl(s, 0, IPC_RMID, arg);
  return 1;
}

static int obten_sem(){
   /* Busca un semaforo disponible */
   key_t clave;
   int semid;

   for (clave = 2; clave < 1000; clave++)
       {
	 semid = semget(clave, 1, 0660 | IPC_CREAT | IPC_EXCL);
	 if (semid >= 0) return semid;
       }
   return -1; /* Ninguno disponible */
}

