// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameObject
//      Abstract class for game all objects. Contains models, evaluates basic physics 
//      and executes other behaviour logic, sends render request to renderer.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
GameObject::GameObject()
{
	Debug("GameObject: object instantiated.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool GameObject::Initialize() {

	Debug ("GameObject: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool GameObject::Shutdown() {

	Debug ("GameObject: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool GameObject::Logic() {
	Debug ("GameObject: Logic() called.");

	// TODO: Update position / rotation based on velocities
	
	return true;
}

// |----------------------------------------------------------------------------|
// |						        Render()									|
// |----------------------------------------------------------------------------|
bool GameObject::Render() {
	Debug ("GameObject: Render() called.");
	
	if (!m_model) 
	{
		Debug ("GameObject: ERROR - no model.");
		return false;
	}

	// Place texture in buffer (as needed)
	AssetManager::GetSingleton().LoadTexture(m_texture);
	
	// Transform matrices to prep for model render
	Matrix4x4 matWorld, matTrans, matRotX, matRotY, matRotZ;
	matTrans.Translation(m_position.x, m_position.y, m_position.z);
	matRotX.RotationX(m_orientation.x);
	matRotY.RotationY(m_orientation.y);
	matRotZ.RotationZ(m_orientation.z);
	// TODO: Change to Yaw, Pitch, Roll when cannon has own class (cannon must be pitch, then yaw)
	matWorld =  matRotX * matRotY * matRotZ * matTrans;
	
	// Render Model
	m_model->SetWorldMatrix(matWorld);
	m_model->Render();

	return true;
}

