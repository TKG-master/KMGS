#include "FixedSequence.h"
#include "ActionCheckState.h"
#include "ActionWait.h"
#include "ActionTurnTo.h"
#include "ActionCheckTurn.h"


FixedSequence::FixedSequence()
{
    this->AddChild(new ActionCheckState(EStateType::Fixed));
    this->AddChild(new ActionWait());
    this->AddChild(new ActionTurnTo(0));
    this->AddChild(new ActionCheckTurn());
}
