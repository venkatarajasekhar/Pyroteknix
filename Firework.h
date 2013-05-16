// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Firework
//      Controls everything relating to a Firework, including particle system for 
//		trail, explosion, trajectory, and lighting
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <list>
#include <math.h>
#include "Util.h"
#include "Billboard.h"
#include "FireworkEffect.h"
#include "ParticleSystem.h"


// |----------------------------------------------------------------------------|
// |                        Class Definition: Firework                          |
// |----------------------------------------------------------------------------|
class Firework : public Billboard {


public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Firework();
	Firework(const Firework&);
	virtual ~Firework();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Render();
	
	// Setters
	void virtual SetTexture(std::string name) {m_texture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	void virtual SetTarget(Coord val);
	
	// Firework
	void virtual Explode();
	void virtual Fire();
	bool virtual HasExploded() { return m_hasExploded; }

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // Firework parameters
	FireworkEffect* m_explosion;
	ParticleSystem* m_trail;
	Coord m_target;
	float m_speed;
	bool m_hasExploded;
};

#endif