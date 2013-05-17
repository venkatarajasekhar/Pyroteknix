// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Firework
//      Controls everything relating to a Firework, including particle system for 
//		trail, explosion, trajectory, and lighting


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Firework.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Firework::Firework() :
    Billboard(),
	m_explosion(0),
	m_trail(0),
	m_speed(300.0f),
	m_hasExploded(true)
{
	Debug ("Firework: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
Firework::Firework(const Firework&) {
	Debug ("Firework: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
Firework::~Firework() {
	Debug ("Firework: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Firework::Initialize() {
    GameObject::Initialize();
	
	// Set up mina graphic
	SetModel("quad");
	SetTexture("particle_point");
	
	// Set up explosion effect
	m_explosion = new FireworkEffect;
	m_explosion->SetModel("quad");
	m_explosion->SetTexture("particle_point");
	m_explosion->SetPosition(m_position);
	m_explosion->SetInitialSpeed(100.0f);
	m_explosion->SetParticleDrag(0.2f);
	m_explosion->SetParticleLifetime(2.0f);
	m_explosion->SetParticleFadeout(0.5f);
	m_explosion->SetMaxParticles(10);
	m_explosion->Initialize();
	
	// Set up trail effect
	m_trail = new ParticleSystem;
	m_trail->SetModel("quad");
	m_trail->SetTexture("particle_point");
	m_trail->SetPosition(m_position);
	m_trail->SetParticleVelocityVariation(Coord(30.0f,30.0f,30.0f));
	m_trail->SetParticleSpawnFrequency(0.1f);
	m_trail->SetParticleLifetime(1.0f);
	m_trail->SetParticleFadeout(0.3f);
	m_trail->SetMaxParticles(10);
	m_trail->SetSpawnParticles(false);
	m_trail->Initialize();

	Debug ("Firework: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool Firework::Shutdown() {
    GameObject::Shutdown();

	m_explosion->Shutdown();
	m_trail->Shutdown();

	Debug ("Firework: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool Firework::Logic() {
	Debug ("Firework: Logic() called.");
	
	if (!m_active) return true;
	
	// If we haven't exploded yet...
	if (!m_hasExploded)
	{
		// Determine if velocity would take us past target. If so, set position as target and explode
		float distanceToTarget = (m_target - m_position).Magnitude();
		float positionIncrement = (m_linearVelocity * (1.0f / 40.0f)).Magnitude();
		if (distanceToTarget < positionIncrement)
		{ // Arrive
			m_position = m_target;
			Explode();
		}
		else
		{
			// Move position based on velocity
			m_position += m_linearVelocity * (1.0f / 40.0f);
		}
		
		// Move all child objects
		m_explosion->SetPosition(m_position);
		m_trail->SetPosition(m_position);
	}
	
	// Call logic functions for child objects
	m_explosion->Logic();
	m_trail->Logic();

	return true;
}


// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool Firework::Render() {
	Debug ("Firework: Render() called.");
    
	if (!m_active) return true;
	
	// Render self only if haven't already exploded
	if(!m_hasExploded)
		Billboard::Render();
	
	// Render children
	m_explosion->Render();
	m_trail->Render();

	return true;
}


// |----------------------------------------------------------------------------|
// |							  SetTarget()									|
// |----------------------------------------------------------------------------|
void Firework::SetTarget(Coord val) {
	Debug ("Firework: SetTarget() called.");
    
	m_target = val;
	
	// Set velocity towards target at m_speed
	Coord direction = m_target - m_position;
	direction = direction / direction.Magnitude(); // Normallize
	m_linearVelocity = direction * m_speed;

	return;
}


// |----------------------------------------------------------------------------|
// |							    Explode()									|
// |----------------------------------------------------------------------------|
void Firework::Explode() {
	Debug ("Firework: Explode() called.");
    
	m_explosion->Explode();
	m_trail->SetSpawnParticles(false);

	m_hasExploded = true;
	
	return;
}


// |----------------------------------------------------------------------------|
// |							     Fire()		    							|
// |----------------------------------------------------------------------------|
void Firework::Fire() {
	Debug ("Firework: Fire() called.");
	
	m_position = Coord(0.0f,0.0f,0.0f);
	m_trail->SetSpawnParticles(true);
	m_hasExploded = false;
	
	return;
}