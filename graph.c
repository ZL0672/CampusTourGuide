/***********************************************************
* 版权所有 (C)2026, 庄鲁
*
* 文件名称： graph.c
* 文件标识：无
* 内容摘要：该源文件实现了校园导游系统图数据结构的操作与核心算法。
*           具体包括：校园地图数据的初始化(InitGraph)、景点信息查询
*           (QuerySpotInfo)、基于Dijkstra算法的最短路径查找
*           (FindShortestPath)、显示所有景点(DisplayAllSpots)及
*           显示邻接矩阵(DisplayAdjMatrix)等功能。
* 其它说明：无
* 当前版本： V2.0
* 作   者：庄鲁
* 完成日期： 2026.2.26
*
* 修改记录1：
* 修改日期：2026.2.23
* 版本号： V1.0
* 修改人： 庄鲁
* 修改内容：注释修改
**********************************************************/


// graph.c - 校园地图操作与最短路径算法实现
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "icons.h"  // 包含图标定义

// ==================== 数据初始化 ====================
void InitGraph(Graph* g) {
    // 初始化10个景点
    g->spotCount = 10;

    // 景点0: 三元湖
    g->spots[0].id = 0;
    strcpy(g->spots[0].name, "三元湖");
    strcpy(g->spots[0].brief, "校园中心的人工湖，标志性景观");
    strcpy(g->spots[0].description, "校园中心的人工湖，标志性景观。湖中夏季荷花盛开，湖心设有烟雨亭，与钟楼倒影相映成趣，是师生散步、静心思考的理想之地，也是校园的标志性景点之一。");

    // 景点1: 钟楼
    g->spots[1].id = 1;
    strcpy(g->spots[1].name, "钟楼");
    strcpy(g->spots[1].brief, "坐落于三元湖北端，中轴线建筑");
    strcpy(g->spots[1].description, "坐落于三元湖北端，中轴线建筑。钟楼每个整点会敲响悠扬的钟声，默默见证着一届届学子的成长，承载着烟大人的共同记忆，是校园的标志性建筑。");

    // 景点2: 八景园
    g->spots[2].id = 2;
    strcpy(g->spots[2].name, "八景园");
    strcpy(g->spots[2].brief, "由八条小径通向中心广场的园林");
    strcpy(g->spots[2].description, "由八条小径通向中心广场的园林。春季园内百花争艳、绿树成荫，秋冬时节松树常青，是师生拍照、课余休憩的热门地点，四季景色各异。");

    // 景点3: 承先图书馆
    g->spots[3].id = 3;
    strcpy(g->spots[3].name, "承先图书馆");
    strcpy(g->spots[3].brief, "烟大主要图书馆，知识核心区");
    strcpy(g->spots[3].description, "烟大主要图书馆，知识核心区。馆内馆藏丰富，学习氛围浓厚，许多学生在此埋头苦读至深夜，是学子汲取知识、梦想启航的重要场所。");

    // 景点4: 青春广场
    g->spots[4].id = 4;
    strcpy(g->spots[4].name, "青春广场");
    strcpy(g->spots[4].brief, "校园内大型开放活动空间");
    strcpy(g->spots[4].description, "校园内大型开放活动空间。广场开阔，充满青春活力，常用于举办文化活动和社团集会，是学生集体活动与日常休闲的主要场所，体现校园活力。");

    // 景点5: 烟大小树林
    g->spots[5].id = 5;
    strcpy(g->spots[5].name, "烟大小树林");
    strcpy(g->spots[5].brief, "校园天然林木区域");
    strcpy(g->spots[5].description, "校园天然林木区域。树林静谧，绿意盎然，是晨读、散步、交谈的好去处，为师生提供清新的氧吧和放松身心的天然空间。");

    // 景点6: 东门海滩
    g->spots[6].id = 6;
    strcpy(g->spots[6].name, "东门海滩");
    strcpy(g->spots[6].brief, "北校区东门外天然海水浴场");
    strcpy(g->spots[6].description, "北校区东门外天然海水浴场。沙滩平缓开阔，沙质细腻，可散步、观海、看日落，是烟大独有的地理优势，感受面朝大海，诗意生活的绝佳地点。");

    // 景点7: 体育场
    g->spots[7].id = 7;
    strcpy(g->spots[7].name, "体育场");
    strcpy(g->spots[7].brief, "综合运动场，锻炼身体场所");
    strcpy(g->spots[7].description, "综合运动场，锻炼身体场所。包含足球场、跑道等设施，场上总有运动健儿挥洒汗水，看台是观赏晚霞的好位置，充满健康、活力的青春气息。");

    // 景点8: 逸夫图书馆
    g->spots[8].id = 8;
    strcpy(g->spots[8].name, "逸夫图书馆");
    strcpy(g->spots[8].brief, "烟大另一主要图书馆");
    strcpy(g->spots[8].description, "烟大另一主要图书馆。建筑风格独特，馆藏资源丰富，学习环境安静，是学生自习、查阅资料的重要场所，与承先图书馆共同构成校园知识中心。");

    // 景点9: 综合楼
    g->spots[9].id = 9;
    strcpy(g->spots[9].name, "综合楼");
    strcpy(g->spots[9].brief, "校园多功能教学楼");
    strcpy(g->spots[9].description, "校园多功能教学楼。集教学办公于一体，风格现代，设施完善，体现校园的学术氛围。");


    // ==================== 初始化邻接矩阵 ====================
    // 首先将所有路径初始化为INF
    for (int i = 0; i < MAX_SPOTS; i++) {
        for (int j = 0; j < MAX_SPOTS; j++) {
            g->matrix[i][j] = INF;
        }
        g->matrix[i][i] = 0; // 自己到自己的距离为0
    }

    // 根据文档设置路径距离
    g->matrix[0][1] = g->matrix[1][0] = 80;      // 三元湖 ↔ 钟楼
    g->matrix[0][2] = g->matrix[2][0] = 200;     // 三元湖 ↔ 八景园
    g->matrix[0][3] = g->matrix[3][0] = 50;      // 三元湖 ↔ 承先图书馆
    g->matrix[1][4] = g->matrix[4][1] = 250;     // 钟楼 ↔ 青春广场
    g->matrix[2][3] = g->matrix[3][2] = 150;     // 八景园 ↔ 承先图书馆
    g->matrix[2][5] = g->matrix[5][2] = 180;     // 八景园 ↔ 烟大小树林
    g->matrix[3][4] = g->matrix[4][3] = 180;     // 承先图书馆 ↔ 青春广场
    g->matrix[4][5] = g->matrix[5][4] = 200;     // 青春广场 ↔ 烟大小树林
    g->matrix[4][8] = g->matrix[8][4] = 600;     // 青春广场 ↔ 逸夫图书馆
    g->matrix[4][9] = g->matrix[9][4] = 650;     // 青春广场 ↔ 综合楼
    g->matrix[5][7] = g->matrix[7][5] = 300;     // 烟大小树林 ↔ 体育场
    g->matrix[5][8] = g->matrix[8][5] = 700;     // 烟大小树林 ↔ 逸夫图书馆
    g->matrix[6][7] = g->matrix[7][6] = 480;     // 东门海滩 ↔ 体育场
    g->matrix[7][9] = g->matrix[9][7] = 400;     // 体育场 ↔ 综合楼
    g->matrix[8][9] = g->matrix[9][8] = 100;     // 逸夫图书馆 ↔ 综合楼
}

