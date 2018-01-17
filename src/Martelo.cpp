#include "Martelo.h"

Martelo::Martelo()
{
	SetStatus(false);
}

void Martelo::draw(ofVec2f xy)
{
	if (GetStatus()) {
		ofVec2f posicao = GetPos() - xy;
		ofSetColor(255, 255, 0);
		ofDrawRectangle(posicao, m_tamanho, m_tamanho);
	}
}

void Martelo::update(ofVec2f xy, vector<Inimigo>* inis)
{
	if (!GetStatus()) SetPos(xy); 
	if (GetStatus()){		
		for (int i = 0; i < inis->size(); i++) {
			ofVec2f raioPermit = (inis->at(i).GetPos() - GetPos());
			float dist = raioPermit.length();
			if (dist <= 30) {
				inis->at(i).SetCongelar(true);
			}
		}
	}
}


void Martelo::Mover(ofVec2f vou, int velocidade)
{
	SetNovaPos(vou);
	SetPos(GetPos() - ((GetPos() - vou).normalize() * velocidade));
}

bool Martelo::Stop(ofVec2f xy) {

	ofVec2f raioPermit = (xy - GetNovaPos());
	float dist = raioPermit.length();
	if (dist <= 10) {
		return true;
	}
	return false;
}

ofVec2f Martelo::GetPos()
{
	return m_pos;
}

ofVec2f Martelo::GetNovaPos()
{
	return m_novaPos;
}

ofVec2f Martelo::GetPlayerPos()
{
	return m_posPlayer;
}

bool Martelo::GetStatus()
{
	return m_status;
}

void Martelo::SetPos(int x, int y)
{
	m_pos.set(x, y);
}

void Martelo::SetPos(ofVec2f xy)
{
	m_pos.set(xy);
}

void Martelo::SetNovaPos(ofVec2f xy)
{
	m_novaPos.set(xy);
}

void Martelo::SetPlayerPos(ofVec2f xy)
{
	m_posPlayer.set(xy);
}

void Martelo::SetStatus(bool status)
{
	m_status = status;
}
