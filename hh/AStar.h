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
};



//#pragma once
//#include <vector>
//#include <queue>
//#include <unordered_map>
//#include <cmath>
//#include <limits>
//
//// 2Dベクトルを表す構造体
//struct AStarVec2 {
//    // X座標値を格納する
//    std::int_fast32_t x{};
//    // Z座標値を格納する
//    std::int_fast32_t z{};
//
//    // デフォルトコンストラクタ
//    constexpr AStarVec2() noexcept = default;
//
//    // コンストラクタ（座標値を指定）
//    constexpr AStarVec2(const std::int_fast32_t x_, const std::int_fast32_t z_) noexcept : x(x_), z(z_) {}
//
//    // 等価演算子（ベクトル同士の比較）
//    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
//        return vec2_.x == x && vec2_.z == z;
//    }
//};
//
//// A*アルゴリズムのノードを表す構造体
//struct AStarNode {
//    // ノードの位置
//    AStarVec2 position{};
//    // 親ノードの位置
//    AStarVec2 parent_node{};
//    // スタートノードからこのノードまでの距離
//    std::int_fast32_t distance{};
//    // このノードのコスト（f = g + h）
//    std::int_fast32_t cost{};
//
//    // デフォルトコンストラクタ
//    constexpr AStarNode() noexcept = default;
//
//    // コンストラクタ（全てのパラメータを指定）
//    constexpr AStarNode(const AStarVec2& pos_, const AStarVec2& parent_node_, const std::int_fast32_t distance_, const std::int_fast32_t cost_) noexcept
//        : position(pos_), parent_node(parent_node_), distance(distance_), cost(cost_) {}
//
//    // 等価演算子（ノード同士の比較）
//    constexpr bool operator==(const AStarNode& node_) const noexcept {
//        return position == node_.position;
//    }
//
//    // 等価演算子（ノードとベクトルの比較）
//    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
//        return position == vec2_;
//    }
//};
//
//// A*アルゴリズムを実装するクラス
//class Astar {
//private:
//    // グリッド（マップ）データ
//    std::vector<std::vector<int>> grid;
//
//    // ヒューリスティック関数
//    float heuristic(const AStarVec2& a, const AStarVec2& b);
//
//public:
//    // コンストラクタ
//    Astar(const std::vector<std::vector<int>>& grid);
//
//    // パスを見つける関数
//    std::vector<AStarNode> findPath(const AStarVec2& start, const AStarVec2& goal);
//};
