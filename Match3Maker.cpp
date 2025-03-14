// Match3Maker.cpp : Defines the entry point for the console application.
//
#pragma warning(disable : 4996)
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include "tga.h"
#include <Windows.h>

CTGA *img = 0;
CTGA *img_out = 0;

void convertTo(char fileIN[], char fileOUT[], unsigned long x, unsigned long y)
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->resizeTo(x, y);
	img->setA(255);
	img->save(fileOUT);
	delete img;
}


// napis wyciągnięty z pliku fileIN wycentrowany w nowym obrazie i zapisany w fileOUT

void generatePopup(char fileIN[], char fileOUT[], unsigned long x, unsigned long y)
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->clip();
	img_out = new CTGA(x, y);

	if (!img->isSpriteFit(x, y))
	{
		while (!img->isSpriteFit(x, y))
			img->resizeSprite(.9f);
	}

	img->renderSprite((x/2) - (img->_spriteSizeX / 2), (y/2) - (img->_spriteSizeY / 2), img_out->_buffer, x, y);
	img_out->flipV();
	img_out->save(fileOUT);

	delete img;
	delete img_out;
}

// wyrenderuj na górze

void renderUP(char fileIN[], char fileOUT[], unsigned long x, unsigned long y)
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->clip();
	img_out = new CTGA(x, y);

	if (!img->isSpriteFit(x, y))
	{
		while (!img->isSpriteFit(x, y))
			img->resizeSprite(.9f);
	}

	img->renderSprite((x / 2) - (img->_spriteSizeX / 2), y - img->_spriteSizeY, img_out->_buffer, x, y);
	img_out->flipV();
	img_out->save(fileOUT);

	delete img;
	delete img_out;
}


// wyrenderuj w lewym górnym rogu

void renderGemC(char fileIN[], char fileOUT[])
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->flipV();
	img->clip();
	img_out = new CTGA(128, 128);

	if (!img->isSpriteFit(96, 96))
	{
		while (!img->isSpriteFit(96, 96))
			img->resizeSprite(.9f);
	}

	img->renderSprite(0,0, img_out->_buffer, 128, 128);
	img_out->save(fileOUT);

	delete img;
	delete img_out;
}


// wyrenderuj na dole, wycentrowane

void renderBottom(char fileIN[], char fileOUT[], unsigned long x, unsigned long y)
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->flipV();
	img->clip();
	img_out = new CTGA(x, y);

	if (!img->isSpriteFit(x, y))
	{
		while (!img->isSpriteFit(x, y))
			img->resizeSprite(.9f);
	}

	img->renderSprite((x / 2) - (img->_spriteSizeX / 2), y - img->_spriteSizeY , img_out->_buffer, x, y);
	img_out->save(fileOUT);

	delete img;
	delete img_out;
}

// wyrenderuj na dole, wycentrowane, cofniete o polowe

void renderBottom25(char fileIN[], char fileOUT[], unsigned long x, unsigned long y)
{
	img = new CTGA(fileIN);
	img->cleanAlfa();
	img->flipV();
	img->clip();
	img_out = new CTGA(x, y);

	if (!img->isSpriteFit(x, y))
	{
		while (!img->isSpriteFit(x, y))
			img->resizeSprite(.9f);
	}

	img->renderSprite((x / 2) - (img->_spriteSizeX / 2), y - img->_spriteSizeY -(img->_spriteSizeY/2), img_out->_buffer, x, y);
	img_out->save(fileOUT);

	delete img;
	delete img_out;
}


void processPopup(char name[])
{
	char temp[1024];
	char in[1024], out[1024];

	sprintf(temp, "gm convert 1-in-png\\%s.png 2-out-tga\\%s.tga", name, name);
	system(temp);

	sprintf(in, "2-out-tga\\%s.tga", name);
	sprintf(out, "3-out-converted\\en_popup_%s_HDS.tga", name);
	generatePopup(in, out, 2048, 1536);
	
	sprintf(out, "3-out-converted\\en_popup_%s_SDS.tga", name);
	generatePopup(in, out, 1024, 768);
	
	sprintf(out, "3-out-converted\\en_popup_%s_SDW.tga", name);
	generatePopup(in, out, 1366, 768);
	
	sprintf(out, "3-out-converted\\en_popup_%s_HDW.tga", name);
	generatePopup(in, out, 1920, 1080);

	sprintf(temp, "gm convert 3-out-converted\\en_popup_%s_HDS.tga 4-out-png\\en_popup_%s_HDS.png", name, name); system(temp);
	sprintf(temp, "gm convert 3-out-converted\\en_popup_%s_SDS.tga 4-out-png\\en_popup_%s_SDS.png", name, name); system(temp);
	sprintf(temp, "gm convert 3-out-converted\\en_popup_%s_HDW.tga 4-out-png\\en_popup_%s_HDW.png", name, name); system(temp);
	sprintf(temp, "gm convert 3-out-converted\\en_popup_%s_SDW.tga 4-out-png\\en_popup_%s_SDW.png", name, name); system(temp);

}

