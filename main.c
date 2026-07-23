/***********************************************************
* 版权所有 (C)2026, 庄鲁
*
* 文件名称： main.c
* 文件标识：无
* 内容摘要：该文件是校园导游系统的主程序入口。负责系统整体流程控制，
*           包括欢迎/退出界面的显示、主菜单的循环与用户交互、以及根据
*           用户选择调用对应的功能模块（如图片地图打开、景点查询、路径
*           规划等）。集成了输入验证和错误处理逻辑。
* 其它说明：无
* 当前版本： V2.0
* 作   者：庄鲁
* 完成日期： 2026.2.26
*
* 修改记录1：
* 修改日期：2026.2.24
* 版本号： V1.0
* 修改人： 庄鲁
* 修改内容：图片的正确文件调用与显示，emoji图标的正确编码显示
**********************************************************/



// main.c - 校园导游系统主程序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "icons.h"

// ==================== 功能模块函数声明 ====================
void ShowWelcome();                     // 显示欢迎界面
int DisplayMenu();                      // 显示主菜单
void ShowGoodbye();                     // 显示退出界面
int CheckImageFile(const char* filename); // 检查图片文件
void OpenImageMap();                    // 打开图片地图
int GetValidInt(int min, int max);      // 获取有效整数（输入验证增强）
void HandleSpotQuery(Graph* graph);     // 处理景点查询
void HandlePathQuery(Graph* graph);     // 处理路径查询

// ==================== 图片处理功能 ====================
// 检查图片文件是否存在
int CheckImageFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// 打开图片查看器
void OpenImageMap() {
    // 尝试的图片文件名列表
    const char* imageFiles[] = {
        "campus_map.jpg", "campus_map.png",
        "map.jpg", "map.png",
        "校园地图.jpg", "校园地图.png"
    };
    int fileCount = sizeof(imageFiles) / sizeof(imageFiles[0]);

    // 查找存在的图片文件
    const char* foundFile = NULL;
    for (int i = 0; i < fileCount; i++) {
        if (CheckImageFile(imageFiles[i])) {
            foundFile = imageFiles[i];
            break;
        }
    }

    if (foundFile) {
        printf("%s 找到图片文件：%s\n", ICON_SUCCESS, foundFile);
        printf("%s 正在尝试打开图片  ...\n", ICON_INFO);

#ifdef _WIN32
        char command[256];
        sprintf(command, "start \"校园地图\" \"%s\"", foundFile);
        int result = system(command);
        if (result == 0) {
            printf("%s 图片已成功打开！\n", ICON_SUCCESS);
        }
        else {
            printf("%s 无法自动打开图片，请手动打开文件。\n", ICON_WARNING);
        }
#else
        printf("%s 非Windows系统，请手动打开图片文件\n", ICON_INFO);
#endif

        printf("\n%s 如果图片没有自动打开，请手动打开文件：%s\n",
            ICON_TIP, foundFile);
    }
    else {
        printf("%s 未找到校园地图图片文件！\n", ICON_ERROR);
        printf("%s 请确保图片文件放在以下位置：\n", ICON_TIP);
        printf("  1. 与 main.c 同一目录\n");
        printf("  2. 文件名应为：campus_map.jpg 或 campus_map.png\n");
        printf("\n%s 当前目录下的文件：\n", ICON_INFO);
        system("dir *.jpg *.png *.bmp 2>nul || echo '未找到图片文件'");
    }
}

// ==================== 输入验证增强 ====================
// 获取有效整数（输入验证增强）
int GetValidInt(int min, int max) {
    int value;
    char input[100];

    while (1) {
        // 读取整行输入
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("%s 读取输入失败！\n", ICON_ERROR);
            continue;
        }

        // 尝试转换为整数
        if (sscanf(input, "%d", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
            else {
                printf("%s 请输入 %d-%d 之间的数字：", ICON_WARNING, min, max);
            }
        }
        else {
            printf("%s 请输入有效的数字：", ICON_ERROR);
        }
    }
}

// ==================== 查询处理模块 ====================
// 处理景点查询
void HandleSpotQuery(Graph* graph) {
    ClearScreen();

    // 自动显示景点列表
    printf("%s 请参考以下景点列表输入代号：\n", ICON_TIP);
    DisplayAllSpots(graph);
    printf("\n");

    printf("%s 请输入要查询的景点代号（%d-%d）：",
        ICON_SEARCH, 0, graph->spotCount - 1);

    int spotId = GetValidInt(0, graph->spotCount - 1);

    ClearScreen();
    ShowProcessing("正在查询景点信息");//动画效果
    ClearScreen();
    QuerySpotInfo(graph, spotId);
}

