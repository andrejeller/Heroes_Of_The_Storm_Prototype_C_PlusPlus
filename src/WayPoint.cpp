#include "WayPoint.h"

WayPoint::WayPoint()
{
}

WayPoint::WayPoint(int x, int y)
{
	SetPos(x, y);
	SetStatus(true);
}

void WayPoint::draw(ofVec2f xy)
{
	ofVec2f posicao = GetPos() - xy;
	if (GetStatus()) {
		ofSetColor(100, 100, 255);
		ofDrawCircle(posicao, 6);	
	}
}

void WayPoint::SetPos(int x, int y)
{
	m_pos.set(x, y);
}

void WayPoint::SetStatus(bool status)
{
	m_status = status;
}

void WayPoint::TrocaStatus()
{
	if (GetStatus()) SetStatus(false);
	if (!GetStatus()) SetStatus(true);
}

ofVec2f WayPoint::GetPos()
{
	return m_pos;
}

bool WayPoint::GetStatus()
{
	return m_status;
}
