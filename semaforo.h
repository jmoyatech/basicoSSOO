/* fichero semaforo.h */


# define SIGNAL              1
# define WAIT               -1
# define TRUE                1
# define FALSE               0

typedef int SEMAFORO;

/* Primitivas: */
extern SEMAFORO sem_create(int valor_inicial);
extern int sem_wait(SEMAFORO s);
extern int sem_signal(SEMAFORO s);
extern int sem_delete(SEMAFORO s);

/* Estructuras de datos a utilizar: */
union semun {
  int val;                    /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};

                                                                         