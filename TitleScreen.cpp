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
	m_titleTextTexture(0),
	m_titleTextImage(0),
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
	
	// Set up Title image
	m_titleTextTexture = AssetManager::GetSingleton().GetRedAlphaTexture("titleText");
	m_titleTextImage = new Image2D;
	m_titleTextImage->SetWidth(512);
	m_titleTextImage->SetHeight(512);
	m_titleTextImage->SetDepth(0x00000F);

	Debug ("TitleScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Shutdown() {
	Debug ("TitleScreen::Shutdown called.");
	Screen::Shutdown();
	
	Debug ("TitleScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Logic() {
	Debug ("TitleScreen::Logic() called.");
	
	// Check for move to next screen
	if((pad[0].buttons & PAD_TRI) || (pad[0].buttons & PAD_CROSS) || (pad[0].buttons & PAD_SQUARE) || (pad[0].buttons & PAD_CIRCLE))
	{
		m_done = true;
		m_nextScreen = SCREEN_LEVEL;
	}

    Screen::Logic();
	
	return true;
}

// |----------------------------------------------------------------------------|
// |							    Render()									|
// |----------------------------------------------------------------------------|
bool TitleScreen::Render() {
	Debug ("TitleScreen::Render() called.");
	
	// Place texture in buffer (as needed)
	AssetManager::GetSingleton().LoadTexture(m_titleTextTexture);
	
	// Render title image
	m_titleTextImage->Render();

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