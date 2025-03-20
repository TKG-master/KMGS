#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <cstdint>

// 2Dベクトルを表す構造体
struct AStarVec2 {
    std::int_fast32_t x{};
    std::int_fast32_t z{};

    constexpr AStarVec2() noexcept = default;
    constexpr AStarVec2(const std::int_fast32_t x_, const std::int_fast32_t z_) noexcept : x(x_), z(z_) {}

    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
        return vec2_.x == x && vec2_.z == z;
    }
};

// A*アルゴリズムのノードを表す構造体
struct AStarNode {
    AStarVec2 position{};
    AStarVec2 parent_node{};
    std::int_fast32_t distance{};
    std::int_fast32_t cost{};

    constexpr AStarNode() noexcept = default;
    constexpr AStarNode(const AStarVec2& pos_, const AStarVec2& parent_node_, const std::int_fast32_t distance_, const std::int_fast32_t cost_) noexcept
        : position(pos_), parent_node(parent_node_), distance(distance_), cost(cost_) {}

    constexpr bool operator==(const AStarNode& node_) const noexcept {
        return position == node_.position;
    }

    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
        return position == vec2_;
    }
};

// A*アルゴリズムを実装するクラス
class Astar {
private:
    std::vector<std::vector<int>> grid;

    int_fast32_t heuristic(const AStarVec2& a, const AStarVec2& b);

public:
    Astar(const std::vector<std::vector<int>>& grid);
    std::vector<AStarNode> findPath(const AStarVec2& start, const AStarVec2& goal);
    // 音の減衰を計算し、音が到達可能かを判定する関数
    bool isSoundReachable(const AStarVec2& start, const AStarVec2& goal, float initialVolume, float attenuationRate, float minThreshold);
};