#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <cstdint>

// 2D�x�N�g����\���\����
struct AStarVec2 {
    std::int_fast32_t x{};
    std::int_fast32_t z{};

    constexpr AStarVec2() noexcept = default;
    constexpr AStarVec2(const std::int_fast32_t x_, const std::int_fast32_t z_) noexcept : x(x_), z(z_) {}

    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
        return vec2_.x == x && vec2_.z == z;
    }
};

// A*�A���S���Y���̃m�[�h��\���\����
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

// A*�A���S���Y������������N���X
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
//// 2D�x�N�g����\���\����
//struct AStarVec2 {
//    // X���W�l���i�[����
//    std::int_fast32_t x{};
//    // Z���W�l���i�[����
//    std::int_fast32_t z{};
//
//    // �f�t�H���g�R���X�g���N�^
//    constexpr AStarVec2() noexcept = default;
//
//    // �R���X�g���N�^�i���W�l���w��j
//    constexpr AStarVec2(const std::int_fast32_t x_, const std::int_fast32_t z_) noexcept : x(x_), z(z_) {}
//
//    // �������Z�q�i�x�N�g�����m�̔�r�j
//    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
//        return vec2_.x == x && vec2_.z == z;
//    }
//};
//
//// A*�A���S���Y���̃m�[�h��\���\����
//struct AStarNode {
//    // �m�[�h�̈ʒu
//    AStarVec2 position{};
//    // �e�m�[�h�̈ʒu
//    AStarVec2 parent_node{};
//    // �X�^�[�g�m�[�h���炱�̃m�[�h�܂ł̋���
//    std::int_fast32_t distance{};
//    // ���̃m�[�h�̃R�X�g�if = g + h�j
//    std::int_fast32_t cost{};
//
//    // �f�t�H���g�R���X�g���N�^
//    constexpr AStarNode() noexcept = default;
//
//    // �R���X�g���N�^�i�S�Ẵp�����[�^���w��j
//    constexpr AStarNode(const AStarVec2& pos_, const AStarVec2& parent_node_, const std::int_fast32_t distance_, const std::int_fast32_t cost_) noexcept
//        : position(pos_), parent_node(parent_node_), distance(distance_), cost(cost_) {}
//
//    // �������Z�q�i�m�[�h���m�̔�r�j
//    constexpr bool operator==(const AStarNode& node_) const noexcept {
//        return position == node_.position;
//    }
//
//    // �������Z�q�i�m�[�h�ƃx�N�g���̔�r�j
//    constexpr bool operator==(const AStarVec2& vec2_) const noexcept {
//        return position == vec2_;
//    }
//};
//
//// A*�A���S���Y������������N���X
//class Astar {
//private:
//    // �O���b�h�i�}�b�v�j�f�[�^
//    std::vector<std::vector<int>> grid;
//
//    // �q���[���X�e�B�b�N�֐�
//    float heuristic(const AStarVec2& a, const AStarVec2& b);
//
//public:
//    // �R���X�g���N�^
//    Astar(const std::vector<std::vector<int>>& grid);
//
//    // �p�X��������֐�
//    std::vector<AStarNode> findPath(const AStarVec2& start, const AStarVec2& goal);
//};
