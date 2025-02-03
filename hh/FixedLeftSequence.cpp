#include "FixedLeftSequence.h"
#include "ActionCheckState.h"
#include "ActionWait.h"
#include "ActionTurnTo.h"
#include "ActionCheckTurn.h"

FixedLeftSequence::FixedLeftSequence()
{
    this->AddChild(new ActionCheckState(EStateType::FixedLeft));
    this->AddChild(new ActionWait());
    this->AddChild(new ActionTurnTo(1));
    this->AddChild(new ActionCheckTurn());
}