// ==================== 功能实现 ====================

// 显示所有景点列表（紧凑格式）
void DisplayAllSpots(Graph* g) {
    printf("\n");
    PrintTitle("校园景点列表");
    printf("%s 共有 %d 个景点：\n\n", ICON_SPOT, g->spotCount);

    for (int i = 0; i < g->spotCount; i++) {
        printf("[%d] %s %s: %s\n\n",
            g->spots[i].id, ICON_SPOT, g->spots[i].name, g->spots[i].brief);
    }

    printf("%s 使用提示：查询时请输入景点代号（方括号内的数字）。\n", ICON_TIP);
}

// 查询景点信息
void QuerySpotInfo(Graph* g, int spotId) {
    //条件判断
    if (spotId < 0 || spotId >= g->spotCount) {
        printf("\n%s 错误：景点代号无效！请输入 0~%d 之间的数字。\n",
            ICON_ERROR, g->spotCount - 1);
        return;
    }

    printf("\n");
    PrintTitle("景点详细信息");

    // 基本信息
    printf("%s 景点名称：%s\n", ICON_SPOT, g->spots[spotId].name);
    printf("%s 景点代号：%d\n", "🔢", spotId);
    printf("%s 简介：%s\n", "📄", g->spots[spotId].brief);

    // 详细描述
    printf("%s 详细介绍：\n", "📋");
    printf("   %s\n\n", g->spots[spotId].description);

    // 显示与该景点相连的路径
    printf("%s 可直接到达的景点：\n", ICON_PATH);
    int hasConnection = 0;//路径标识
    //排除自己到自己的情况，检查两点中是否有路径连接，且距离必须大于0
    for (int i = 0; i < g->spotCount; i++) {
        if (i != spotId && g->matrix[spotId][i] != INF && g->matrix[spotId][i] > 0) {
            printf("  %s %s (%d米)\n", ICON_ARROW, g->spots[i].name, g->matrix[spotId][i]);
            hasConnection = 1;
        }
    }
    if (!hasConnection) {
        printf("  %s 该景点暂时没有直接连接的路径。\n", "➖");
    }
    PrintDivider();//打印分隔线
}


