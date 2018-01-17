#pragma once
#include "ofMain.h"
#include "ofVec2f.h"
//#include "Muradin.h"
#include <vector>
#include "WayPoint.h"
#include <time.h>


class Inimigo {
private: 
	ofVec2f m_pos, m_newPos;
	int m_wayPoint, m_velocidade, m_tempo;
	bool m_seguirPlayer, m_status, m_mover, m_congela;
	

public:
	Inimigo();
	Inimigo(int x, int y);

	void update(vector<WayPoint>* caminho, ofVec2f xy, int size);
	//void update(Muradin* a);
	void draw(ofVec2f xy);
	void Mover(int v);

	bool VerificarDist(ofVec2f xy, int distPermit);

	int GetWayPoint();
	int GetTempo();
	bool GetStatus();
	bool GetSeguir();
	bool GetMover();
	bool GetCongelar();
	ofVec2f GetPos();
	ofVec2f GetNewPos();
	
	void SetPos(ofVec2f xy);
	void SetPos(int x, int y);
	void SetNewPos(ofVec2f xy);
	void SetWayPoint(int numero);
	
	void SetSeguir(bool sim);
	void SetStatus(bool status);
	void SetMover(bool status);
	void SetCongelar(bool status);
	void SetTempo(int tempo);
	
};
