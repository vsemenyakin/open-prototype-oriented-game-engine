///////////////////////////////////////////////////////////////////////////////
#ifndef PLSTATEMACHINE_H_
#define PLSTATEMACHINE_H_

///////////////////////////////////////////////////////////////////////////////
#include "../Base/PLCore.h"
#include "Reflection/PLReflection.h"

#include <map>

///////////////////////////////////////////////////////////////////////////////
extern PLString *const kPLStateMachineInitialState;

///////////////////////////////////////////////////////////////////////////////
struct
{
	std::map<PLString, PLReflection *> connections;
	PLReflection *loopReflection;
	void *userInfo;
} typedef PLState;

///////////////////////////////////////////////////////////////////////////////
class PLStateMachine : public PLObject
{
private:
	PLString *currentStateName;

	PLReflection *statesChangingReflection(PLString *inStateNameA,
			PLString *inStateNameB);
	PLReflection *stateLoopReflection(PLString *inStateName);

protected:
	PLState *currentState;
	std::map<PLString, PLState *> states;

public:
	// Class lifecycle
	PLStateMachine();
	virtual ~PLStateMachine();

	// Declaration
	bool declareStateWithName(PLString *inName);
	bool declareStateWithName(PLString *inName, void *inUserInfo);
	bool declareSubmachineWithName(PLStateMachine *inMachine, PLString *inName);

	// Structure building
	bool createLoopConnection(PLString *inStateName,
			PLReflection *inReflection);
	bool connectStates(PLString *inStateNameA, PLString *inStateNameB,
			PLReflection *inReflection);

	// State changing
	bool performLoop();
	bool changeState(PLString *inNextStateName, void *inUserInfo);
	bool setState(PLString *inStateName);

	// Accessors
	bool containsState(PLString *inStateName);
	void *userInfoForState(PLString *inStateName);
};

#endif /* PLSTATEMACHINE_H_ */
