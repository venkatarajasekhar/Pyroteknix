// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// FireworkEffect
//      Manages a set of particles, emitted and handled based on set parameters
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <list>
#include <math.h>
#include "Util.h"
#include "Billboard.h"


// |----------------------------------------------------------------------------|
// |                     Class Definition: FireworkEffect                       |
// |----------------------------------------------------------------------------|
class FireworkEffect : public Billboard {

public:

    //|-------------------------------Public TypeDefs---------------------------|

    struct ParticleType
	{
		Coord position;
		float red, green, blue, alpha;
        float lifetime;
        float maxLife;
		Coord velocity;

        bool operator<(const ParticleType& rhs);
	};

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	FireworkEffect();
	FireworkEffect(const FireworkEffect&);
	virtual ~FireworkEffect();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Render();
	
	// Emit max particles at m_particleInitialSpeed in a ring.
	void Explode();

    // Setters
    void SetParticleSize(float val) { m_particleSize = val; }
    void SetInitialSpeed(float val) { m_particleInitialSpeed = val; }
    void SetParticleDrag(float val) { m_particleDrag = val; }
    void SetParticleLifetime(float val) { m_particleLifetime = val; }
    void SetParticleFadeout(float val) { m_particleFadeout = val; }
    void SetMaxParticles(int val) { m_maxParticles = val; }
    
    void SetTint(float r, float g, float b, float a = 1.0f) {
        m_tintR = r;
        m_tintG = g;
        m_tintB = b;
        m_alpha = a;
    }
    void SetTintVar(float r, float g, float b, float a = 1.0f) {
        m_tintRVar = r;
        m_tintGVar = g;
        m_tintBVar = b;
        m_alphaVar = a;
    }

protected:
   
    //|----------------------------Protected Functions-------------------------|

	void UpdateParticles();
	void KillParticles();

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // FireworkEffect system parameters
    float m_tintR, m_tintG, m_tintB, m_alpha;
    float m_tintRVar, m_tintGVar, m_tintBVar, m_alphaVar;
    float m_particleSize;
	float m_particleInitialSpeed;
	float m_particleDrag;
    float m_particleLifetime;
	float m_particleFadeout;
    int m_maxParticles;

    // Particle management data members
    float m_accumulatedTime;
	float m_frameTime;
    std::list<ParticleType> m_particles;
};