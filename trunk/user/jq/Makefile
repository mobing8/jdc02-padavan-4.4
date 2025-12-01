# 1. 插件基础配置
NAME := jq
VERSION := 1.7.1
INSTALL_DIR := $(shell pwd)/install
TARGET_DIR := $(INSTALL_DIR)/

# 2. jq预编译二进制路径
JQ_BIN_PATH := files/jq

# 3. 准备安装目录
prepare:
    rm -rf $(INSTALL_DIR)
    mkdir -p $(TARGET_DIR)/usr/bin  # jq安装到/usr/bin（系统默认路径）

# 4. 安装jq（直接复制预编译二进制）
install: prepare
    @echo "===== 安装jq 1.7.1（mipsel预编译版）====="
    if [ ! -f $(JQ_BIN_PATH) ]; then \
        echo "错误：jq预编译文件 $(JQ_BIN_PATH) 不存在！"; \
        exit 1; \
    fi
    # 复制jq到固件的/usr/bin目录（系统可调用路径）
    cp $(JQ_BIN_PATH) $(TARGET_DIR)/usr/bin/
    # 赋予可执行权限
    chmod +x $(TARGET_DIR)/usr/bin/jq

# 5. 清理编译残留
clean:
    rm -rf $(INSTALL_DIR)

# 6. Padavan编译脚本调用目标
all: install