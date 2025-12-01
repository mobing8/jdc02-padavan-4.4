NAME := smartdns
VERSION := v38
INSTALL_DIR := $(shell pwd)/install
CC := mipsel-linux-gcc
CFLAGS := -mips32r2 -msoft-float -O2

prepare:
	rm -rf $(INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)/usr/bin $(INSTALL_DIR)/etc/smartdns $(INSTALL_DIR)/etc/init.d

install: prepare
	# 编译 SmartDNS（适配 mipsel 软浮点）
	make CC=$(CC) CFLAGS="$(CFLAGS)" -j$(nproc)
	# 安装二进制文件
	cp src/smartdns $(INSTALL_DIR)/usr/bin/
	# 安装默认配置
	cp conf/smartdns.conf $(INSTALL_DIR)/etc/smartdns/
	# 安装启动脚本（开机自启）
	echo '#!/bin/sh' > $(INSTALL_DIR)/etc/init.d/S98smartdns
	echo '/usr/bin/smartdns -c /etc/smartdns/smartdns.conf' >> $(INSTALL_DIR)/etc/init.d/S98smartdns
	chmod +x $(INSTALL_DIR)/etc/init.d/S98smartdns

clean:
	make clean
	rm -rf $(INSTALL_DIR)

all: install