// 处理路径查询
void HandlePathQuery(Graph* graph) {
    ClearScreen();

    // 自动显示景点列表
    printf("%s 请参考以下景点列表输入代号：\n", ICON_TIP);
    DisplayAllSpots(graph);
    printf("\n");

    printf("%s 请输入起点景点代号（%d-%d）：",
        ICON_START, 0, graph->spotCount - 1);
    int startId = GetValidInt(0, graph->spotCount - 1);

    printf("%s 请输入终点景点代号（%d-%d）：",
        ICON_END, 0, graph->spotCount - 1);
    int endId = GetValidInt(0, graph->spotCount - 1);

    ClearScreen();
    ShowProcessing("正在计算最短路径");
    ClearScreen();
    FindShortestPath(graph, startId, endId);
}

// ==================== 界面函数 ====================
// 显示欢迎界面
void ShowWelcome() {
    ClearScreen();

    printf("\n\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("            🏫 欢迎使用校园导游系统 🗺️\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("             版本 2.0 - 图片地图版\n");
    printf("             基于《数据结构与算法》课程设计\n");
    printf("             所含景点：10个 | 算法：Dijkstra\n");
    printf("═══════════════════════════════════════════════════════════\n");

    printf("\n%s 系统初始化中...", ICON_INFO);
    fflush(stdout);

    // 简单的加载动画
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(300);
    }

    printf(" %s 完成！\n\n", ICON_SUCCESS);
}

// 显示主菜单
int DisplayMenu() {
    int choice;

    printf("\n");
    PrintTitle("主菜单");

    printf("%s 1. 查看校园地图\n", ICON_MAP);
    printf("%s 2. 显示所有景点列表\n", ICON_SPOT);
    printf("%s 3. 查询景点详细信息\n", ICON_SEARCH);
    printf("%s 4. 查询景点间最短路径\n", ICON_PATH);
    printf("%s 5. 查看详细路径数据（邻接矩阵）\n", ICON_INFO);
    printf("%s 0. 退出系统\n", ICON_EXIT);

    PrintDivider();

    printf("\n%s 请选择功能（输入0-5）：", "👉");

    choice = GetValidInt(0, 5);
    return choice;
}

// 显示退出界面
void ShowGoodbye() {
    printf("\n\n");
    PrintDivider();
    printf("            🙏 感谢使用校园导游系统！\n");
    printf("            😊 祝您旅途愉快，再见！\n");
    PrintDivider();
    printf("\n");
}

// ==================== 主函数 ====================
int main() {
    // 初始化控制台（支持UTF-8）
    InitConsole();

    // 显示欢迎界面
    ShowWelcome();

    // 初始化校园图
    Graph campus;
    InitGraph(&campus);

    printf("%s 校园地图数据加载完成！\n", ICON_SUCCESS);
    printf("%s 系统包含 %d 个景点，%d 条路径\n\n", ICON_INFO, campus.spotCount, 13);

    int choice;

    do {
        // 显示主菜单并获取用户选择
        choice = DisplayMenu();

        switch (choice) {
        case 1: // 显示校园地图
            ClearScreen();
            ShowProcessing("正在查找图片地图");
            OpenImageMap();
            break;

        case 2: // 显示所有景点列表
            ClearScreen();
            DisplayAllSpots(&campus);
            break;

        case 3: // 查询景点信息
            HandleSpotQuery(&campus);
            break;

        case 4: // 查询最短路径
            HandlePathQuery(&campus);
            break;

        case 5: // 显示邻接矩阵
            ClearScreen();
            ShowProcessing("正在生成邻接矩阵");
            DisplayAdjMatrix(&campus);
            break;

        case 0: // 退出系统
            ShowGoodbye();
            break;

        default:
            printf("%s 无效的选择，请重新输入！\n", ICON_ERROR);
            break;
        }
        // 暂停，等待用户查看结果（非退出时）
        if (choice != 0) {
            WaitForContinue();
            ClearScreen();
        }

    } while (choice != 0);

    return 0;
}