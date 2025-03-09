#include "MobileKeyboard.h"

CMobileKeyboard::CMobileKeyboard() : _cState(0)
{
	_cLanguage = LANG_ENGLAND;

	_pKeyboardBackground = NULL;

	_pKey1 = _pKey2 = _pKey3 = _pKey4 = _pKey5 = _pKey6 = _pKey7 = _pKey8 = _pKey9 = _pKey0 = NULL;

	_pKeyA = _pKeyB = _pKeyC = _pKeyD = _pKeyE = _pKeyF = _pKeyG = _pKeyH = _pKeyI = _pKeyJ = NULL;
	_pKeyK = _pKeyL = _pKeyM = _pKeyN = _pKeyO = _pKeyP = _pKeyQ = _pKeyR = _pKeyS = _pKeyT = NULL;
	_pKeyU = _pKeyV = _pKeyW = _pKeyX = _pKeyY = _pKeyZ = NULL;

	_pKeySPACE = NULL;
	_pKeyDELETE = NULL;
	_pKeyENTER = NULL;
}

CMobileKeyboard::CMobileKeyboard(char cLanguage): _cState(0)
{
	_cLanguage = cLanguage;

	_pKeyboardBackground = NULL;

	_pKey1 = _pKey2 = _pKey3 = _pKey4 = _pKey5 = _pKey6 = _pKey7 = _pKey8 = _pKey9 = _pKey0 = NULL;

	_pKeyA = _pKeyB = _pKeyC = _pKeyD = _pKeyE = _pKeyF = _pKeyG = _pKeyH = _pKeyI = _pKeyJ = NULL;
	_pKeyK = _pKeyL = _pKeyM = _pKeyN = _pKeyO = _pKeyP = _pKeyQ = _pKeyR = _pKeyS = _pKeyT = NULL;
	_pKeyU = _pKeyV = _pKeyW = _pKeyX = _pKeyY = _pKeyZ = NULL;

	_pKeySPACE = NULL;
	_pKeyDELETE = NULL;
	_pKeyENTER = NULL;

}

CMobileKeyboard::~CMobileKeyboard()
{
	_cState = 0;
	Close();
}


