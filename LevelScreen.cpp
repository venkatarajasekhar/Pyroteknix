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
    Screen()
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
	GameObject* cannon = new GameObject;
	cannon->SetModel("cannon");
	cannon->SetTexture("cannon");
	cannon->SetPosition(Coord(0.0f,0.0f,0.0f));
	m_gameObjects.push_back(cannon);
	
	// Create game object for base
	GameObject* base = new GameObject;
	base->SetModel("base");
	base->SetTexture("base");
	base->SetPosition(Coord(0.0f,0.0f,0.0f));
	m_gameObjects.push_back(base);

	Debug ("LevelScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Shutdown() {
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