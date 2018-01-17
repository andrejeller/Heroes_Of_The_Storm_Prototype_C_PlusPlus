#pragma once
#include "ofMain.h"
#include "ofVec2f.h"

class Tiro {
private: 
	ofVec2f m_pos, m_novaPos;
	bool m_status;
	int m_tamanho = 3, m_dano;
	
public:
	Tiro();
	Tiro(ofVec2f posicao);
			
	void setup(int dano);
	void update(ofVec2f xy);
	void draw(ofVec2f xy);
	void disparar(ofVec2f xy);
	void verificarColisao(ofVec2f xy);
	
	ofVec2f GetPos();
	ofVec2f GetNovaPos();
	bool Stop(ofVec2f xy);
	bool GetStatus();
	
	void SetPos(ofVec2f xy);
	void SetPos(int x, int y);
	void SetNovaPos(ofVec2f xy);
	void SetNovaPos(int x, int y);
	void SetDano(int d);
	void SetTamanho(int s);
	void SetStatus(bool status);

};
