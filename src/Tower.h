#pragma once
#include "ofMain.h"
#include "Tiro.h"
#include "ofVec2f.h"

class Tower {
private: 
	ofVec2f m_pos;
	int m_vida, m_tamanho, m_numeroTiro, m_tempo;
	bool m_status;
	Tiro* tiro[20];

public:
	Tower(int x, int y, int size);
	~Tower();

	void update(ofVec2f xy);
	void draw(ofVec2f xy);

	bool verificarProximidade(ofVec2f xy);
	bool possoAtacar();
	void atacar(ofVec2f xy);

	int GetVida();
	int GetTamanho();
	int GetNumeroTiro();
	bool GetStatus();
	ofVec2f GetPos();
	
	void SetPos(ofVec2f xy);
	void SetPos(int x, int y);
	void SetNumeroTiro(int n);
	void SetVida(int l);	
	void SetTamanho(int s);
	void SetStatus(bool status);
	
};
