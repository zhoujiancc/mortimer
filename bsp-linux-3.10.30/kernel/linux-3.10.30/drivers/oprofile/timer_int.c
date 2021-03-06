/**
 * @file timer_int.c
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon <levon@movementarian.org>
 */

#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/smp.h>
#include <linux/oprofile.h>
#include <linux/profile.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/hrtimer.h>
#include <asm/irq_regs.h>
#include <asm/ptrace.h>

#include "oprof.h"


#ifdef CONFIG_ADVANCE_OPROFILE
#include <kdebugd/kdebugd.h>
#endif /* CONFIG_ADVANCE_OPROFILE */

#ifdef CONFIG_ADVANCE_OPROFILE
static atomic_t g_aop_pc_sample_count;
#endif /* CONFIG_ADVANCE_OPROFILE */


static DEFINE_PER_CPU(struct hrtimer, oprofile_hrtimer);
static int ctr_running;


#ifdef CONFIG_ADVANCE_OPROFILE
/* get the vale of pc sample Count */
int aop_get_pc_sample_count(void)
{
      return atomic_read(&g_aop_pc_sample_count);
}

#ifdef CONFIG_CACHE_ANALYZER
void aop_inc_pc_sample_count(void)
{
	atomic_inc(&g_aop_pc_sample_count);
}
#endif

/* reset the PC sample count to zero */
void  aop_reset_pc_sample_count(void)
{
      atomic_set(&g_aop_pc_sample_count, 0);
}

/* Change for 100us granularity */

#ifdef CONFIG_AOP_GRANULARITY_100us
#define AOP_100USEC (MSEC_PER_SEC * 10)
#define AOP_GRANULARITY  ((((NSEC_PER_SEC + AOP_100USEC/2)/AOP_100USEC)))
#elif defined(CONFIG_AOP_GRANULARITY_1ms)
#define AOP_GRANULARITY  (((NSEC_PER_SEC + MSEC_PER_SEC/2) / MSEC_PER_SEC))
#elif defined(CONFIG_AOP_GRANULARITY_4ms)
#define AOP_GRANULARITY  TICK_NSEC
#else
#define AOP_GRANULARITY  TICK_NSEC
#endif

#define AOP_TICK_TIME    (AOP_GRANULARITY)

#endif /* CONFIG_ADVANCE_OPROFILE */

static enum hrtimer_restart oprofile_hrtimer_notify(struct hrtimer *hrtimer)
{
	oprofile_add_sample(get_irq_regs(), 0);

#ifndef CONFIG_ADVANCE_OPROFILE
	hrtimer_forward_now(hrtimer, ns_to_ktime(TICK_NSEC));
#else
	hrtimer_forward_now(hrtimer, ns_to_ktime(AOP_TICK_TIME));
	atomic_inc(&g_aop_pc_sample_count);
#endif/* CONFIG_ADVANCE_OPROFILE */

	return HRTIMER_RESTART;
}

static void __oprofile_hrtimer_start(void *unused)
{
	struct hrtimer *hrtimer = &__get_cpu_var(oprofile_hrtimer);

	if (!ctr_running)
		return;

	hrtimer_init(hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer->function = oprofile_hrtimer_notify;

#ifndef CONFIG_ADVANCE_OPROFILE
	hrtimer_start(hrtimer, ns_to_ktime(TICK_NSEC),
		      HRTIMER_MODE_REL_PINNED);
#else
	hrtimer_start(hrtimer, ns_to_ktime(AOP_TICK_TIME),
		      HRTIMER_MODE_REL_PINNED);
#endif/* CONFIG_ADVANCE_OPROFILE */

}

static int oprofile_hrtimer_start(void)
{
	get_online_cpus();
	ctr_running = 1;
	on_each_cpu(__oprofile_hrtimer_start, NULL, 1);
	put_online_cpus();
	return 0;
}

static void __oprofile_hrtimer_stop(int cpu)
{
	struct hrtimer *hrtimer = &per_cpu(oprofile_hrtimer, cpu);

	if (!ctr_running)
		return;

	hrtimer_cancel(hrtimer);
}

static void oprofile_hrtimer_stop(void)
{
	int cpu;

	get_online_cpus();
	for_each_online_cpu(cpu)
		__oprofile_hrtimer_stop(cpu);
	ctr_running = 0;
	put_online_cpus();
}

static int __cpuinit oprofile_cpu_notify(struct notifier_block *self,
					 unsigned long action, void *hcpu)
{
	long cpu = (long) hcpu;

	switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		smp_call_function_single(cpu, __oprofile_hrtimer_start,
					 NULL, 1);
		break;
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		__oprofile_hrtimer_stop(cpu);
		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block __refdata oprofile_cpu_notifier = {
	.notifier_call = oprofile_cpu_notify,
};

static int oprofile_hrtimer_setup(void)
{
	return register_hotcpu_notifier(&oprofile_cpu_notifier);
}

static void oprofile_hrtimer_shutdown(void)
{
	unregister_hotcpu_notifier(&oprofile_cpu_notifier);
}

int oprofile_timer_init(struct oprofile_operations *ops)
{
	ops->create_files	= NULL;
	ops->setup		= oprofile_hrtimer_setup;
	ops->shutdown		= oprofile_hrtimer_shutdown;
	ops->start		= oprofile_hrtimer_start;
	ops->stop		= oprofile_hrtimer_stop;
	ops->cpu_type		= "timer";
	printk(KERN_INFO "oprofile: using timer interrupt.\n");
	return 0;
}
