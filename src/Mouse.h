#pragma once
#include "ofMain.h"
#include "ofVec2f.h"

class Mouse {

private:
	ofVec2f m_pos, m_click;
	
public:

	Mouse();
		
	void draw(ofVec2f xy);
	
	ofVec2f GetPos();
	ofVec2f GetPosClicada();

	void SetPos(int x, int y);
	void SetPosClick(int x, int y);
	
};
