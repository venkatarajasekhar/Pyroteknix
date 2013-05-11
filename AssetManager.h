// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AssetManager
//      Manages loading and unloading assets including textures and models
#pragma once

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "singleton.h"
#include <string>
#include <map>


// |----------------------------------------------------------------------------|
// |                              Class: AssetManager                           |
// |----------------------------------------------------------------------------|
class AssetManager : public CSingleton<AssetManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	AssetManager();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();
	
	// Put texture on buffer
	void LoadTexture(CTexture* texture, int target=0);

    // Getters
    CTexture* GetTexture(std::string name, bool blackTransparent = false, bool redAsAlpha = false);
    CTexture* GetBlackTransparentTexture(std::string name);
    CTexture* GetRedAlphaTexture(std::string name);
    CMs3dModel* GetModel(std::string name);
	CFont* GetFont(std::string name);

private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|

    std::map<std::string,CTexture*> m_textures;
    std::map<std::string,CTexture*> m_blackTransparentTextures;
    std::map<std::string,CTexture*> m_redAlphaTextures;
    std::map<std::string,CMs3dModel*> m_models;
    std::map<std::string,CFont*> m_fonts;
	
	// Texture Loading
	CTexture* m_loadedTexture1;
	CTexture* m_loadedTexture2;
	CTexture* m_selectedTexture;
	int m_lastUsed;

};