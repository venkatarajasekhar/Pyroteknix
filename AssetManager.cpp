// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// AssetManager
//      Manages loading and unloading assets including textures, models, and sounds


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "AssetManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
AssetManager::AssetManager() :
	m_loadedTexture1(0),
	m_loadedTexture2(0),
	m_selectedTexture(0),
	m_lastUsed(1)
{
}

// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool AssetManager::Initialize()
{
    // Load in defaults
    GetTexture("default");
    GetModel("default");
    GetFont("defaultFont");

    return true;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void AssetManager::Shutdown()
{
    // De-allocate all textures
    for (std::map<string,CTexture*>::iterator it=m_textures.begin(); it!=m_textures.end(); ++it)
    {
        delete it->second;
        it->second = 0;
    }
    for (std::map<string,CTexture*>::iterator it=m_blackTransparentTextures.begin(); it!=m_blackTransparentTextures.end(); ++it)
    {
        delete it->second;
        it->second = 0;
    }
    for (std::map<string,CTexture*>::iterator it=m_redAlphaTextures.begin(); it!=m_redAlphaTextures.end(); ++it)
    {
        delete it->second;
        it->second = 0;
    }
    // De-allocate all models
    for (std::map<string,CMs3dModel*>::iterator it=m_models.begin(); it!=m_models.end(); ++it)
    {
        delete it->second;
        it->second = 0;
    }
    // De-allocate all fonts
    for (std::map<string,CFont*>::iterator it=m_fonts.begin(); it!=m_fonts.end(); ++it)
    {
        delete it->second;
        it->second = 0;
    }
	
    // Clear maps
    m_textures.clear();
    m_blackTransparentTextures.clear();
    m_redAlphaTextures.clear();
    m_models.clear();
    m_fonts.clear();
    return;
}


// |----------------------------------------------------------------------------|
// |                              LoadTexture                                   |
// |----------------------------------------------------------------------------|
void AssetManager::LoadTexture(CTexture* texture, int target)
{
	Debug ("AssetManager::LoadTexture called.");
	
	if (!texture) return;
	
	// If the texture is already loaded somewhere, select it, set it as last used, and return
	if (texture == m_loadedTexture1)
	{
		if (texture != m_selectedTexture)
		{
			texture->Select();
			m_selectedTexture = texture;
		}
		m_lastUsed = 1;
		return;
	}
	else if (texture == m_loadedTexture2)
	{
		if (texture != m_selectedTexture)
		{
			texture->Select();
			m_selectedTexture = texture;
		}
		m_lastUsed = 2;
		return;
	}
	// If it's not loaded, set target based on lastUsed (if 1, 2, if 2, 1)
	// Hopefully will keep us from switching textures too much
	if (target == 0)
	{
		if(m_lastUsed == 1) target = 2;
		if(m_lastUsed == 2) target = 1;
	}
	
	// If target is buffer 1
	if (target == 1)
	{
		texture->Upload(TEXBUF480);
		m_loadedTexture1 = texture;
		m_selectedTexture = texture;
		m_lastUsed = 1;
	}
	else if (target == 2)
	{
		texture->Upload(TEXBUF496);
		m_loadedTexture2 = texture;
		m_selectedTexture = texture;
		m_lastUsed = 2;
	}
	texture->Select();
	return;
}


// |----------------------------------------------------------------------------|
// |                              GetTexture                                    |
// |----------------------------------------------------------------------------|
CTexture* AssetManager::GetTexture(std::string name, bool blackTransparent, bool redAsAlpha)
{
	Debug ("AssetManager::GetTexture called.");
    const char* nameC = name.c_str();

    // If the texture is already in the map, just return it
    if (blackTransparent && m_blackTransparentTextures.count(name)) 
    {
	    Debug ("AssetManager: Texture found: %s", nameC);
        return m_blackTransparentTextures[name];
    }
    else if (redAsAlpha && m_redAlphaTextures.count(name)) 
    {
	    Debug ("AssetManager: Texture found: %s", nameC);
        return m_redAlphaTextures[name];
    }
    else if (m_textures.count(name)) 
    {
	    Debug ("AssetManager: Texture found: %s", nameC);
        return m_textures[name];
    }
    // If not, try loading it from file.
	
    // Construct string name
    std::string filePath = "data/textures/";
    filePath += name;
    filePath += ".bmp";
    const char* filePathC = filePath.c_str();

    // Attempt to load
    CTexture* texture = new CTexture;
    bool result = texture->LoadBitmap(filePathC, blackTransparent, redAsAlpha);
    if (!result)
    {
	    Debug("AssetManager: Unable to load texture: %s", nameC);
        return m_textures["default"];
    }

    // If it was loaded, add it to the map and return it.
    if (blackTransparent) m_blackTransparentTextures[name] = texture;
    else if (redAsAlpha) m_redAlphaTextures[name] = texture;
    else m_textures[name] = texture;
	Debug ("AssetManager: Texture loaded: %s", nameC);
    return texture;
}
CTexture* AssetManager::GetBlackTransparentTexture(std::string name)
{
	return GetTexture(name, true, false);
}
CTexture* AssetManager::GetRedAlphaTexture(std::string name)
{
	return GetTexture(name, false, true);
}


// |----------------------------------------------------------------------------|
// |                                 GetModel                                   |
// |----------------------------------------------------------------------------|
CMs3dModel* AssetManager::GetModel(std::string name)
{
	Debug ("AssetManager::GetModel called.");
    const char* nameC = name.c_str();

    // If the texture is already in the map, just return it
    if (m_models.count(name)) 
    {
	    Debug ("AssetManager: model found: %s", nameC);
        return m_models[name];
    }

    // If not, try loading it from file.
    // Construct string name
    std::string filePath = "data/models/";
    filePath += name;
    filePath += ".txt";
    const char* filePathC = filePath.c_str();

    // Attempt to load
    CMs3dModel* model = new CMs3dModel;
    bool result = model->LoadModelData(filePathC, false);
    if (!result)
    {
	    Debug ("AssetManager: Unable to load model: %s", nameC);
        return m_models["default"];
    }

    // If it was loaded, add it to the map and return it.
    m_models[name] = model;
	Debug ("AssetManager: model loaded: %s", nameC);
    return model;
}


// |----------------------------------------------------------------------------|
// |                               GetFont                                      |
// |----------------------------------------------------------------------------|
CFont* AssetManager::GetFont(std::string name)
{
	Debug ("AssetManager::GetFont called.");
    const char* nameC = name.c_str();

    // If the font is already in the map, just return it
    if (m_fonts.count(name)) 
    {
	    Debug ("AssetManager: Font found: %s", nameC);
        return m_fonts[name];
    }
    // If not, try loading it from file.
	
    // Construct string name
    std::string filePath = "data/fonts/";
    filePath += name;
    filePath += ".dat";
    const char* filePathC = filePath.c_str();

    // Attempt to load
    CFont* font = new CFont;
    bool result = font->Load(filePathC, true);
    if (!result)
    {
	    Debug("AssetManager: Unable to load font: %s", nameC);
        return m_fonts["defaultFont"];
    }
	
	// Attempt to load font texture
    GetRedAlphaTexture(name);

    // If it was loaded, add it and its texture to the map and return it.
    m_fonts[name] = font;
	Debug ("AssetManager: Font loaded: %s", nameC);
    return font;
}