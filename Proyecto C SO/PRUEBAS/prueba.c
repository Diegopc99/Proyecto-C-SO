#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

void prueba1(void);
void prueba2(void);
void prueba3(void);
void prueba4(void);
void prueba5(void);
void prueba6(void);
void prueba7(void);
void prueba8(void);
void prueba9(void);
void prueba10(void);
void prueba11(void);
void prueba12(void);
void prueba13(void);

int main(int argc, char *argv[]){
    int numeroPrueba = 0;
    numeroPrueba = atoi(argv[1]);

    
    struct sched_param nodo;
    nodo.sched_priority=99;
    if(sched_setscheduler(0,SCHED_FIFO, &nodo)!=0){
        printf("Error creando el proceso de batería de pruebas\n");
        printf("Saliendo de la aplicación de baterías...\n");
        return 0;
    }
    
    
    switch (numeroPrueba)
    {
    case 1:
        prueba1();
        break;
    case 2:
        prueba2();
        break;
    case 3:
        prueba3();
        break;
    case 4:
        prueba4();
        break;
    case 5:
        prueba5();
        break;
    case 6:
        prueba6();
        break;
    case 7:
        prueba7();
        break;
    case 8:
        prueba8();
        break;
    case 9:
	prueba9();
	break;
    case 10:
	prueba10();
	break;
    case 11:
	prueba11();
	break;
    case 12:
	prueba12();
	break;
    case 13:
	prueba13();
	break;
    default:
        printf("No ha seleccionado un número de prueba válida\n");
        break;
    }

    printf("FIN DE LA BATERIA DE PRUEBAS\n");
    return 0;

}

// Se encolan 2 procesos de ADMIN y 2 de EVENTOS

// Resultado: saldrá por pantalla el fin de ejecución de los procesos FIFO (ADMIN1 y ADMIN2)
// e inmediatamente después los de consulta RR (EVENTOS1 y EVENTOS2)

void prueba1(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 1     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i=0;
    int error;

    for(i = 0; i<2; i++){
    	error=fork();
    	if(error<0){
      	  printf("Error creando el proceso fork 1\n");
        	printf("Saliendo de la aplicación de pruebas...\n\n");
        	return;
    	}
    	if(error==0){
        	if(execve("ADMIN", NULL, NULL)<0){
        	    printf("Error creando el proceso de ADMIN %i\n", i);
       		}else{
        	    printf("Éxito creando el proceso de ADMIN %i\n", i);
        	}
    	}
    }

    for(i = 0; i<2; i++){

    	error=fork();
    	if(error<0){
        	printf("Error creando el proceso fork 2\n");
        	printf("Saliendo de la aplicación de pruebas...\n\n");
        	return;
    	}

    	if(error==0){
        	if(execve("EVENTOS", NULL, NULL)<0){
          		printf("Error creando el proceso de EVENTOS %i\n", i);
        	}else{
            		printf("Éxito creando el proceso de EVENTOS %i\n", i);
        	}
    	}
    }

    for(i = 0; i<5; i++){
        wait(5);
    }

    return;
}


// Introducimos en el sistema por orden dos procesos de PAGOS y dos de ADMIN

// Resultado: se muestra por pantalla el fin de ejecución de los procesos
// por orden de llegada al sistema (ADMIN1 - ADMIN2 - PAGOS1 - PAGOS2)

void prueba2(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 2     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    for(i = 0; i<2; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("PAGOS", NULL, NULL)<0){
                printf("Error creando el proceso de PAGOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PAGOS %i\n", i);
            }
        }
    }

    for(i = 0; i<2; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
        }
    }

    for(i=0;i<10;i++){
        wait(5);
    }

    return;
}

// Introducimos en el sistema 7 procesos de GRADAS, 3 de PAGOS, y uno de ADMIN

// Resultado: se muestra por pantalla la expulsión del sistema de un proceso víctima
// (uno de GRADAS) y el fin de ejecución de ADMIN - 3xPAGOS - 6xGRADAS en ese orden