// ==================== Dijkstra算法辅助函数 ====================


//在未访问节点中找到距离最小的节点索引
static int FindMinDistance(int dist[], int visited[], int n) {
    int minDist = INF;//初始化起点到临近节点最小距离为无限大 
    int minIndex = -1;//若无未访问节点，理论上不会发生，返回 -1可触发主函数检查

    //如果此节点未访问并且距离小于当前距离则进行节点与距离的更新
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] < minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }

    return minIndex;//返回距离最小的未访问节点索引
}


//重构并打印最短路径
static void PrintShortestPath(Graph* g, int prev[], int startId, int endId, int dist[]) {

    // 添加参数验证
    if (!g || startId < 0 || startId >= g->spotCount || endId < 0 || endId >= g->spotCount) {
        printf("%s 错误：参数无效！\n", ICON_ERROR);
        return;
    }

    // 检查是否可达，从起点到终点的距离仍然是无穷大则不连通
    if (dist[endId] == INF) {
        printf("%s 无法从 [%s] 到达 [%s]\n",
            ICON_ERROR, g->spots[startId].name, g->spots[endId].name);
        printf("%s 可能原因：两景点间无连通路径。\n", ICON_TIP);
        return;
    }

    // 重构路径
    int path[MAX_SPOTS];//path数组中存储的是从终点到起点的逆序路径
    int pathCount = 0;//作为路径长度的计数器，用于下面的反转path数组
    int current = endId;//从终点开始

    //current==-1即已经回溯到起点
    //prev[current]存储了到 current的最短路径上的前一个节点
    while (current != -1) {
        path[pathCount++] = current;
        current = prev[current];
    }

    // 反转路径（从起点到终点）
    for (int i = 0; i < pathCount / 2; i++) {
        int temp = path[i];
        path[i] = path[pathCount - 1 - i];
        path[pathCount - 1 - i] = temp;
    }

    // 显示路径详情
    printf("%s 起点：%s\n", ICON_START, g->spots[startId].name);
    printf("%s 终点：%s\n", ICON_END, g->spots[endId].name);
    printf("%s 最短距离：%d 米\n\n", ICON_DISTANCE, dist[endId]);

    printf("%s 推荐路线：\n", "👣");
    for (int i = 0; i < pathCount; i++) {
        if (i == 0) {
            printf("  %s %d. %s\n", "🚩", path[i], g->spots[path[i]].name);
        }
        else if (i == pathCount - 1) {
            printf("     %s %d. %s %s\n", ICON_ARROW, path[i],
                g->spots[path[i]].name, ICON_SUCCESS);
        }
        else {
            printf("     %s %d. %s\n", ICON_ARROW, path[i], g->spots[path[i]].name);
        }

        // 显示段距离
        if (i < pathCount - 1) {
            int segmentDist = g->matrix[path[i]][path[i + 1]];
            if (segmentDist != INF) {
                printf("        %s 步行约 %d 米\n", ICON_DISTANCE, segmentDist);
            }
        }
    }

    // 路径总览
    printf("\n%s 路径总览：", ICON_MAP);
    for (int i = 0; i < pathCount; i++) {
        printf("%s", g->spots[path[i]].name);
        if (i < pathCount - 1) printf(" %s ", ICON_ARROW);
    }

    printf("\n\n%s 预计步行时间：约 %d 分钟（按步行速度80米/分钟计算）\n",
        "⏱️", (dist[endId] + 40) / 80);
    printf("%s 祝您游览愉快！\n", "😊");
}


