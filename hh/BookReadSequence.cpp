#include "BookReadSequence.h"
#include "ActionCheckState.h"
#include "ActionBookRead.h"

BookReadSequence::BookReadSequence()
{
	this->AddChild(new ActionCheckState(EStateType::BookRead));
	this->AddChild(new ActionBookRead());
}
