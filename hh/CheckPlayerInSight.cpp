#include "CheckPlayerInSight.h"
#include "Enemy.h"
#include "player.h"

bool CheckPlayerInSight::Execute(Enemy* enemy) {
    // �v���C���[�����E���ɂ��邩�ǂ������`�F�b�N
    // ���̃`�F�b�N�i���ۂɂ͎��E�Ɋւ���v�Z�������j

    return  enemy->IsInView(enemy->GetPosition(), enemy->Getforward(), 60.0f, enemy->getPlayer()->GetPosition(), 50.0f);
}
