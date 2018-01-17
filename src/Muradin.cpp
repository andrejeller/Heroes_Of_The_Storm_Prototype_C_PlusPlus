#include "Muradin.h"
#include "Inimigo.h"

Muradin::Muradin()
{
}

Muradin::Muradin(int x, int y)
{
	SetPos(x, y);
	SetAtaqueE(false);
	SetAtaqueQ(false);
	SetAtaqueR(false);
	SetAtaqueW(false);
	SetMover(false);
	SetBoom(false);
	SetClick(false);
	m_size = 40;
	m_zoom = 60;
	m_tempoBoom = ofGetElapsedTimeMillis();
	m_raioBoom = 10;
	SetVelocidade(2);
	SetTiroTempo(ofGetElapsedTimeMillis());
	SetVida(3);
}

void Muradin::update(ofVec2f mouse, vector<Inimigo>* inis)
{
	SetNovaPos(mouse);
	mart.update(GetPos(), inis);

	if (m_mover)
	{
		if (!m_ataqueE && !m_ataqueQ)// && !m_atackR && !m_atackW )
			Mover(m_velocidade);
	}
	if (GetAtaqueE() && GetClick()) // Quando o Ataque estiver ativo, e o click for efetuado, atacar
	{
		AtackE();
		//SetJump(true);
		// deleta os iniminos do <vector> na distancia do ataque, quando o personagem esta "caindo"
	}
	if (GetAtaqueQ()) // Quando o Ataque estiver ativo, mostra distancia possivel para realizar o ataque
	{
		AtackQ(mouse);
	}

	/// -- Mata os Inimigos Durante o Boom, no raio limite...
	if (GetBoom()) {
		for (int i = 0; i < inis->size(); i++) {
			if (!VerificaPos(inis->at(i).GetPos(), m_raioBoom)) {
				inis->erase(inis->begin() + i);
			}
		}
	}

		
	 /// Faz os inimigos pararem quando atingem uma distancia de 30px do player.
	/// Para materia de matematica
	for (int i = 0; i < inis->size(); i++) {
		ofVec2f raioPermit = (inis->at(i).GetPos() - GetPos());
		float dist = raioPermit.length();
		if (dist <= 30) {
			inis->at(i).SetMover(false);
		}
	}
	// Tiros para matematica 
	for (int j = 0; j < tiros.size(); j++) {
		//Update Tiros
		tiros.at(j).update(GetPos());
		//Apaga tiros quendo chegam em destino
		if (!tiros.at(j).GetStatus())
			tiros.erase(tiros.begin() + j);
		/*for (int i = 0; i < inis->size(); i++) {
			if (tiros.at(j).GetPos() == inis->at(i).GetPos());
				inis->erase(inis->begin() + i);
			}*/
	}
}



void Muradin::update(ofVec2f mouse)
{
	if (GetAtaqueW()) {
		AtackW(mouse);
	} // em produçao para matematica
}


void Muradin::draw(ofVec2f camera, ofVec2f mouse)
{
	ofVec2f posicao = GetPos() - camera;

	// --- Area de Pulo Permitida
	if (m_ataqueE == true && m_click == false) {
		ofSetColor(100, 100, 0, 150);
		ofDrawCircle(posicao, 150);
	}
	// --- Quando o personagem estiver "caindo" fazer o BOOM
	if (GetBoom()) { 
		Boom(posicao); 
		if (m_raioBoom >= 150) {
			m_raioBoom = 10;
			SetBoom(false);
		}
	}		
	
	// --- Ataque do martelo
	if (m_ataqueQ == true && m_click == false) {
		ofSetColor(255, 255, 255);
		ofDrawArrow(posicao, mouse - camera, 10);
		ofSetColor(100, 100, 100, 100);
		ofDrawCircle(posicao, 115);
	}
	
	ofSetColor(255,0,0);
	ofDrawRectangle(posicao - m_size / 2, m_size, m_size);

	mart.draw(camera);
	// --- Ataque W // Para materia de Matematica
	for (int i = 0; i < tiros.size(); i++) {
		tiros.at(i).draw(camera);
	}
}

void Muradin::AtackQ(ofVec2f xy)
{
	//---- lança "martelo"
	mart.SetStatus(true);
	
	if (mart.GetStatus() && GetClick()) {
		//Após efetuar o click move o "martelo"
		mart.Mover(xy, 3);
	}
	if (mart.Stop(mart.GetPos())) {
		SetClick(false);
		SetAtaqueQ(false);
		mart.SetStatus(false);
	}

	/* -- Para Materia de Matematica
	if (mart.Stop(mart.GetPosXY())) {
		//Após o "martelo" chegar no local destino, Desativa A variavel do ataque e do martelo.
		SetClick(false);
		SetAtackQ(false);
		mart.SetStatus(false);
	}
	*/
}

void Muradin::AtackW(ofVec2f mouse)
{	/// --- Para materia de Matematica
	if (ofGetElapsedTimeMillis() - GetTempoTiro() >= 1000) {
		SetTiroTempo(ofGetElapsedTimeMillis());
		tiros.push_back(Tiro(GetPos()));
		for (int i = 0; i < tiros.size(); i++) {
			tiros.at(i).disparar(mouse);
		}
	}
}

