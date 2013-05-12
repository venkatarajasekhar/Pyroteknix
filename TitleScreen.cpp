// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// TitleScreen
//      Splash screen shown at the start of the game


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "TitleScreen.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
TitleScreen::TitleScreen() :
    Screen()
{
	Debug ("TitleScreen: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
TitleScreen::TitleScreen(const TitleScreen&) {
	Debug ("TitleScreen: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
TitleScreen::~TitleScreen() {
	Debug ("TitleScreen: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Initialize() {
	Debug ("TitleScreen::Initialize() called.");

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

	Debug ("TitleScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Shutdown() {
	Screen::Shutdown();
	
	Debug ("TitleScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Logic() {
	Debug ("TitleScreen::Logic() called.");

	
    Screen::Logic();
	
	return true;
}

// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Render() {
	Debug ("TitleScreen::Render() called.");

    Screen::Render();

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnLoad()									|
// |----------------------------------------------------------------------------|
// Called when the screen is loaded.
bool TitleScreen::OnLoad() {
	Debug("TitleScreen::OnLoad called");
	Screen::OnLoad();
	
	// Set Camera Position
	CPipeline::GetSingleton().PositionCamera(Vector4(0.0f, 00.0f, 400.0f, 1.0f), 23.0f * 3.14f / 180.0f, 0.0f);

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
bool TitleScreen::OnExit() {
	Debug("TitleScreen::OnExit called.");

	return true;
}