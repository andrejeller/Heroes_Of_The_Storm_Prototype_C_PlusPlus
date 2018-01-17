#pragma once
#include "ofMain.h"
#include "ofVec2f.h"
#include "Martelo.h"
#include "Inimigo.h"
#include "Tiro.h"
#include <vector>

class Muradin {

private:
	ofVec2f m_pos, m_novaPos, m_posAtaque;

	int m_dano, m_velocidade;
	int m_size, m_zoom, m_tempoBoom, m_raioBoom, m_tempoTiro;
	bool m_ataqueQ, m_ataqueW, m_ataqueE, m_ataqueR;
	bool m_pular, m_mover, m_click, m_boom;
	
	vector<Tiro> tiros; /// para materia de matematica
	Martelo mart;
	int m_vida;
public:
	
	
	Muradin();
	Muradin(int x, int y);

	void draw(ofVec2f camera, ofVec2f mouse);
	void update(ofVec2f mouse, vector<Inimigo>* inis);
	void update(ofVec2f mouse);
		
	void AtackQ(ofVec2f xy);
	void AtackW(ofVec2f xy);
	void AtackE();
	void AtackR();
	void Mover(int v);
	void Regenera();
	
	void Pular();
	void Cair();
	void Boom(ofVec2f xy);
	bool PermicaoClick(ofVec2f xy, int dist);
	bool VerificaPos(ofVec2f xy, int distPermit);
	void Colisao(int x, int y, int w, int h);		
	
	int GetDano();
	int GetVida();
	int GetTempoTiro();

	bool GetBoom();
	bool GetClick();
	bool GetPular();
	bool GetAtaqueQ();
	bool GetAtaqueW();
	bool GetAtaqueE();
	bool GetAtaqueR();
	
	ofVec2f GetPos();
	ofVec2f GetNovaPos();
	ofVec2f GetAtackPosXY();

	void SetDano(int d);
	void SetPos(ofVec2f xy);
	void SetVida(int v);//
	void SetNovaPos(ofVec2f xy);
	void SetVelocidade(int velocidade);

	void SetBoom(bool b);
	void SetClick(bool c);
	void SetPular(bool j);
	void SetMover(bool m);
	void SetAtaqueQ(bool q);
	void SetAtaqueW(bool w);
	void SetAtaqueE(bool e);
	void SetAtaqueR(bool r);
	void SetTiroTempo(int tempo);

	void SetPos(int x, int y);
	void SetNovaPos(int x, int y);
	void SetAtackPos(int x, int y);
		
};
