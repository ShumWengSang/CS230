//------------------------------------------------------------------------------
//
// File Name:	Behavior.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include <functional>
#include "Component.h"
//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct GameObject * GameObjectPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct Behavior * BehaviorPtr;

typedef void(Behavior::*BehaviorFunctionPtr)();
typedef void(Behavior::*BehaviorFunctionPtrDt)(float dt);

//typedef std::function<void(Behavior&)> BehaviorFunctionPtr;
//typedef std::function<void(float)> BehaviorFunctionPtrDt;

// This structure is being declared publicly, as it will be used to implement
// pseudo-inheritance in Project 5.
// NOTE: You are not allowed to change the contents of this structure, as it is
// part of the public interface.
typedef struct Behavior : public Component
{
protected:

	// Behavior Finite-State Machine (FSM) state variables.
	int stateCurr;
	int stateNext;

	friend class Spaceship;

	virtual void OnExit() = 0;
	virtual void OnInit() = 0;
	virtual void OnUpdate(float dt) = 0;

	// Additional variables shared by all behaviors.
	// NOTE: Variables that are unique to a specific behavior should not be placed here.

	// Generic timer - may be used as a life timer or a weapon cooldown timer.
	// (Default = 0, means infinite amount of time remaining or weapon can be fired.)
	float	timer;

public:
	// Dynamically allocate a clone of an existing behavior.
	// (Hint: Perform a shallow copy of the member variables, then change the 'parent' pointer.)
	// Params:
	//	 other = Pointer to the component to be cloned.
	//   parent = Pointer to the cloned component's parent.
	// Returns:
	//	 If 'other' is valid and the memory allocation was successful,
	//	   then return a pointer to the cloned component,
	//	   else return NULL.
	// virtual BehaviorPtr Clone(GameObjectPtr parent = NULL) const = 0;
	Behavior(const Behavior& other) = default;
	Behavior(int curr, int next, GameObjectPtr parent);
	virtual ~Behavior();

	void Draw() override;

	// Update the behavior component.
	// (Hint: Refer to the Word document for detailed instructions regarding this function.)
	// Params:
	//	 behavior = Pointer to the behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

} Behavior;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
