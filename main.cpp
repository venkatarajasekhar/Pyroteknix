/*
* "PS2" Application Framework
*
* University of Abertay Dundee
* May be used for educational purposed only
*
* Author - Dr Henry S Fortuna
*
* $Revision: 1.5 $
* $Date: 2007/08/27 20:22:34 $
*
*/

#include <sps2lib.h>
#include <sps2tags.h>
#include <sps2util.h>
#include <sps2regstructs.h>
#include <assert.h>
#include <memory.h>
#include <signal.h>
#include "PS2Defines.h"
#include "ps2maths.h"
#include "ps2matrix4x4.h"
#include "pad.h"
#include "sps2wrap.h"
#include "dma.h"
#include "texture.h"
#include "font.h"
#include "pipeline.h"
#include "entities.h"
#include "vumanager.h"
#include "timer.h"
#include "ms3dmodel.h"
#include "terrain.h"

// My includes
#include "AssetManager.h"
#include "GameObject.h"

/*
	Look at the start of the vcl code to get the positions
	and layout of the packet data in VU data memory.
	Remember that the data sent to the VU must be in 
	the specified format of the PS2 WILL CRASH

*/


// These two external function pointers are exported by the VU code
// and we can now use them as pointers to the compiled VU data
extern "C" uint64 VU_vu1code_start;
extern "C" uint64 VU_vu1code_end;


bool g_bLoop = true;

void sig_handle(int sig)
{
	g_bLoop = false;
}


