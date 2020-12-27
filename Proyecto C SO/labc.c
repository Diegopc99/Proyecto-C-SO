#include <linux/labc.h> 

#define T_MAX 10
#define UMBRAL 7

//#define PRIORIDAD_ADMIN 1
//#define PRIORIDAD_PAGOS 2
//#define PRIORIDAD_ANULACIONES 3
//#define PRIORIDAD_PRERESERVAS 4
//#define PRIORIDAD_EVENTOS 6
//#define PRIORIDAD_GRADAS 5
//#define PRIORIDAD_DEFECTO -1

int n_procesos_admin = 0;
int n_procesos_pagos = 0;
int n_procesos_anulaciones = 0;
int n_procesos_prereservas = 0;
int n_procesos_eventos = 0;
int n_procesos_gradas = 0;


int crear_proceso(struct task_struct *tsk){

	int error = 0;
	int cola;

	if(strcmp(tsk->comm,"ADMIN")==0){
		tsk->tipo = PRIORIDAD_ADMIN;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_admin++;
			struct sched_param param;
			param.sched_priority = 90;
			cola=SCHED_FIFO;
			error = sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de administracion creado.\n");
			}
			
		}else{
			n_procesos_admin++;
			printk("No se puede crear el proceso de administracion.\n");
			tsk->tipo = PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}
	}

	if(strcmp(tsk->comm,"PAGOS")==0){
		tsk->tipo = PRIORIDAD_PAGOS;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_pagos++;
			struct sched_param param;
			param.sched_priority = 80;
			cola=SCHED_FIFO;
			error=sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de pago creado.\n");
			}
		}else{
			n_procesos_pagos++;
			printk("No se puede crear el proceso de pago.\n");
			tsk->tipo = PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}
	}


	if(strcmp(tsk->comm,"ANULACIONES")==0){
		tsk->tipo = PRIORIDAD_ANULACIONES;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_anulaciones++;
			struct sched_param param;
			param.sched_priority = 70;
			cola=SCHED_RR;
			error=sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de anulacion creado.\n");
			}
		}else{
			n_procesos_anulaciones++;
			printk("No se puede crear el proceso de anulacion.\n");
			tsk->tipo =PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}
	}

	if(strcmp(tsk->comm,"PRERESERVAS")==0){
		tsk->tipo = PRIORIDAD_PRERESERVAS;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_prereservas++;
			struct sched_param param;
			param.sched_priority = 60;
			cola=SCHED_RR;
			error=sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de pre-reservas creado.\n");
			}
		}else{
			n_procesos_prereservas++;
			printk("No se puede crear el proceso de pre-reservas y reservas.\n");
			tsk->tipo =PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}
	}

	if(strcmp(tsk->comm,"EVENTOS")==0){
		tsk->tipo = PRIORIDAD_EVENTOS;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_eventos++;
			struct sched_param param;
			param.sched_priority = 40;
			cola=SCHED_RR;
			error=sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de eventos creado.\n");
			}
		}else{
			n_procesos_eventos++;
			printk("No se puede crear el proceso de eventos.\n");
			tsk->tipo =PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}	
	}

	if(strcmp(tsk->comm,"GRADAS")==0){
		tsk->tipo = PRIORIDAD_GRADAS;
		
		if(comprobacion(tsk) == 0 ){ ///Comprobamos si se pueden o no anadir procesos
			
			n_procesos_gradas++;
			struct sched_param param;
			param.sched_priority = 50;
			cola=SCHED_RR;
			error=sched_setscheduler(tsk,cola,&param);

			if(error==(-1)){
				printk("Error en el setscheduler.\n");
			}else{
				printk("Proceso de gradas creado.\n");
			}
		}else{
			n_procesos_gradas++;
			printk("No se puede crear el proceso de gradas.\n");
			tsk->tipo=PRIORIDAD_DEFECTO;
			matar_proceso(tsk);
		}
	}

	return 0;
}


int matar_proceso(struct task_struct *tsk){
	
	// int kill_pid(struct pid *pid, int sig, int priv); 
		
	if(tsk->tipo == PRIORIDAD_ADMIN || tsk->tipo == PRIORIDAD_PAGOS || tsk->tipo == PRIORIDAD_ANULACIONES || tsk->tipo == PRIORIDAD_PRERESERVAS || tsk->tipo == PRIORIDAD_EVENTOS ||tsk->tipo == PRIORIDAD_GRADAS || tsk->tipo == PRIORIDAD_DEFECTO){
	
		kill_pid(find_vpid(tsk->pid),SIGKILL,1);
		return 0;
	}

	return 1;
}


void estado_proceso(){
	
	printk("Numero de procesos de administracion: %i\n",n_procesos_admin);
	printk("Numero de procesos de pagos: %i\n",n_procesos_pagos);
	printk("Numero de procesos de anulaciones: %i\n",n_procesos_anulaciones);
	printk("Numero de procesos de pre-reservas: %i\n",n_procesos_prereservas);
	printk("Numero de procesos de gradas: %i\n",n_procesos_gradas);
	printk("Numero de procesos de eventos: %i\n",n_procesos_eventos);	
	
	return;
}


