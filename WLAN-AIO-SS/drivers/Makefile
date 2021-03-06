#
export ATH_DRIVER_TOPDIR=${ATH_TOPDIR}/drivers

#################################################################################################################################
# Compat related flags
export
COMPAT_LATEST_VERSION = 1
KERNEL_VERSION := $(shell make -C $(KERNELPATH) kernelversion | sed -n 's/^\([0-9]\)\..*/\1/p')
ifneq ($(KERNEL_VERSION),2)
KERNEL_SUBLEVEL := $(shell make -C $(KERNELPATH) kernelversion | sed -n 's/^3\.\([0-9]\+\).*/\1/p')
else
COMPAT_26LATEST_VERSION = 39
KERNEL_26SUBLEVEL := $(shell make -C $(KERNELPATH) kernelversion | sed -n 's/^2\.6\.\([0-9]\+\).*/\1/p')
COMPAT_26VERSIONS := $(shell I=$(COMPAT_26LATEST_VERSION); while [ "$$I" -gt $(KERNEL_26SUBLEVEL) ]; do echo $$I; I=$$(($$I - 1)); done)
$(foreach ver,$(COMPAT_26VERSIONS),$(eval CONFIG_COMPAT_KERNEL_2_6_$(ver)=y))
KERNEL_SUBLEVEL := -1
endif
COMPAT_VERSIONS := $(shell I=$(COMPAT_LATEST_VERSION); while [ "$$I" -gt $(KERNEL_SUBLEVEL) ]; do echo $$I; I=$$(($$I - 1)); done)
$(foreach ver,$(COMPAT_VERSIONS),$(eval CONFIG_COMPAT_KERNEL_3_$(ver)=y))
#
# Need to build compat_firmware_class.ko ?
#
include $(KERNELPATH)/.config
ifdef CONFIG_COMPAT_KERNEL_2_6_33
ifdef CONFIG_FW_LOADER
 CONFIG_COMPAT_FIRMWARE_CLASS=m
endif
endif

#################################################################################################################################
# CFG80211 related flags

# Default always ON even kernel config don't support it.
ifndef CONFIG_CFG80211
CONFIG_CFG80211=m
DEF_CFG80211=y
endif

ifndef CONFIG_CFG80211_DEFAULT_PS
CONFIG_CFG80211_DEFAULT_PS=y
DEF_CFG80211_DEFAULT_PS=y
endif

# We need CONFIG_WIRELESS_EXT for CONFIG_CFG80211_WEXT for every kernel 
# version. The new way CONFIG_CFG80211_WEXT is called from the kernel 
# does not work with compat-wireless because it calls some callback 
# function on struct wiphy. This struct is shipped with compat-wireless 
# and changes from kernel version to version. We are using the 
# wireless_handlers attribute which will be activated by 
ifdef CONFIG_WIRELESS_EXT
ifndef CONFIG_CFG80211_WEXT
CONFIG_CFG80211_WEXT=y
DEF_CFG80211_WEXT=y
endif
endif

ifdef CONFIG_PMF_SUPPORT
ATH_LOCAL_CFLAGS += -DPMF_SUPPORT=y
endif

ifdef CONFIG_CE_SUPPORT
ATH_LOCAL_CFLAGS += -DCE_SUPPORT=y
endif

ifdef CONFIG_ATHTST_SUPPORT
ATH_LOCAL_CFLAGS += -DATHTST_SUPPORT=y
endif

ifdef CONFIG_SWOW_SUPPORT
ATH_LOCAL_CFLAGS += -DCONFIG_SWOW_SUPPORT=y
endif

ifdef CONFIG_TX99_SUPPORT
CONFIG_NL80211_TESTMODE=y
ATH_LOCAL_CFLAGS += -DTX99_SUPPORT=y -DCONFIG_NL80211_TESTMODE=y
endif

ifdef CONFIG_ACS_SUPPORT
ATH_LOCAL_CFLAGS += -DACS_SUPPORT=y
endif

ifdef CONFIG_ACL_SUPPORT
ATH_LOCAL_CFLAGS += -DACL_SUPPORT=y
endif

ifdef CONFIG_CFG80211_INTERNAL_REGDB
CONFIG_ATH6KL_INTERNAL_REGDB=y
ATH_LOCAL_CFLAGS += -DCONFIG_ATH6KL_INTERNAL_REGDB=y
endif

