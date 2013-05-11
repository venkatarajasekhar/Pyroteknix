// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameObject
//      Abstract class for game all objects. Contains models, evaluates basic physics 
//      and executes other behaviour logic, sends render request to renderer.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <string>
#include "Util.h"
#include "Coord.h"
#include "AssetManager.h"


// |----------------------------------------------------------------------------|
// |                        Class Definition: GameObject                        |
// |----------------------------------------------------------------------------|
class GameObject {

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	GameObject();

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
    // Performs logic functions for the object
    bool virtual Logic();
    
    // Sends any models associated with the object to the renderer
    bool virtual Render();

    // Getter functions
    Coord virtual GetPosition() {return m_position; }
    Coord virtual GetOrientation() {return m_orientation; }
    Coord virtual GetLinearVelocity() {return m_linearVelocity; }
    Coord virtual GetAngularVelocity() {return m_angularVelocity; }
	CTexture* GetTexture() {return m_texture;}
	CMs3dModel* GetModel() {return m_model;}

    // Setter functions
    void virtual SetPosition(Coord position) {m_position = position;}
    void virtual SetOrientation(Coord orientation) {m_orientation = orientation;}
    void virtual SetLinearVelocity(Coord linearVelocity) {m_linearVelocity = linearVelocity;}
    void virtual SetAngularVelocity(Coord angularVelocity) {m_angularVelocity = angularVelocity;}
	void virtual SetTexture(CTexture* value) {m_texture = value;}
	void virtual SetTexture(std::string name) {m_texture = AssetManager::GetSingleton().GetTexture(name);}
	void virtual SetModel(CMs3dModel* value) {m_model = value;}
	void virtual SetModel(std::string name) {m_model = AssetManager::GetSingleton().GetModel(name);}
	
protected:
    
    //|---------------------------Protected Data Members-----------------------|
    Coord m_position;               // Position of the object
    Coord m_orientation;            // Orientation in pitch, yaw, roll
    Coord m_linearVelocity;         // Velocity of the object (updates the position in the Frame function)
    Coord m_angularVelocity;        // Angular velocity in pitch/s, yaw/s, roll/s

    // Graphics
    CTexture* m_texture; 
	CMs3dModel* m_model;

};