#include "SerchSequence.h"
#include "ActionCheckState.h"
#include "ActionWait.h"
#include "ActionCheck.h"
#include "ActionPathMove.h"


SerchSequence::SerchSequence()
{
    this->AddChild(new ActionCheckState(EStateType::Serch));
    this->AddChild(new ActionWait());
    this->AddChild(new ActionCheck());
    this->AddChild(new ActionPathMove());
}
