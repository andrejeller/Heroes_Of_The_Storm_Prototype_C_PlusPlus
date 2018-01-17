#include "Tiro.h"

Tiro::Tiro()
{
	SetStatus(false);
}

Tiro::Tiro(ofVec2f posicao)
{
	SetPos(posicao);
}

void Tiro::setup(int dano)
{
	SetTamanho(3);
	SetDano(dano);
}

void Tiro::update(ofVec2f xy)
{
	if (GetStatus()) {
		//verificarColisao(xy);
		if (Stop(GetPos())) {
			SetPos(GetPos() - ((GetPos() - GetNovaPos()).normalize() * 1));
		}
		else {
			SetStatus(false);
		}
		if (GetPos() == GetNovaPos()) {
			SetStatus(false);
		}
	}
}

void Tiro::draw(ofVec2f xy)
{
	ofVec2f posicao = GetPos() - xy;

	if (GetStatus()) {
		ofSetColor(255, 255, 255);
		ofDrawCircle(posicao, m_tamanho);
	}
}

void Tiro::disparar(ofVec2f xy) {
	SetNovaPos(xy);
	SetStatus(true);
}

void Tiro::verificarColisao(ofVec2f xy) {
	ofVec2f raioColisao = (GetPos() - xy);
	float dist = raioColisao.length();
	if (dist <= 5) {
		//Muradin::SetVida(Muradin::GetVida() - 1);
	}	
}

bool Tiro::Stop(ofVec2f xy) {

	ofVec2f raioPermit = (xy - GetNovaPos());
	float dist = raioPermit.length();
	if (dist >= 2) {
		return true;
	}
	return false;
}

ofVec2f Tiro::GetPos()
{
	return m_pos;
}

ofVec2f Tiro::GetNovaPos()
{
	return m_novaPos;
}

bool Tiro::GetStatus()
{
	return m_status;
}

void Tiro::SetPos(ofVec2f xy)
{
	m_pos = xy;
}

void Tiro::SetPos(int x, int y)
{
	m_pos.set(x, y);
}

void Tiro::SetNovaPos(ofVec2f xy)
{
	m_novaPos = xy;
}

void Tiro::SetNovaPos(int x, int y)
{
	m_novaPos.x = x;
	m_novaPos.y = y;
}

void Tiro::SetDano(int dano)
{
	m_dano = dano;
}

void Tiro::SetTamanho(int size)
{
	m_tamanho = size;
}

void Tiro::SetStatus(bool status)
{
	m_status = status;
}
