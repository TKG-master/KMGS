#include "patrolSequence.h"

//����N���X�̃C���N���[�h
#include "ActionCheckState.h"
#include "ActionSelectNextWaypoint.h"
#include "ActionMoveToWaypoint.h"
#include "ActionCheckArrival.h"
#include "ActionLookaround.h"


patrolSequence::patrolSequence()
{
    this->AddChild(new ActionCheckState(EStateType::Patrolling));
    this->AddChild(new ActionSelectNextWaypoint());
    this->AddChild(new ActionMoveToWaypoint());
    this->AddChild(new ActionCheckArrival());
    this->AddChild(new ActionLookaround());
}
