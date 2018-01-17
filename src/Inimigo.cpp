#include "Inimigo.h"

Inimigo::Inimigo()
{
}

Inimigo::Inimigo(int x, int y)
{
	SetPos(x, y);
	SetWayPoint(0);
	SetStatus(true);
	SetCongelar(false);
	SetMover(true);
	SetTempo(ofGetElapsedTimeMillis());

}


void Inimigo::update(vector<WayPoint>* caminho, ofVec2f xy, int size)
{

	if (GetMover()) {
		m_velocidade = 1 + rand() % 3;

		if (VerificarDist(xy, 100)) {
			SetSeguir(true);
		}
		else
			SetSeguir(false);

		if (!GetSeguir()) {
			SetNewPos(caminho->at(GetWayPoint()).GetPos());


			Mover(m_velocidade);

			if (VerificarDist(GetNewPos(), 2)) {
				SetWayPoint(GetWayPoint() + 1);
				if (GetWayPoint() >= size)
					SetWayPoint(0);
			}
		}

		if (GetSeguir()) {
			SetNewPos(xy);
			Mover(1);
		}
	}
	if (GetCongelar()) {
		SetMover(false);
		if (ofGetElapsedTimeMillis() - GetTempo() >= 10000) {
			SetTempo(ofGetElapsedTimeMillis());
			SetCongelar(false);
		}
	}

	if (!GetMover() && !GetCongelar()) {
		if (ofGetElapsedTimeMillis() - GetTempo() >= 10) {
			SetMover(true);
			SetTempo(ofGetElapsedTimeMillis());
		}
	}
		
}

void Inimigo::draw(ofVec2f xy)
{
	if (GetStatus()) {
		ofVec2f posicao = GetPos() - xy;
		ofSetColor(255, 255, 255);
		ofDrawCircle(posicao, 7);
	}
}

void Inimigo::Mover(int v)
{
	if (GetStatus()) {
		SetPos(GetPos() - ((GetPos() - GetNewPos()).normalize() * v));
	}
}

bool Inimigo::VerificarDist(ofVec2f xy, int distPermit) {

	ofVec2f raioPermit = (xy - GetPos());
	float dist = raioPermit.length();
	if (dist <= distPermit) {
		return true;
	}
	return false;
}

int Inimigo::GetWayPoint()
{
	return m_wayPoint;
}

int Inimigo::GetTempo()
{
	return m_tempo;
}

bool Inimigo::GetStatus()
{
	return m_status;
}

bool Inimigo::GetSeguir()
{
	return m_seguirPlayer;
}

bool Inimigo::GetMover()
{
	return m_mover;
}

bool Inimigo::GetCongelar()
{
	return m_congela;
}

ofVec2f Inimigo::GetPos()
{
	return m_pos;
}

ofVec2f Inimigo::GetNewPos()
{
	return m_newPos;
}

void Inimigo::SetPos(ofVec2f xy)
{
	m_pos = xy;
}

void Inimigo::SetPos(int x, int y)
{
	m_pos.set(x, y);
}

void Inimigo::SetNewPos(ofVec2f xy)
{
	m_newPos = xy;
}

void Inimigo::SetWayPoint(int numero)
{
	m_wayPoint = numero;
}

void Inimigo::SetSeguir(bool sim)
{
	m_seguirPlayer = sim;
}

void Inimigo::SetStatus(bool status)
{
	m_status = status;
}

void Inimigo::SetMover(bool status)
{
	m_mover = status;
}

void Inimigo::SetCongelar(bool status)
{
	m_congela = status;
}

void Inimigo::SetTempo(int tempo)
{
	m_tempo = tempo;
}
