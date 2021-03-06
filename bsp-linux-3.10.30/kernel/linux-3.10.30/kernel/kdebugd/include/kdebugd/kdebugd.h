/*
 * kdebugd.h
 *
 * Copyright (C) 2009 Samsung Electronics
 * Created by lee jung-seung (js07.lee@samsung.com)
 *
 * NOTE:
 *
 */

#ifndef __KDEBUGD_H__
#define __KDEBUGD_H__

#include<linux/sched.h>
#include <linux/elf.h>


#define DEBUGD_MAX_EVENTS			(64)
#define DEBUG_MAX_RAW_CHARS			(128)
#define DEBUGD_MAX_CHARS			((int)64)
#define KDEBUGD_STRING	"kdebugd"

/* Input is received as a string. */
struct sec_kdbg_input_event {
    /* null terminated string */
    char input_string[DEBUGD_MAX_CHARS];
};


/*
 * Events (results of Get Kdebugd Event)
 */

typedef struct sec_kdbg_input_event debugd_event_t;
struct debugd_queue {
	unsigned int            event_head;
	unsigned int            event_tail;
	debugd_event_t		events[DEBUGD_MAX_EVENTS];
};

/* Defined in driver/tty/n_tty.c for handling kdebugd serial inputs */
extern char kdbg_buf[DEBUG_MAX_RAW_CHARS];

typedef enum {
	KDBG_TAB_NO_ACTION = 1,
#ifndef CONFIG_KDEBUGD_FTRACE
	KDBG_TAB_SHOW_TASK
#else
	KDBG_TAB_SHOW_TASK,
	KDBG_TAB_FTRACE
#endif
} KDBG_TAB_ACTION;

/* Get action executed on pressing TAB key */
KDBG_TAB_ACTION kdbg_get_tab_action(void);
/* Set action executed on pressing TAB key */
void kdbg_set_tab_action(KDBG_TAB_ACTION action);

/* What to do when you press enter key from kdebugd. */
void kdbg_enter_action(void);

/* handle special cases of enter key from kdebugd */
void kdbg_enter_special_action(void);

/* Displays current pids and task names to choose from */
void kdbg_tab_action(void);

/* Handle multiple threads with similar names */
long kdbg_tab_process_event(debugd_event_t *event);

/* enum for kdebugd menu num */
typedef enum {
	KDBG_MENU_SHOW_TASK_STATE = 1,
	KDBG_MENU_SHOW_TASK_PRIORITY,
	KDBG_MENU_TASK_STATE_BACKTRACE,
	KDBG_MENU_TASK_FOR_COREDUMP,
	KDBG_MENU_SHOW_CPU_USAGE,
	KDBG_MENU_VIRTUAL_TO_PHYSICAL,
	KDBG_MENU_SHOW_USER_THREAD_REGS,
	KDBG_MENU_SHOW_USER_MAPS_WITH_PID,
	KDBG_MENU_SHOW_USER_STACK_WITH_PID,
	KDBG_MENU_SHOW_USER_STACK_BACKTRACE,
	KDBG_MENU_DUMP_SYMBOL_USER_STACK,
	KDBG_MENU_FUTEX,
#ifdef CONFIG_KDEBUGD_FTRACE
	KDBG_MENU_FTRACE,
#endif /* CONFIG_KDEBUGD_FTRACE */
	KDBG_MENU_MEMORY_VALIDATOR,
	KDBG_MENU_TRACE_THREAD_PC,
	KDBG_MENU_SCHED_HISTORY,
	KDBG_MENU_COUNTER_MONITOR,
	KDBG_MENU_COUNTER_MONITOR_CPU_USAGE,
	KDBG_MENU_COUNTER_MONITOR_EACH_THREAD,
	KDBG_MENU_COUNTER_MONITOR_DISK_USAGE,
#ifdef CONFIG_CACHE_ANALYZER
	KDBG_MENU_COUNTER_MONITOR_PMU_EVENTS,
#endif
	KDBG_MENU_COUNTER_MONITOR_MEMORY_USAGE,
	KDBG_MENU_COUNTER_MONITOR_NETWORK_USAGE,
	KDBG_MENU_COUNTER_MONITOR_CPU_FREQ,
	KDBG_MENU_ELF,
	KDBG_MENU_AOP,
	KDBG_MENU_DTVLOGD_LOG,
	KDBG_MENU_MEM_DBG,
	KDBG_MENU_KEY_TEST_PLAYER,
#ifdef CONFIG_KDEBUGD_PRINT_ONOFF
	KDBG_MENU_PRINT_ONOFF,
#endif
	KDBG_MENU_FD_DEBUG,
	KDBG_MENU_KDBG_CONFIG,
#ifdef CONFIG_KDML
	KDBG_MENU_KDML,
#endif
	KDBG_MENU_MAX
} KDBG_MENU_NUM;

