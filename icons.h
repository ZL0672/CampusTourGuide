/***********************************************************
* 版权所有 (C)2026, 庄鲁
*
* 文件名称： icons.h
* 文件标识：无
* 内容摘要：该头文件定义了控制台界面使用的Emoji图标常量与工具函数。
*           包括清屏、打印分割线、显示处理动画、等待用户继续等函数，用于增强
*           校园导游系统的用户交互体验与界面美观度。
* 其它说明：无
* 当前版本： V2.0
* 作   者：庄鲁
* 完成日期： 2026.2.26
*
* 修改记录1：
* 修改日期：2026.2.24
* 版本号： V1.0
* 修改人： 庄鲁
* 修改内容：修改对于Emoji图标正确的编码显示
**********************************************************/


#pragma once
// icons.h - Emoji图标定义与工具函数

#ifndef ICONS_H //头文件保护，防止同一个头文件被多次包含避免重复定义
#define ICONS_H //写下标记

#include <stdio.h>
#include <windows.h> //操作系统头文件，用于控制台等操作

// ==================== Emoji 图标定义 ====================
// 直接使用Emoji字符
//在内存中存储为UTF-8字节序列
#define ICON_SPOT      "🏛️ "      // 景点
#define ICON_START     "📍 "      // 起点
#define ICON_END       "🎯 "      // 终点
#define ICON_MAP       "🗺️ "      // 地图
#define ICON_PATH      "🛣️ "      // 路径
#define ICON_DISTANCE  "📏 "      // 距离
#define ICON_ARROW     "➡️ "      // 箭头
#define ICON_SEARCH    "🔍 "      // 查询
#define ICON_RECOMMEND "⭐ "      // 推荐
#define ICON_TIP       "💡 "      // 提示
#define ICON_SUCCESS   "✅ "      // 成功
#define ICON_ERROR     "❌ "      // 错误
#define ICON_WARNING   "⚠️ "      // 警告
#define ICON_INFO      "ℹ️ "      // 信息
#define ICON_EXIT      "🚪 "      // 退出

// 其他Emoji
#define SMILE_FACE     "😊 "      // 笑脸
#define CLOCK_ICON     "⏱️ "      // 时间
#define FOOTPRINT      "👣 "      // 脚步
#define FLAG_ICON      "🚩 "      // 旗帜

// ==================== 工具函数 ====================

 // Windows下设置控制台编码为UTF-8
//正确显示emoji表情也兼顾中文字符的兼容显示

//static方便多个源文件共享使用，同时又避免了因重复定义而产生的链接错误。
static void InitConsole() {
   
    SetConsoleOutputCP(65001);
}

// 清屏函数
static void ClearScreen() {
    system("cls");//Windows特有命令
}

// 打印分割线
static void PrintDivider() {
    printf("═══════════════════════════════════════════════════════════\n");
}

// 打印带图标的菜单标题，在多个功能的标题中都应用了
static void PrintTitle(const char* text) {
    printf("\n");
    PrintDivider();
    printf("          🗺️  %s\n", text);
    PrintDivider();
}

// 显示处理动画，const保护指针参数指向的数据不被修改，message用于传递要显示的处理状态消息
static void ShowProcessing(const char* message) {

    printf("\n");
    // 直接输出信息图标和操作描述
    printf("%s %s", ICON_INFO, message);
    fflush(stdout);//强制输出缓冲区内容直接显示,确保实时显示

    // 简单的点状动画
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(400);//Windows函数，暂停300ms
    }

    // 输出完成标记，确保无额外字符
    printf(" %s 完成！\n", ICON_SUCCESS);
    fflush(stdout);

}

// 暂停程序，等待用户按Enter键，
static void WaitForContinue() {
    printf("\n%s 按Enter键继续...", ICON_TIP);
    fflush(stdout);//强制输出缓冲区即使没有换行符

    // 使用fgets读取整行，包括换行符
    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // 读取失败，直接返回
        return;
    }
    // fgets会读取换行符，所以不需要额外处理
}
#endif // ICONS_H