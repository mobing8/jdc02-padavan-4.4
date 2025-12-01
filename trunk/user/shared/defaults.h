/*
 * 许可证声明：
 * 本程序为自由软件，可自由分发和修改，遵循 GNU 通用公共许可证（GPL）V2 或更高版本。
 * 本程序仅提供"按原样"使用，不保证任何明示或暗示的担保（如适销性、特定用途适用性）。
 * 详细许可证条款可查看 GNU 官方文档，或联系自由软件基金会。
 */

// 头文件保护：防止该文件被重复包含（避免编译冲突）
#ifndef _defaults_h_
#define _defaults_h_

// 包含 Ralink/MTK 芯片的板级定义头文件（提供 BOARD_PID 等硬件相关宏）
#include <ralink_board.h>

// -------------------------- 系统基础配置 --------------------------
#define SYS_SHELL		"/bin/sh"          // 系统默认shell终端（精简版Padavan核心终端，用于命令行交互）
#define SYS_EXEC_PATH		"/usr/sbin:/usr/bin:/sbin:/bin"  // 系统命令搜索路径（核心命令存放目录，精简版保留的基础路径）
#define SYS_EXEC_PATH_OPT	"/opt/sbin:/opt/bin:/usr/sbin:/usr/bin:/sbin:/bin"  // 扩展命令搜索路径（含/opt目录，用于第三方工具/插件）
#define SYS_HOME_PATH_ROOT	"/home/admin"      // 管理员（root）的家目录（精简版可能仅保留目录结构，无多余文件）

// -------------------------- 用户/权限配置 --------------------------
#define SYS_USER_ROOT		"admin"            // 系统超级管理员用户名（登录路由WebUI/SSH的默认用户名）
#define SYS_GROUP_ROOT		"root"             // 管理员用户组（最高权限组）
#define SYS_USER_NOBODY		"nobody"           // 无权限用户（用于运行低权限服务，提升安全性）
#define SYS_GROUP_NOGROUP	"nogroup"          // 无权限用户组（对应nobody用户，限制资源访问）

// -------------------------- LAN 网络默认配置 --------------------------
#define DEF_LAN_ADDR		"192.168.68.1"     // 路由LAN口默认IP地址（登录WebUI的默认地址，如 http://192.168.68.1）
#define DEF_LAN_DHCP_BEG	"192.168.68.100"   // DHCP服务器地址池起始IP（局域网设备自动获取IP的起始值）
#define DEF_LAN_DHCP_END	"192.168.68.244"   // DHCP服务器地址池结束IP（最多支持 244-100+1=145 台设备接入）
#define DEF_LAN_MASK		"255.255.255.0"    // LAN口子网掩码（默认24位掩码，局域网网段为 192.168.68.0/24）

// -------------------------- WiFi 网络默认配置 --------------------------
#define DEF_WLAN_2G_CC		"CN"               // 2.4G WiFi 国家码（CN=中国，对应国内WiFi信道/功率标准）
#define DEF_WLAN_5G_CC		"US"               // 5G WiFi 国家码（US=美国，支持更多5G信道，部分地区需手动调整）
#define DEF_WLAN_2G_SSID	BOARD_PID "RE-CP-02"    // 2.4G WiFi 默认名称（BOARD_PID=产品ID，即你配置的 "RE-CP-02"；%s 是后缀，最终为 "RE-CP-02_2G" 之类）
#define DEF_WLAN_5G_SSID	BOARD_PID "RE-CP-02-5G" // 5G WiFi 默认名称（格式：产品ID_5G_后缀，如 "RE-CP-02_5G"）
#define DEF_WLAN_2G_GSSID	BOARD_PID "GUEST"  // 2.4G 访客WiFi默认名称（带GUEST标识，隔离主网络）
#define DEF_WLAN_5G_GSSID	BOARD_PID "GUEST-5G"  // 5G 访客WiFi默认名称
#define DEF_WLAN_2G_PSK		""       // 2.4G WiFi 默认密码空
#define DEF_WLAN_5G_PSK		""       // 5G WiFi 默认密码空

// -------------------------- 系统默认参数 --------------------------
#define DEF_ROOT_PASSWORD	"admin"            // 管理员默认密码（登录WebUI/SSH的默认密码，必须修改！）
#define DEF_SMB_WORKGROUP	"WORKGROUP"        // SMB文件共享默认工作组（Windows默认工作组名称，方便局域网访问）
#define DEF_TIMEZONE		"CST-8"            // 系统默认时区（CST-8=中国标准时间，UTC+8时区）
#define DEF_NTP_SERVER0		"ntp1.aliyun.com"  // 主NTP时间服务器（阿里云NTP，国内网络稳定，用于同步系统时间）
#define DEF_NTP_SERVER1		"2001:470:0:50::2" // 备用NTP服务器（IPv6地址，兼容IPv6网络环境）

// -------------------------- 加密相关配置（条件编译） --------------------------
#ifdef SUPPORT_OPENSSL_EC  // 若启用了 OpenSSL 椭圆曲线（EC）支持（对应配置：CONFIG_FIRMWARE_INCLUDE_OPENSSL_EC=y）
#define DEF_HTTPS_CIPH_LIST	"ECDH+CHACHA20:ECDH+AESGCM:DH+AESGCM:DH+AES256:DH+AES:DH+3DES:RSA+AES:RSA+3DES:!ADH:!MD5:!DSS"
// HTTPS 支持的加密套件列表（优先椭圆曲线加密，安全性更高，兼容主流浏览器）
#else
#define DEF_HTTPS_CIPH_LIST	"DH+AESGCM:DH+AES256:DH+AES:DH+3DES:RSA+AES:RSA+3DES:!ADH:!MD5:!DSS"
// 未启用椭圆曲线时的HTTPS加密套件（仅保留传统加密算法，兼容性更广但安全性略低）
#endif

#define DEF_OVPNS_CIPH_LIST	"CHACHA20-POLY1305:AES-256-GCM:AES-128-GCM"  // OpenVPN服务器（OVPNS）支持的加密套件（优先高效安全的ChaCha20和AES-GCM）
#define DEF_OVPNC_CIPH_LIST	"CHACHA20-POLY1305:AES-256-GCM:AES-128-GCM"  // OpenVPN客户端（OVPNC）支持的加密套件（与服务器端一致，确保连接兼容性）

// 结束头文件保护
#endif