void CMobileKeyboard::Open(CScreen *pScreen)
{
	_cState = 0;

    if (pScreen->_isHDS)
    {
        _pKey0 = new CButton((char*)"en_key_00.png",(char*)"en_key_02.png",(char*)"en_key_01.png",0,0,64,64);
        _pKey1 = new CButton((char*)"en_key_10.png",(char*)"en_key_12.png",(char*)"en_key_11.png",0,0,64,64);
        _pKey2 = new CButton((char*)"en_key_20.png",(char*)"en_key_22.png",(char*)"en_key_21.png",0,0,64,64);
        _pKey3 = new CButton((char*)"en_key_30.png",(char*)"en_key_32.png",(char*)"en_key_31.png",0,0,64,64);
        _pKey4 = new CButton((char*)"en_key_40.png",(char*)"en_key_42.png",(char*)"en_key_41.png",0,0,64,64);
        _pKey5 = new CButton((char*)"en_key_50.png",(char*)"en_key_52.png",(char*)"en_key_51.png",0,0,64,64);
        _pKey6 = new CButton((char*)"en_key_60.png",(char*)"en_key_62.png",(char*)"en_key_61.png",0,0,64,64);
        _pKey7 = new CButton((char*)"en_key_70.png",(char*)"en_key_72.png",(char*)"en_key_71.png",0,0,64,64);
        _pKey8 = new CButton((char*)"en_key_80.png",(char*)"en_key_82.png",(char*)"en_key_81.png",0,0,64,64);
        _pKey9 = new CButton((char*)"en_key_90.png",(char*)"en_key_92.png",(char*)"en_key_91.png",0,0,64,64);

        _pKeyA = new CButton((char*)"en_key_a0.png",(char*)"en_key_a2.png",(char*)"en_key_a1.png",0,0,64,64);
        _pKeyB = new CButton((char*)"en_key_b0.png",(char*)"en_key_b2.png",(char*)"en_key_b1.png",0,0,64,64);
        _pKeyC = new CButton((char*)"en_key_c0.png",(char*)"en_key_c2.png",(char*)"en_key_c1.png",0,0,64,64);
        _pKeyD = new CButton((char*)"en_key_d0.png",(char*)"en_key_d2.png",(char*)"en_key_d1.png",0,0,64,64);
        _pKeyE = new CButton((char*)"en_key_e0.png",(char*)"en_key_e2.png",(char*)"en_key_e1.png",0,0,64,64);
        _pKeyF = new CButton((char*)"en_key_f0.png",(char*)"en_key_f2.png",(char*)"en_key_f1.png",0,0,64,64);
        _pKeyG = new CButton((char*)"en_key_g0.png",(char*)"en_key_g2.png",(char*)"en_key_g1.png",0,0,64,64);
        _pKeyH = new CButton((char*)"en_key_h0.png",(char*)"en_key_h2.png",(char*)"en_key_h1.png",0,0,64,64);
        _pKeyI = new CButton((char*)"en_key_i0.png",(char*)"en_key_i2.png",(char*)"en_key_i1.png",0,0,64,64);
        _pKeyJ = new CButton((char*)"en_key_j0.png",(char*)"en_key_j2.png",(char*)"en_key_j1.png",0,0,64,64);
        
        _pKeyK = new CButton((char*)"en_key_k0.png",(char*)"en_key_k2.png",(char*)"en_key_k1.png",0,0,64,64);
        _pKeyL = new CButton((char*)"en_key_l0.png",(char*)"en_key_l2.png",(char*)"en_key_l1.png",0,0,64,64);
        _pKeyM = new CButton((char*)"en_key_m0.png",(char*)"en_key_m2.png",(char*)"en_key_m1.png",0,0,64,64);
        _pKeyN = new CButton((char*)"en_key_n0.png",(char*)"en_key_n2.png",(char*)"en_key_n1.png",0,0,64,64);
        _pKeyO = new CButton((char*)"en_key_o0.png",(char*)"en_key_o2.png",(char*)"en_key_o1.png",0,0,64,64);
        _pKeyP = new CButton((char*)"en_key_p0.png",(char*)"en_key_p2.png",(char*)"en_key_p1.png",0,0,64,64);
        _pKeyQ = new CButton((char*)"en_key_q0.png",(char*)"en_key_q2.png",(char*)"en_key_q1.png",0,0,64,64);
        _pKeyR = new CButton((char*)"en_key_r0.png",(char*)"en_key_r2.png",(char*)"en_key_r1.png",0,0,64,64);
        _pKeyS = new CButton((char*)"en_key_s0.png",(char*)"en_key_s2.png",(char*)"en_key_s1.png",0,0,64,64);
        _pKeyT = new CButton((char*)"en_key_t0.png",(char*)"en_key_t2.png",(char*)"en_key_t1.png",0,0,64,64);

        _pKeyU = new CButton((char*)"en_key_u0.png",(char*)"en_key_u2.png",(char*)"en_key_u1.png",0,0,64,64);
        _pKeyV = new CButton((char*)"en_key_v0.png",(char*)"en_key_v2.png",(char*)"en_key_v1.png",0,0,64,64);
        _pKeyW = new CButton((char*)"en_key_w0.png",(char*)"en_key_w2.png",(char*)"en_key_w1.png",0,0,64,64);
        _pKeyX = new CButton((char*)"en_key_x0.png",(char*)"en_key_x2.png",(char*)"en_key_x1.png",0,0,64,64);
        _pKeyY = new CButton((char*)"en_key_y0.png",(char*)"en_key_y2.png",(char*)"en_key_y1.png",0,0,64,64);
        _pKeyZ = new CButton((char*)"en_key_z0.png",(char*)"en_key_z2.png",(char*)"en_key_z1.png",0,0,64,64);

        _pKeySPACE = new CButton((char*)"en_key_space0.png",(char*)"en_key_space2.png",(char*)"en_key_space1.png",0,0,64,64);
        _pKeyDELETE = new CButton((char*)"en_key_delete0.png",(char*)"en_key_delete2.png",(char*)"en_key_delete1.png",0,0,64,64);
        _pKeyENTER = new CButton((char*)"en_key_enter0.png",(char*)"en_key_enter2.png",(char*)"en_key_enter1.png",0,0,64,64);
    }
    else
    {
        _pKey0 = new CButton((char*)"en_key128_00.png",(char*)"en_key128_02.png",(char*)"en_key128_01.png",0,0,128,128);
        _pKey1 = new CButton((char*)"en_key128_10.png",(char*)"en_key128_12.png",(char*)"en_key128_11.png",0,0,128,128);
        _pKey2 = new CButton((char*)"en_key128_20.png",(char*)"en_key128_22.png",(char*)"en_key128_21.png",0,0,128,128);
        _pKey3 = new CButton((char*)"en_key128_30.png",(char*)"en_key128_32.png",(char*)"en_key128_31.png",0,0,128,128);
        _pKey4 = new CButton((char*)"en_key128_40.png",(char*)"en_key128_42.png",(char*)"en_key128_41.png",0,0,128,128);
        _pKey5 = new CButton((char*)"en_key128_50.png",(char*)"en_key128_52.png",(char*)"en_key128_51.png",0,0,128,128);
        _pKey6 = new CButton((char*)"en_key128_60.png",(char*)"en_key128_62.png",(char*)"en_key128_61.png",0,0,128,128);
        _pKey7 = new CButton((char*)"en_key128_70.png",(char*)"en_key128_72.png",(char*)"en_key128_71.png",0,0,128,128);
        _pKey8 = new CButton((char*)"en_key128_80.png",(char*)"en_key128_82.png",(char*)"en_key128_81.png",0,0,128,128);
        _pKey9 = new CButton((char*)"en_key128_90.png",(char*)"en_key128_92.png",(char*)"en_key128_91.png",0,0,128,128);
    
        _pKeyA = new CButton((char*)"en_key128_a0.png",(char*)"en_key128_a2.png",(char*)"en_key128_a1.png",0,0,128,128);
        _pKeyB = new CButton((char*)"en_key128_b0.png",(char*)"en_key128_b2.png",(char*)"en_key128_b1.png",0,0,128,128);
        _pKeyC = new CButton((char*)"en_key128_c0.png",(char*)"en_key128_c2.png",(char*)"en_key128_c1.png",0,0,128,128);
        _pKeyD = new CButton((char*)"en_key128_d0.png",(char*)"en_key128_d2.png",(char*)"en_key128_d1.png",0,0,128,128);
        _pKeyE = new CButton((char*)"en_key128_e0.png",(char*)"en_key128_e2.png",(char*)"en_key128_e1.png",0,0,128,128);
        _pKeyF = new CButton((char*)"en_key128_f0.png",(char*)"en_key128_f2.png",(char*)"en_key128_f1.png",0,0,128,128);
        _pKeyG = new CButton((char*)"en_key128_g0.png",(char*)"en_key128_g2.png",(char*)"en_key128_g1.png",0,0,128,128);
        _pKeyH = new CButton((char*)"en_key128_h0.png",(char*)"en_key128_h2.png",(char*)"en_key128_h1.png",0,0,128,128);
        _pKeyI = new CButton((char*)"en_key128_i0.png",(char*)"en_key128_i2.png",(char*)"en_key128_i1.png",0,0,128,128);
        _pKeyJ = new CButton((char*)"en_key128_j0.png",(char*)"en_key128_j2.png",(char*)"en_key128_j1.png",0,0,128,128);
    
        _pKeyK = new CButton((char*)"en_key128_k0.png",(char*)"en_key128_k2.png",(char*)"en_key128_k1.png",0,0,128,128);
        _pKeyL = new CButton((char*)"en_key128_l0.png",(char*)"en_key128_l2.png",(char*)"en_key128_l1.png",0,0,128,128);
        _pKeyM = new CButton((char*)"en_key128_m0.png",(char*)"en_key128_m2.png",(char*)"en_key128_m1.png",0,0,128,128);
        _pKeyN = new CButton((char*)"en_key128_n0.png",(char*)"en_key128_n2.png",(char*)"en_key128_n1.png",0,0,128,128);
        _pKeyO = new CButton((char*)"en_key128_o0.png",(char*)"en_key128_o2.png",(char*)"en_key128_o1.png",0,0,128,128);
        _pKeyP = new CButton((char*)"en_key128_p0.png",(char*)"en_key128_p2.png",(char*)"en_key128_p1.png",0,0,128,128);
        _pKeyQ = new CButton((char*)"en_key128_q0.png",(char*)"en_key128_q2.png",(char*)"en_key128_q1.png",0,0,128,128);
        _pKeyR = new CButton((char*)"en_key128_r0.png",(char*)"en_key128_r2.png",(char*)"en_key128_r1.png",0,0,128,128);
        _pKeyS = new CButton((char*)"en_key128_s0.png",(char*)"en_key128_s2.png",(char*)"en_key128_s1.png",0,0,128,128);
        _pKeyT = new CButton((char*)"en_key128_t0.png",(char*)"en_key128_t2.png",(char*)"en_key128_t1.png",0,0,128,128);
    
        _pKeyU = new CButton((char*)"en_key128_u0.png",(char*)"en_key128_u2.png",(char*)"en_key128_u1.png",0,0,128,128);
        _pKeyV = new CButton((char*)"en_key128_v0.png",(char*)"en_key128_v2.png",(char*)"en_key128_v1.png",0,0,128,128);
        _pKeyW = new CButton((char*)"en_key128_w0.png",(char*)"en_key128_w2.png",(char*)"en_key128_w1.png",0,0,128,128);
        _pKeyX = new CButton((char*)"en_key128_x0.png",(char*)"en_key128_x2.png",(char*)"en_key128_x1.png",0,0,128,128);
        _pKeyY = new CButton((char*)"en_key128_y0.png",(char*)"en_key128_y2.png",(char*)"en_key128_y1.png",0,0,128,128);
        _pKeyZ = new CButton((char*)"en_key128_z0.png",(char*)"en_key128_z2.png",(char*)"en_key128_z1.png",0,0,128,128);
        
        _pKeySPACE = new CButton((char*)"en_key128_space0.png",(char*)"en_key128_space2.png",(char*)"en_key128_space1.png",0,0,128,128);
        _pKeyDELETE = new CButton((char*)"en_key128_delete0.png",(char*)"en_key128_delete2.png",(char*)"en_key128_delete1.png",0,0,128,128);
        _pKeyENTER = new CButton((char*)"en_key128_enter0.png",(char*)"en_key128_enter2.png",(char*)"en_key128_enter1.png",0,0,128,128);
        
    }
    _pScreen = pScreen;
	_isActive = true ;

}