int main(void)
{	
	// Make sure these four lines are put first since some of the 
	// other classes need the managers to be initialised so they 
	// can pick up the correct data.	
	SPS2Manager.Initialise(4096);	// 4096 * 4K Pages = 16MB Total
	VIFStaticDMA.Initialise(3072);	// 1536 * 4K Pages = 6MB Static DMA
	VIFDynamicDMA.Initialise(256);	// 256 * 4K Pages * 2 Buffers =
									// 2MB Dynamic DMA
	Pipeline.Initialise();			// Initialise graphics pipline class
	
	
	// Initialise Lighting
	// Three lights and Ambient light
	//							Direction vector				  Colour	
	Pipeline.SetLight1(Vector4( 1.0f, 0.2f, 0.0f, 0.0f), Vector4(128.0f,128.0f,128.0f,0.0f));
	Pipeline.SetLight2(Vector4(-1.0f,-0.2f, 0.0f, 0.0f), Vector4(0.0f,128.0f,0.0f,0.0f));
	Pipeline.SetLight3(Vector4( 0.0f, 0.0f,-1.0f, 0.0f), Vector4(0.0f,0.0f,128.0f,0.0f));
	//                            Colour
	Pipeline.SetAmbient(Vector4(30.0f,30.0f,30.0f,0.0f));
	
	// Performance timer - call after SPS2Manager.Initialise()
	CTimer Timer;
	
	// Initialise control pad 0
	if(!pad_init(PAD_0, PAD_INIT_LOCK | PAD_INIT_ANALOGUE | PAD_INIT_PRESSURE))
	{
		printf("Failed to initialise control pad\n");
		pad_cleanup(PAD_0);
		exit(0);
	}	
	
	// Initialise the VU1 manager class
	CVU1MicroProgram VU1MicroCode(&VU_vu1code_start, &VU_vu1code_end);
	
	// Upload the microcode
	VU1MicroCode.Upload();

	// Register our signal function for every possible signal (i.e. ctrl + c)
	for(int sig=0; sig<128; sig++)
		signal(sig, sig_handle);
		
		
	// Set up the DMA packet to clear the screen. We want to clear to blue.
	SPS2Manager.InitScreenClear(0, 0x25, 0x50);
	
	// Load in texture and models ----------------------------------------------
	
	// Set up asset loader
	AssetManager assetManager;
	assetManager.Initialize();
	
	// Create game object for cannon
	GameObject* cannon = new GameObject;
	cannon->SetModel("cannon");
	cannon->SetTexture("cannon");
	
	// Load in crosshair texture
	CTexture* crosshairTexture = assetManager.GetTexture("crosshair");
	
	// Terrain to render
	CTerrain Terrain;
	
	// Load the font bitmap and data
	CFont* font = assetManager.GetFont("font");
	CTexture* fontTexture = assetManager.GetTexture("font");

	// Upload these once to VRAM since
	// they are not going to change
	fontTexture->Upload(TEXBUF496);
	
	// Set Up Camera --------------------------------------------------------------
	
	Pipeline.PositionCamera(Vector4(0.0f, 55.0f, 80.0f, 1.0f), Vector4(0.0f, 40.0f, 0.0f, 1.0f));

	int Frame = 0;
	float fps = 0.0f;
		
	// The main Render loop -------------------------------------------------------
	while(g_bLoop)
	{
		//start the time
  		Timer.PrimeTimer();
  		
		VIFDynamicDMA.Fire();
		
		// Update Control Pad
		pad_update(PAD_0);
		
		// Check for exit condition
		if((pad[0].buttons & PAD_START)&&(pad[0].buttons & PAD_SELECT)) g_bLoop = false;
		
		// Rotate the cannon based on user input
		static float sfRotLocalY = 0.0f;
		static float sfRotLocalX = 0.0f;
		sfRotLocalY += pad[0].pressures[PAD_PLEFT] * 0.1f;
		sfRotLocalY -= pad[0].pressures[PAD_PRIGHT] * 0.1f;
		sfRotLocalX -= pad[0].pressures[PAD_PUP] * 0.1f;
		sfRotLocalX += pad[0].pressures[PAD_PDOWN] * 0.1f;
		cannon->SetOrientation(cannon->GetOrientation()+Coord(sfRotLocalX,sfRotLocalY,0.0f));
		
		// Get any camera movements
		// Get any requested translations
		float Strafe =   pad[0].axes[PAD_AXIS_LX];
		float Advance =  pad[0].axes[PAD_AXIS_LY];
		float UpDown =   (pad[0].pressures[PAD_PL1] - pad[0].pressures[PAD_PL2]);
		
		// Get requested rotations
		float YRot = pad[0].axes[PAD_AXIS_RY];
		float XRot = pad[0].axes[PAD_AXIS_RX];
				
		// Reset camera to default position if requested
		if(pad[0].buttons & PAD_R3)
		{
			Pipeline.PositionCamera(Vector4(0.0f, 55.0f, 80.0f, 1.0f), Vector4(0.0f, 40.0f, 0.0f, 1.0f));
		}
		
		// Update the Camera and viewProjection matrices
		Pipeline.Update(Strafe, Advance, UpDown, YRot, XRot);
		
		// Prepare scene for rendering	
		SPS2Manager.BeginScene();
		
		// Select the Cross texture
		crosshairTexture->Upload(TEXBUF480);
		crosshairTexture->Select();
			
			// Render terrain
			Terrain.SetWorldMatrix(Matrix4x4::IDENTITY);
			Terrain.Render();	
				
		// Select the model texture	
		cannon->GetTexture()->Upload(TEXBUF480);
		cannon->GetTexture()->Select();
		
			// Render Model
			cannon->Render();
		
		// Select the Font texture	
		fontTexture->Select();
		
			// Render some text
			font->printfL(  	-300, -240, 127, 127, 127, 127, 
							"Camera Position (x, y, z) = (%3.1f, %3.1f, %3.1f)", 
							Pipeline.GetCameraX(), Pipeline.GetCameraY(), Pipeline.GetCameraZ());
			font->printfL(  	-300, -210, 127, 127, 127, 127, 
							"Camera Rotation in Degrees (XRot, YRot) = (%3.1f, %3.1f)", 
							RadToDeg(Pipeline.GetCameraXRot()), RadToDeg(Pipeline.GetCameraYRot()));
			font->printfC(  200, -240, 127, 127, 127, 127, "Frame: %d\nFPS: %.1f" , Frame++, fps);
					
		//calculate the current frame rate in frames per second	
		fps = Timer.GetFPS();
		
		SPS2Manager.EndScene();	
		
		if(pad[0].pressed & PAD_TRI)SPS2Manager.ScreenShot();		
	}

	pad_cleanup(PAD_0);
	
	// Shutdown asset manager
	assetManager.Shutdown();
	
	return 0;
}

