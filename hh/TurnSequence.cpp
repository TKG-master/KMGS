#include "TurnSequence.h"
#include "ActionCheckState.h"
#include "ActionPerformTurn.h"


TurnSequence::TurnSequence()
{
	this->AddChild(new ActionCheckState(EStateType::Turn));
	this->AddChild(new ActionPerformTurn());
}
