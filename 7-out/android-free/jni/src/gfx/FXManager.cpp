// profile graczy

#include "FXManager.h"

CFXManager::CFXManager()
{
	_pImage[0] = new CSprite((char*)"m1.png");
	_pImage[1] = new CSprite((char*)"m2.png");
	_pImage[2] = new CSprite((char*)"m3.png");
	_pImage[3] = new CSprite((char*)"m4.png");
	_pImage[4] = new CSprite((char*)"m5.png");
	_pImage[5] = new CSprite((char*)"m6.png");
	_pImage[6] = new CSprite((char*)"m7.png");
	_pImage[7] = new CSprite((char*)"m8.png");
	_pImage[8] = new CSprite((char*)"m9.png");
	_pImage[9] = new CSprite((char*)"ma.png");
	_pImage[10] = new CSprite((char*)"mb.png");
	_pImage[11] = new CSprite((char*)"mc.png");
	_pImage[12] = new CSprite((char*)"md.png");
	_pImage[13] = new CSprite((char*)"me.png");

}

CFXManager::~CFXManager()
{
	for (int i = 0; i < 14; i++)
		SafeDelete(_pImage[i]);

	for (int i = 0; i < _pParticles.size(); i++)
	{
		if (_ulTimerEnd[i] != 0)
		{
			_pParticles[i]->pImage(NULL);
			SafeDelete(_pParticles[i]);
			_ulTimerEnd[i] = 0;
		}
	}

	_pParticles.clear();

	_ulTimerStart.clear();
	_ulTimerEnd.clear();
	_cLayer.clear();

}

int CFXManager::Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime)
{
	return Add(iType, x, y, r, g, b, a, ulTimerStart, ulTime, 0);
}

int CFXManager::Add(int iType, int x, int y, float r, float g, float b, float a, unsigned long ulTimerStart, unsigned long ulTime, char cLayer)
{
	int iReturn = 0;

	switch (iType)
	{

		case FX_SHOW_BOMB:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));
	
			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
		break;

		case FX_RAINBOW_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_DIAMOND_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 50,
				x - 50, y - 50, x + 50, y + 50,
				-.30f, -.30f, .30f, .30f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_SMALL_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 150,
				x-50, y-50, x+50, y+ 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 500));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_BIG_EXPLOSION:
			_pParticles.push_back(new CParticle2DManager(_pImage[10], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(false);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_SMALL_LOOP:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 10,
				x - 5, y - 5, x + 5, y + 5,
				-0.25f, -0.25f, 0.25f, 0.25f,
				1.0f, -.0025f, -.0075f,
				0.0f, -.1f, .1f,
				1000, 3000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_BIG_LOOP:
			_pParticles.push_back(new CParticle2DManager(_pImage[1], 300,
				x - 50, y - 50, x + 50, y + 50,
				-3.0f, -3.0f, 3.0f, 3.0f,
				1.0f, -.001f, -.005f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_HINT:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 25,
				x - 8, y - 8, x + 8, y + 8,
				-.003f, -.003f, .003f, .003f,
				1.0f, -.01f, -.05f,
				0.5f, -1.0f, 1.0f,
				100, 1000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;

		case FX_MENU_BUTTON:
			_pParticles.push_back(new CParticle2DManager(_pImage[3], 3,
				x - 16, y - 16, x + 32, y + 32,
				-.003f, -.003f, .003f, .003f,
				0.0f, .001f, .005f,
				0.5f, -.05f, .05f,
				100, 5000));

			_pParticles[_pParticles.size() - 1]->Color(r, g, b, a);				// zmieniamy kolor ostatnio dodanego elementu
			_pParticles[_pParticles.size() - 1]->isLoop(true);					// przy eksplozji nie odnawiamy
			_ulTimerStart.push_back(ulTimerStart);
			_ulTimerEnd.push_back(ulTimerStart + ulTime);
			iReturn = _pParticles.size() - 1;
			_cLayer.push_back(cLayer);
			break;


	}

	return iReturn;

}

void CFXManager::Remove(int id)
{
	_pParticles[id]->pImage(NULL);
	SafeDelete(_pParticles[id]);
	_ulTimerEnd[id] = 0;
}

// renderujemy dla wszystkich warstw

void CFXManager::Render(unsigned long ulTimer)
{
	for (int i = 0; i < _pParticles.size(); i++)
	{
		if (ulTimer < _ulTimerEnd[i])
		{
			_pParticles[i]->Render(ulTimer);
		}
		else
		{
			if (_ulTimerEnd[i] != 0)
			{
				_pParticles[i]->pImage(NULL);
				SafeDelete(_pParticles[i]);
				_ulTimerEnd[i] = 0;
			}
		}
	}
}

// renderujemy tylko dla wybranej warstwy

void CFXManager::Render(unsigned long ulTimer, char cLayer)
{
	for (int i = 0; i < _pParticles.size(); i++)
	{
		if (ulTimer < _ulTimerEnd[i])
		{
			if (_cLayer[i]==cLayer)
			_pParticles[i]->Render(ulTimer);
		}
		else
		{
			if (_ulTimerEnd[i] != 0)
			{
				_pParticles[i]->pImage(NULL);
				SafeDelete(_pParticles[i]);
				_ulTimerEnd[i] = 0;
			}
		}
	}
}