int kdbg_get_task_status(void);

#ifdef CONFIG_KDEBUGD_FUTEX
struct futex_waiter {
	int hash_key;
	int wait_msec;
	struct task_struct *task;
};
#endif

struct aop_register {
	int (*aop_is_oprofile_init) (void);
	int (*aop_oprofile_start) (void);
	void  (*aop_oprofile_stop) (void);
	int (*aop_event_buffer_open) (void **dcookie_user_data);
	ssize_t  (*aop_read_event_buffer) (unsigned long *buf,
		unsigned long *size);
	void (*aop_event_buffer_clear) (void);
	int (*aop_clear_cpu_buffers) (void);
	void (*aop_wake_up_buffer_waiter) (void);
	void (*aop_dcookie_release) (void *dcookie_user_data);
	int (*aop_get_pc_sample_count)(void);
	void (*aop_reset_pc_sample_count)(void);
	unsigned long aop_oprofile_buffer_size;
};

/*Create the linked list while the task are getting killed.
 * This creation is done at the time when the task is about to
 * die and not at the processing time of raw data. This is
 * because at the processing time, some threads/processes
 * might be cleaned up(dead) and doesn't have any task_struct for them.*/
extern void aop_create_dead_list(struct task_struct *tsk);

extern struct kdbg_mem_watch  kdbg_mem_watcher;

extern unsigned int kdebugd_running;
#ifdef CONFIG_KDEBUGD_BG
extern unsigned int kdbg_mode;
#endif
extern struct debugd_queue kdebugd_queue;
int kdebugd_start(void);
void queue_add_event(struct debugd_queue *q, debugd_event_t *event);

unsigned long kdbg_get_uptime(void);
unsigned long kdbg_get_uptime_ms(void);

long debugd_get_event_as_numeric(debugd_event_t *event, int *is_number);
void debugd_get_event(debugd_event_t *event);
int kdbg_register(char *name, int (*func)(void), void (*turnoff)(void), KDBG_MENU_NUM menu_idx);
int kdbg_unregister(KDBG_MENU_NUM menu_idx);

void task_state_help(void);

struct task_struct *find_user_task_with_pid(void);

int kdebugd_status(void);

#ifdef CONFIG_TASK_STATE_BACKTRACE
void kdbg_unwind_mem_stack_kernel(const char *str, unsigned long bottom, unsigned long top);
#endif

int kdbg_elf_chk_machine_type(Elf32_Ehdr Ehdr);

int kdbg_chk_pfn_valid(unsigned long pfn);
int kdbg_chk_vaddr_valid(void *addr);

void kdbg_dump_mem(const char *str, unsigned long bottom, unsigned long top);

#ifdef CONFIG_KDEBUGD_FUTEX
extern int read_hash_queue (struct futex_waiter *waiter_array, const int max_waiters, int wait_msec);
#endif

/* Look up the first VMA which satisfies  addr < vm_end,  NULL if none. */
struct vm_area_struct*
find_vma2(struct mm_struct *mm, unsigned long addr);

int status_sched_history(void);

void sched_history_OnOff(void);

struct task_struct *get_task_with_given_pid(pid_t pid);

int show_sched_history(void);

int show_state_prio(void);
void wrap_show_task(struct task_struct *);

struct aop_register *aop_alloc(void);
void aop_dealloc(void);

