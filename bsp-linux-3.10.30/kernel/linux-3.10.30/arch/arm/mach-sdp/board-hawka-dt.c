/*
 * Copyright (C) 2014 Samsung Electronics Co.Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/of_platform.h>
#include <linux/export.h>
#include <linux/clocksource.h>
#include <linux/clk-provider.h>
#include <linux/irqchip/arm-gic.h>

#include <asm/mach/arch.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/setup.h>
#include <asm/mach/map.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/setup.h>
#include <asm/memory.h>
#include <mach/sdp_smp.h>
#include "common.h"

#include <mach/map.h>

#undef SFR0_BASE
#define SFR0_BASE		(0x10000000)
#undef SFR0_SIZE
#define SFR0_SIZE		(0x01000000)

#define SDP1412_MISC_BASE	0x10f80000
#define SDP1412_MISC_POWER_CTL	0x10
#define SDP1412_MISC_BOOTUP	0x3E0

static struct map_desc sdp1412_io_desc[] __initdata = {
	[0] = {
		.virtual	= (unsigned long)VA_SFR0_BASE,
		.pfn		= __phys_to_pfn(SFR0_BASE),
		.length		= SFR0_SIZE,
		.type		= MT_DEVICE,
	},
};

static char const *sdp1412_dt_compat[] __initdata = {
	"samsung,sdp1412",
	NULL
};

#if defined(CONFIG_SMP)
static int __cpuinit sdp1412_powerup_cpu(unsigned int cpu)
{
#if 0	
	u32 val;
	u32 base = SFR_VA + SDP1412_MISC_BASE - SFR0_BASE;

	/* reset contorl */
	val = readl((void *)(base + 0xC)) | (1U << (cpu + 4)) | (1U << (cpu + 8));
	//val = readl((void *)(base + 0xC)) | (1 << cpu);
	writel(val, (void *)(base + 0xC));

	/* set cpu power up */
	val = readl((void *)(base + SDP1412_MISC_POWER_CTL + cpu*4));
	val |= 1;
	writel(val, (void *)(base + SDP1412_MISC_POWER_CTL + cpu*4));

	/* wait for power up */
//	while (((readl((void *)(base + 0x4)) >> (12 + (cpu * 4))) & 0xF) != 0);
#endif	
	return 0;
}

static int __cpuinit sdp1412_powerdown_cpu(unsigned int cpu)
{
#if 0	
	u32 val;
	u32 base = SFR_VA + SDP1412_MISC_BASE - SFR0_BASE;
	int timeout = 10;

	/* auto mode off */
//	val = readl((void *)(base + 0x10 + (cpu * 4))) | (1 << 12);
//	writel(val, (void *)(base + 0x10 + (cpu * 4)));

	/* wait for wfi */
	while (timeout--) {
		if (((readl((void *)base) >> (cpu + 24)) & 0x1))
			break;
		pr_info("wait for wfi\n");
		udelay(1000);
	}
	if (!timeout)
		pr_info("wait for wfi timeout\n");

	/* reset control */
	val = readl((void *)(base + 0xC)) & ~((1U << (cpu + 4)) | (1U << (cpu + 8)));
	//val = readl((void *)(base + 0xC)) & ~(1 << cpu);
	writel(val, (void *)(base + 0xC));

	/* delay */
	udelay(10);

	/* set cpu power down */
	val = readl((void *)(base + SDP1412_MISC_POWER_CTL + cpu*4));
	val |= 1 << 4;
	writel(val, (void *)(base + SDP1412_MISC_POWER_CTL + cpu*4));

	/* wait for power down */
//	while (((readl((void *)(base + 0x4)) >> (12 + (cpu * 4))) & 0xF) != 0x7);
#endif
	return 0;
}

static __cpuinit int sdp1412_install_warp(unsigned int cpu)
{
	void __iomem *base;

	base = ioremap(SDP1412_MISC_BASE, 0x400);
	writel_relaxed(virt_to_phys(sdp_secondary_startup)
		, (void *) ((u32) base + SDP1412_MISC_BOOTUP + cpu * 4));
	dmb();	
	udelay(1);	
	iounmap(base);
	return 0;
}

struct sdp_power_ops sdp1412_power_ops = {
	.powerup_cpu	= sdp1412_powerup_cpu,
	.powerdown_cpu	= sdp1412_powerdown_cpu,
	.install_warp	= sdp1412_install_warp,
};
#endif

#if !defined(CONFIG_SPARSEMEM)
extern phys_addr_t sdp_sys_mem0_size;
#endif

static void __init hawka_map_io(void)
{
	iotable_init(sdp1412_io_desc, ARRAY_SIZE(sdp1412_io_desc));
#if defined (CONFIG_SMP)
	sdp_platsmp_init(&sdp1412_power_ops);
#endif

#if !defined(CONFIG_SPARSEMEM)
	sdp_sys_mem0_size = meminfo.bank[0].size;
	if(meminfo.nr_banks > 1)
		sdp_sys_mem0_size += meminfo.bank[1].size;
#endif
}

static void __init sdp1412_init_time(void)
{
#ifdef CONFIG_OF
	of_clk_init(NULL);
	clocksource_of_init();
#endif
}

static void __init sdp1412_reserve(void)
{
}

DT_MACHINE_START(SDP1412_DT, "Samsung SDP1412(Flattened Device Tree)")
	/* Maintainer: */
	.init_irq	= sdp_init_irq,
	.smp		= smp_ops(sdp_smp_ops),
	.map_io		= hawka_map_io,
	.init_machine	= sdp_dt_init_machine,
	.init_time	= sdp1412_init_time,
	.dt_compat	= sdp1412_dt_compat,
	.restart	= sdp_restart,
	.reserve	= sdp1412_reserve,
MACHINE_END