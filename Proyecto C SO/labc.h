#include <linux/sched.h>
#include <linux/string.h>
#include <linux/signal.h>  //Definicion de kill_pid()
#include <asm/cputime.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/list.h>

#define PRIORIDAD_ADMIN 1
#define PRIORIDAD_PAGOS 2
#define PRIORIDAD_ANULACIONES 3
#define PRIORIDAD_PRERESERVAS 4
#define PRIORIDAD_GRADAS 5
#define PRIORIDAD_EVENTOS 6
#define PRIORIDAD_DEFECTO -1

int crear_proceso(struct task_struct*);

int matar_proceso(struct task_struct*);

void estado_proceso (void);

int buscar_victima(int);

int comprobar_timer(void);

int buscar_bloqueados(void);

int actualizar_contaje_colas(struct task_struct*);

int comprobacion(struct task_struct*);


