#include "BookconnectionSequence.h"
#include "ActionCheckState.h"
#include "ActionWait.h"
#include "ActionCheck.h"
#include "ActionPathMove.h"

BookconnectionSequence::BookconnectionSequence()
{
    this->AddChild(new ActionCheckState(EStateType::Bookconnection));
    this->AddChild(new ActionWait());
    this->AddChild(new ActionCheck());
    this->AddChild(new ActionPathMove());
}
