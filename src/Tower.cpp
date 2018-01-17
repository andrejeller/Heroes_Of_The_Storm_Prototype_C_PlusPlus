#include "Tower.h"

Tower::Tower(int x, int y, int size)
{
	SetPos(x, y);
	SetTamanho(size);
	SetStatus(true);
	SetNumeroTiro(0);
	for (int i = 0; i < 20; i++) {
		tiro[i] = new Tiro();
		tiro[i]->SetPos(x, y);
	}
}

Tower::~Tower()
{
}

void Tower::update(ofVec2f xy)
{
	if (GetStatus()) {
		if (verificarProximidade(xy) && possoAtacar()) {
			if (GetNumeroTiro() <= 20)
			{
				atacar(xy);
				SetNumeroTiro(GetNumeroTiro() + 1);
			}			
		}

		if (GetNumeroTiro() >= 20)
		{
			SetNumeroTiro(22);
		}

		for (int i = 0; i < 20; i++) {
			tiro[i]->update(xy);
		}
	}
}

void Tower::draw(ofVec2f xy)
{
	ofVec2f posicao = GetPos() - xy;

	ofSetColor(100, 150, 150);
	ofDrawRectangle(posicao - GetTamanho()/2, GetTamanho(), GetTamanho());
	
	if (GetStatus()) ofSetColor(0, 255, 0);
	if (!GetStatus()) ofSetColor(255, 0, 0);
	ofDrawCircle(posicao, GetTamanho()/4);
	
	for (int i = 0; i < 20; i++) { tiro[i]->draw(xy); }
}

bool Tower::verificarProximidade(ofVec2f xy) {
	ofVec2f raioPermit = (xy - GetPos());
	float dist = raioPermit.length();
	if (dist <= 100) {
		return true;
	}
	return false;
}

bool Tower::possoAtacar() {
	if (ofGetElapsedTimeMillis() - m_tempo >= 1000) {
		return true;
	}
	return false;
}

void Tower::atacar(ofVec2f xy) {
	tiro[m_numeroTiro]->disparar(xy);
	m_tempo = ofGetElapsedTimeMillis();
}

int Tower::GetVida()
{
	return m_vida;
}

int Tower::GetTamanho()
{
	return m_tamanho;
}

int Tower::GetNumeroTiro()
{
	return m_numeroTiro;
}

bool Tower::GetStatus()
{
	return m_status;
}

ofVec2f Tower::GetPos()
{
	return m_pos;
}

void Tower::SetPos(ofVec2f xy)
{
	m_pos = xy;
}

void Tower::SetPos(int x, int y)
{
	m_pos.set(x, y);
}

void Tower::SetNumeroTiro(int n)
{
	m_numeroTiro = n;
}

void Tower::SetVida(int l)
{
	m_vida = l;
}

void Tower::SetTamanho(int s)
{
	m_tamanho = s;
}

void Tower::SetStatus(bool status)
{
	m_status = status;
}
