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
	m_firework(0),
	m_budget(0),
	m_costCross(0),
	m_cooldown(0.0f),
	m_accumulatedTime(0.0f),
	m_budgetDisplay(0),
	m_people(0),
	m_happiness(0),
	m_numPeople(0),
	m_peopleIncrementX(0),
	m_fireworkRange(0),
	m_happinessTime(0),
	m_happinessCooldown(0),
	m_score(0),
	m_scoreDisplay(0),
	m_fireworkScore(0),
	m_winDialogue(0),
	m_lossDialogue(0),
	m_gameover(false),
	m_won(false),
	m_cannonSound("cannon_whistle", AssetManager::GetSingleton().GetAudioDevice()),
	m_fireworkSound("firework", AssetManager::GetSingleton().GetAudioDevice()),
	m_flash(0)
{
	Debug ("LevelScreen: object instantiated.");
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
	
	// Set up backdrop
	Image2D* backdrop = new Image2D;
	CTexture* backdropTexture = AssetManager::GetSingleton().GetTexture("backdrop");
	backdrop->SetTexture(backdropTexture);
	backdrop->SetWidth(1024);
	backdrop->SetHeight(1024);
	backdrop->SetDepth(0x0000FF);
	m_gameObjects.push_back(backdrop);
	
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
	
	// Create audience objects, set up happiness
	GameObject* person; 
	m_numPeople = 10;
	m_people = new GameObject*[m_numPeople];
	m_happiness = new int[m_numPeople];
	m_peopleIncrementX = 60.0f;
	m_fireworkRange = 200.0f;
	m_happinessCooldown = 5.0f;
	m_happinessTime = 0.0f;
	float peopleZ = -125.0f;
	float peopleScale = 0.65f;
	float startingX = -1 * m_peopleIncrementX * (m_numPeople - 1) / 2.0f;
	for (int i = 0; i < m_numPeople; ++i )
	{
		person = new GameObject;
		person->SetModel("person");
		person->SetTexture("person_happy");
		person->SetPosition(Coord(startingX+m_peopleIncrementX*i,-10.0f,peopleZ));
		person->SetScale(peopleScale);
		m_gameObjects.push_back(person);
		m_people[i] = person;
		m_happiness[i] = 3;
	}
	
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
	
	// Firework setup
	m_firework = new Firework;
	m_firework->Initialize();
	m_firework->SetTarget(Coord(0.0f,250.0f,-150.0f));
	m_gameObjects.push_back(m_firework);
	
	// Firework costs setup
	m_budget = 2500;
	m_costCross = 60;
	m_cooldown = 1.0f;
	m_accumulatedTime = 0.0f;
	m_budgetDisplay = new Text;
	m_budgetDisplay->SetFont("defaultFont");
	m_budgetDisplay->SetTexture("defaultFont");
	char buffer [50];
	sprintf (buffer, "Budget: $%d", m_budget);
	m_budgetDisplay->SetString(buffer);
	m_budgetDisplay->SetPosition(Coord(150.0f,-250.0f,0.0f));
	m_overlayObjects.push_back(m_budgetDisplay);
	
	// Cost display
	Image2D* costs = new Image2D;
	costs->SetModel("quad");
	costs->SetTexture(AssetManager::GetSingleton().GetBlackTransparentTexture("controls"));
	costs->SetX(-250);
	costs->SetY(-200);
	costs->SetWidth(128);
	costs->SetHeight(128);
	costs->SetDepth(0xFFFFF1);
	costs->SetTint(0x80,0x80,0x80,0x80);
	m_overlayObjects.push_back(costs);
	// Cross Cost
	Text* crossCost = new Text;
	crossCost->SetFont("defaultFont");
	crossCost->SetTexture("defaultFont");
	sprintf (buffer, "$%d", m_costCross);
	crossCost->SetString(buffer);
	crossCost->SetPosition(Coord(-265.0f,-160.0f,0.0f));
	m_overlayObjects.push_back(crossCost);

	// Score
	m_score = 0;
	m_fireworkScore = 10;
	m_scoreDisplay = new Text;
	m_scoreDisplay->SetFont("defaultFont");
	m_scoreDisplay->SetTexture("defaultFont");
	buffer [50];
	sprintf (buffer, "Score: %d", m_score);
	m_scoreDisplay->SetString(buffer);
	m_scoreDisplay->SetPosition(Coord(-20.0f,-250.0f,0.0f));
	m_overlayObjects.push_back(m_scoreDisplay);
	
	// Timer
	m_timeRemaining = 60;
	m_timeDisplay = new Text;
	m_timeDisplay->SetFont("defaultFont");
	m_timeDisplay->SetTexture("defaultFont");
	buffer [50];
	sprintf (buffer, "Time: %d", ((int)m_timeRemaining));
	m_timeDisplay->SetString(buffer);
	m_timeDisplay->SetPosition(Coord(-20.0f,-220.0f,0.0f));
	m_overlayObjects.push_back(m_timeDisplay);
	
	// Dialogue background
	
	// Winning Dialogue
	m_winDialogue = new Text;
	m_winDialogue->SetFont("defaultFont");
	m_winDialogue->SetTexture("defaultFont");
	buffer [50];
	sprintf (buffer, "You Win!\n\nScore: %d\n\nPress START\nto return to the title screen.", m_score);
	m_winDialogue->SetString(buffer);
	m_winDialogue->SetPosition(Coord(-100.0f,-150.0f,0.0f));
	m_overlayObjects.push_back(m_winDialogue);
	// Losing Dialogue
	m_lossDialogue = new Text;
	m_lossDialogue->SetFont("defaultFont");
	m_lossDialogue->SetTexture("defaultFont");
	buffer [50];
	sprintf (buffer, "You Lose!\n\nScore: %d\n\nPress START\nto return to the title screen.", m_score);
	m_lossDialogue->SetString(buffer);
	m_lossDialogue->SetPosition(Coord(-100.0f,-150.0f,0.0f));
	m_overlayObjects.push_back(m_lossDialogue);
	
	// Create screen flash
	m_flash = new Image2D;
	m_flash->SetModel("quad");
	m_flash->SetTexture(AssetManager::GetSingleton().GetBlackTransparentTexture("flash"));
	m_flash->SetWidth(1024);
	m_flash->SetHeight(1024);
	m_flash->SetDepth(0xFFFFFF);
	m_flash->SetTint(0x80,0x80,0x80,0x80);
	m_flash->Disable();
	m_overlayObjects.push_back(m_flash);
	Debug ("LevelScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Shutdown() {
	Debug ("LevelScreen::Shutdown called.");
	
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
	
	// Disable screen flash
	m_flash->Disable();
	
	// If game is over, wait for button press
	if(m_gameover)
	{
		if(pad[0].buttons & PAD_START)
		{
			m_done = true;
			m_nextScreen = SCREEN_TITLE;
		}
		return true; // Skip all other processing
	}
	
	// Update time
	m_accumulatedTime += 1.0f / 40.0f;
	m_happinessTime += 1.0f / 40.0f;
	m_timeRemaining -= 1.0f / 40.0f;
	char buffer [50];
	sprintf (buffer, "Time: %d", ((int)m_timeRemaining));
	m_timeDisplay->SetString(buffer);
	
	// Disable vibration if it's time
	if (m_accumulatedTime > 0.2f)
		set_actuator(0, 0, 0);
	
	// Move crosshair
	float moveX = 0.0f;
	float moveY = 0.0f;
	moveX += pad[0].axes[PAD_AXIS_LX] * m_aimSpeed;
	moveY += pad[0].axes[PAD_AXIS_LY] * m_aimSpeed;
	
	// Clamp to screen bounds
	float maxX = 300.0f;
	float minX = -300.0f;
	float maxY = 50.0f;
	float minY = -250.0f;
	if (m_crosshair->GetX()+moveX > maxX) moveX = maxX - m_crosshair->GetX();
	if (m_crosshair->GetX()+moveX < minX) moveX = minX - m_crosshair->GetX();
	if (m_crosshair->GetY()+moveY > maxY) moveY = maxY - m_crosshair->GetY();
	if (m_crosshair->GetY()+moveY < minY) moveY = minY - m_crosshair->GetY();
	
	m_crosshair->SetX(m_crosshair->GetX()+moveX);
	m_crosshair->SetY(m_crosshair->GetY()+moveY);
	
	// Move cannon
	Coord rotation = m_cannon->GetOrientation();
	rotation.x += moveY*-0.002f;
	rotation.y += moveX*-0.005f;
	m_cannon->SetOrientation(rotation);
	Coord fireworkTarget = Coord(
			m_crosshair->GetX()*1.4f,
			m_crosshair->GetY()*-1.4f+250.0f,
			-150.0f);
	
	// Decay happiness if it's time
	if (m_happinessTime > m_happinessCooldown)
	{
		// Start cooldown
		m_happinessTime = 0.0f;
		
		for (int i = 0; i < m_numPeople; ++i )
		{
			m_happiness[i]--;
		}
	}
	
	// If button pressed and time greater than cooldown, fire firework
	if( 	( (pad[0].buttons & PAD_TRI) || (pad[0].buttons & PAD_CROSS) || (pad[0].buttons & PAD_SQUARE) || (pad[0].buttons & PAD_CIRCLE) )
		&&   ( m_budget >= m_costCross )
		&&   (m_accumulatedTime > m_cooldown)
		&&	 (m_firework->HasExploded())
	)
	{
		// Fire firework
		m_firework->Fire();
		m_firework->SetTarget(fireworkTarget);
		
		// Vibrate controller
		set_actuator(0, 1, 255);
		
		// Play sound
		m_cannonSound.Play();
	
		// Enable screen flash
		m_flash->Enable();
		
		// Start cooldown
		m_accumulatedTime = 0.0f;
		
		// Deduct from budget
		m_budget -= m_costCross;
		buffer [50];
		sprintf (buffer, "Budget: $%d", m_budget);
		m_budgetDisplay->SetString(buffer);
		
		// Gain points based on happiness and firework value
		float fireworkX = fireworkTarget.x;
		float startingX = -1 * m_peopleIncrementX * (m_numPeople - 1) / 2.0f;
		for (int i = 0; i < m_numPeople; ++i )
		{
			if (m_happiness[i] < 0) continue; // skip processing this person if they have already left
			
			float personX = startingX+m_peopleIncrementX*i;
			if (personX > (fireworkX - m_fireworkRange) && personX < (fireworkX + m_fireworkRange) )
			{
				m_score += m_fireworkScore * m_happiness[i]++; // ALSO applise happiness to person, AFTER score calculated
			}
		}
		// Update score display
		buffer [50];
		sprintf (buffer, "Score: %d", m_score);
		m_scoreDisplay->SetString(buffer);
		
	}
	
	// Process happiness changes
	int numRemainingPeople = 0;
	for (int i = 0; i < m_numPeople; ++i )
	{
		if (m_happiness[i] >= 3) 
		{
			m_people[i]->SetTexture("person_happy");
			m_happiness[i] = 3;
			numRemainingPeople++;
		}
		if (m_happiness[i] == 2) 
		{
			m_people[i]->SetTexture("person_meh");
			numRemainingPeople++;
		}
		if (m_happiness[i] == 1) 
		{
			m_people[i]->SetTexture("person_angry");
			numRemainingPeople++;
		}
		if (m_happiness[i] <= 0) 
		{
			m_people[i]->Disable();
			m_happiness[i] = 0;
		}
	}
	
	// Determine if we've lost
	if (!numRemainingPeople)
	{
		m_gameover = true;
		buffer [50];
		sprintf (buffer, "You Lose!\n\nScore: %d\n\nPress START\nto return to the title screen.", m_score);
		m_lossDialogue->SetString(buffer);
		m_lossDialogue->Enable();
	}
	
	// Determine if we've won
	if (m_timeRemaining <= 0)
	{
		m_gameover = true;
		m_won = true;
		buffer [50];
		sprintf (buffer, "You Win!\n\nScore: %d\n\nPress START\nto return to the title screen.", m_score);
		m_winDialogue->SetString(buffer);
		m_winDialogue->Enable();
	}
	
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

	// Reset game state
	m_won = false;
	m_gameover = false;
	m_winDialogue->Disable();
	m_lossDialogue->Disable();
	
	// Reset people and happiness
	for (int i = 0; i < m_numPeople; ++i )
	{
		m_people[i]->SetTexture("person_happy");
		m_people[i]->Enable();
		m_happiness[i] = 3;
	}
	
	// Reset score
	m_score = 0;
	
	// Reset budget
	m_budget = 2500;
	
	// Reset time
	m_timeRemaining = 60;
	m_accumulatedTime = 0;
	m_happinessTime = 0;
	
	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
bool LevelScreen::OnExit() {
	Debug("LevelScreen::OnExit called.");

	return true;
}