void CMobileKeyboard::Close()
{
//	SafeDelete(_pKeyboardBackground);

	SafeDelete(_pKey1); SafeDelete(_pKey2); SafeDelete(_pKey3);
	SafeDelete(_pKey4); SafeDelete(_pKey5); SafeDelete(_pKey6);
	SafeDelete(_pKey7); SafeDelete(_pKey8); SafeDelete(_pKey9);
	SafeDelete(_pKey0);

	SafeDelete(_pKeyA);	SafeDelete(_pKeyB);	SafeDelete(_pKeyC);
	SafeDelete(_pKeyD);	SafeDelete(_pKeyE);	SafeDelete(_pKeyF);
	SafeDelete(_pKeyG);	SafeDelete(_pKeyH);	SafeDelete(_pKeyI);
	SafeDelete(_pKeyJ);	SafeDelete(_pKeyK);	SafeDelete(_pKeyL);
	SafeDelete(_pKeyM);	SafeDelete(_pKeyN);	SafeDelete(_pKeyO);
	SafeDelete(_pKeyP);	SafeDelete(_pKeyQ);	SafeDelete(_pKeyR);
	SafeDelete(_pKeyS);	SafeDelete(_pKeyT);	SafeDelete(_pKeyU);
	SafeDelete(_pKeyV);	SafeDelete(_pKeyW);	SafeDelete(_pKeyX);
	SafeDelete(_pKeyY);	SafeDelete(_pKeyZ);	

	SafeDelete(_pKeySPACE);
	SafeDelete(_pKeyDELETE);
	SafeDelete(_pKeyENTER);

	_isActive = false;
}

