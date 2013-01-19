///////////////////////////////////////////////////////////////////////////////
#include "PLStateMachine.h"
#include "Reflection/PLReflection.h"

///////////////////////////////////////////////////////////////////////////////
PLString *const kPLStateMachineInitialState = PL_STR("initialState");

///////////////////////////////////////////////////////////////////////////////
PLStateMachine::PLStateMachine()
{
	declareStateWithName(kPLStateMachineInitialState);
}

PLStateMachine::~PLStateMachine()
{
}

///////////////////////////////////////////////////////////////////////////////
bool PLStateMachine::declareStateWithName(PLString *inName, void *inUserInfo)
{
	if (states.end() !=  states.find(inName))
	{
		return false;
	}

	PLState *theState = new PLState();
	theState->userInfo = inUserInfo;
	states[inName] = theState;
	return true;
}

bool PLStateMachine::declareStateWithName(PLString *inName)
{
	return declareStateWithName(inName, NULL);
}

///////////////////////////////////////////////////////////////////////////////
bool PLStateMachine::connectStates(PLString *inStateNameA,
		PLString *inStateNameB, PLReflection *inReflection)
{
	if (containsState(inStateNameA) && inStateNameA == inStateNameB)
	{
		states[inStateNameA]->loopReflection = inReflection;
		return true;
	}

	if (containsState(inStateNameB))
	{
		((states[inStateNameA])->connections)[inStateNameB] = inReflection;
		return true;
	}

	return false;
}

bool PLStateMachine::createLoopConnection(PLString *inStateName,
		PLReflection *inReflection)
{
	return connectStates(inStateName, inStateName, inReflection);
}

///////////////////////////////////////////////////////////////////////////////
bool PLStateMachine::changeState(PLString *inNextStateName, void *inUserInfo)
{
	if (currentStateName == inNextStateName)
	{
		if (NULL == currentState->loopReflection)
		{
			return false;
		}

		//theReflection->setArgument(inUserInfo);
		currentState->loopReflection->call();

		return true;
	}

	PLReflection *theReflection = statesChangingReflection(currentStateName,
			inNextStateName);
	if (NULL != theReflection)
	{
		theReflection->setArgument(inUserInfo);
		theReflection->call();

		currentState = states[inNextStateName];
		currentStateName = inNextStateName;

		return true;
	}

	return false;
}

bool PLStateMachine::performLoop()
{
	//return changeState(currentStateName);
}

///////////////////////////////////////////////////////////////////////////////
bool PLStateMachine::setState(PLString *inStateName)
{
	if (containsState(inStateName))
	{
		currentState = states[inStateName];
		currentStateName = inStateName;

		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
PLReflection *PLStateMachine::stateLoopReflection(
		PLString *inStateName)
{
	if (containsState(inStateName))
	{
		return states[inStateName]->loopReflection;
	}

	return NULL;
}

PLReflection *PLStateMachine::statesChangingReflection(
		PLString *inStateNameA, PLString *inStateNameB)
{
	if (containsState(inStateNameA) && containsState(inStateNameB))
	{
		return (states[inStateNameA]->connections)[inStateNameB];
	}
	else
	{
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
bool PLStateMachine::containsState(PLString *inStateName)
{
	return states.end() != states.find(inStateName);
}

void *PLStateMachine::userInfoForState(PLString *inStateName)
{
	return states[inStateName]->userInfo;
}
