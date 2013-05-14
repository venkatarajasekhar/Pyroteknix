// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Screen containing a game level


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "LevelScreen.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen() :
    Screen(),
	m_crosshair(0),
	m_aimSpeed(10),
	m_cannon(0),
	m_explode(false),
	fireworkEffect(0)
{
	Debug ("LevelScreen: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen(const LevelScreen&) {
	Debug ("LevelScreen: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
LevelScreen::~LevelScreen() {
	Debug ("LevelScreen: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Initialize() {
	Debug ("LevelScreen::Initialize() called.");

    // Initialize parent class
    Screen::Initialize();
	
	// Create game object for cannon
	m_cannon = new GameObject;
	m_cannon->SetModel("cannon");
	m_cannon->SetTexture("cannon");
	m_cannon->SetPosition(Coord(0.0f,0.0f,0.0f));
	m_cannon->SetOrientation(Coord(-3.14f/4.0f,0.0f,0.0f));
	m_gameObjects.push_back(m_cannon);
	
	// Create game object for base
	GameObject* base = new GameObject;
	base->SetModel("base");
	base->SetTexture("base");
	base->SetPosition(Coord(0.0f,0.0f,0.0f));
	m_gameObjects.push_back(base);
	
	// Create crosshair
	m_crosshair = new Image2D;
	m_crosshair->SetModel("quad");
	m_crosshair->SetTexture("crosshair");
	m_crosshair->SetX(0);
	m_crosshair->SetY(0);
	m_crosshair->SetWidth(32);
	m_crosshair->SetHeight(32);
	m_crosshair->SetDepth(0xFFFFF0);
	m_crosshair->SetTint(0x80,0x00,0x00,0x80);
	m_overlayObjects.push_back(m_crosshair);
	
	// Create FireworkEffect for testing
	fireworkEffect = new FireworkEffect;
	fireworkEffect->SetModel("quad");
	fireworkEffect->SetTexture("particle_point");
	fireworkEffect->SetPosition(Coord(0.0f,300.0f,0.0f));
	fireworkEffect->SetInitialSpeed(100.0f);
	fireworkEffect->SetParticleDrag(0.2f);
	fireworkEffect->SetParticleLifetime(3.0f);
	fireworkEffect->SetParticleFadeout(1.0f);
	fireworkEffect->SetMaxParticles(20);
	m_gameObjects.push_back(fireworkEffect);

	Debug ("LevelScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Shutdown() {
	Debug ("LevelScreen::Shutdown called.");
	
	// TEMP
	fireworkEffect->Shutdown();
	
	Screen::Shutdown();
	
	Debug ("LevelScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Logic() {
	Debug ("LevelScreen::Logic() called.");

    Screen::Logic();
	
	// TEMP
	if (!m_explode)
	{
		fireworkEffect->Explode();
		m_explode = true;
	}
	
	// Move crosshair
	float moveX = 0.0f;
	float moveY = 0.0f;
	moveX += pad[0].axes[PAD_AXIS_LX] * m_aimSpeed;
	moveY += pad[0].axes[PAD_AXIS_LY] * m_aimSpeed;
	m_crosshair->SetX(m_crosshair->GetX()+moveX);
	m_crosshair->SetY(m_crosshair->GetY()+moveY);
	
	// Move cannon
	Coord rotation = m_cannon->GetOrientation();
	rotation.x += moveY*-0.003f;
	rotation.y += moveX*-0.005f;
	m_cannon->SetOrientation(rotation);

	return true;
}

// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Render() {
	Debug ("LevelScreen::Render() called.");

    Screen::Render();

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnLoad()									|
// |----------------------------------------------------------------------------|
// Called when the screen is loaded.
bool LevelScreen::OnLoad() {
	Debug("LevelScreen::OnLoad called");
	Screen::OnLoad();
	
	// Set Camera Position
	CPipeline::GetSingleton().PositionCamera(Vector4(0.0f, 00.0f, 400.0f, 1.0f), 23.0f * 3.14f / 180.0f, 0.0f);

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
bool LevelScreen::OnExit() {
	Debug("LevelScreen::OnExit called.");

	return true;
}