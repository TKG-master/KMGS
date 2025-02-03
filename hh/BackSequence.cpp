#include "BackSequence.h"
#include "ActionCheckState.h"
#include "ActionWait.h"
#include "ActionCheck.h"
#include "ActionPathMove.h"

BackSequence::BackSequence()
{
    this->AddChild(new ActionCheckState(EStateType::Back));
    this->AddChild(new ActionWait());
    this->AddChild(new ActionCheck());
    this->AddChild(new ActionPathMove());
}
