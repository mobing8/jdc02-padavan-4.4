# 1. 插件基础配置（Padavan user 目录必需）
NAME := openclash
VERSION := v0.45.121  # 与OpenClash源码版本一致
INSTALL_DIR := $(shell pwd)/install  # 编译临时安装目录
TARGET_DIR := $(INSTALL_DIR)/  # 映射到固件根目录

# 2. 交叉编译器配置（适配MT7621软浮点）
CC := mipsel-linux-gcc
CFLAGS := -mips32r2 -msoft-float -O2

# 3. Mihomo核心配置（保留原文件名，与你的核心文件一致）
MIHOMO_CORE := Clash.Meta-linux-mipsle-softfloat-v1.10.0
MIHOMO_CORE_PATH := files/$(MIHOMO_CORE)  # 核心存放路径（你的files目录下）

# 4. 依赖声明（编译顺序：先编译这些工具）
DEPENDS := "curl jq base64 iptables smartdns ipset openssl"

# 5. 准备安装目录（清空旧文件）
prepare:
	rm -rf $(INSTALL_DIR)
	# 创建固件内的关键目录
	mkdir -p $(TARGET_DIR)/etc/openclash  # 核心+规则文件目录
	mkdir -p $(TARGET_DIR)/usr/lib/lua/luci  # LuCI逻辑路径
	mkdir -p $(TARGET_DIR)/www  # WebUI静态文件路径
	mkdir -p $(TARGET_DIR)/etc/init.d  # 启动脚本路径

# 6. 安装Mihomo核心（复制到规则文件同目录）
install_core: prepare
	@echo "===== 安装Mihomo核心（保留原文件名）====="
	if [ ! -f $(MIHOMO_CORE_PATH) ]; then \
		echo "错误：核心文件 $(MIHOMO_CORE_PATH) 不存在！"; \
		exit 1; \
	fi
	# 复制核心到 /etc/openclash（与规则文件同目录）
	cp $(MIHOMO_CORE_PATH) $(TARGET_DIR)/etc/openclash/
	# 赋予核心可执行权限
	chmod +x $(TARGET_DIR)/etc/openclash/$(MIHOMO_CORE)

# 7. 安装OpenClash插件组件（适配你的目录结构）
install_plugin: install_core
	@echo "===== 安装OpenClash插件组件 ====="
	# 1. 安装LuCI逻辑（WebUI交互代码）
	cp -r luasrc/* $(TARGET_DIR)/usr/lib/lua/luci/
	
	# 2. 安装WebUI静态文件（页面展示）
	cp -r root/www/* $(TARGET_DIR)/www/
	
	# 3. 安装规则文件（你的root/etc/openclash下的所有文件）
	cp -r root/etc/openclash/* $(TARGET_DIR)/etc/openclash/
	
	# 4. 安装启动脚本（你的root/etc/init.d/openclash）
	# 复制并重命名为S99openclash（Padavan开机自启脚本命名规则）
	cp root/etc/init.d/openclash $(TARGET_DIR)/etc/init.d/S99openclash
	# 修改启动脚本中的核心路径（指向/etc/openclash下的Mihomo原文件名）
	sed -i "s|clash|$(MIHOMO_CORE)|g" $(TARGET_DIR)/etc/init.d/S99openclash
	sed -i "s|/path/to/clash|/etc/openclash/$(MIHOMO_CORE)|g" $(TARGET_DIR)/etc/init.d/S99openclash
	
	# 5. 安装中文语言包
	cp -r po/zh-cn/* $(TARGET_DIR)/usr/lib/lua/luci/i18n/openclash.zh-cn.lmo 2>/dev/null
	
	# 6. 修复所有文件权限
	chmod +x $(TARGET_DIR)/etc/init.d/S99openclash
	chmod -R 755 $(TARGET_DIR)/www/luci-static/resources/openclash
	chmod -R 755 $(TARGET_DIR)/etc/openclash

# 8. 清理编译残留
clean:
	rm -rf $(INSTALL_DIR)
	rm -f $(MIHOMO_CORE).gz 2>/dev/null

# 9. Padavan编译脚本自动调用的目标
all: install_plugin