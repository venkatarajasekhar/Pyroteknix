// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Billboard
//      Special game object that automatically orients itself to face the camera


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Billboard.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Billboard::Billboard()
{
	Debug("Billboard: object instantiated.");
}

// |----------------------------------------------------------------------------|
// |						        Render()									|
// |----------------------------------------------------------------------------|
bool Billboard::Render() {
	Render(m_position);
}
bool Billboard::Render(Coord position) {
	Debug ("Billboard: Render() called.");
	
	if (!m_model) 
	{
		Debug ("Billboard: ERROR - no model.");
		return false;
	}

	// Place texture in buffer (as needed)
	AssetManager::GetSingleton().LoadTexture(m_texture);
	
	// Transform matrices to prep for model render
	Matrix4x4 matWorld, matTrans, matRotX, matRotY;
	Coord cameraPosition(CPipeline::GetSingleton().GetCameraX(), CPipeline::GetSingleton().GetCameraY(), CPipeline::GetSingleton().GetCameraZ());
	Coord direction = position - cameraPosition;
    float mag = sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
    float yaw = atan2(direction.x,direction.z);
    float pitch = 3.14159265359/2 - acos(-direction.y / mag);
	matTrans.Translation(position.x, position.y, position.z);
	matRotX.RotationX(pitch);
	matRotY.RotationY(yaw);
	matWorld =  matRotX * matRotY * matTrans;
	
	// Render Model
	m_model->SetWorldMatrix(matWorld);
	m_model->Render();

	return true;
}