int buscar_victima(int prioridad){
	
	struct task_struct *tsk;

	for_each_process(tsk){
	
		if(tsk->tipo == PRIORIDAD_EVENTOS){
			matar_proceso(tsk);	
			printk("Se ha eliminado un proceso de eventos como victima de uno de admin.\n");
			return 0;
		}else{
			if(tsk->tipo == PRIORIDAD_GRADAS){
				matar_proceso(tsk);
				printk("Se ha eliminado un proceso de gradas como victima de uno de admin.\n");
				return 0;
			}else{
				if(tsk->tipo == PRIORIDAD_PRERESERVAS){
					matar_proceso(tsk);
					printk("Se ha eliminado un proceso de pre-reservas como victima de uno de admin.\n");
					return 0;
				}
			}
		}
	}
	
	
	return 1; /// Retorna un error, no hay ningun proceso que pueda ser sustituto
}

int comprobar_timer(){

	struct task_struct *tsk;
		
	for_each_process(tsk){

		if(tsk->tipo == PRIORIDAD_ADMIN || tsk->tipo == PRIORIDAD_PAGOS || tsk->tipo == PRIORIDAD_ANULACIONES || tsk->tipo == PRIORIDAD_PRERESERVAS || tsk->tipo == PRIORIDAD_EVENTOS ||tsk->tipo == PRIORIDAD_GRADAS){

			if(cputime_to_secs(tsk->utime) == 10){  // utime = tiempo de ususario acumulado por un proceso
				
				printk("Tiempo de vida maximo del proceso con pid %d (nombre %s, tiempo %lo) expirado, eliminando proceso...\n",tsk->pid, tsk->comm,cputime_to_secs(tsk->utime));
				tsk->tipo = PRIORIDAD_DEFECTO;
				matar_proceso(tsk);
			}
		}
	}
	
	return 0;

}


int buscar_bloqueados(){
	
	return 1;
}


int actualizar_contaje_colas(struct task_struct *tsk){

	long cpu_time = 0;	

	if(strcmp(tsk->comm,"ADMIN") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_admin = n_procesos_admin -1;
		printk("Actualizada la lista de procesos encolados: proceso de admin eliminado.\n");
		return 0;
	
	}else if(strcmp(tsk->comm,"PAGOS") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_pagos = n_procesos_pagos -1;
		printk("Actualizada la lista de procesos encolados: proceso de pagos eliminado.\n");
		return 0;
	
	}else if(strcmp(tsk->comm,"ANULACIONES") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_anulaciones = n_procesos_anulaciones -1;
		printk("Actualizada la lista de procesos encolados: proceso de anulaciones eliminado.\n");
		return 0;
	
	}else if(strcmp(tsk->comm,"PRERESERVAS") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_prereservas = n_procesos_prereservas -1;
		printk("Actualizada la lista de procesos encolados: proceso de pre-reservas eliminado.\n");
		return 0;
	
	}else if(strcmp(tsk->comm,"GRADAS") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_gradas = n_procesos_gradas -1;
		printk("Actualizada la lista de procesos encolados: proceso de gradas eliminado.\n");
		return 0;
	
	}else if(strcmp(tsk->comm,"EVENTOS") == 0){
	
		cpu_time = cputime_to_secs(tsk->utime);
		n_procesos_eventos = n_procesos_eventos -1;
		printk("Actualizada la lista de procesos encolados: proceso de eventos eliminado.\n");
		return 0;
	
	}
	return 1;
}


int comprobacion(struct task_struct *tsk){

	int total_procesos = n_procesos_admin + n_procesos_pagos + n_procesos_anulaciones + n_procesos_prereservas + n_procesos_eventos + n_procesos_gradas;
	int error = 0;
	
	if(total_procesos >= T_MAX){  //  UMBRAL < T_MAX < total_proceos
		
		if(strcmp(tsk->comm,"ADMIN") == 0){
		
			error = buscar_victima(tsk->tipo);		

			if(error == 1){

				printk("Error al encontrar una victima para encolar el proceso de admin.\n");
				return 1;
			}
			if(error == 0){
				////Exito al buscar victima y colocar el proceso de admin
				return 0;
			}
		}

		printk("UMBRAL < T_MAX < total_proceos | No se anade proceso.\n");
		return 1;

	}else{
		
		if(total_procesos < UMBRAL){  //  total_procesos < UMBRAL < T_MAX
			
			printk("total_procesos < UMBRAL < T_MAX | Anadiendo proceso....\n");
			return 0;

		}else{  //  UMBRAL < total_procesos < T_MAX

			if(strcmp(tsk->comm,"ADMIN") == 0){
				printk("UMBRAL < total_procesos < T_MAX | Proceso actual de admin: anadiendo proceso...\n");				
				return 0;
			}else if(strcmp(tsk->comm,"PAGOS") == 0){
				printk("UMBRAL < total_procesos < T_MAX | Proceso actual de pagos: anadiendo proceso...\n");
				return 0;
			}else if(strcmp(tsk->comm,"ANULACIONES") == 0){
				printk("UMBRAL < total_procesos < T_MAX | Proceso actual de anulaciones: anadiendo proceso...\n");
				return 0;
			}else{
				printk("UMBRAL < total_procesos < T_MAX | Proceso actual de inferior prio a anulaciones: No se anade proceso.\n");
				return 1;
			
			}
		}
	}
	 
}



