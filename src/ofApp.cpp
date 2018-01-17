#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);

	estadoDeJogo = 0;
	menu.load("menu.png");

	mostrarRotas = false;
	AtivaDelete = false;
	Apagao = false;

	Mouse.SetPos(ofGetMouseX(), ofGetMouseY());
	Muri = new Muradin(1671, 545);
	
	tod = new Mapa("tod.jpg");

	towers[0] = new Tower(690, 327, 30);
	towers[1] = new Tower(1330, 330, 30);
	towers[2] = new Tower(750, 560, 30);
	towers[3] = new Tower(1270, 565, 30);
	towers[4] = new Tower(714, 814, 30);
	towers[5] = new Tower(1303, 816, 30);

	caminhoA.push_back(WayPoint(150, 453));
	caminhoA.push_back(WayPoint(150, 453));
	caminhoA.push_back(WayPoint(352, 545));
	caminhoA.push_back(WayPoint(525, 476));
	caminhoA.push_back(WayPoint(709, 363));
	caminhoA.push_back(WayPoint(1006, 301));
	caminhoA.push_back(WayPoint(1312, 368));
	caminhoA.push_back(WayPoint(1299, 528));
	caminhoA.push_back(WayPoint(726, 528));
	caminhoA.push_back(WayPoint(539, 509));
	caminhoA.push_back(WayPoint(352, 545));
	
	caminhoB.push_back(WayPoint(150, 453));
	caminhoB.push_back(WayPoint(352, 545));
	caminhoB.push_back(WayPoint(544, 592));
	caminhoB.push_back(WayPoint(748, 600));
	caminhoB.push_back(WayPoint(846, 559));
	caminhoB.push_back(WayPoint(1169, 565));
	caminhoB.push_back(WayPoint(1268, 605));
	caminhoB.push_back(WayPoint(1284, 773));
	caminhoB.push_back(WayPoint(725, 850));
	caminhoB.push_back(WayPoint(534, 625));
	caminhoB.push_back(WayPoint(352, 545));

	inimigosCaminhoA.push_back(Inimigo(150, 452));
	inimigosCaminhoB.push_back(Inimigo(150, 452));
}

//--------------------------------------------------------------
void ofApp::update() {
	
	switch (estadoDeJogo)
	{	
	case 0:
		break;
	case 1:
		srand(time(NULL));
		/// -- Camera
		camera.set(Muri->GetPos().x - (ofGetWidth() / 2), Muri->GetPos().y - (ofGetHeight() / 2));
		/// -- Player
		Muri->update(Mouse.GetPosClicada(), &inimigosCaminhoA);
		Muri->update(Mouse.GetPosClicada(), &inimigosCaminhoB);
		Muri->update(Mouse.GetPos());
		/// -- Mapa
		tod->update(camera);
		/// -- Torres
		for (int i = 0; i < 6; i++)
			towers[i]->update(Muri->GetPos());

		/// -- Criação Inimigos
		spawnInimigos();
		
		/// -- Inimigos + Rotas
		updadeRotas();

		/// -- 'Delete/Free'
		ativa_delete();
		apagao();
		break;

	default:
		break;
	}

	ofHideCursor();	
	//std::cout << Muri->GetPosXY() << std::endl;
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	switch (estadoDeJogo)
	{
	case 0:
		ofPushMatrix();
		menu.setAnchorPercent(0.5, 0.5);
		menu.draw(ofGetWidth() / 2, ofGetHeight() / 2);
		ofPopMatrix();
		break;
	case 1:
		tod->draw(camera);
		Muri->draw(camera, Mouse.GetPos());
		for (int i = 0; i < 6; i++)
			towers[i]->draw(camera);
		for (unsigned int i = 0; i < inimigosCaminhoA.size(); i++)
			inimigosCaminhoA.at(i).draw(camera);
		for (unsigned int i = 0; i < inimigosCaminhoB.size(); i++)
			inimigosCaminhoB.at(i).draw(camera);
		if (mostrarRotas) {
			for (int i = 0; i < caminhoA.size(); i++)
				caminhoA.at(i).draw(camera);

			for (int i = 0; i < caminhoB.size(); i++)
				caminhoB.at(i).draw(camera);

			for (int i = 0; i < caminhoA.size(); i++) {
				ofSetColor(255, 255, 255);
				int j = i + 1;
				if (j >= caminhoA.size()) j = 0;
				ofDrawArrow(caminhoA.at(i).GetPos() - camera, caminhoA.at(j).GetPos() - camera, 4);
			}
			for (int i = 0; i < caminhoB.size(); i++) {
				ofSetColor(255, 200, 200);
				int j = i + 1;
				if (j >= caminhoB.size()) j = 0;
				ofDrawArrow(caminhoB.at(i).GetPos() - camera, caminhoB.at(j).GetPos() - camera, 4);
			}

		}
		break;
	default:
		break;
	}
	Mouse.draw(camera);		
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (estadoDeJogo)
	{
	case 0:
		if (key == 13) estadoDeJogo = 1;
		break;
	case 1:
		if (!Muri->GetAtaqueE() && !Muri->GetAtaqueQ()) {
			// ---- Q
			if (key == 113) Muri->SetAtaqueQ(true);
			// ---- W, Tiros Matetmatica
			if (key == 119) Muri->SetAtaqueW(true);
			// ---- E
			if (key == 101) Muri->SetAtaqueE(true);
			// ---- R
			if (key == 114)	Muri->SetAtaqueR(true);
		}	
		// ---- I -- Para Informações
		if (key == 105) { 
			if (!mostrarRotas) mostrarRotas = true;
			else mostrarRotas = false;
		}
		// ---- UP, aumenta spawnTime
		if (key == 357)	spawnTime = spawnTime * 2;
		// --- Down, diminui spawnTime
		if (key == 359) spawnTime = spawnTime / 2;
		// --- Left, Ativar Deletede memoria
		if (key == 356) {
			if (!AtivaDelete) AtivaDelete = true;
			else AtivaDelete = false;
		}
		// --- Right, Move para Direita
		if (key == 358) Apagao = true;
		// --- B, Volta ao ponto inicial 
		if (key == 98) { 
			Muri->SetPos(1671, 545); 
			Mouse.SetPosClick(1671, 545);
		}
		// --- Z, Velocidade ++
		if (key == 122) Muri->SetVelocidade(4);
			
		break;
	default:
		break;
	}
	
	std::cout << key << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	// --- Z, Velocidade --
	if (key == 122) Muri->SetVelocidade(2);
	// ---- W, Tiros Matetmatica
	if (key == 119)	Muri->SetAtaqueW(false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	Mouse.SetPos(x + camera.x, y + camera.y);
	//std::cout << x << " , " << y << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	
	if (!Muri->GetClick()) {
		if (button == 2) {
			Muri->SetMover(true);
			Mouse.SetPosClick(x + camera.x, y + camera.y);
		}
	}
	
	if (button == 2) {
		if (Muri->GetAtaqueE()) {
			if (Muri->PermicaoClick(Mouse.GetPosClicada(), 150)) {
				Mouse.SetPosClick(x + camera.x, y + camera.y);
				Muri->SetClick(true);
				}
		}

		if (Muri->GetAtaqueQ()) {
			if (Muri->PermicaoClick(Mouse.GetPosClicada(), 115)) {
				Mouse.SetPosClick(x + camera.x, y + camera.y);
				Muri->SetClick(true);
				}
		}
		
	}
	
	//std::cout << button << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