void processBackground()
{
	system("gm convert 1-in-png\\background_HDS.png 2-out-tga\\background_HDS.tga");
	system("gm convert 1-in-png\\background_HDW.png 2-out-tga\\background_HDW.tga");

	img = new CTGA((char*)"2-out-tga\\background_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(2048, 1536);
	img->flipV();
	img->save((char*)"3-out-converted\\background_HDS.tga");
	delete img;

	img = new CTGA((char*)"2-out-tga\\background_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(1024, 768);
	img->flipV();
	img->save((char*)"3-out-converted\\background_SDS.tga");
	delete img;

	img = new CTGA((char*)"2-out-tga\\background_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1920, 1080);
	img->flipV();
	img->save((char*)"3-out-converted\\background_HDW.tga");
	delete img;

	img = new CTGA((char*)"2-out-tga\\background_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1366, 768);
	img->flipV();
	img->save((char*)"3-out-converted\\background_SDW.tga");
	delete img;

	system("gm convert 3-out-converted\\background_HDS.tga 4-out-png\\background_HDS.png");
	system("gm convert 3-out-converted\\background_HDW.tga 4-out-png\\background_HDW.png");
	system("gm convert 3-out-converted\\background_SDS.tga 4-out-png\\background_SDS.png");
	system("gm convert 3-out-converted\\background_SDW.tga 4-out-png\\background_SDW.png");

}

void processMenu()
{
	CTGA *title = 0;

	system("gm convert 1-in-png\\e_mmenu_HDS.png 2-out-tga\\e_mmenu_HDS.tga");
	system("gm convert 1-in-png\\e_mmenu_HDW.png 2-out-tga\\e_mmenu_HDW.tga");
	system("gm convert 1-in-png\\title.png 2-out-tga\\title.tga");

	// HDS

	img = new CTGA((char*)"2-out-tga\\e_mmenu_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(2048, 1536);
	img->flipV();

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(2048, 1536))
	{
		while (!title->isSpriteFit(2048, 1536))
			title->resizeSprite(.9f);
	}

	title->renderSprite(1024 - (title->_spriteSizeX / 2), 768 - (title->_spriteSizeY / 2), img->_buffer, 2048, 1536);

	img->save((char*)"3-out-converted\\e_mmenu_HDS.tga");
	delete img;
	delete title;

	// SDS

	img = new CTGA((char*)"2-out-tga\\e_mmenu_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(1024, 768);
	img->flipV();

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1024, 768))
	{
		while (!title->isSpriteFit(1024, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(512 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1024, 768);

	img->save((char*)"3-out-converted\\e_mmenu_SDS.tga");
	delete img;
	delete title;

	// HDW

	img = new CTGA((char*)"2-out-tga\\e_mmenu_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1920, 1080);
	img->flipV();

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1920, 1080))
	{
		while (!title->isSpriteFit(1920, 1080))
			title->resizeSprite(.9f);
	}

	title->renderSprite(960 - (title->_spriteSizeX / 2), 540 - (title->_spriteSizeY / 2), img->_buffer, 1920, 1080);
	
	img->save((char*)"3-out-converted\\e_mmenu_HDW.tga");
	delete img;
	delete title;

	// SDW

	img = new CTGA((char*)"2-out-tga\\e_mmenu_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1366, 768);
	img->flipV();

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1366, 768))
	{
		while (!title->isSpriteFit(1366, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(683 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1366, 384);

	img->save((char*)"3-out-converted\\e_mmenu_SDW.tga");
	delete img;
	delete title;

	system("gm convert 3-out-converted\\e_mmenu_HDS.tga 4-out-png\\e_mmenu_HDS.png");
	system("gm convert 3-out-converted\\e_mmenu_HDW.tga 4-out-png\\e_mmenu_HDW.png");
	system("gm convert 3-out-converted\\e_mmenu_SDS.tga 4-out-png\\e_mmenu_SDS.png");
	system("gm convert 3-out-converted\\e_mmenu_SDW.tga 4-out-png\\e_mmenu_SDW.png");

}

void processGameOver()
{
	CTGA *title = 0;

	system("gm convert 1-in-png\\gameover_HDS.png 2-out-tga\\gameover_HDS.tga");
	system("gm convert 1-in-png\\gameover_HDW.png 2-out-tga\\gameover_HDW.tga");
	system("gm convert 1-in-png\\gameover.png 2-out-tga\\gameover.tga");

	// HDS

	img = new CTGA((char*)"2-out-tga\\gameover_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(2048, 1536);
	img->flipV();
	img->dark(8);	
	img->blur(64);

	title = new CTGA((char*)"2-out-tga\\gameover.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(2048, 1536))
	{
		while (!title->isSpriteFit(2048, 1536))
			title->resizeSprite(.9f);
	}

	title->renderSprite(1024 - (title->_spriteSizeX / 2), 768 - (title->_spriteSizeY / 2), img->_buffer, 2048, 1536);

	img->setA(255);
	img->save((char*)"3-out-converted\\gameover_HDS.tga");
	delete img;
	delete title;

	// SDS

	img = new CTGA((char*)"2-out-tga\\gameover_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(1024, 768);
	img->flipV();
	img->dark(8);
	img->blur(64);

	title = new CTGA((char*)"2-out-tga\\gameover.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1024, 768))
	{
		while (!title->isSpriteFit(1024, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(512 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1024, 768);

	img->setA(255);
	img->save((char*)"3-out-converted\\gameover_SDS.tga");
	delete img;
	delete title;

	// HDW

	img = new CTGA((char*)"2-out-tga\\gameover_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1920, 1080);
	img->flipV();
	img->dark(8);
	img->blur(64);

	title = new CTGA((char*)"2-out-tga\\gameover.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1920, 1080))
	{
		while (!title->isSpriteFit(1920, 1080))
			title->resizeSprite(.9f);
	}

	title->renderSprite(960 - (title->_spriteSizeX / 2), 540 - (title->_spriteSizeY / 2), img->_buffer, 1920, 1080);
	
	img->setA(255);
	img->save((char*)"3-out-converted\\gameover_HDW.tga");
	delete img;
	delete title;

	// SDW

	img = new CTGA((char*)"2-out-tga\\gameover_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1366, 768);
	img->flipV();
	img->dark(8);
	img->blur(64);

	title = new CTGA((char*)"2-out-tga\\gameover.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1366, 768))
	{
		while (!title->isSpriteFit(1366, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(683 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1366, 384);

	img->setA(255);
	img->save((char*)"3-out-converted\\gameover_SDW.tga");
	delete img;
	delete title;

	system("gm convert 3-out-converted\\gameover_HDS.tga 4-out-png\\gameover_HDS.png");
	system("gm convert 3-out-converted\\gameover_HDW.tga 4-out-png\\gameover_HDW.png");
	system("gm convert 3-out-converted\\gameover_SDS.tga 4-out-png\\gameover_SDS.png");
	system("gm convert 3-out-converted\\gameover_SDW.tga 4-out-png\\gameover_SDW.png");

}

void processStart()
{
	CTGA *title = 0;

	system("gm convert 1-in-png\\start_HDS.png 2-out-tga\\start_HDS.tga");
	system("gm convert 1-in-png\\start_HDW.png 2-out-tga\\start_HDW.tga");
	system("gm convert 1-in-png\\title.png 2-out-tga\\title.tga");

	// HDS

	img = new CTGA((char*)"2-out-tga\\start_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(2048, 1536);
	img->flipV();
//	img->dark(8);
	img->blur(8);

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(2048, 1536))
	{
		while (!title->isSpriteFit(2048, 1536))
			title->resizeSprite(.9f);
	}

	title->renderSprite(1024 - (title->_spriteSizeX / 2), 768 - (title->_spriteSizeY / 2), img->_buffer, 2048, 1536);

	img->save((char*)"3-out-converted\\start_HDS.tga");
	delete img;
	delete title;

	// SDS

	img = new CTGA((char*)"2-out-tga\\start_HDS.tga");
	img->cleanAlfa();
	img->resizeTo(1024, 768);
	img->flipV();
//	img->dark(8);
	img->blur(8);

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1024, 768))
	{
		while (!title->isSpriteFit(1024, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(512 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1024, 768);

	img->save((char*)"3-out-converted\\start_SDS.tga");
	delete img;
	delete title;

	// HDW

	img = new CTGA((char*)"2-out-tga\\start_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1920, 1080);
	img->flipV();
//	img->dark(8);
	img->blur(8);

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1920, 1080))
	{
		while (!title->isSpriteFit(1920, 1080))
			title->resizeSprite(.9f);
	}

	title->renderSprite(960 - (title->_spriteSizeX / 2), 540 - (title->_spriteSizeY / 2), img->_buffer, 1920, 1080);

	img->save((char*)"3-out-converted\\start_HDW.tga");
	delete img;
	delete title;

	// SDW

	img = new CTGA((char*)"2-out-tga\\start_HDW.tga");
	img->cleanAlfa();
	img->resizeTo(1366, 768);
	img->flipV();
//	img->dark(8);
	img->blur(8);

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1366, 768))
	{
		while (!title->isSpriteFit(1366, 768))
			title->resizeSprite(.9f);
	}

	title->renderSprite(683 - (title->_spriteSizeX / 2), 384 - (title->_spriteSizeY / 2), img->_buffer, 1366, 384);

	img->save((char*)"3-out-converted\\start_SDW.tga");
	delete img;
	delete title;

	system("gm convert 3-out-converted\\start_HDS.tga 4-out-png\\start_HDS.png");
	system("gm convert 3-out-converted\\start_HDW.tga 4-out-png\\start_HDW.png");
	system("gm convert 3-out-converted\\start_SDS.tga 4-out-png\\start_SDS.png");
	system("gm convert 3-out-converted\\start_SDW.tga 4-out-png\\start_SDW.png");

}


void processHelp()
{
	system("gm convert 1-in-png\\help.png 2-out-tga\\help.tga");
	system("gm convert 1-in-png\\menu.png 2-out-tga\\menu.tga");

	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_click_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_click_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_over_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_over_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_static_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\help.tga", (char*)"3-out-converted\\hint_static_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_click_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_click_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_over_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_over_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_static_128px.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_static_256px.tga", 256, 256);

	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_click.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_over.tga", 128, 128);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_static.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_click256.tga", 256, 256);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_over256.tga", 256, 256);
	generatePopup((char*)"2-out-tga\\menu.tga", (char*)"3-out-converted\\menu_static256.tga", 256, 256);

	system("gm convert 3-out-converted\\hint_click_128px.tga 4-out-png\\hint_click_128px.png");
	system("gm convert 3-out-converted\\hint_click_256px.tga 4-out-png\\hint_click_256px.png");
	system("gm convert 3-out-converted\\hint_over_128px.tga 4-out-png\\hint_over_128px.png");
	system("gm convert 3-out-converted\\hint_over_256px.tga 4-out-png\\hint_over_256px.png");
	system("gm convert 3-out-converted\\hint_static_128px.tga 4-out-png\\hint_static_128px.png");
	system("gm convert 3-out-converted\\hint_static_256px.tga 4-out-png\\hint_static_256px.png");

	system("gm convert 3-out-converted\\menu_click_128px.tga 4-out-png\\menu_click_128px.png");
	system("gm convert 3-out-converted\\menu_click_256px.tga 4-out-png\\menu_click_256px.png");
	system("gm convert 3-out-converted\\menu_over_128px.tga 4-out-png\\menu_over_128px.png");
	system("gm convert 3-out-converted\\menu_over_256px.tga 4-out-png\\menu_over_256px.png");
	system("gm convert 3-out-converted\\menu_static_128px.tga 4-out-png\\menu_static_128px.png");
	system("gm convert 3-out-converted\\menu_static_256px.tga 4-out-png\\menu_static_256px.png");


	system("gm convert 3-out-converted\\menu_click.tga 4-out-png\\menu_click.png");
	system("gm convert 3-out-converted\\menu_click256.tga 4-out-png\\menu_click256.png");
	
	system("gm convert 3-out-converted\\menu_over.tga 4-out-png\\menu_over.png");
	system("gm convert 3-out-converted\\menu_over256.tga 4-out-png\\menu_over256.png");
	
	system("gm convert 3-out-converted\\menu_static.tga 4-out-png\\menu_static.png");
	system("gm convert 3-out-converted\\menu_static256.tga 4-out-png\\menu_static256.png");


}


void processDigits()
{
	system("gm convert 1-in-png\\0.png 2-out-tga\\0.tga");
	system("gm convert 1-in-png\\1.png 2-out-tga\\1.tga");
	system("gm convert 1-in-png\\2.png 2-out-tga\\2.tga");
	system("gm convert 1-in-png\\3.png 2-out-tga\\3.tga");
	system("gm convert 1-in-png\\4.png 2-out-tga\\4.tga");
	system("gm convert 1-in-png\\5.png 2-out-tga\\5.tga");
	system("gm convert 1-in-png\\6.png 2-out-tga\\6.tga");
	system("gm convert 1-in-png\\7.png 2-out-tga\\7.tga");
	system("gm convert 1-in-png\\8.png 2-out-tga\\8.tga");
	system("gm convert 1-in-png\\9.png 2-out-tga\\9.tga");

	generatePopup((char*)"2-out-tga\\0.tga", (char*)"3-out-converted\\0.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\0.tga", (char*)"3-out-converted\\0b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\1.tga", (char*)"3-out-converted\\1.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\1.tga", (char*)"3-out-converted\\1b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\2.tga", (char*)"3-out-converted\\2.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\2.tga", (char*)"3-out-converted\\2b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\3.tga", (char*)"3-out-converted\\3.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\3.tga", (char*)"3-out-converted\\3b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\4.tga", (char*)"3-out-converted\\4.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\4.tga", (char*)"3-out-converted\\4b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\5.tga", (char*)"3-out-converted\\5.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\5.tga", (char*)"3-out-converted\\5b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\6.tga", (char*)"3-out-converted\\6.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\6.tga", (char*)"3-out-converted\\6b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\7.tga", (char*)"3-out-converted\\7.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\7.tga", (char*)"3-out-converted\\7b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\8.tga", (char*)"3-out-converted\\8.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\8.tga", (char*)"3-out-converted\\8b.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\9.tga", (char*)"3-out-converted\\9.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\9.tga", (char*)"3-out-converted\\9b.tga", 128, 128);

	system("gm convert 3-out-converted\\0.tga 4-out-png\\0.png");
	system("gm convert 3-out-converted\\0b.tga 4-out-png\\0b.png");
	system("gm convert 3-out-converted\\1.tga 4-out-png\\1.png");
	system("gm convert 3-out-converted\\1b.tga 4-out-png\\1b.png");
	system("gm convert 3-out-converted\\2.tga 4-out-png\\2.png");
	system("gm convert 3-out-converted\\2b.tga 4-out-png\\2b.png");
	system("gm convert 3-out-converted\\3.tga 4-out-png\\3.png");
	system("gm convert 3-out-converted\\3b.tga 4-out-png\\3b.png");
	system("gm convert 3-out-converted\\4.tga 4-out-png\\4.png");
	system("gm convert 3-out-converted\\4b.tga 4-out-png\\4b.png");
	system("gm convert 3-out-converted\\5.tga 4-out-png\\5.png");
	system("gm convert 3-out-converted\\5b.tga 4-out-png\\5b.png");
	system("gm convert 3-out-converted\\6.tga 4-out-png\\6.png");
	system("gm convert 3-out-converted\\6b.tga 4-out-png\\6b.png");
	system("gm convert 3-out-converted\\7.tga 4-out-png\\7.png");
	system("gm convert 3-out-converted\\7b.tga 4-out-png\\7b.png");
	system("gm convert 3-out-converted\\8.tga 4-out-png\\8.png");
	system("gm convert 3-out-converted\\8b.tga 4-out-png\\8b.png");
	system("gm convert 3-out-converted\\9.tga 4-out-png\\9.png");
	system("gm convert 3-out-converted\\9b.tga 4-out-png\\9b.png");

	system("gm convert 1-in-png\\x10.png 2-out-tga\\x10.tga");
	system("gm convert 1-in-png\\x1.png 2-out-tga\\x1.tga");
	system("gm convert 1-in-png\\x2.png 2-out-tga\\x2.tga");
	system("gm convert 1-in-png\\x3.png 2-out-tga\\x3.tga");
	system("gm convert 1-in-png\\x4.png 2-out-tga\\x4.tga");
	system("gm convert 1-in-png\\x5.png 2-out-tga\\x5.tga");
	system("gm convert 1-in-png\\x6.png 2-out-tga\\x6.tga");
	system("gm convert 1-in-png\\x7.png 2-out-tga\\x7.tga");
	system("gm convert 1-in-png\\x8.png 2-out-tga\\x8.tga");
	system("gm convert 1-in-png\\x9.png 2-out-tga\\x9.tga");

	generatePopup((char*)"2-out-tga\\x10.tga", (char*)"3-out-converted\\x10_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x10.tga", (char*)"3-out-converted\\x10_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x1.tga", (char*)"3-out-converted\\x1_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x1.tga", (char*)"3-out-converted\\x1_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x2.tga", (char*)"3-out-converted\\x2_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x2.tga", (char*)"3-out-converted\\x2_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x3.tga", (char*)"3-out-converted\\x3_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x3.tga", (char*)"3-out-converted\\x3_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x4.tga", (char*)"3-out-converted\\x4_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x4.tga", (char*)"3-out-converted\\x4_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x5.tga", (char*)"3-out-converted\\x5_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x5.tga", (char*)"3-out-converted\\x5_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x6.tga", (char*)"3-out-converted\\x6_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x6.tga", (char*)"3-out-converted\\x6_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x7.tga", (char*)"3-out-converted\\x7_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x7.tga", (char*)"3-out-converted\\x7_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x8.tga", (char*)"3-out-converted\\x8_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x8.tga", (char*)"3-out-converted\\x8_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\x9.tga", (char*)"3-out-converted\\x9_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\x9.tga", (char*)"3-out-converted\\x9_HDS.tga", 128, 128);

	system("gm convert 3-out-converted\\x1_SDS.tga 4-out-png\\x1_SDS.png");
	system("gm convert 3-out-converted\\x1_HDS.tga 4-out-png\\x1_HDS.png");
	system("gm convert 3-out-converted\\x2_SDS.tga 4-out-png\\x2_SDS.png");
	system("gm convert 3-out-converted\\x2_HDS.tga 4-out-png\\x2_HDS.png");
	system("gm convert 3-out-converted\\x3_SDS.tga 4-out-png\\x3_SDS.png");
	system("gm convert 3-out-converted\\x3_HDS.tga 4-out-png\\x3_HDS.png");
	system("gm convert 3-out-converted\\x4_SDS.tga 4-out-png\\x4_SDS.png");
	system("gm convert 3-out-converted\\x4_HDS.tga 4-out-png\\x4_HDS.png");
	system("gm convert 3-out-converted\\x5_SDS.tga 4-out-png\\x5_SDS.png");
	system("gm convert 3-out-converted\\x5_HDS.tga 4-out-png\\x5_HDS.png");
	system("gm convert 3-out-converted\\x6_SDS.tga 4-out-png\\x6_SDS.png");
	system("gm convert 3-out-converted\\x6_HDS.tga 4-out-png\\x6_HDS.png");
	system("gm convert 3-out-converted\\x7_SDS.tga 4-out-png\\x7_SDS.png");
	system("gm convert 3-out-converted\\x7_HDS.tga 4-out-png\\x7_HDS.png");
	system("gm convert 3-out-converted\\x8_SDS.tga 4-out-png\\x8_SDS.png");
	system("gm convert 3-out-converted\\x8_HDS.tga 4-out-png\\x8_HDS.png");
	system("gm convert 3-out-converted\\x9_SDS.tga 4-out-png\\x9_SDS.png");
	system("gm convert 3-out-converted\\x9_HDS.tga 4-out-png\\x9_HDS.png");
	system("gm convert 3-out-converted\\x10_SDS.tga 4-out-png\\x10_SDS.png");
	system("gm convert 3-out-converted\\x10_HDS.tga 4-out-png\\x10_HDS.png");

	system("gm convert 1-in-png\\100.png 2-out-tga\\100.tga");
	system("gm convert 1-in-png\\250.png 2-out-tga\\250.tga");
	system("gm convert 1-in-png\\500.png 2-out-tga\\500.tga");
	system("gm convert 1-in-png\\1000.png 2-out-tga\\1000.tga");

	generatePopup((char*)"2-out-tga\\100.tga", (char*)"3-out-converted\\score100_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\100.tga", (char*)"3-out-converted\\score100_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\250.tga", (char*)"3-out-converted\\score250_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\250.tga", (char*)"3-out-converted\\score250_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\500.tga", (char*)"3-out-converted\\score500_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\500.tga", (char*)"3-out-converted\\score500_HDS.tga", 128, 128);

	generatePopup((char*)"2-out-tga\\1000.tga", (char*)"3-out-converted\\score1000_SDS.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\1000.tga", (char*)"3-out-converted\\score1000_HDS.tga", 128, 128);

	system("gm convert 3-out-converted\\score100_SDS.tga 4-out-png\\score100_SDS.png");
	system("gm convert 3-out-converted\\score100_HDS.tga 4-out-png\\score100_HDS.png");

	system("gm convert 3-out-converted\\score250_SDS.tga 4-out-png\\score250_SDS.png");
	system("gm convert 3-out-converted\\score250_HDS.tga 4-out-png\\score250_HDS.png");

	system("gm convert 3-out-converted\\score500_SDS.tga 4-out-png\\score500_SDS.png");
	system("gm convert 3-out-converted\\score500_HDS.tga 4-out-png\\score500_HDS.png");

	system("gm convert 3-out-converted\\score1000_SDS.tga 4-out-png\\score1000_SDS.png");
	system("gm convert 3-out-converted\\score1000_HDS.tga 4-out-png\\score1000_HDS.png");

}

void processTapTap()
{
	system("gm convert 1-in-png\\taptap.png 2-out-tga\\taptap.tga");

	renderBottom25((char*)"2-out-tga\\taptap.tga", (char*)"3-out-converted\\taptap_HDS.tga", 2048, 1536);
	renderBottom25((char*)"2-out-tga\\taptap.tga", (char*)"3-out-converted\\taptap_SDS.tga", 1024, 768);
	renderBottom25((char*)"2-out-tga\\taptap.tga", (char*)"3-out-converted\\taptap_HDW.tga", 1920, 1080);
	renderBottom25((char*)"2-out-tga\\taptap.tga", (char*)"3-out-converted\\taptap_SDW.tga", 1366, 768);

	system("gm convert 3-out-converted\\taptap_SDS.tga 4-out-png\\taptap_SDS.png");
	system("gm convert 3-out-converted\\taptap_HDS.tga 4-out-png\\taptap_HDS.png");
	system("gm convert 3-out-converted\\taptap_SDW.tga 4-out-png\\taptap_SDW.png");
	system("gm convert 3-out-converted\\taptap_HDW.tga 4-out-png\\taptap_HDW.png");
}


void processIcon()
{
	CTGA *title;
	CTGA *background;

	system("gm convert 1-in-png\\icon-shape.png 2-out-tga\\icon-shape.tga");

	img = new CTGA((char*)"2-out-tga\\icon-shape.tga");
	img->cleanAlfa();

	background = new CTGA((char*)"2-out-tga\\background_HDS.tga");
	background->cleanAlfa();
	background->flipV();
	background->blur(8);
	background->renderChannel(img->_buffer, 1024, 1024);

	title = new CTGA((char*)"2-out-tga\\title.tga");
	title->cleanAlfa();
	title->flipV();
	title->clip();

	if (!title->isSpriteFit(1024, 1024))
	{
		while (!title->isSpriteFit(1024, 1024))
			title->resizeSprite(.9f);
	}

	title->renderSprite(512 - (title->_spriteSizeX / 2), 512 - (title->_spriteSizeY / 2), img->_buffer, 1024, 1024);

	img->setA(255, 0, 300, 1024, 800);
	img->save((char*)"3-out-converted\\1024.tga");
	delete img;
	delete title;
	delete background;

	system("gm convert 3-out-converted\\1024.tga 3-out-converted\\1024.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\drawable-hdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\drawable-hdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\drawable-hdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\drawable-hdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-ldpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\drawable-ldpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-ldpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-ldpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-mdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\drawable-mdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-mdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\drawable-mdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\drawable-xhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\drawable-xhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\drawable-xhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\drawable-xhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\drawable-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 114x114 7-out\\android\\res\\drawable-xxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\drawable-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\drawable-xxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\drawable-xxxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 192x192 7-out\\android\\res\\drawable-xxxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\drawable-xxxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\drawable-xxxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\mipmap-hdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\mipmap-hdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\mipmap-hdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android\\res\\mipmap-hdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android\\res\\mipmap-ldpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\mipmap-ldpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android\\res\\mipmap-ldpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android\\res\\mipmap-ldpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\mipmap-mdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\mipmap-mdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\mipmap-mdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android\\res\\mipmap-mdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\mipmap-xhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\mipmap-xhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\mipmap-xhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android\\res\\mipmap-xhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\mipmap-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 144x144 7-out\\android\\res\\mipmap-xxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\mipmap-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android\\res\\mipmap-xxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\mipmap-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 192x192 7-out\\android\\res\\mipmap-xxxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\mipmap-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android\\res\\mipmap-xxhdpi\\ic_sync_black_24dp.png");

	// android-free

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\drawable-hdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\drawable-hdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\drawable-hdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\drawable-hdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-ldpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\drawable-ldpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-ldpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-ldpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-mdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\drawable-mdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-mdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\drawable-mdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\drawable-xhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\drawable-xhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\drawable-xhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\drawable-xhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\drawable-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 114x114 7-out\\android-free\\res\\drawable-xxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\drawable-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\drawable-xxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\drawable-xxxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 192x192 7-out\\android-free\\res\\drawable-xxxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\drawable-xxxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\drawable-xxxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\mipmap-hdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\mipmap-hdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\mipmap-hdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 36x36 7-out\\android-free\\res\\mipmap-hdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android-free\\res\\mipmap-ldpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\mipmap-ldpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android-free\\res\\mipmap-ldpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 12x12 7-out\\android-free\\res\\mipmap-ldpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\mipmap-mdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\mipmap-mdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\mipmap-mdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 24x24 7-out\\android-free\\res\\mipmap-mdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\mipmap-xhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\mipmap-xhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\mipmap-xhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 48x48 7-out\\android-free\\res\\mipmap-xhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 144x144 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 72x72 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_sync_black_24dp.png");

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_info_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 192x192 7-out\\android-free\\res\\mipmap-xxxhdpi\\ic_launcher.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_notifications_black_24dp.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 96x96 7-out\\android-free\\res\\mipmap-xxhdpi\\ic_sync_black_24dp.png");

	// marketing

	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 512x512 7-out\\_marketing\\512.png");
	system("gm convert -size 1024x1024 3-out-converted\\1024.png -resize 4096x4096 7-out\\_marketing\\4096.png");

	system("del 3-out-converted\\1024.png");

}

void processGems()
{

	system("gm convert 1-in-png\\gem1.png 2-out-tga\\gem1.tga");
	system("gm convert 1-in-png\\gem2.png 2-out-tga\\gem2.tga");
	system("gm convert 1-in-png\\gem3.png 2-out-tga\\gem3.tga");
	system("gm convert 1-in-png\\gem4.png 2-out-tga\\gem4.tga");
	system("gm convert 1-in-png\\gem5.png 2-out-tga\\gem5.tga");
	system("gm convert 1-in-png\\gem6.png 2-out-tga\\gem6.tga");
	system("gm convert 1-in-png\\gem7.png 2-out-tga\\gem7.tga");
	system("gm convert 1-in-png\\gem8.png 2-out-tga\\gem8.tga");
	system("gm convert 1-in-png\\gem9.png 2-out-tga\\gem9.tga");
	system("gm convert 1-in-png\\gem10.png 2-out-tga\\gem10.tga");
	system("gm convert 1-in-png\\gem11.png 2-out-tga\\gem11.tga");

	generatePopup((char*)"2-out-tga\\gem1.tga", (char*)"3-out-converted\\gem1.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem1.tga", (char*)"3-out-converted\\gem1b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem1.tga", (char*)"3-out-converted\\gem1c.tga");

	generatePopup((char*)"2-out-tga\\gem2.tga", (char*)"3-out-converted\\gem2.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem2.tga", (char*)"3-out-converted\\gem2b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem2.tga", (char*)"3-out-converted\\gem2c.tga");

	generatePopup((char*)"2-out-tga\\gem3.tga", (char*)"3-out-converted\\gem3.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem3.tga", (char*)"3-out-converted\\gem3b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem3.tga", (char*)"3-out-converted\\gem3c.tga");

	generatePopup((char*)"2-out-tga\\gem4.tga", (char*)"3-out-converted\\gem4.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem4.tga", (char*)"3-out-converted\\gem4b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem4.tga", (char*)"3-out-converted\\gem4c.tga");

	generatePopup((char*)"2-out-tga\\gem5.tga", (char*)"3-out-converted\\gem5.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem5.tga", (char*)"3-out-converted\\gem5b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem5.tga", (char*)"3-out-converted\\gem5c.tga");

	generatePopup((char*)"2-out-tga\\gem6.tga", (char*)"3-out-converted\\gem6.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem6.tga", (char*)"3-out-converted\\gem6b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem6.tga", (char*)"3-out-converted\\gem6c.tga");

	generatePopup((char*)"2-out-tga\\gem7.tga", (char*)"3-out-converted\\gem7.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem7.tga", (char*)"3-out-converted\\gem7b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem7.tga", (char*)"3-out-converted\\gem7c.tga");

	generatePopup((char*)"2-out-tga\\gem8.tga", (char*)"3-out-converted\\gem8.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem8.tga", (char*)"3-out-converted\\gem8b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem8.tga", (char*)"3-out-converted\\gem8c.tga");

	generatePopup((char*)"2-out-tga\\gem9.tga", (char*)"3-out-converted\\gem9.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem9.tga", (char*)"3-out-converted\\gem9b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem9.tga", (char*)"3-out-converted\\gem9c.tga");

	generatePopup((char*)"2-out-tga\\gem10.tga", (char*)"3-out-converted\\gem10.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem10.tga", (char*)"3-out-converted\\gem10b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem10.tga", (char*)"3-out-converted\\gem10c.tga");

	generatePopup((char*)"2-out-tga\\gem11.tga", (char*)"3-out-converted\\gem11.tga", 64, 64);
	generatePopup((char*)"2-out-tga\\gem11.tga", (char*)"3-out-converted\\gem11b.tga", 128, 128);
	renderGemC((char*)"2-out-tga\\gem11.tga", (char*)"3-out-converted\\gem11c.tga");

	system("gm convert 3-out-converted\\gem1.tga 4-out-png\\gem1.png");
	system("gm convert 3-out-converted\\gem1b.tga 4-out-png\\gem1b.png");
	system("gm convert 3-out-converted\\gem1c.tga 4-out-png\\gem1c.png");

	system("gm convert 3-out-converted\\gem2.tga 4-out-png\\gem2.png");
	system("gm convert 3-out-converted\\gem2b.tga 4-out-png\\gem2b.png");
	system("gm convert 3-out-converted\\gem2c.tga 4-out-png\\gem2c.png");

	system("gm convert 3-out-converted\\gem3.tga 4-out-png\\gem3.png");
	system("gm convert 3-out-converted\\gem3b.tga 4-out-png\\gem3b.png");
	system("gm convert 3-out-converted\\gem3c.tga 4-out-png\\gem3c.png");

	system("gm convert 3-out-converted\\gem4.tga 4-out-png\\gem4.png");
	system("gm convert 3-out-converted\\gem4b.tga 4-out-png\\gem4b.png");
	system("gm convert 3-out-converted\\gem4c.tga 4-out-png\\gem4c.png");

	system("gm convert 3-out-converted\\gem5.tga 4-out-png\\gem5.png");
	system("gm convert 3-out-converted\\gem5b.tga 4-out-png\\gem5b.png");
	system("gm convert 3-out-converted\\gem5c.tga 4-out-png\\gem5c.png");

	system("gm convert 3-out-converted\\gem6.tga 4-out-png\\gem6.png");
	system("gm convert 3-out-converted\\gem6b.tga 4-out-png\\gem6b.png");
	system("gm convert 3-out-converted\\gem6c.tga 4-out-png\\gem6c.png");

	system("gm convert 3-out-converted\\gem7.tga 4-out-png\\gem7.png");
	system("gm convert 3-out-converted\\gem7b.tga 4-out-png\\gem7b.png");
	system("gm convert 3-out-converted\\gem7c.tga 4-out-png\\gem7c.png");

	system("gm convert 3-out-converted\\gem8.tga 4-out-png\\gem8.png");
	system("gm convert 3-out-converted\\gem8b.tga 4-out-png\\gem8b.png");
	system("gm convert 3-out-converted\\gem8c.tga 4-out-png\\gem8c.png");
	system("gm convert 3-out-converted\\gem8.tga 4-out-png\\gem8_00.png");
	system("gm convert 3-out-converted\\gem8b.tga 4-out-png\\gem8b_00.png");
	system("gm convert 3-out-converted\\gem8c.tga 4-out-png\\gem8c_00.png");

	system("gm convert 3-out-converted\\gem9.tga 4-out-png\\gem9.png");
	system("gm convert 3-out-converted\\gem9b.tga 4-out-png\\gem9b.png");
	system("gm convert 3-out-converted\\gem9c.tga 4-out-png\\gem9c.png");
	system("gm convert 3-out-converted\\gem9.tga 4-out-png\\gem9_00.png");
	system("gm convert 3-out-converted\\gem9b.tga 4-out-png\\gem9b_00.png");
	system("gm convert 3-out-converted\\gem9c.tga 4-out-png\\gem9c_00.png");

	system("gm convert 3-out-converted\\gem10.tga 4-out-png\\gem10.png");
	system("gm convert 3-out-converted\\gem10b.tga 4-out-png\\gem10b.png");
	system("gm convert 3-out-converted\\gem10c.tga 4-out-png\\gem10c.png");
	system("gm convert 3-out-converted\\gem10.tga 4-out-png\\gem10_00.png");
	system("gm convert 3-out-converted\\gem10b.tga 4-out-png\\gem10b_00.png");
	system("gm convert 3-out-converted\\gem10c.tga 4-out-png\\gem10c_00.png");

	system("gm convert 3-out-converted\\gem11.tga 4-out-png\\gem11.png");
	system("gm convert 3-out-converted\\gem11b.tga 4-out-png\\gem11b.png");
	system("gm convert 3-out-converted\\gem11c.tga 4-out-png\\gem11c.png");
	system("gm convert 3-out-converted\\gem11.tga 4-out-png\\gem11_00.png");
	system("gm convert 3-out-converted\\gem11b.tga 4-out-png\\gem11b_00.png");
	system("gm convert 3-out-converted\\gem11c.tga 4-out-png\\gem11c_00.png");

}

void processMarketing()
{

	convertTo((char*)"3-out-converted\\start_HDW.tga", (char*)"7-out\\_marketing\\1280x720.tga", 1280, 720);
	convertTo((char*)"3-out-converted\\start_HDW.tga", (char*)"7-out\\_marketing\\1024x500.tga", 1024, 500);
	convertTo((char*)"3-out-converted\\start_HDW.tga", (char*)"7-out\\_marketing\\180x120.tga", 180, 120);
	convertTo((char*)"3-out-converted\\start_HDW.tga", (char*)"7-out\\_marketing\\MAIN.tga", 1920, 1080);

	system("gm convert 7-out\\_marketing\\1280x720.tga 7-out\\_marketing\\1280x720.png");
	system("gm convert 7-out\\_marketing\\1024x500.tga 7-out\\_marketing\\1024x500.png");
	system("gm convert 7-out\\_marketing\\180x120.tga 7-out\\_marketing\\180x120.png");
	system("gm convert 7-out\\_marketing\\MAIN.tga 7-out\\_marketing\\MAIN.png");

	system("del 7-out\\_marketing\\1280x720.tga");
	system("del 7-out\\_marketing\\1024x500.tga");
	system("del 7-out\\_marketing\\180x120.tga");
	system("del 7-out\\_marketing\\MAIN.tga");

}

void fastSave(char f[], char v[])
{
	FILE *file;

	if ((file = fopen(f, "wt")) == NULL)
	{
		printf("ERROR - cannot write fastSave!!\n");
		return;
	}

	fprintf(file, v);
	fclose(file);

}

void processScript()
{
	char linia[1024];
	FILE *in;

	char appName[1024];
	char appTag[1024];
	char appShortTag[1024];	// bez com.shodan9
	char adMobApp[1024];
	char adMobBaner[1024];
	char adMobVideo[1024];
	
	std::string line;

	std::ifstream infile("5-in-script\\config.inc");

	std::getline(infile, line);
	strcpy(appName, line.c_str());

	std::getline(infile, line);
	strcpy(appTag, line.c_str());

	std::getline(infile, line);
	strcpy(adMobApp, line.c_str());

	std::getline(infile, line);
	strcpy(adMobBaner, line.c_str());

	std::getline(infile, line);
	strcpy(adMobVideo, line.c_str());

	fastSave((char*)"5-in-script\\.appName", appName);
	fastSave((char*)"5-in-script\\.appTag", appTag);
	fastSave((char*)"5-in-script\\.appMobApp", adMobApp);
	fastSave((char*)"5-in-script\\.appMobBaner", adMobBaner);
	fastSave((char*)"5-in-script\\.appMobVideo", adMobVideo);

	memset(appShortTag, 0, 1000);

	for (int i = 0; i < 256; i++)
		appShortTag[i] = appTag[12 + i];

	sprintf(linia, "mkdir 7-out\\android\\src\\com\\shodan9\\%s", appShortTag);
	system(linia);

	sprintf(linia, "mkdir 7-out\\android-free\\src\\com\\shodan9\\%s", appShortTag);
	system(linia);


	// retail .project

	system("copy 5-in-script\\retail\\project.0 7-out\\android\\.project");
	system("type 5-in-script\\.appName >> 7-out\\android\\.project");
	system("type 5-in-script\\retail\\project.1 >> 7-out\\android\\.project");

	// retail AndroidManifest.xml

	system("copy 5-in-script\\retail\\AndroidManifest.0 7-out\\android\\AndroidManifest.xml");
	system("type 5-in-script\\.appTag >> 7-out\\android\\AndroidManifest.xml");
	system("type 5-in-script\\retail\\AndroidManifest.1 >> 7-out\\android\\AndroidManifest.xml");
	system("type 5-in-script\\.appName >> 7-out\\android\\AndroidManifest.xml");
	system("type 5-in-script\\retail\\AndroidManifest.2 >> 7-out\\android\\AndroidManifest.xml");

	// retail build.xml

	system("copy 5-in-script\\retail\\build.0 7-out\\android\\build.xml");
	system("type 5-in-script\\.appName >> 7-out\\android\\build.xml");
	system("type 5-in-script\\retail\\build.1 >> 7-out\\android\\build.xml");

	// retail Game.java

	sprintf(linia, "copy 5-in-script\\retail\\Game.0 7-out\\android\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);
	//system("copy 5-in-script\\retail\\Game.0 6-out-script\\retail\\Game.java");

	sprintf(linia, "type 5-in-script\\.appTag >> 7-out\\android\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);
	//system("type 5-in-script\\.appTag >> 6-out-script\\retail\\Game.java");
	
	sprintf(linia, "type 5-in-script\\retail\\Game.1 >> 7-out\\android\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);
	//system("type 5-in-script\\retail\\Game.1 >> 6-out-script\\retail\\Game.java");

	// retail strings.xml

	system("copy 5-in-script\\retail\\strings.0 7-out\\android\\res\\values\\strings.xml");
	system("type 5-in-script\\.appName >> 7-out\\android\\res\\values\\strings.xml");
	system("type 5-in-script\\retail\\Strings.1 >> 7-out\\android\\res\\values\\strings.xml");

	// free .project

	system("copy 5-in-script\\free\\project.0 7-out\\android-free\\.project");
	system("type 5-in-script\\.appName >> 7-out\\android-free\\.project");
	system("type 5-in-script\\free\\project.1 >> 7-out\\android-free\\.project");

	// free AndroidManifest.xml

	system("copy 5-in-script\\free\\AndroidManifest.0 7-out\\android-free\\AndroidManifest.xml");
	system("type 5-in-script\\.appTag >> 7-out\\android-free\\AndroidManifest.xml");
	system("type 5-in-script\\free\\AndroidManifest.1 >> 7-out\\android-free\\AndroidManifest.xml");
	system("type 5-in-script\\.appName >> 7-out\\android-free\\AndroidManifest.xml");
	system("type 5-in-script\\free\\AndroidManifest.2 >> 7-out\\android-free\\AndroidManifest.xml");

	// free build.xml

	system("copy 5-in-script\\free\\build.0 7-out\\android-free\\build.xml");
	system("type 5-in-script\\.appName >> 7-out\\android-free\\build.xml");
	system("type 5-in-script\\free\\build.1 >> 7-out\\android-free\\build.xml");

	// free Game.java

	sprintf(linia, "copy 5-in-script\\free\\Game.0 7-out\\android-free\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);

	sprintf(linia, "type 5-in-script\\.appTag >> 7-out\\android-free\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);

	sprintf(linia, "type 5-in-script\\free\\Game.1 >> 7-out\\android-free\\src\\com\\shodan9\\%s\\Game.java", appShortTag);
	system(linia);

//	system("copy 5-in-script\\free\\Game.0 6-out-script\\free\\Game.java");
//	system("type 5-in-script\\.appTag >> 6-out-script\\free\\Game.java");
//	system("type 5-in-script\\free\\Game.1 >> 6-out-script\\free\\Game.java");

	// free strings.xml

	system("copy 5-in-script\\free\\strings.0 7-out\\android-free\\res\\values\\strings.xml");
	system("type 5-in-script\\.appName >> 7-out\\android-free\\res\\values\\strings.xml");
	system("type 5-in-script\\free\\strings.1 >> 7-out\\android-free\\res\\values\\strings.xml");

	// free main.xml

	system("copy 5-in-script\\free\\main.0 7-out\\android-free\\res\\layout\\main.xml");
	system("type 5-in-script\\.appMobBaner >> 7-out\\android-free\\res\\layout\\main.xml");
	system("type 5-in-script\\free\\main.1 >> 7-out\\android-free\\res\\layout\\main.xml");

	// free SDLActivity.java

	system("copy 5-in-script\\free\\SDLActivity.0 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\.appMobApp >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\free\\SDLActivity.1 >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\.appMobVideo >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\free\\SDLActivity.2 >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\.appMobBaner >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
	system("type 5-in-script\\free\\SDLActivity.3 >> 7-out\\android-free\\src\\org\\libsdl\\app\\SDLActivity.java");
}

// 1 ciemny niebieski
// 2 ciemny zielony
// 3 jasny niebieski
// 4 ciemny czerwony
// 5 fioletowy
// 6 brazowy
// 7 standard szary
// 8 ciemny szary
// 9 jasny niebieski
// 10 bardzo jasny zielony
// 11 bardzo jasny niebieski


int main()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	short c3 = 10, c1 = 11, c2 = 14;

	system("del /s /f /q 7-out\\android\\*.*");
	system("del /s /f /q 7-out\\android-free\\*.*");

	system("rd 7-out\\android /S /Q");
	system("rd 7-out\\android-free /S /Q");

	system("robocopy 5-in-script\\android 7-out\\android\\ /s /e");
	system("robocopy 5-in-script\\android-free 7-out\\android-free\\ /s /e");

	system("del /Q 1-in-png\\*.*");
	system("del /Q 2-out-tga\\*.*");
	system("del /Q 3-out-converted\\*.*");
	system("del /Q 4-out-png\\*.*");
	system("del /Q 6-out-script\\*.*");

	system("del /Q 7-out\\*.*");
	system("del /Q 7-out\\_marketing\\*.*");
	system("del /Q 7-out\\assets\\*.*");
	system("del /Q 7-out\\res\\*.*");

	system("copy 0-in\\*.png 1-in-png\\*.*");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("script...");
	processScript();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");


	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("gems...");
	processGems();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1); 
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("background...");
	processBackground();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("menu...");
	processMenu();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("start...");
	processStart();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");


	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("help...");
	processHelp();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("game over...");
	processGameOver();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("digits...");
	processDigits();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("taptap...");
	processTapTap();
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("excelent...");
	processPopup((char*)"excelent");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("good...");
	processPopup((char*)"good");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("outstanding...");
	processPopup((char*)"outstanding");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("perfect...");
	processPopup((char*)"perfect");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("start...");
	processPopup((char*)"start");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("super...");
	processPopup((char*)"super");
	SetConsoleTextAttribute(hConsole, c3);
	printf("OK!\n");

	SetConsoleTextAttribute(hConsole, c1);
	printf("PROCESS: ");
	SetConsoleTextAttribute(hConsole, c2);
	printf("assets...\n");
	SetConsoleTextAttribute(hConsole, 7);

	processIcon();
	processMarketing();

	system("copy 4-out-png\\*.* 7-out\\android\\assets\\*.*");
	system("copy 4-out-png\\*.* 7-out\\android-free\\assets\\*.*");

	SetConsoleTextAttribute(hConsole, c3);
	printf("ASSETS OK!\n");

	return 0;
}

