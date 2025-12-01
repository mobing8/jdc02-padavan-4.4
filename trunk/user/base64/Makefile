NAME := base64
INSTALL_DIR := $(shell pwd)/install

install:
    rm -rf $(INSTALL_DIR)
    mkdir -p $(INSTALL_DIR)/usr/bin
    # 创建 base64 脚本，调用 busybox 的 base64 功能
    echo '#!/bin/sh' > $(INSTALL_DIR)/usr/bin/base64
    echo 'busybox base64 "$@"' >> $(INSTALL_DIR)/usr/bin/base64
    # 赋予可执行权限
    chmod +x $(INSTALL_DIR)/usr/bin/base64

clean:
    rm -rf $(INSTALL_DIR)

all: install