// Dijkstra算法核心实现
static int DijkstraAlgorithm(Graph* g, int startId, int endId,
    int dist[], int visited[], int prev[]) {
    int n = g->spotCount;

    // 初始化
    for (int i = 0; i < n; i++) {
        dist[i] = INF;// 初始距离设为无穷大
        visited[i] = 0;// 所有节点未访问
        prev[i] = -1;//前置节点初始都为-1
    }
    dist[startId] = 0; // 起点到自身的距离为0，

    // 主循环
    for (int count = 0; count < n - 1; count++) {
        // 找到未访问节点中距离最小的
        int u = FindMinDistance(dist, visited, n);

        if (u == -1) break; // 所有可达节点已访问
        if (u == endId) break; // 已找到到终点的最短路径

        visited[u] = 1;//标记这个节点为已访问

        // 更新邻接节点的距离
        /*更新条件：
        1. 节点j未访问
        2. 存在边(u, j)（graph[u][j]非0）
        3. 当前距离非无穷大（避免溢出）
        4. 新路径更短 */
        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->matrix[u][v] != INF && dist[u] != INF &&
                dist[u] + g->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->matrix[u][v];
                prev[v] = u;
            }
        }
    }

    return (dist[endId] != INF);
}


//查找最短路径主函数，调用Dijkstra算法并显示结果
void FindShortestPath(Graph* g, int startId, int endId) {
    // 输入验证
    if (startId < 0 || startId >= g->spotCount ||
        endId < 0 || endId >= g->spotCount) {
        printf("\n%s 错误：景点代号无效！请输入 0~%d 之间的数字。\n",
            ICON_ERROR, g->spotCount - 1);
        return;
    }

    if (startId == endId) {
        printf("\n%s 起点和终点相同，无需移动。\n", ICON_INFO);
        return;
    }

    // Dijkstra算法
    int dist[MAX_SPOTS];//存储从起点到各节点的最短距离
    int visited[MAX_SPOTS];// 标记节点是否已访问
    int prev[MAX_SPOTS];//记录当前路径下节点的前一个节点

    int found = DijkstraAlgorithm(g, startId, endId, dist, visited, prev);

    // 输出结果
    printf("\n");
    PrintTitle("最短路径查询结果");

    if (found) {
        PrintShortestPath(g, prev, startId, endId, dist);
    }
    else {
        printf("%s 无法从 [%s] 到达 [%s]\n",
            ICON_ERROR, g->spots[startId].name, g->spots[endId].name);
        printf("%s 可能原因：两景点间无连通路径。\n", ICON_TIP);
    }
    PrintDivider();
}

// 显示邻接矩阵（完美对齐版）
void DisplayAdjMatrix(Graph* g) {
    printf("\n");
    PrintTitle("邻接矩阵（距离数据）");
    printf("%s INF 表示两点间无直接路径\n\n", ICON_INFO);

    // 第一行：列标题
    printf("%-12s", "代号\\目标");
    for (int j = 0; j < g->spotCount; j++) {
        printf("%6d", j);
    }
    printf("\n");

    // 分隔线
    printf("------------");
    for (int j = 0; j < g->spotCount; j++) {
        printf("------");
    }
    printf("\n");

    // 矩阵内容
    for (int i = 0; i < g->spotCount; i++) {
        // 行标题：景点代号和名称
        char rowTitle[20];
        snprintf(rowTitle, sizeof(rowTitle), "%d:%-6s", i, g->spots[i].name);
        printf("%-12s", rowTitle);

        // 距离数据
        for (int j = 0; j < g->spotCount; j++) {
            if (g->matrix[i][j] == INF) {
                printf("%6s", "INF");
            }
            else if (g->matrix[i][j] == 0) {
                printf("%6d", 0);
            }
            else {
                printf("%6d", g->matrix[i][j]);
            }
        }
        printf("\n");
    }
    // 空行
    printf("\n");
    printf("\n%s 注：此矩阵用于存储校园图中各景点间的路径长度（米）。\n", ICON_TIP);
}