#ifdef CONFIG_CACHE_ANALYZER
/* Mode of sampling */
enum aop_sample_mode {
	TIMER_SAMPLING,
	PERF_EVENTS_SAMPLING,
	INVALID_SAMPLING_MODE
};

int aop_get_sampling_mode(void);
int aop_switch_to_timer_sampling(void);
int aop_switch_to_perf_events_sampling(void);
#endif

extern int aop_is_oprofile_init (void);
/* Copy event buffer data to aop buffer */
extern ssize_t aop_read_event_buffer(unsigned long *buf, unsigned long *size);

/* Open event & cpu buffer to setup oprofile */
extern int aop_event_buffer_open(void **dcookie_user_data);

/* Clear the even buffer and set the writing position to zero */
extern void aop_event_buffer_clear(void);

/* clear the cpu buffer after stop the oprofile,
as we don't shutdown the oprofile while stop, we must clear the cpu buffer */

extern int aop_clear_cpu_buffers(void);

/* Wake up the waiting process if any. This happens
 * on "echo 0 >/dev/oprofile/enable" so the daemon
 * processes the data remaining in the event buffer.
 */
extern void aop_wake_up_buffer_waiter(void);

/* get the vale of pc sample Count */
extern int aop_get_pc_sample_count(void);

#ifdef CONFIG_CACHE_ANALYZER
/* increment the vale of pc sample Count */
extern void aop_inc_pc_sample_count(void);
#endif

/* reset the PC sample count to zero */
extern void aop_reset_pc_sample_count(void);

/* release the oprofile module by removing the oprofile module */
extern void aop_release(void);


#ifdef CONFIG_KDEBUGD_AGENT_SMACK_DISABLE
extern unsigned long kdbg_smack_enable;
int kdbg_smack_control(void);
int kdbg_smack_conf_read(struct file *pfile,
		char __user *buffer, size_t count, loff_t *offset);

int kdbg_smack_conf_write(struct file *file,
		const char __user *buffer, size_t count, loff_t *data);
#endif
#if defined(CONFIG_KDEBUGD_MISC) && defined(CONFIG_SCHED_HISTORY)
extern void schedule_history(struct task_struct *next, int cpu);
#endif

struct kdbg_mem_watch {
    unsigned int pid;
    unsigned int tgid;
    unsigned int u_addr;
    unsigned int buff;
    unsigned int watching;
};

#ifdef CONFIG_KDEBUGD_MISC
	extern unsigned int kdebugd_nobacktrace;
#endif

#ifdef CONFIG_KDGB_SUPPRESS_PRINTK
extern int kdbg_outside_print;
#define PRINT_KD_STR     "<D>"
#else
#define PRINT_KD_STR
#endif

#define  PRINT_KD(fmt , args ...)  	 printk(PRINT_KD_STR fmt, ##args)

#ifdef CONFIG_KDEBUGD_COUNTER_MONITOR
typedef int (*counter_monitor_func_t)(void);

int register_counter_monitor_func(counter_monitor_func_t func);

int unregister_counter_monitor_func (counter_monitor_func_t func);

/* States ---*/
typedef enum {
	E_NONE = 0,
	E_INITIALIZED,
	E_RUNNING,
    E_RUN_N_PRINT,
	E_DESTROYING,
    E_DESTROYED
} sec_counter_mon_state_t;

typedef enum {
	ERR_INVALID = 0,
	ERR_NO_MEM,
	ERR_DUPLICATE,
	ERR_INVALID_ARG,
	ERR_NOT_SUPPORTED
} sec_counter_mon_error_t;

#ifdef CONFIG_KDEBUGD_PRINT_ONOFF
int kdbg_printf_status(void);
int kdbg_print_enable(void);
#endif

#endif

#ifdef CONFIG_KDEBUGD_FD_DEBUG
int kdbg_fd_debug_handler(void);
int kdbg_fd_debug_status(void);
#endif

#ifdef CONFIG_ADVANCE_OPROFILE
extern  void kdbg_aop_user_backtrace(struct pt_regs * const regs, unsigned int depth);
#endif

#ifdef CONFIG_KDEBUGD_HUB_DTVLOGD
extern int dtvlogd_buffer_printf(void);
#endif

#endif	/* __KDEBUGD_H__ */