void prueba3(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 3     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    for(i = 0; i<7; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }
    }

    for(i = 0; i<3; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("PAGOS", NULL, NULL)<0){
                printf("Error creando el proceso de PAGOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PAGOS %i\n", i);
            }
        }
    }

    error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
        }    

    for(i=0;i<11;i++){
        wait(11);
    }

    return;
}

// Introducimos en el sistema 7 procesos de GRADAS, 3 de PAGOS, y 1 de GRADAS

// Resultado: se muestra por pantalla la expulsión del sistema de GRADAS por no entrar
// en el sistema al no ser prioritario y finaliza la ejecución de los diez primeros
// (3xPAGOS - 7xGRADAS)

void prueba4(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 4     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    for(i = 0; i<7; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }
    }

    for(i = 0; i<3; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("PAGOS", NULL, NULL)<0){
                printf("Error creando el proceso de PAGOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PAGOS %i\n", i);
            }
        }
    }

    error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }    

    for(i=0;i<11;i++){
        wait(11);
    }

    return;
}


// Introducimos en el sistema 1 proceso de EVENTOS que supera el tiempo maximo del sistema

// Resultado: se echará del sistema por superar el tiempo maximo mostrando el mensaje por pantalla:
// "Tiempo de vida máximo del proceso con PID X (nombre EVENTOS - con tiempo 10) expirado. Eliminando 
// proceso..."
void prueba5(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 5     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("EVENTOS", NULL, NULL)<0){
                printf("Error creando el proceso de EVENTOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de EVENTOS %i\n", i);
            }
    }

    for(i=0;i<10;i++){
        wait(10);
    }
 

    return;
}

// Introducimos en el sistema 6 procesos de GRADAS y 2 de ADMIN

// RESULTADO: comprobamos tras introducir el 7o proceso que el sistema informa de cierto nivel de saturacion
// (supera el umbral de saturacion - 7 procesos pero siguen entrando procesos prioritarios)
// y finaliza los procesos de forma controlada
// (2xADMIN - 6xGRADAS)

void prueba6(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 6     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    for(i = 0; i<6; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }
    }

    for(i = 0; i<2; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
        }
    }

    for(i=0;i<9;i++){
        wait(9);
    }

    return;
}



// Introducimos en el sistema 7 procesos de GRADAS y 1 de EVENTOS

// RESULTADO: comprobamos tras introducir el 7 proceso que el sistema informa de cierto nivel de
// saturacion y el proceso de EVENTOS no entra al sistema. Se muestra por pantalla el mensaje:
// " Proceso actual de inferior prio a pagos: No se anade proceso"
void prueba7(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 7     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

    for(i = 0; i<7; i++){
        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }
    }

        error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("EVENTOS", NULL, NULL)<0){
                printf("Error creando el proceso de EVENTOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de EVENTOS %i\n", i);
            }
        }


    for(i=0;i<9;i++){
        wait(9);
    }

    return;
}


// Introducimos en el sistema 6 procesos en el sistema, uno de cada tipo en este orden:
// ANULACIONES PRERESERVAS GRADAS EVENTOS PAGOS ADMIN
// RESULTADO: comprobamos tras introducir los 6 procesos que ADMIN y PAGOS se ejecutan
// primero siguiendo la politica FIFO y a continuacion los de RR con sus correspondientes
// mensajes de finalizacion de ejecucion

void prueba8(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 8     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;

        

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("ANULACIONES", NULL, NULL)<0){
                printf("Error creando el proceso de ANULACIONES %i\n", i);
            }else{
                printf("Éxito creando el proceso de ANULACIONES %i\n", i);
            }
        }

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("PRERESERVAS", NULL, NULL)<0){
                printf("Error creando el proceso de PRERESERVAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PRERESERVAS %i\n", i);
            }
        }

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
        }

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("EVENTOS", NULL, NULL)<0){
                printf("Error creando el proceso de EVENTOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de EVENTOS %i\n", i);
            }
        }

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
        }
        if(error==0){
            if(execve("PAGOS", NULL, NULL)<0){
                printf("Error creando el proceso de PAGOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PAGOS %i\n", i);
            }
        }

	error=fork();
        if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");

            return;
        }
        if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
        }

	for(i=0;i<6;i++){
        wait(6);
    	}
   

    return;
}


