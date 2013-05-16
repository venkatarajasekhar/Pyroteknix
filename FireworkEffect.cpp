// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// FireworkEffect
//      Manages a set of particles, emitted and handled based on set parameters


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "FireworkEffect.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
FireworkEffect::FireworkEffect() :
    Billboard(),
    m_tintR(1.0f),
    m_tintG(1.0f),
    m_tintB(1.0f),
    m_alpha(1.0f),
    m_tintRVar(0.0f),
    m_tintGVar(0.0f),
    m_tintBVar(0.0f),
    m_alphaVar(0.0f),
    m_particleSize(0.0f),
    m_particleInitialSpeed(0.0f),
    m_particleDrag(0.0f),
    m_particleFadeout(0.0f),
    m_particleLifetime(0.0f),
    m_maxParticles(0),
	m_gravity(1.5f),
    m_accumulatedTime(0.0f),
    m_frameTime(0.0f)
{
	Debug ("FireworkEffect: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
FireworkEffect::FireworkEffect(const FireworkEffect&) {
	Debug ("FireworkEffect: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
FireworkEffect::~FireworkEffect() {
	Debug ("FireworkEffect: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool FireworkEffect::Initialize() {
    GameObject::Initialize();

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

    // Clear any elements in the list
    m_particles.clear();

	Debug ("FireworkEffect: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool FireworkEffect::Shutdown() {
    GameObject::Shutdown();

    // Clear any elements in the list
    m_particles.clear();
	m_accumulatedTime = 0.0f;

	Debug ("FireworkEffect: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool FireworkEffect::Logic() {
	Debug ("FireworkEffect: Logic() called.");
	
	if (!m_active) return true;
	
	// Increment the frame time.
    m_frameTime = (1.0f/40.0f);
	
	// Update the position of the particles.
	UpdateParticles();

	// Release old particles.
	KillParticles();

	return true;
}


// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool FireworkEffect::Render() {
	Debug ("FireworkEffect: Render() called.");
    
	if (!m_active) return true;
	
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
		// TODO: Particle Coloring, alpha
        //m_graphic->SetTint(it->red,it->green,it->blue,it->alpha);
        Billboard::Render(it->position);
    }

	return true;
}


// |----------------------------------------------------------------------------|
// |						       Explode()			    					|
// |----------------------------------------------------------------------------|
void FireworkEffect::Explode() {
	Debug ("FireworkEffect: Explode() called.");
   
    float angle = 0;
	float angleInc = 2*3.14 / m_maxParticles;
	
	for (int i = 0; i < m_maxParticles; ++i)
    {
		// Increment angle at which particle will be fired
		angle += angleInc;
	
		// Now generate the randomized particle properties.
        ParticleType newParticle;
		newParticle.position.x = m_position.x;
		newParticle.position.y = m_position.y;
		newParticle.position.z = m_position.z;

		newParticle.velocity.x = m_particleInitialSpeed * cos(angle);
        newParticle.velocity.y = m_particleInitialSpeed * sin(angle);
		newParticle.velocity.z = 0.0f;
        
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
void FireworkEffect::UpdateParticles() {
	Debug ("FireworkEffect: UpdateParticles() called.");
    
    std::list<ParticleType>::iterator it;
    for (it=m_particles.begin(); it!=m_particles.end(); ++it)
    {
		// Edit particle velocity based on system drag
		it->velocity *= (1 - (m_particleDrag) * m_frameTime);
		it->velocity.y -= m_gravity;
		
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
bool ParticleIsDead (const FireworkEffect::ParticleType& val) 
{ 
	return (val.lifetime > val.maxLife); 
}
void FireworkEffect::KillParticles() {
	Debug ("FireworkEffect: KillParticles() called.");
    
    m_particles.remove_if (ParticleIsDead);

	return;
}


// |----------------------------------------------------------------------------|
// |					    ParticleType::operator<()							|
// |----------------------------------------------------------------------------|
bool FireworkEffect::ParticleType::operator<(const ParticleType& rhs) {
	
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
