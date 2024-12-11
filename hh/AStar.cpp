#include "Astar.h"
#include <iostream>

float Astar::heuristic(const AStarVec2& a, const AStarVec2& b)
{
    return std::abs(a.x - b.x) + std::abs(a.z - b.z);
}

Astar::Astar(const std::vector<std::vector<int>>& grid) : grid(grid) {}

std::vector<AStarNode> Astar::findPath(const AStarVec2& start, const AStarVec2& goal)
{
    // ノード比較のためのラムダ関数。コストが小さい順に並べるための比較関数
    auto compare = [](const AStarNode& a, const AStarNode& b) {
        return a.cost > b.cost;
        };
    // 優先度付きキュー (最小ヒープ) を使ってオープンリストを作成
    std::priority_queue<AStarNode, std::vector<AStarNode>, decltype(compare)> openList(compare);
    // オープンリストとクローズドリストを管理するマップ
    std::unordered_map<int, AStarNode> openMap, closedMap;

    // 開始ノードを作成し、オープンリストに追加
    AStarNode startNode(start, start, 0, heuristic(start, goal));
    openList.push(startNode);
    openMap[start.x * grid[0].size() + start.z] = startNode;

    // オープンリストが空になるまでループする
    while (!openList.empty()) {
        // オープンリストからコストの最も低いノードを取得する
        AStarNode current = openList.top();
        openList.pop();
        // オープンマップからも削除
        openMap.erase(current.position.x * grid[0].size() + current.position.z);

        // 目標位置に到達したとき経路を再構築して返す
        if (current.position == goal) {
            std::vector<AStarNode> path;
            while (!(current.position == start)) {
                path.push_back(current);
                current = closedMap[current.parent_node.x * grid[0].size() + current.parent_node.z];
            }
            path.push_back(current);
            std::reverse(path.begin(), path.end());
            return path;
        }

        // 現在のノードをクローズドリストに追加
        closedMap[current.position.x * grid[0].size() + current.position.z] = current;


        // 隣接ノードの座標
        std::vector<AStarVec2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };//右　左　下　上
        for (const auto& dir : directions) {
            AStarVec2 neighborPos(current.position.x + dir.x, current.position.z + dir.z);
            // 隣接ノードがグリッド内かつ障害物でない場合
            if (neighborPos.x >= 0 && neighborPos.x < grid.size() && neighborPos.z >= 0 && neighborPos.z < grid[0].size()) {
                if (grid[neighborPos.x][neighborPos.z] != 1 && grid[neighborPos.x][neighborPos.z] != 6)
                {
                    // 隣接ノードがクローズドリストにある場合は無視する
                    if (closedMap.find(neighborPos.x * grid[0].size() + neighborPos.z) != closedMap.end()) continue;


                    // 現在のノードから隣接ノードへの暫定の移動コストを計算
                    std::int_fast32_t tentative_g = current.distance + 1;
                    // 隣接ノードを作成し、コストを計算
                    AStarNode neighbor(neighborPos, current.position, tentative_g, tentative_g + heuristic(neighborPos, goal));

                    // 隣接ノードがオープンリストにないまたは新しいコストが既存のコストよりも小さい場合
                    if (openMap.find(neighborPos.x * grid[0].size() + neighborPos.z) == openMap.end() || tentative_g < openMap[neighborPos.x * grid[0].size() + neighborPos.z].distance) {
                        // 隣接ノードをオープンリストに追加しオープンマップを更新
                        openList.push(neighbor);
                        openMap[neighborPos.x * grid[0].size() + neighborPos.z] = neighbor;
                    }
                }
            }
        }
    }

    // 目標位置に到達できなかった場合空の経路を返す
    return {};
}
