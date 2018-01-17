#pragma once
#include "ofMain.h"
#include "ofVec2f.h"
#include "Inimigo.h"

class Martelo {

private:
	ofVec2f  m_pos, m_novaPos, m_posPlayer;	
	bool m_status;
	int m_tamanho = 10;

public:

	Martelo();
	
	void draw(ofVec2f xy);
	void update(ofVec2f xy, vector<Inimigo>* inis);
	
	void Mover(ofVec2f vou, int velocidade);
	bool Stop(ofVec2f xy);

	//// ----- Geters
	ofVec2f GetPos();
	ofVec2f GetNovaPos();
	ofVec2f GetPlayerPos();
	bool GetStatus();
	

	//// ---- Set	
	void SetPos(int x, int y);
	void SetPos(ofVec2f xy);
	void SetNovaPos(ofVec2f xy);
	void SetPlayerPos(ofVec2f xy);
	void SetStatus(bool status);


};