ifdef BUILD_2.6.23_SUPPORT
ATH_LOCAL_CFLAGS += -DCE_OLD_KERNEL_SUPPORT_2_6_23=y
endif

#################################################################################################################################
# ATH6KL related flags
ATH_LOCAL_CFLAGS += -DCONFIG_ATH6KL_DEBUG=y

#################################################################################################################################
# Add flags to compiler
ifdef DEF_CFG80211
ATH_LOCAL_CFLAGS += -DCONFIG_CFG80211=y
endif

ifdef DEF_CFG80211_DEFAULT_PS
ATH_LOCAL_CFLAGS += -DCONFIG_CFG80211_DEFAULT_PS=y
endif

ifdef DEF_CFG80211_WEXT
ATH_LOCAL_CFLAGS += -DCONFIG_CFG80211_WEXT=y
endif

#ifdef BUILD_REG_SS_PATCH
CFG_BUILD_FW_SS_REG=y
#endif

ifdef CONFIG_CFG80211_INTERNAL_REGDB
ATH_LOCAL_CFLAGS += -DCONFIG_CFG80211_INTERNAL_REGDB=y
endif

ifdef CONFIG_CE_2_SUPPORT
ATH_LOCAL_CFLAGS += -DCE_2_SUPPORT=y
endif

ifdef CONFIG_KERNEL_3_8_2
ATH_LOCAL_CFLAGS += -DCONFIG_KERNEL_3_8_2=y
ATH_LOCAL_CFLAGS += -DATH6KL_SUPPORT_NL80211_KERNEL3_8=y
endif

ifdef CONFIG_KERNEL_3_5_7
ATH_LOCAL_CFLAGS += -DCONFIG_KERNEL_3_5_7=y
ATH_LOCAL_CFLAGS += -DATH6KL_SUPPORT_NL80211_KERNEL3_5=y
endif

ifdef CONFIG_KERNEL_3_10_9
ATH_LOCAL_CFLAGS += -DCONFIG_KERNEL_3_10_9=y
ATH_LOCAL_CFLAGS += -DATH6KL_SUPPORT_NL80211_KERNEL3_9=y
endif

ifdef CONFIG_KERNEL_3_4_39
ATH_LOCAL_CFLAGS += -DCONFIG_KERNEL_3_4_39=y
ATH_LOCAL_CFLAGS += -DATH6KL_SUPPORT_NL80211_KERNEL3_4=y
endif

ifdef CONFIG_DIRECT_AUDIO_SUPPORT
ATH_LOCAL_CFLAGS += -DDIRECT_AUDIO_SUPPORT=y
endif

ifdef USB_CUSTOMIZE_SUSPEND
ATH_LOCAL_CFLAGS += -DUSB_CUSTOMIZE_SUSPEND=y
endif

ifndef CONFIG_NL80211_TESTMODE
CONFIG_NL80211_TESTMODE=y
ATH_LOCAL_CFLAGS += -DCONFIG_NL80211_TESTMODE=y
endif

ifdef CE_INDIV_WORK_ITEM
ATH_LOCAL_CFLAGS += -DCE_INDIV_WORK_ITEM=y
endif

#################################################################################################################################
all: driver_clean driver_build

clean: driver_clean

driver_build: firmware_toarray
	@echo Build drivers
ifdef CONFIG_KERNEL_3_8_2
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_382 modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/cfg80211_382/Module.symvers modules 
else
ifdef CONFIG_KERNEL_3_5_7
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_357 modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/cfg80211_357/Module.symvers modules 
else
ifdef CONFIG_KERNEL_3_10_9
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_3109 modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/cfg80211_3109/Module.symvers modules 
else
ifdef CONFIG_KERNEL_3_4_39
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_3439 modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/cfg80211_3439/Module.symvers modules 
else
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/compat modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211 KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/compat/Module.symvers modules
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl KBUILD_EXTRA_SYMBOLS=$(ATH_DRIVER_TOPDIR)/cfg80211/Module.symvers modules
endif
endif
endif
endif

