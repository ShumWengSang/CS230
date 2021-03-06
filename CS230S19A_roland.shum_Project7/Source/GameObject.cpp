//------------------------------------------------------------------------------
//
// File Name:	GameObject.c
// Author(s):	Roland Shum
// Project:		MyGame
// Course:		CS230S19
//
// Copyright � 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameObject.h"

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 name = The name of the game object being created.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
GameObject::GameObject(const char *name) : name(name), components{ 0 }, isDestroyedp(0)
{

}

// Dynamically allocate a clone of an existing game object.
// (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
// (WARNING: When you clone the behavior component you need to change the 'parent' variable.)
// Params:
//	 other = Pointer to the game object to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned object,
//	   else return NULL.
GameObject::GameObject(const GameObject &copy) :name(copy.name), components{ 0 }, isDestroyedp(copy.isDestroyedp)
{
  // Clone the gameobject.
	for (int i = 0; i < Component::Max_Component_Type; i++)
	{
		if (copy.components[i] != NULL)
		{
			this->components[i] = copy.components[i]->Clone();
			this->components[i]->SetParent(this);
		}
	}
	

 // // Clone the components and set them.
	//if(copy.behavior != NULL)
	//	this->behavior = copy.behavior->Clone();
	//if(copy.sprite != NULL)
	//	this->sprite = new Sprite(*copy.sprite);
	//if(copy.animation != NULL)
	//	this->animation = new Animation(*copy.animation);
	//if(copy.physics != NULL)
	//	this->physics = new Physics(*copy.physics);
	//if(copy.transform != NULL)
	//	this->transform = new Transform(*copy.transform);
	//if(copy.collider != NULL)
	//	this->collider = copy.collider->Clone();
}

// Flag a game object for destruction.
// (Note: This is to avoid game objects being destroyed while they are being processed.)
// Params:
//	 gameObject = Pointer to the game object to be destroyed.
// Returns:
//	 If 'gameObject' is valid,
//	   then set the 'isDestroyed' boolean variable,
//	   else bail.
void GameObject::Destroy()
{
	this->isDestroyedp = true;
}

// Check whether a game object has been flagged for destruction.
// Params:
//	 gameObject = Pointer to the game object to be checked.
// Returns:
//	 If 'gameObject' is valid,
//	   then return the 'isDestroyed' boolean variable,
//	   else return false.
bool GameObject::isDestroyed()
{
	return this->isDestroyedp;
}

// Free the memory associated with a game object, including all components.
// (Also, set the game object pointer to NULL.)
// Params:
//	 gameObject = Pointer to the game object pointer.
GameObject::~GameObject()
{
	for (int i = 0; i < Component::Max_Component_Type; i++)
	{
		if (components[i] != NULL)
		{
			delete this->components[i];
			this->components[i] = NULL;
		}
	}
}

// Attach a physics component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   physics = Pointer to the physics component to be attached.
void GameObject::addPhysics(PhysicsPtr physics)
{
	/* Delete the previous physics, then set. */
	addComponent(physics);
}

// Attach an animation component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   animation = Pointer to the animation component to be attached.
void GameObject::addAnimation(AnimationPtr animation)
{
	addComponent(animation);
}

// Attach a sprite component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   sprite = Pointer to the sprite component to be attached.
void GameObject::addSprite(SpritePtr sprite)
{
	addComponent(sprite);
}

// Attach a transform component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   transform = Pointer to the transform component to be attached.
void GameObject::addTransform(TransformPtr transform)
{
	addComponent(transform);
}

// Attach a behavior component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   behavior = Pointer to the behavior component to be attached.
void GameObject::addBehavior(BehaviorPtr behavior)
{
	addComponent(behavior);
    // Set the behavior
	//GameObject *thisPtr(this);
	// Set the parent
    //behavior->parent = GameObjectSPtr(thisPtr);
}

// Attach a collider component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   collider = Pointer to the collider component to be attached.
void GameObject::addCollider(ColliderPtr collider)
{
	addComponent(collider);
	//collider->parent = gameObject;
	//gameObject->collider = collider;
}

// Get the physics component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
PhysicsPtr GameObject::getPhysics() const
{
	return dynamic_cast<PhysicsPtr>(this->components[Component::Physics]);
}

// Get the animation component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached animation component,
//		else return NULL.
AnimationPtr GameObject::getAnimation() const
{
	return dynamic_cast<AnimationPtr>(this->components[Component::Animation]);
}

// Get the sprite component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached sprite component,
//		else return NULL.
SpritePtr GameObject::getSprite() const
{
	return dynamic_cast<SpritePtr>(this->components[Component::Sprite]);
}

// Get the transform component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached transform component,
//		else return NULL.
TransformPtr GameObject::getTransform() const
{
	return dynamic_cast<TransformPtr>(this->components[Component::Transform]);
}

// Get the collider component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached collider component,
//		else return NULL.
ColliderPtr GameObject::getCollider() const
{
	return dynamic_cast<ColliderPtr>(this->components[Component::Collider]);
}

// Get the behavior component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached behavior component,
//		else return NULL.
BehaviorPtr GameObject::getBehavior() const
{
	return dynamic_cast<BehaviorPtr>(this->components[Component::Behavior]);
}

// Get the game object's name.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the game object's name,
//		else return NULL.
const char * GameObject::getName() const
{
	return this->name;
}

// Compare the game object's name with the specified name.
// Params:
//	 gameObject = Pointer to the game object.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the game object pointer is valid,
//		then return true if the names match, false otherwise,
//		else return false.
bool GameObject::isNamed(const char * name) const
{
    // Compare both strings. IF they are the same
    if (strcmp(this->name, name) == 0)
    {
      return true;
    }
    // else return false
    return false;
}

// Update any components attached to the game object.
// (Hint: You will need to call PhysicsUpdate().)
// (NOTE: You must first check for a valid pointer before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
//	 dt = Change in time (in seconds) since the last game loop.
void GameObject::Update(float dt)
{
	for (int i = 0; i < Component::Max_Component_Type; i++)
	{
		if (this->components[i] != NULL)
		{
			this->components[i]->Update(dt);
		}
	}
}

// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObject::Draw() const
{
	for (int i = 0; i < Component::Max_Component_Type; i++)
	{
		if (this->components[i] != NULL)
		{
			this->components[i]->Draw();
		}
	}
}

ComponentPtr GameObject::getComponent(Component::TypeEnum type) const
{
	return this->components[type];
}

void GameObject::addComponent(ComponentPtr component)
{
	int index = component->GetComponent();
	if (this->components[index] != NULL)
	{
		printf("There is something here already!\n");
		delete components[index];
	}
	this->components[index] = component;
	component->SetParent(this);
}