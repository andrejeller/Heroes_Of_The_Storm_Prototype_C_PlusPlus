#include "Mouse.h"

Mouse::Mouse()
{
}

void Mouse::draw(ofVec2f xy)
{
	ofVec2f posicao = GetPos() - xy;
	ofSetColor(255, 0, 0);
	ofDrawCircle(posicao, 4);
}

void Mouse::SetPosClick(int x, int y)
{
	m_click.set(x,y);
}

ofVec2f Mouse::GetPos()
{
	return m_pos;
}

ofVec2f Mouse::GetPosClicada()
{
	return m_click;
}

void Mouse::SetPos(int x, int y)
{
	m_pos.set(x,y);
}
