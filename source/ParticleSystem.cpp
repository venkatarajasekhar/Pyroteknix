// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ParticleSystem
//      Manages a set of particles, emitted and handled based on set parameters


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "ParticleSystem.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
ParticleSystem::ParticleSystem() :
    m_tintR(1.0f),
    m_tintG(1.0f),
    m_tintB(1.0f),
    m_alpha(1.0f),
    m_tintRVar(0.0f),
    m_tintGVar(0.0f),
    m_tintBVar(0.0f),
    m_alphaVar(0.0f),
    m_particleDeviation(0.0f,0.0f,0.0f),
    m_particleVelocity(0.0f,0.0f,0.0f),
    m_particleVelocityVariation(0.0f,0.0f,0.0f),
    m_particleSize(0),
    m_particleSpawnFrequency(0),
    m_particleFadeout(0),
    m_particleLifetime(0),
    m_maxParticles(0),
	m_spawnParticles(true),
    m_accumulatedTime(0.0f),
    m_frameTime(0.0f),
    m_particles(0),
    Billboard()
{
	Debug ("ParticleSystem: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
ParticleSystem::ParticleSystem(const ParticleSystem&) {
	Debug ("ParticleSystem: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
ParticleSystem::~ParticleSystem() {
	Debug ("ParticleSystem: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Initialize() {
    GameObject::Initialize();

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;
	m_timer.PrimeTimer();

    // Clear any elements in the list
    m_particles.clear();

	Debug ("ParticleSystem: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Shutdown() {
    GameObject::Shutdown();

    // Clear any elements in the list
    m_particles.clear();
	m_accumulatedTime = 0.0f;

	Debug ("ParticleSystem: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Logic() {
	Debug ("ParticleSystem: Logic() called.");
	
	if (!m_active) return true;
	
	// Increment the frame time.
    //m_frameTime = m_timer.GetTimeDelta() / 1000;
    m_frameTime = (1.0f/40.0f);
	Debug ("ParticleSystem: m_frameTime = %f",m_frameTime);
	m_accumulatedTime += m_frameTime;
	Debug ("ParticleSystem: m_accumulatedTime = %f",m_accumulatedTime);
    
	// Move position based on velocity
	m_position += m_linearVelocity * (1.0f / 40.0f);
	
	// Emit new particles.
	EmitParticles();
	
	// Update the position of the particles.
	UpdateParticles();

	// Release old particles.
	KillParticles();

	return true;
}


// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool ParticleSystem::Render() {
	Debug ("ParticleSystem: Render() called.");
    
	if (!m_active) return true;
	
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
		// TODO: Particle Coloring
        //m_graphic->SetTint(it->red,it->green,it->blue,it->alpha);
        Billboard::Render(it->position);
    }

	return true;
}


// |----------------------------------------------------------------------------|
// |						   EmitParticles()			    					|
// |----------------------------------------------------------------------------|
void ParticleSystem::EmitParticles() {
	Debug ("ParticleSystem: EmitParticles() called.");
    

	// Set emit particle to false for now.
	bool emitParticle = false;
    
	// Check if it is time to emit a new particle or not.
	if(m_accumulatedTime > (m_particleSpawnFrequency))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}
    else return;
    
	if((emitParticle == true) && (m_particles.size() < (m_maxParticles - 1)) && m_spawnParticles)
    {
	    Debug ("ParticleSystem: Emitting Particle. --------------------------------------------------------------------");

		// Now generate the randomized particle properties.
        ParticleType newParticle;
		newParticle.position.x = m_position.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.x;
		newParticle.position.y = m_position.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.y;
		newParticle.position.z = m_position.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleDeviation.z;

		newParticle.velocity.x = m_particleVelocity.x + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.x;
        newParticle.velocity.y = m_particleVelocity.y + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.y;
		newParticle.velocity.z = m_particleVelocity.z + (((float)rand()-(float)rand())/RAND_MAX) * m_particleVelocityVariation.z;
        
		newParticle.red   = Clamp(m_tintR + (((float)rand()-(float)rand())/RAND_MAX) * m_tintRVar,0.0f,1.0f);
		newParticle.green = Clamp(m_tintG + (((float)rand()-(float)rand())/RAND_MAX) * m_tintGVar,0.0f,1.0f);
		newParticle.blue  = Clamp(m_tintB + (((float)rand()-(float)rand())/RAND_MAX) * m_tintBVar,0.0f,1.0f);
		newParticle.alpha = Clamp(m_alpha + (((float)rand()-(float)rand())/RAND_MAX) * m_alphaVar,0.0f,1.0f);

		newParticle.lifetime = 0.0f;
        newParticle.maxLife = m_particleLifetime;

        // Add the new particle to the list
        m_particles.push_back(newParticle);
    }

	return;
}


// |----------------------------------------------------------------------------|
// |						   UpdateParticles()			    				|
// |----------------------------------------------------------------------------|
void ParticleSystem::UpdateParticles() {
	Debug ("ParticleSystem: UpdateParticles() called.");
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
        // Move particle based on velocity
        it->position += it->velocity * m_frameTime;

        // Update particle lifetime
        it->lifetime += m_frameTime;

        // Update particle alpha
        if (it->lifetime > m_particleFadeout)
            it->alpha = m_alpha * (m_particleLifetime - it->lifetime) / (m_particleLifetime - m_particleFadeout);
    }

    // Sort particles based on distance from camera
    m_particles.sort();

	return;
}


// |----------------------------------------------------------------------------|
// |						   KillParticles()			    					|
// |----------------------------------------------------------------------------|
// is_dead check for particles
bool ParticleIsDead (const ParticleSystem::ParticleType& val) 
{ 
	return (val.lifetime > val.maxLife); 
}
void ParticleSystem::KillParticles() {
	Debug ("ParticleSystem: KillParticles() called.");
    
    m_particles.remove_if (ParticleIsDead);

	return;
}


// |----------------------------------------------------------------------------|
// |					    ParticleType::operator<()							|
// |----------------------------------------------------------------------------|
bool ParticleSystem::ParticleType::operator<(const ParticleType& rhs) {
	
	Coord cameraPosition(CPipeline::GetSingleton().GetCameraX(), CPipeline::GetSingleton().GetCameraY(), CPipeline::GetSingleton().GetCameraZ());
    Coord direction = cameraPosition - position;
    float distanceSqrThis = direction.x*direction.x 
        + direction.y*direction.y 
        + direction.z*direction.z;
    direction = cameraPosition - rhs.position;
    float distanceSqrRHS = direction.x*direction.x 
        + direction.y*direction.y 
        + direction.z*direction.z;

	return distanceSqrThis > distanceSqrRHS;
}