unsigned char CMobileKeyboard::cRender(CTouch *pTouch,unsigned long ulTimer)
{
	int y1,y2, x1, iStepX, iSize;
	unsigned char cKey;

	cKey = KEY_NONE;

	// pierwszy rzad

    if (_pScreen->_isHDS)
    {
		iSize = 128;
		y1 = 700; y2 = 700 + iSize;
		x1 = 64; iStepX = 128+64;
    }
    else if (_pScreen->_isSDS)
    {
		iSize = 64;
		y1 = 384; y2 = 384 + iSize;
		x1 = 32; iStepX = 96;
    }
    else if (_pScreen->_isSDS)
    {
		iSize = 64;
		y1 = 250; y2 = 250 + iSize;
		x1 = 64; iStepX = 80;
    }
    else if (_pScreen->_isSDW)
    {
		iSize = 64;
		y1 = 250; y2 = 250 + iSize;
		x1 = 96; iStepX = 96;
    }

	_pKey1->Position(x1 + (iStepX * 0), y1);	_pKey1->SetHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKey1->Render(pTouch) == ON_LEFT) cKey = KEY_1;
	_pKey2->Position(x1 + (iStepX * 1), y1); _pKey2->SetHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKey2->Render(pTouch) == ON_LEFT) cKey = KEY_2;
	_pKey3->Position(x1 + (iStepX * 2), y1); _pKey3->SetHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKey3->Render(pTouch) == ON_LEFT) cKey = KEY_3;
	_pKey4->Position(x1 + (iStepX * 3), y1); _pKey4->SetHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKey4->Render(pTouch) == ON_LEFT) cKey = KEY_4;
	_pKey5->Position(x1 + (iStepX * 4), y1); _pKey5->SetHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKey5->Render(pTouch) == ON_LEFT) cKey = KEY_5;
	_pKey6->Position(x1 + (iStepX * 5), y1); _pKey6->SetHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKey6->Render(pTouch) == ON_LEFT) cKey = KEY_6;
	_pKey7->Position(x1 + (iStepX * 6), y1); _pKey7->SetHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKey7->Render(pTouch) == ON_LEFT) cKey = KEY_7;
	_pKey8->Position(x1 + (iStepX * 7), y1); _pKey8->SetHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKey8->Render(pTouch) == ON_LEFT) cKey = KEY_8;
	_pKey9->Position(x1 + (iStepX * 8), y1); _pKey9->SetHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKey9->Render(pTouch) == ON_LEFT) cKey = KEY_9;
	_pKey0->Position(x1 + (iStepX * 9), y1); _pKey0->SetHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKey0->Render(pTouch) == ON_LEFT) cKey = KEY_0;
	
	// drugi rzad

    if (_pScreen->_isHDS)
    {
		iSize = 128;
		y1 = 700 + iSize + 32;
		y2 = 700 + iSize + iSize + 32;
        
    }
    else if (_pScreen->_isSDS)
    {
		iSize = 64;
		y1 = 384 + iSize + 32;
		y2 = 384 + iSize + iSize + 32;
    }
    else
    {
		iSize = 64;
		y1 = 250 + iSize + 32;
		y2 = 250 + iSize + iSize + 32;
    }
    
	_pKeyQ->Position(x1 + (iStepX * 0), y1); _pKeyQ->SetHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKeyQ->Render(pTouch) == ON_LEFT) cKey = KEY_Q;
	_pKeyW->Position(x1 + (iStepX * 1), y1); _pKeyW->SetHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyW->Render(pTouch) == ON_LEFT) cKey = KEY_W;
	_pKeyE->Position(x1 + (iStepX * 2), y1); _pKeyE->SetHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyE->Render(pTouch) == ON_LEFT) cKey = KEY_E;
	_pKeyR->Position(x1 + (iStepX * 3), y1); _pKeyR->SetHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyR->Render(pTouch) == ON_LEFT) cKey = KEY_R;
	_pKeyT->Position(x1 + (iStepX * 4), y1); _pKeyT->SetHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyT->Render(pTouch) == ON_LEFT) cKey = KEY_T;
	_pKeyY->Position(x1 + (iStepX * 5), y1); _pKeyY->SetHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyY->Render(pTouch) == ON_LEFT) cKey = KEY_Y;
	_pKeyU->Position(x1 + (iStepX * 6), y1); _pKeyU->SetHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyU->Render(pTouch) == ON_LEFT) cKey = KEY_U;
	_pKeyI->Position(x1 + (iStepX * 7), y1); _pKeyI->SetHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyI->Render(pTouch) == ON_LEFT) cKey = KEY_I;
	_pKeyO->Position(x1 + (iStepX * 8), y1); _pKeyO->SetHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyO->Render(pTouch) == ON_LEFT) cKey = KEY_O;
	_pKeyP->Position(x1 + (iStepX * 9), y1); _pKeyP->SetHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKeyP->Render(pTouch) == ON_LEFT) cKey = KEY_P;

	// trzeci rzad 
    
    if (_pScreen->_isHDS)
    {
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32;
        
    }
    else if (_pScreen->_isSDS)
    {
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32;
    }
    else
    {
		iSize = 64;
		y1 = 250 + iSize + 32 + iSize + 32;
		y2 = 250 + iSize + iSize + 32 + iSize + 32;
    }

	_pKeyA->Position(x1 + (iStepX * 0), y1); _pKeyA->SetHotCoords(x1 + (iStepX * 0), y1, x1 + (iStepX * 0) + iSize, y2); if (_pKeyA->Render(pTouch) == ON_LEFT) cKey = KEY_A;
	_pKeyS->Position(x1 + (iStepX * 1), y1); _pKeyS->SetHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyS->Render(pTouch) == ON_LEFT) cKey = KEY_S;
	_pKeyD->Position(x1 + (iStepX * 2), y1); _pKeyD->SetHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyD->Render(pTouch) == ON_LEFT) cKey = KEY_D;
	_pKeyF->Position(x1 + (iStepX * 3), y1); _pKeyF->SetHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyF->Render(pTouch) == ON_LEFT) cKey = KEY_F;
	_pKeyG->Position(x1 + (iStepX * 4), y1); _pKeyG->SetHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyG->Render(pTouch) == ON_LEFT) cKey = KEY_G;
	_pKeyH->Position(x1 + (iStepX * 5), y1); _pKeyH->SetHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyH->Render(pTouch) == ON_LEFT) cKey = KEY_H;
	_pKeyJ->Position(x1 + (iStepX * 6), y1); _pKeyJ->SetHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyJ->Render(pTouch) == ON_LEFT) cKey = KEY_J;
	_pKeyK->Position(x1 + (iStepX * 7), y1); _pKeyK->SetHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyK->Render(pTouch) == ON_LEFT) cKey = KEY_K;
	_pKeyL->Position(x1 + (iStepX * 8), y1); _pKeyL->SetHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyL->Render(pTouch) == ON_LEFT) cKey = KEY_L;
	_pKeyENTER->Position(x1 + (iStepX * 9), y1); _pKeyENTER->SetHotCoords(x1 + (iStepX * 9), y1, x1 + (iStepX * 9) + iSize, y2); if (_pKeyENTER->Render(pTouch) == ON_LEFT) cKey = KEY_ENTER;

	// czwarty rzad

    if (_pScreen->_isHDS)
    {
		iSize = 128;
		y1 = 700 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 700 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
    }
    else if (_pScreen->_isSDS)
    {
		iSize = 64;
		y1 = 384 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 384 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
    }
    else
    {
		iSize = 64;
		y1 = 250 + iSize + 32 + iSize + 32 + iSize + 32;
		y2 = 250 + iSize + iSize + 32 + iSize + 32 + iSize + 32;
    }

	_pKeyZ->Position(x1 + (iStepX * 1), y1); _pKeyZ->SetHotCoords(x1 + (iStepX * 1), y1, x1 + (iStepX * 1) + iSize, y2); if (_pKeyZ->Render(pTouch) == ON_LEFT) cKey = KEY_Z;
	_pKeyX->Position(x1 + (iStepX * 2), y1); _pKeyX->SetHotCoords(x1 + (iStepX * 2), y1, x1 + (iStepX * 2) + iSize, y2); if (_pKeyX->Render(pTouch) == ON_LEFT) cKey = KEY_X;
	_pKeyC->Position(x1 + (iStepX * 3), y1); _pKeyC->SetHotCoords(x1 + (iStepX * 3), y1, x1 + (iStepX * 3) + iSize, y2); if (_pKeyC->Render(pTouch) == ON_LEFT) cKey = KEY_C;
	_pKeyV->Position(x1 + (iStepX * 4), y1); _pKeyV->SetHotCoords(x1 + (iStepX * 4), y1, x1 + (iStepX * 4) + iSize, y2); if (_pKeyV->Render(pTouch) == ON_LEFT) cKey = KEY_V;
	_pKeyB->Position(x1 + (iStepX * 5), y1); _pKeyB->SetHotCoords(x1 + (iStepX * 5), y1, x1 + (iStepX * 5) + iSize, y2); if (_pKeyB->Render(pTouch) == ON_LEFT) cKey = KEY_B;
	_pKeyN->Position(x1 + (iStepX * 6), y1); _pKeyN->SetHotCoords(x1 + (iStepX * 6), y1, x1 + (iStepX * 6) + iSize, y2); if (_pKeyN->Render(pTouch) == ON_LEFT) cKey = KEY_N;
	_pKeyM->Position(x1 + (iStepX * 7), y1); _pKeyM->SetHotCoords(x1 + (iStepX * 7), y1, x1 + (iStepX * 7) + iSize, y2); if (_pKeyM->Render(pTouch) == ON_LEFT) cKey = KEY_M;
	_pKeyDELETE->Position(x1 + (iStepX * 8), y1); _pKeyDELETE->SetHotCoords(x1 + (iStepX * 8), y1, x1 + (iStepX * 8) + iSize, y2); if (_pKeyDELETE->Render(pTouch) == ON_LEFT) cKey = KEY_DELETE;

	return cKey;
}
