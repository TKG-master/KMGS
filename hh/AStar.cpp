#include "Astar.h"
#include <iostream>

float Astar::heuristic(const AStarVec2& a, const AStarVec2& b)
{
    return std::abs(a.x - b.x) + std::abs(a.z - b.z);
}

Astar::Astar(const std::vector<std::vector<int>>& grid) : grid(grid) {}

std::vector<AStarNode> Astar::findPath(const AStarVec2& start, const AStarVec2& goal)
{
    // �m�[�h��r�̂��߂̃����_�֐��B�R�X�g�����������ɕ��ׂ邽�߂̔�r�֐�
    auto compare = [](const AStarNode& a, const AStarNode& b) {
        return a.cost > b.cost;
        };
    // �D��x�t���L���[ (�ŏ��q�[�v) ���g���ăI�[�v�����X�g���쐬
    std::priority_queue<AStarNode, std::vector<AStarNode>, decltype(compare)> openList(compare);
    // �I�[�v�����X�g�ƃN���[�Y�h���X�g���Ǘ�����}�b�v
    std::unordered_map<int, AStarNode> openMap, closedMap;

    // �J�n�m�[�h���쐬���A�I�[�v�����X�g�ɒǉ�
    AStarNode startNode(start, start, 0, heuristic(start, goal));
    openList.push(startNode);
    openMap[start.x * grid[0].size() + start.z] = startNode;

    // �I�[�v�����X�g����ɂȂ�܂Ń��[�v����
    while (!openList.empty()) {
        // �I�[�v�����X�g����R�X�g�̍ł��Ⴂ�m�[�h���擾����
        AStarNode current = openList.top();
        openList.pop();
        // �I�[�v���}�b�v������폜
        openMap.erase(current.position.x * grid[0].size() + current.position.z);

        // �ڕW�ʒu�ɓ��B�����Ƃ��o�H���č\�z���ĕԂ�
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

        // ���݂̃m�[�h���N���[�Y�h���X�g�ɒǉ�
        closedMap[current.position.x * grid[0].size() + current.position.z] = current;


        // �אڃm�[�h�̍��W
        std::vector<AStarVec2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };//�E�@���@���@��
        for (const auto& dir : directions) {
            AStarVec2 neighborPos(current.position.x + dir.x, current.position.z + dir.z);
            // �אڃm�[�h���O���b�h������Q���łȂ��ꍇ
            if (neighborPos.x >= 0 && neighborPos.x < grid.size() && neighborPos.z >= 0 && neighborPos.z < grid[0].size()) {
                if (grid[neighborPos.x][neighborPos.z] != 1 && grid[neighborPos.x][neighborPos.z] != 6)
                {
                    // �אڃm�[�h���N���[�Y�h���X�g�ɂ���ꍇ�͖�������
                    if (closedMap.find(neighborPos.x * grid[0].size() + neighborPos.z) != closedMap.end()) continue;


                    // ���݂̃m�[�h����אڃm�[�h�ւ̎b��̈ړ��R�X�g���v�Z
                    std::int_fast32_t tentative_g = current.distance + 1;
                    // �אڃm�[�h���쐬���A�R�X�g���v�Z
                    AStarNode neighbor(neighborPos, current.position, tentative_g, tentative_g + heuristic(neighborPos, goal));

                    // �אڃm�[�h���I�[�v�����X�g�ɂȂ��܂��͐V�����R�X�g�������̃R�X�g�����������ꍇ
                    if (openMap.find(neighborPos.x * grid[0].size() + neighborPos.z) == openMap.end() || tentative_g < openMap[neighborPos.x * grid[0].size() + neighborPos.z].distance) {
                        // �אڃm�[�h���I�[�v�����X�g�ɒǉ����I�[�v���}�b�v���X�V
                        openList.push(neighbor);
                        openMap[neighborPos.x * grid[0].size() + neighborPos.z] = neighbor;
                    }
                }
            }
        }
    }

    // �ڕW�ʒu�ɓ��B�ł��Ȃ������ꍇ��̌o�H��Ԃ�
    return {};
}
