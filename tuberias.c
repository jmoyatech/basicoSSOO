#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
 
 #define PROPI 0
 #define SISTEMA 1
  
  void escriure_error (char *miss,int tipus);
  void manejador1(int);
   
   int main (int argc,char *argv[]){
   int contador, tubo1[2],tubo2[2],pid;
   pipe (tubo1);
   pipe (tubo2);
   contador=0;
   char buff[100];
   char temp[100];
    
    	if (signal (SIGINT, manejador1) == SIG_ERR){
    			perror ("No se puede cambiar signal");
    				}
    				 
    				  
    				   
    				   	if (argc>2) escriure_error("Error de Parametros, mas de los debidos!!!\n",PROPI);
    				   		if (argc==1) escriure_error("Error de Parametros debes indicar el nombre del proceso a ejecutar\n",PROPI);
    				   			pid=fork();
    				   				if (pid<0) escriure_error("Error al crear al hijo\n",PROPI);
    				   					if (pid>0){
    				   						close(tubo1[0]);
    				   							close(tubo2[1]);
    				   								write(tubo1[1],&contador,sizeof(contador));
    				   										while(1){
    				   												read(tubo2[0],&contador,sizeof(contador));
    				   															sprintf(buff,"contador %d\n",contador);
    				   																		write(1,buff,strlen(buff));
    				   																					contador++;
    				   																							write(tubo1[1],&contador,sizeof(contador));
    				   																									}
    				   																										}
    				   																											else{
    				   																											 
    				   																											 		close(tubo1[1]);
    				   																											 				close(tubo2[0]);
    				   																											 				 
    				   																											 				 		/*close(0);
    				   																											 				 		                dup(tubo1[0]);
    				   																											 				 		                                close(1);
    				   																											 				 		                                                dup(tubo2[1]);*/
    				   																											 				 		                                                 
    				   																											 				 		                                                 		dup2(tubo1[0],0);
    				   																											 				 		                                                 				dup2(tubo2[1],1);
    				   																											 				 		                                                 				 
    				   																											 				 		                                                 				 		strcpy (temp, "./");
    				   																											 				 		                                                 				 				strcat (temp, argv[1]);
    				   																											 				 		                                                 				 				 
    				   																											 				 		                                                 				 				 		execlp(temp,"pong",NULL);
    				   																											 				 		                                                 				 				 				//execlp("./2","pong",NULL);
    				   																											 				 		                                                 				 				 					}
    				   																											 				 		                                                 				 				 					 
    				   																											 				 		                                                 				 				 					  
    				   																											 				 		                                                 				 				 					  }
    				   																											 				 		                                                 				 				 					   
    				   																											 				 		                                                 				 				 					   void escriure_error(char *miss, int tipus){
    				   																											 				 		                                                 				 				 					   	char buff[100];
    				   																											 				 		                                                 				 				 					   	 
    				   																											 				 		                                                 				 				 					   	 	if (tipus == PROPI) sprintf(buff, "%s\n", miss);
    				   																											 				 		                                                 				 				 					   	 		else sprintf(buff,"%s: %s\n", miss, strerror(errno));
    				   																											 				 		                                                 				 				 					   	 		 
    				   																											 				 		                                                 				 				 					   	 		 	write(2, buff, strlen(buff));
    				   																											 				 		                                                 				 				 					   	 		 		exit(1);
    				   																											 				 		                                                 				 				 					   	 		 		}
    				   																											 				 		                                                 				 				 					   	 		 		 
    				   																											 				 		                                                 				 				 					   	 		 		  
    				   																											 				 		                                                 				 				 					   	 		 		  void manejador1(int numero){
    				   																											 				 		                                                 				 				 					   	 		 		  	//signal(SIGINT,SIG_DFL);
    				   																											 				 		                                                 				 				 					   	 		 		  		printf("Hemos entrado en el manejador 1\n");
    				   																											 				 		                                                 				 				 					   	 		 		  		 
    				   																											 				 		                                                 				 				 					   	 		 		  		 }