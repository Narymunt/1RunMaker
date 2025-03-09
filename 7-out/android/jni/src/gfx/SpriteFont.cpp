#include "SpriteFont.h"

#pragma warning (disable:4244)

CSpriteFont::CSpriteFont()
{
	for (int i=0; i<37; i++)
		m_pCharTable[i] = NULL;

	m_pCharTable[0] = new CSprite((char*)"font_a.png",0,0,512,512);
	m_pCharTable[1] = new CSprite((char*)"font_b.png",0,0,512,512);
	m_pCharTable[2] = new CSprite((char*)"font_c.png",0,0,512,512);
	m_pCharTable[3] = new CSprite((char*)"font_d.png",0,0,512,512);
	m_pCharTable[4] = new CSprite((char*)"font_e.png",0,0,512,512);
	m_pCharTable[5] = new CSprite((char*)"font_f.png",0,0,512,512);
	m_pCharTable[6] = new CSprite((char*)"font_g.png",0,0,512,512);
	m_pCharTable[7] = new CSprite((char*)"font_h.png",0,0,512,512);
	m_pCharTable[8] = new CSprite((char*)"font_i.png",0,0,512,512);
	m_pCharTable[9] = new CSprite((char*)"font_j.png",0,0,512,512);
	m_pCharTable[10] = new CSprite((char*)"font_k.png",0,0,512,512);
	m_pCharTable[11] = new CSprite((char*)"font_l.png",0,0,512,512);
	m_pCharTable[12] = new CSprite((char*)"font_m.png",0,0,512,512);
	m_pCharTable[13] = new CSprite((char*)"font_n.png",0,0,512,512);
	m_pCharTable[14] = new CSprite((char*)"font_o.png",0,0,512,512);
	m_pCharTable[15] = new CSprite((char*)"font_p.png",0,0,512,512);
	m_pCharTable[16] = new CSprite((char*)"font_q.png",0,0,512,512);
	m_pCharTable[17] = new CSprite((char*)"font_r.png",0,0,512,512);
	m_pCharTable[18] = new CSprite((char*)"font_s.png",0,0,512,512);
	m_pCharTable[19] = new CSprite((char*)"font_t.png",0,0,512,512);
	m_pCharTable[20] = new CSprite((char*)"font_u.png",0,0,512,512);
	m_pCharTable[21] = new CSprite((char*)"font_v.png",0,0,512,512);
	m_pCharTable[22] = new CSprite((char*)"font_w.png",0,0,512,512);
	m_pCharTable[23] = new CSprite((char*)"font_x.png",0,0,512,512);
	m_pCharTable[24] = new CSprite((char*)"font_y.png",0,0,512,512);
	m_pCharTable[25] = new CSprite((char*)"font_z.png",0,0,512,512);
	m_pCharTable[26] = new CSprite((char*)"font_coma.png",0,0,512,512);
	m_pCharTable[27] = new CSprite((char*)"font_0.png",0,0,512,512);
	m_pCharTable[28] = new CSprite((char*)"font_1.png",0,0,512,512);
	m_pCharTable[29] = new CSprite((char*)"font_2.png",0,0,512,512);
	m_pCharTable[30] = new CSprite((char*)"font_3.png",0,0,512,512);
	m_pCharTable[31] = new CSprite((char*)"font_4.png",0,0,512,512);
	m_pCharTable[32] = new CSprite((char*)"font_5.png",0,0,512,512);
	m_pCharTable[33] = new CSprite((char*)"font_6.png",0,0,512,512);
	m_pCharTable[34] = new CSprite((char*)"font_7.png",0,0,512,512);
	m_pCharTable[35] = new CSprite((char*)"font_8.png",0,0,512,512);
	m_pCharTable[36] = new CSprite((char*)"font_9.png",0,0,512,512);
}


CSpriteFont::~CSpriteFont()
{
	for (int i=0; i<37; i++)
		SafeDelete(m_pCharTable[i]);
}

