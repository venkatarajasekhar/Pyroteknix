// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Image2D
//      Contains model data for a 2D image, renders it to screen.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Image2D.h"


// |----------------------------------------------------------------------------|
// |                          Default Constructor                               |
// |----------------------------------------------------------------------------|
Image2D::Image2D() :
	m_x(0),
	m_y(0),
	m_width(256),
	m_height(256),
	m_depth(0xFFFFFF),
	m_r(0x80),
	m_g(0x80),
	m_b(0x80),
	m_a(0x80)
{
}

bool Image2D::Load()
{
	return true;
}

void Image2D::Render()
{
	Debug ("Image2D::Render called.");
	
	// Determine where to render the image
	uint32 left		= m_x - m_width/2;
	uint32 right	= m_y + m_height/2;
	uint32 top		= m_x - m_width/2;
	uint32 bottom	= m_y + m_height/2;

	// Start DIRECT mode transfer
	VIFDynamicDMA.StartDirect();
									
	// Add the GIFTag
	VIFDynamicDMA.Add128(GS_GIFTAG_BATCH(	1,							// NLOOP
											1,							// EOP
											1,							// PRE
											GS_PRIM(PRIM_SPRITE, 		//PRIM
													PRIM_IIP_FLAT, 
													PRIM_TME_ON,
													PRIM_FGE_OFF, 
													PRIM_ABE_ON, 
													PRIM_AA1_OFF, 
													PRIM_FST_UV, 
													PRIM_CTXT_CONTEXT1, 
													PRIM_FIX_NOFIXDDA),					
											GIF_FLG_PACKED,				//FLG
											GS_BATCH_5(	GIF_REG_RGBAQ, 	//BATCH
														GIF_REG_UV, 
														GIF_REG_XYZ2, 
														GIF_REG_UV, 
														GIF_REG_XYZ2)));				
	// Add Vertex data
	VIFDynamicDMA.Add128(PACKED_RGBA(m_r, m_g, m_b, m_a));
	VIFDynamicDMA.Add128(PACKED_UV(0<<4, 0<<4));
	VIFDynamicDMA.Add128(PACKED_XYZ2(	(left + 2048)<< 4, 
										(top + 2048)<< 4, 
										m_depth, 
										0));						
	VIFDynamicDMA.Add128(PACKED_UV((255<<4), (255<<4)));	
	VIFDynamicDMA.Add128(PACKED_XYZ2(	(right + 2048)<< 4, 
										(bottom + 2048)<< 4, 
										m_depth, 
										0));
			
	
	// End the direct mode
	VIFDynamicDMA.EndDirect();
}
