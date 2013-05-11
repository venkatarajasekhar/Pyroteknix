// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Billboard
//      Special game object that automatically orients itself to face the camera
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <string>
#include <math.h>
#include "Util.h"
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |                         Class Definition: Billboard                        |
// |----------------------------------------------------------------------------|
class Billboard : public GameObject
{

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	Billboard();
	
    // Sends any models associated with the object to the renderer
    bool virtual Render();
    bool virtual Render(Coord position);

};