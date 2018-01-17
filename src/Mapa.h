#pragma once
#include "ofMain.h"
#include "ofVec2f.h"

class Mapa {

private:
	ofImage m_mapa;
	ofVec2f m_pos;
	
public:

	Mapa(string mapaPNG);
		
	void draw(ofVec2f xy);
	void update(ofVec2f cam);
	
	ofVec2f GetPos();
	
	void SetPos(int x, int y);
	void SetPos(ofVec2f xy);
};
