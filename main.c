/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "MonochromeLib.h"
#include "fixed.h"
#include "mode7.h"
#include "key.h"
#include "stdio.h"
const fix s = FIX(8);
const fix horizon = FIX(32);
const fix fov = FIX(60);

	unsigned char spr[8] = {
		0xFF, 0X81, 0X81, 0X81, 0X81, 0X81, 0X81, 0XFF
	};

char machin[] = {
   0,3,1,1,1,4,0,0,0,0,0,0,
   0,2,0,0,0,2,0,0,3,1,4,0,
   0,2,0,7,0,2,0,0,2,0,2,0,
   0,2,0,0,0,2,0,0,2,0,2,0,
   0,2,0,0,0,5,1,1,6,0,2,0,
   0,2,0,0,0,0,0,0,0,0,2,0,
   0,2,0,0,0,0,0,0,0,0,2,0,
   0,2,0,0,0,0,0,0,0,0,2,0,
   0,5,1,1,1,1,1,1,1,1,6,0,
   0,0,0,0,0,0,0,0,0,0,0,0
  };
	char tset[] = {
			0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
			0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,
			0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,
			0xFF,0xFF,0xF0,0xE0,0xC0,0xC0,0xC1,0xC3,
			0xFF,0xFF,0x0F,0x07,0x03,0x03,0x83,0xC3,
			0xC3,0xC1,0xC0,0xC0,0xE0,0xF0,0xFF,0xFF,
			0xC3,0x83,0x03,0x03,0x07,0x0F,0xFF,0xFF,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		};

	M7_TiledMap map = {
		machin,
		tset,
		12, 10
	};






int AddIn_main(int isAppli, unsigned short OptionNum)
{

	char buffer[256]= "";
	M7_Parameters m7p;
	int time = 0;
	int i,j;
	fix mul;
	m7p.camera_angle = 0;
	m7p.camera_pitch = 0;
	m7p.camera_x = 0;
	m7p.camera_y = 0;
	m7p.camera_z = FIX(8);
	m7p.scale_x = FIX(128);
	m7p.scale_y = FIX(64);
	m7p.obj_scale_x = FIX(128);
	m7p.obj_scale_y = FIX(128);


	while(KeyUp(K_EXIT)) {
		time++;
		if(KeyDown(K_LEFT))
			m7p.camera_angle -= FIX(3);
		if(KeyDown(K_RIGHT))
			m7p.camera_angle += FIX(3);
		if(KeyDown(K_UP)) {
			m7p.camera_x += fcos(m7p.camera_angle);
			m7p.camera_y += fsin(m7p.camera_angle);
		}
		if(KeyDown(K_SHIFT))
			m7p.camera_z += FIX(1);
		if(KeyDown(K_ALPHA) && m7p.camera_z > FIX(0))
			m7p.camera_z -= FIX(1);
		if(KeyDown(K_DOWN)) {
			m7p.camera_x -= fcos(m7p.camera_angle);
			m7p.camera_y -= fsin(m7p.camera_angle);
		}
		if(KeyDown(K_7)) {
			m7p.camera_pitch += ftofix(0.2);
			if(m7p.camera_pitch > FIX(90))
				m7p.camera_pitch = FIX(90);
				if(m7p.camera_pitch < FIX(-90))
					m7p.camera_pitch = FIX(-90);
		}
		if(KeyDown(K_4)) {
			m7p.camera_pitch -= ftofix(0.2);
		}
		m7p.camera_angle = MOD(m7p.camera_angle, FIX(360));

		ML_clear_vram();
		mode_7(map, &m7p);

		{
			sprintf(buffer, "angle=%d", UNFIX(m7p.camera_angle));
			PrintMini(0, 0, buffer, MINI_OVER);
			sprintf(buffer, "hor=%d", m7p.horizon);
			PrintMini(0, 6, buffer, MINI_OVER);
			sprintf(buffer, "pch=%f", fixtof(m7p.camera_pitch));
			PrintMini(0, 12, buffer, MINI_OVER);
		}
		ML_display_vram();
		Sleep(1);
	}
	return 1;
}



//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
	return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section