void Muradin::AtackE() // Arremesso de Anão // Jump
{
	if (GetPular()) {
		Mover(5);
		Pular();
	}
	
	if (!GetPular()) {
		Mover(5);
		Cair();
	}
}

void Muradin::AtackR()
{
}

void Muradin::Mover(int v)
{
	if (VerificaPos(GetNovaPos(), 2)) {
		SetPos(GetPos() - ((GetPos() - GetNovaPos()).normalize() * v));
	}
}

void Muradin::Regenera()
{
	///Após 4 segundos sem receber Dano, Regenera vida
	if (m_vida > 40)
		m_vida += 128;
	/// Se 40%- Regenera*2
	if (m_vida < 40)
		m_vida += 128 * 2;
}

void Muradin::Pular()
{
	if (m_size < m_zoom) {
		m_size += 1;		
	}	
	if (m_size == m_zoom){
		SetPular(false);
	}
}

void Muradin::Cair()
{
	if (m_size > 40) {
		m_size -= 1;
	}
	if (m_size == 40) {
		SetAtaqueE(false);
		SetClick(false);
		SetBoom(true);
	}
}

void Muradin::Boom(ofVec2f xy)
{
	if (ofGetElapsedTimeMillis() - m_tempoBoom >= 10) {
			m_raioBoom++;
			m_tempoBoom = ofGetElapsedTimeMillis();
	}
	ofSetColor(100, 100, 100, 150);
	ofDrawCircle(xy, m_raioBoom);
}


bool Muradin::PermicaoClick(ofVec2f xy, int dist)
{
	ofVec2f raioPermit = (xy - GetPos());
	float distancia = raioPermit.length();
	if (distancia <= dist) {
		return true;		
	}
	return false;
}

bool Muradin::VerificaPos(ofVec2f xy, int distPermit) {

	ofVec2f raioPermit = (xy - GetPos());
	float dist = raioPermit.length();
	if (dist >= distPermit) {
		return true;
	}
	return false;
}

void Muradin::Colisao(int x, int y, int w, int h)
{
	if (m_pos.x < x + w) {
		m_mover = false;
	}
	if (m_pos.x + m_size > x) {
		m_mover = false;
	}
	if (m_pos.y < y + h) {
		m_mover = false;
	}
	if (m_pos.y + m_size > y) {
		m_mover = false;
	}
}


/// ---------- 
/// ---------- Getters
/// ----------


bool Muradin::GetAtaqueQ()
{
	return m_ataqueQ;
}

bool Muradin::GetAtaqueW()
{
	return m_ataqueW;
}

bool Muradin::GetAtaqueE()
{
	return m_ataqueE;
}

bool Muradin::GetAtaqueR()
{
	return m_ataqueR;
}

bool Muradin::GetClick()
{
	return m_click;
}

bool Muradin::GetPular()
{
	return m_pular;
}

bool Muradin::GetBoom()
{
	return m_boom;
}

int Muradin::GetVida()
{
	return m_vida;
}

int Muradin::GetTempoTiro()
{
	return m_tempoTiro;
}


int Muradin::GetDano()
{
	return m_dano;
}
ofVec2f Muradin::GetPos()
{
	return m_pos;
}

void Muradin::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Muradin::SetNovaPos(int x, int y)
{
	m_novaPos.x = x;
	m_novaPos.y = y;
}

void Muradin::SetAtackPos(int x, int y)
{
	m_posAtaque.x = x;
	m_posAtaque.y = y;
}


ofVec2f Muradin::GetNovaPos()
{
	return m_novaPos;
}
ofVec2f Muradin::GetAtackPosXY()
{
	return m_posAtaque;
}


/// ---------- 
/// ---------- Setters
/// ----------


void Muradin::SetPos(ofVec2f xy)
{
	m_pos.x = xy.x;
	m_pos.y = xy.y;
}

void Muradin::SetNovaPos(ofVec2f xy)
{
	m_novaPos.x = xy.x;
	m_novaPos.y = xy.y;
}

void Muradin::SetVida(int v)
{
	m_vida = v;
}

void Muradin::SetDano(int d)
{
	m_dano = d;
}

void Muradin::SetVelocidade(int velocidade)
{
	m_velocidade = velocidade;
}

void Muradin::SetAtaqueQ(bool q)
{
	m_ataqueQ = q;
}
void Muradin::SetAtaqueW(bool w)
{
	m_ataqueW = w;
}
void Muradin::SetAtaqueE(bool e)
{
	m_ataqueE = e;
	if (e == true)
	{
		m_pular = true;
	}
}
void Muradin::SetAtaqueR(bool r)
{
	m_ataqueR = r;
}
void Muradin::SetTiroTempo(int tempo)
{
	m_tempoTiro = tempo;
}
void Muradin::SetClick(bool c)
{
	m_click = c;
}
void Muradin::SetPular(bool j)
{
	m_pular = j;
}
void Muradin::SetBoom(bool b)
{
	m_boom = b;
}
void Muradin::SetMover(bool m)
{
	m_mover = m;
}