// Introducimos en el sistema 11 procesos de ADMIN, el último no entra ya que uno de ADMIN no echa
// a otro

// Resultado: el último creado no entra en el sistema y se finaliza la ejecucion de los 10xADMIN

void prueba9(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*       INICIO DE LA PRUEBA 9     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;
	
    for(i=0;i<11;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
    }
    }

    for(i=0;i<12;i++){
        wait(12);
    }
 

    return;
}

// Introducimos en el sistema 5 procesos de ADMIN y uno de EVENTOS que supera el tiempo
// máximo de alojamiento en el sistema

// Resultado: el último creado entra en el sistema  pero caduca y es expulsado

void prueba10(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*      INICIO DE LA PRUEBA 10     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;
	
    for(i=0;i<5;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
    }
    }

    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("EVENTOS", NULL, NULL)<0){
                printf("Error creando el proceso de EVENTOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de EVENTOS %i\n", i);
            }
    }



    for(i=0;i<7;i++){
        wait(7);
    }
 

    return;
}


// Introducimos en el sistema 4 procesos de consulta:
// 2 de EVENTOS y 2 de GRADAS en ese orden

// Resultado: los cuatro procesos se encolan y se ejecutan siguiendo la politica RR

void prueba11(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*      INICIO DE LA PRUEBA 11     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;
	
    for(i=0;i<2;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("EVENTOS", NULL, NULL)<0){
                printf("Error creando el proceso de EVENTOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de EVENTOS %i\n", i);
            }
    }
    }
    
    for(i=0;i<2;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("GRADAS", NULL, NULL)<0){
                printf("Error creando el proceso de GRADAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de GRADAS %i\n", i);
            }
    }
    }



    for(i=0;i<5;i++){
        wait(5);
    }
 

    return;
}


// Introducimos en el sistema 10 procesos de PAGOS y 1 de ADMIN

// Resultado: a pesar de estar congestionado, el sistema no aceptará el proceso de ADMIN 
// por no haber una víctima de un proceso no prioritario (EVENTOS - GRADAS - PRERESERVAS) y por tanto se ejecutarán 10 PAGOS

void prueba12(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*      INICIO DE LA PRUEBA 12     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;
	
    for(i=0;i<10;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("PAGOS", NULL, NULL)<0){
                printf("Error creando el proceso de PAGOS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PAGOS %i\n", i);
            }
    }
    }
    
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
    }




    for(i=0;i<13;i++){
        wait(13);
    }
 

    return;
}

// Introducimos en el sistema 9 procesos de ANULACIONES, 1 de PRERESERVAS y 1 de ADMIN

// Resultado: a pesar de estar congestionado, el sistema aceptará el proceso de ADMIN 
// ya que ANULACIONES es un proceso víctima para que pueda entrar ADMIN
void prueba13(void){
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*      INICIO DE LA PRUEBA 13     *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    int i;
    int error;
	
    for(i=0;i<9;i++){
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("ANULACIONES", NULL, NULL)<0){
                printf("Error creando el proceso de ANULACIONES %i\n", i);
            }else{
                printf("Éxito creando el proceso de ANULACIONES %i\n", i);
            }
    }
    }
    
    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("PRERESERVAS", NULL, NULL)<0){
                printf("Error creando el proceso de PRERESERVAS %i\n", i);
            }else{
                printf("Éxito creando el proceso de PRERESERVAS %i\n", i);
            }
    }

    error=fork();
    if(error<0){
            printf("Error creando el proceso fork\n");
            printf("Saliendo de la aplicación de pruebas...\n\n");
            return;
    }
    if(error==0){
            if(execve("ADMIN", NULL, NULL)<0){
                printf("Error creando el proceso de ADMIN %i\n", i);
            }else{
                printf("Éxito creando el proceso de ADMIN %i\n", i);
            }
    }




    for(i=0;i<11;i++){
        wait(11);
    }
 

    return;
}