void CSpriteFont::Print(int iX, int iY, int iAlfa, float fSizeX, float fSizeY, char cText[])
{
	int iCurrentX;
	char cLetter;

	iCurrentX = iX; 

	for (int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				m_pCharTable[0]->Position(iCurrentX, iY);
				m_pCharTable[0]->Scale(fSizeX,fSizeY);
				m_pCharTable[0]->Render();
				iCurrentX += (int)(400 * fSizeX);  
			break;
			
			case 'B':
				m_pCharTable[1]->Position(iCurrentX, iY);
				m_pCharTable[1]->Scale(fSizeX,fSizeY);
				m_pCharTable[1]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'C':
				m_pCharTable[2]->Position(iCurrentX, iY);
				m_pCharTable[2]->Scale(fSizeX,fSizeY);
				m_pCharTable[2]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'D':
				m_pCharTable[3]->Position(iCurrentX, iY);
				m_pCharTable[3]->Scale(fSizeX,fSizeY);
				m_pCharTable[3]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'E':
				m_pCharTable[4]->Position(iCurrentX, iY);
				m_pCharTable[4]->Scale(fSizeX,fSizeY);
				m_pCharTable[4]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'F':
				m_pCharTable[5]->Position(iCurrentX, iY);
				m_pCharTable[5]->Scale(fSizeX,fSizeY);
				m_pCharTable[5]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'G':
				m_pCharTable[6]->Position(iCurrentX, iY);
				m_pCharTable[6]->Scale(fSizeX,fSizeY);
				m_pCharTable[6]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'H':
				m_pCharTable[7]->Position(iCurrentX, iY);
				m_pCharTable[7]->Scale(fSizeX,fSizeY);
				m_pCharTable[7]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'I':
				m_pCharTable[8]->Position(iCurrentX, iY);
				m_pCharTable[8]->Scale(fSizeX,fSizeY);
				m_pCharTable[8]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'J':
				m_pCharTable[9]->Position(iCurrentX, iY);
				m_pCharTable[9]->Scale(fSizeX,fSizeY);
				m_pCharTable[9]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'K':
				m_pCharTable[10]->Position(iCurrentX, iY);
				m_pCharTable[10]->Scale(fSizeX,fSizeY);
				m_pCharTable[10]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'L':
				m_pCharTable[11]->Position(iCurrentX, iY);
				m_pCharTable[11]->Scale(fSizeX,fSizeY);
				m_pCharTable[11]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'M':
				m_pCharTable[12]->Position(iCurrentX, iY);
				m_pCharTable[12]->Scale(fSizeX,fSizeY);
				m_pCharTable[12]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'N':
				m_pCharTable[13]->Position(iCurrentX, iY);
				m_pCharTable[13]->Scale(fSizeX,fSizeY);
				m_pCharTable[13]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'O':
				m_pCharTable[14]->Position(iCurrentX, iY);
				m_pCharTable[14]->Scale(fSizeX,fSizeY);
				m_pCharTable[14]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'P':
				m_pCharTable[15]->Position(iCurrentX, iY);
				m_pCharTable[15]->Scale(fSizeX,fSizeY);
				m_pCharTable[15]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Q':
				m_pCharTable[16]->Position(iCurrentX, iY);
				m_pCharTable[16]->Scale(fSizeX,fSizeY);
				m_pCharTable[16]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'R':
				m_pCharTable[17]->Position(iCurrentX, iY);
				m_pCharTable[17]->Scale(fSizeX,fSizeY);
				m_pCharTable[17]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'S':
				m_pCharTable[18]->Position(iCurrentX, iY);
				m_pCharTable[18]->Scale(fSizeX,fSizeY);
				m_pCharTable[18]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'T':
				m_pCharTable[19]->Position(iCurrentX, iY);
				m_pCharTable[19]->Scale(fSizeX,fSizeY);
				m_pCharTable[19]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'U':
				m_pCharTable[20]->Position(iCurrentX, iY);
				m_pCharTable[20]->Scale(fSizeX,fSizeY);
				m_pCharTable[20]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'V':
				m_pCharTable[21]->Position(iCurrentX, iY);
				m_pCharTable[21]->Scale(fSizeX,fSizeY);
				m_pCharTable[21]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'W':
				m_pCharTable[22]->Position(iCurrentX, iY);
				m_pCharTable[22]->Scale(fSizeX,fSizeY);
				m_pCharTable[22]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'X':
				m_pCharTable[23]->Position(iCurrentX, iY);
				m_pCharTable[23]->Scale(fSizeX,fSizeY);
				m_pCharTable[23]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Y':
				m_pCharTable[24]->Position(iCurrentX, iY);
				m_pCharTable[24]->Scale(fSizeX,fSizeY);
				m_pCharTable[24]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Z':
				m_pCharTable[25]->Position(iCurrentX, iY);
				m_pCharTable[25]->Scale(fSizeX,fSizeY);
				m_pCharTable[25]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '.':
				m_pCharTable[26]->Position(iCurrentX, iY);
				m_pCharTable[26]->Scale(fSizeX,fSizeY);
				m_pCharTable[26]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '0':
				m_pCharTable[27]->Position(iCurrentX, iY);
				m_pCharTable[27]->Scale(fSizeX,fSizeY);
				m_pCharTable[27]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '1':
				m_pCharTable[28]->Position(iCurrentX, iY);
				m_pCharTable[28]->Scale(fSizeX,fSizeY);
				m_pCharTable[28]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '2':
				m_pCharTable[29]->Position(iCurrentX, iY);
				m_pCharTable[29]->Scale(fSizeX,fSizeY);
				m_pCharTable[29]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '3':
				m_pCharTable[30]->Position(iCurrentX, iY);
				m_pCharTable[30]->Scale(fSizeX,fSizeY);
				m_pCharTable[30]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '4':
				m_pCharTable[31]->Position(iCurrentX, iY);
				m_pCharTable[31]->Scale(fSizeX,fSizeY);
				m_pCharTable[31]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '5':
				m_pCharTable[32]->Position(iCurrentX, iY);
				m_pCharTable[32]->Scale(fSizeX,fSizeY);
				m_pCharTable[32]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '6':
				m_pCharTable[33]->Position(iCurrentX, iY);
				m_pCharTable[33]->Scale(fSizeX,fSizeY);
				m_pCharTable[33]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '7':
				m_pCharTable[34]->Position(iCurrentX, iY);
				m_pCharTable[34]->Scale(fSizeX,fSizeY);
				m_pCharTable[34]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '8':
				m_pCharTable[35]->Position(iCurrentX, iY);
				m_pCharTable[35]->Scale(fSizeX,fSizeY);
				m_pCharTable[35]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '9':
				m_pCharTable[36]->Position(iCurrentX, iY);
				m_pCharTable[36]->Scale(fSizeX,fSizeY);
				m_pCharTable[36]->Render();
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(400 * fSizeX); 
			break;		
		}
	}
}

int CSpriteFont::iSize(float fSizeX, char cText[])	// zwraca ile szerokoœci bêdzie zajmowaæ dany napis
{
	int iCurrentX;
	char cLetter;

	iCurrentX = 0; 

	for (int i=0; i<strlen(cText); i++)
	{
		cLetter = toupper(cText[i]);

		switch (cLetter)
		{

			case 'A':
				iCurrentX += (int)(400 * fSizeX);  
			break;
			
			case 'B':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'C':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'D':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'E':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'F':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'G':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'H':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'I':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'J':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'K':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'L':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'M':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'N':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'O':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'P':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Q':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'R':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'S':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'T':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'U':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'V':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'W':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'X':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Y':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case 'Z':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '.':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '0':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '1':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '2':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '3':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '4':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '5':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '6':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '7':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '8':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case '9':
				iCurrentX += (int)(400 * fSizeX); 
			break;

			case ' ':
				iCurrentX += (int)(400 * fSizeX); 
			break;		
		}
	}

	return iCurrentX;
}