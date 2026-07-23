/***********************************************************
* 版权所有 (C)2026, 庄鲁
*
* 文件名称： graph.h
* 文件标识：无
* 内容摘要：该头文件定义了校园导游系统的核心数据结构（图、景点）及所有操作接口。
*           主要包括景点结构体(Spot)、图结构体(Graph)的声明，以及初始化、查询、
*           路径查找、显示等函数的原型。
* 其它说明：无
* 当前版本： V2.0
* 作   者：庄鲁
* 完成日期： 2026.2.26
**********************************************************/


#pragma once
// graph.h - 校园图数据结构与操作函数声明
#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>  // 添加此头文件用于INT_MAX

#define MAX_SPOTS 20     // 最大景点数
#define INF INT_MAX      // 使用整数最大值表示无穷大

// 景点信息结构体
typedef struct {
    int id;                     // 景点代号
    char name[50];             // 景点名称
    char brief[100];           // 景点简介（新增）
    char description[300];     // 景点详细介绍
} Spot;

// 图结构体（使用邻接矩阵存储）
typedef struct {
    Spot spots[MAX_SPOTS];                 // 景点数组
    int matrix[MAX_SPOTS][MAX_SPOTS];      // 邻接矩阵
    int spotCount;                         // 实际景点数量
} Graph;

// 函数声明
void InitGraph(Graph* g);                         // 初始化校园图
void QuerySpotInfo(Graph* g, int spotId);         // 查询景点信息
void FindShortestPath(Graph* g, int startId, int endId); // 查找最短路径
void DisplayAllSpots(Graph* g);                   // 显示所有景点
void DisplayAdjMatrix(Graph* g);                  // 显示邻接矩阵

#endif // GRAPH_H