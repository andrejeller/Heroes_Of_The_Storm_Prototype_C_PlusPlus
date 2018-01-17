#pragma once
#include "ofMain.h"
#include "ofVec2f.h"

class WayPoint {

private:
	ofVec2f m_pos;
	bool m_status;

public:

	WayPoint();
	WayPoint(int x, int y);
			
	void draw(ofVec2f xy);
	void TrocaStatus();

	ofVec2f GetPos();
	bool GetStatus();

	void SetPos(int x, int y);
	void SetStatus(bool status);	
};
