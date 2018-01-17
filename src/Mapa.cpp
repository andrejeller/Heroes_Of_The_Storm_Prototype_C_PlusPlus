#include "Mapa.h"

Mapa::Mapa(string mapaImg)
{
	m_mapa.load(mapaImg);
}


void Mapa::draw(ofVec2f xy)
{
	ofVec2f posicao = GetPos() - xy;
	ofSetColor(255, 255, 255);
	m_mapa.draw(posicao, 2000, 1000);
}

void Mapa::update(ofVec2f cam)
{
	
}

ofVec2f Mapa::GetPos()
{
	return m_pos;
}

void Mapa::SetPos(int x, int y)
{
	m_pos.set(x,y);
}

void Mapa::SetPos(ofVec2f xy)
{
	m_pos = xy;
}