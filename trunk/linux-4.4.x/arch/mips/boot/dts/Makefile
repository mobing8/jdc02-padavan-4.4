# 新增：指定设备树编译时的头文件搜索路径（指向内核顶层include目录）
DTC_FLAGS += -I$(srctree)/include

dts-dirs	+= brcm
dts-dirs	+= cavium-octeon
dts-dirs	+= ingenic
dts-dirs	+= lantiq
dts-dirs	+= mti
dts-dirs	+= netlogic
dts-dirs	+= qca
dts-dirs	+= ralink  # 包含你的jdcloud-re-cp-02.dts所在目录
dts-dirs	+= xilfpga

obj-y		:= $(addsuffix /, $(dts-dirs))

dtstree		:= $(srctree)/$(src)
dtb-$(CONFIG_OF_ALL_DTBS) := $(patsubst $(dtstree)/%.dts,%.dtb, $(foreach d,$(dts-dirs), $(wildcard $(dtstree)/$(d)/*.dts)))

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtb.S