driver_clean:
	@echo Clean drivers
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/compat clean
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211 clean
ifdef CONFIG_KERNEL_3_8_2
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_382 clean
endif
ifdef CONFIG_KERNEL_3_5_7
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_357 clean
endif
ifdef CONFIG_KERNEL_3_10_9
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_3109 clean
endif
ifdef CONFIG_KERNEL_3_4_39
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/cfg80211_3439 clean
endif
	${MAKEARCH} -C $(KERNELPATH) SUBDIRS=$(ATH_DRIVER_TOPDIR)/ath6kl clean
# Move to BOARD-specific Makefile
#driver_patch:
#	@echo Patch drivers
#	@patch -p0 < patches/00-remore_ns-type.patch
#	@patch -p0 < patches/02-remore_netlink-seq.patch
#	@patch -p0 < patches/03-change_IFF_BRIDGE_PORT.patch

# This is ONLY for USB solution.
firmware_install:
	@echo install AR6004 REV5 firmware
	@rm -rf ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/
	@mkdir -p ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/
	@if [ "$(BUILD_BDATA_DB7)" = "y" ]; then \
	   echo use DB7 Board Data; \
	   cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134-055-ce.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
	 elif [ "$(BUILD_BDATA_XPA)" = "y" ]; then \
		 echo use xPA Board Data; \
	   cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
	 elif [ "$(BUILD_BDATA_XPA_DUAL)" = "y" ]; then \
		 echo use xPA dual Board Data; \
	   cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA_dual.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
	 else \
		 echo use normal Board Data; \
		 cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
	 fi
	@if [ "$(CFG_BUILD_FW_SS_REG)" = "y" ]; then \
	cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ss_3.5.2.bin ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/fw.ram.bin; \
	else \
	cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ce.bin ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw1.3/fw.ram.bin; \
	fi 
	@if [ "$(BOARD_TYPE)" = "x86" ]; then \
		if [ "$(BUILD_DRIVERFW_TOLOCAL)" = "y" ]; then \
			echo install kf firmware to local; \
                        rm -rf /lib/firmware/ath6k/AR6006/hw1.1/; \
                        mkdir -p /lib/firmware/ath6k/AR6006/hw1.1/; \
                        cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/* /lib/firmware/ath6k/AR6006/hw1.1/; \
                        echo end of install kf firmware; \
			echo install AR6004 REV5 firmware to local; \
			rm -rf /lib/firmware/ath6k/AR6004/hw1.3/; \
			mkdir -p /lib/firmware/ath6k/AR6004/hw1.3/; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ce.bin /lib/firmware/ath6k/AR6004/hw1.3/fw.ram.bin; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/selftest.bin /lib/firmware/ath6k/AR6004/hw1.3/selftest.bin; \
			if [ "$(BUILD_BDATA_DB7)" = "y" ]; then \
				echo use DB7 Board Data; \
				cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134-055-ce.bin  /lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
			elif [ "$(BUILD_BDATA_XPA)" = "y" ]; then \
				echo use xPA Board Data; \
				cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA.bin  /lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
			elif [ "$(BUILD_BDATA_XPA_DUAL)" = "y" ]; then \
				echo use xPA dual Board Data; \
				cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA_dual.bin  /lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
			else \
			  echo use normal Board Data; \
			  cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051.bin  /lib/firmware/ath6k/AR6004/hw1.3/bdata.bin; \
	    fi \
		else \
			echo You must be root to install firmware to local...; \
		fi \
	fi
	@if [ "$(BOARD_TYPE)" = "x86" -a "$(BUILD_DRIVERFW_TOLOCAL)" = "y" -a "$(CFG_BUILD_FW_SS_REG)" = "y" ]; then \
		cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ss_3.5.2.bin /lib/firmware/ath6k/AR6004/hw1.3/fw.ram.bin; \
	fi
	@echo install AR6004 REV6 firmware
	@rm -rf ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw2.0/
	@mkdir -p ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw2.0/
	@cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/fw.ram.bin ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw2.0/fw.ram.bin;
	@echo use normal Board Data;
	@cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/bdata.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw2.0/bdata.bin;
	@if [ "$(BOARD_TYPE)" = "x86" -o "$(BOARD_TYPE)" = "x86-ss" ]; then \
		if [ "$(BUILD_DRIVERFW_TOLOCAL)" = "y" ]; then \
			echo install AR6004 REV6 firmware to local; \
			rm -rf /lib/firmware/ath6k/AR6004/hw2.0/; \
			mkdir -p /lib/firmware/ath6k/AR6004/hw2.0/; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/fw.ram.bin /lib/firmware/ath6k/AR6004/hw2.0/fw.ram.bin; \
			echo use normal Board Data; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/bdata.bin  /lib/firmware/ath6k/AR6004/hw2.0/bdata.bin; \
		else \
			echo You must be root to install firmware to local...; \
		fi \
	fi
	@echo install AR6004 REV8 firmware
	@rm -rf ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw3.0/
	@mkdir -p ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw3.0/
	@cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/fw.ram.bin ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw3.0/fw.ram.bin;
	@echo use normal Board Data;
	@cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/bdata.bin  ${INSTALL_ROOT}/lib/firmware/ath6k/AR6004/hw3.0/bdata.bin;
	@if [ "$(BOARD_TYPE)" = "x86" -o "$(BOARD_TYPE)" = "x86-ss" ]; then \
		if [ "$(BUILD_DRIVERFW_TOLOCAL)" = "y" ]; then \
			echo install AR6004 REV8 firmware to local; \
			rm -rf /lib/firmware/ath6k/AR6004/hw3.0/; \
			mkdir -p /lib/firmware/ath6k/AR6004/hw3.0/; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/fw.ram.bin /lib/firmware/ath6k/AR6004/hw3.0/fw.ram.bin; \
			echo use normal Board Data; \
			cp $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/bdata.bin  /lib/firmware/ath6k/AR6004/hw3.0/bdata.bin; \
		else \
			echo You must be root to install firmware to local...; \
		fi \
	fi

firmware_toarray:
	@echo Transfer defaulte bdata to C array
	@if [ "$(BUILD_BDATA_DB7)" = "y" ]; then \
	   echo use DB7 Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134-055-ce.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata.h       fw_bdata; \
	 elif [ "$(BUILD_BDATA_XPA)" = "y" ]; then \
	   echo use xPA Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata.h       fw_bdata; \
	 elif [ "$(BUILD_BDATA_XPA_DUAL)" = "y" ]; then \
	   echo use xPA dual Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA_dual.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata.h       fw_bdata; \
	 else \
	   echo use normal Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata.h       fw_bdata; \
	 fi
	@echo Transfer other bdata to C array;	
	   @echo transfer DB7 Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134-055-ce.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata_db7.h       fw_bdata_db7;
	   @echo transfer xPA Board Data; \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/boardData_2_1_UB134_051-ce_xPA.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata_xpa.h       fw_bdata_xpa;
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/bdata.bin DONE...
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ce.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram.h         fw_ram
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ce.bin DONE...
	@if [ "$(CFG_BUILD_FW_SS_REG)" = "y" ]; then \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ss_3.5.2.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram.h         fw_ram; \
	   echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/fw.ram_64k_ss_3.5.2.bin DONE...; \
	fi
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw1.3/selftest.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_selftest.h         fw_selftest
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/bdata.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata_2_0.h       fw_bdata_2_0;
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/bdata.bin DONE...
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/fw.ram.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram_2_0.h         fw_ram_2_0
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw2.0/fw.ram.bin DONE...
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/bdata.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata_3_0.h       fw_bdata_3_0;
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/bdata.bin DONE...
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/fw.ram.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram_3_0.h         fw_ram_3_0
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6004/hw3.0/fw.ram.bin DONE...
	@${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/bdata.bin  ${ATH_DRIVER_TOPDIR}/ath6kl/fw_bdata_6006_1_1.h       fw_bdata_6006_1_1;
	@echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/bdata.bin DONE...
	@if [ "$(CFG_BUILD_FW_SS_REG)" = "y" ]; then \
     ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/fw.ram_ss.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram_6006_1_1.h        fw_ram_6006_1_1; \
	   echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/fw.ram_ss.bin Done...; \
	 else \
	   ${ATH_TOPDIR}/build/util/ath6kl_bin2hex.sh $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/fw.ram.bin ${ATH_DRIVER_TOPDIR}/ath6kl/fw_ram_6006_1_1.h        fw_ram_6006_1_1; \
	   echo Transfer $(ATH_DRIVER_TOPDIR)/fw/firmware/AR6006/hw1.1/fw.ram.bin Done...; \
	fi
