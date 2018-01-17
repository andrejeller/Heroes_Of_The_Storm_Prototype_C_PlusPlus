#pragma once
#include "ofMain.h"
#include "Muradin.h"
#include "Mouse.h"
#include "Tower.h"
#include "Mapa.h"
#include "WayPoint.h"
#include "Inimigo.h"
#include <vector>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int estadoDeJogo;

	bool mostrarRotas;
	bool AtivaDelete;
	bool Apagao;

	Mapa* tod;
	Mouse Mouse;
	Muradin* Muri;
	Tower* towers[6];
	int tamanho = 3;
	int tempoInis = 0; // Recebe ofGetElapsedTimeMillis()
	int spawnTime = 10000; // Define tempo de spawn

	vector<WayPoint> caminhoA;
	vector<WayPoint> caminhoB;
	vector<Inimigo> inimigosCaminhoA;
	vector<Inimigo> inimigosCaminhoB;
	vector<vector<Inimigo>> inimigos;

	ofVec2f camera;
	ofImage menu;
		


	void updadeRotas() {
		for (unsigned int i = 0; i < inimigosCaminhoA.size(); i++)
			inimigosCaminhoA.at(i).update(&caminhoA, Muri->GetPos(), caminhoA.size());
		for (unsigned int i = 0; i < inimigosCaminhoB.size(); i++)
			inimigosCaminhoB.at(i).update(&caminhoB, Muri->GetPos(), caminhoB.size());

	}
	void spawnInimigos() {
		if (ofGetElapsedTimeMillis() - tempoInis >= spawnTime) {
			inimigosCaminhoA.push_back(Inimigo(150, 452));
			inimigosCaminhoB.push_back(Inimigo(150, 452));
			tempoInis = ofGetElapsedTimeMillis();
		}
	}
	void ativa_delete() {
		if (AtivaDelete) {
			for (int i = 0; i < inimigosCaminhoA.size(); i++) {
				if (inimigosCaminhoA.at(i).GetWayPoint() == 0)
					inimigosCaminhoA.erase(inimigosCaminhoA.begin() + i);
			}
			for (int i = 0; i < inimigosCaminhoB.size(); i++) {
				if (inimigosCaminhoB.at(i).GetWayPoint() == 0)
					inimigosCaminhoB.erase(inimigosCaminhoB.begin() + i);
			}
		}
	}
	void apagao() {
		if (Apagao) {
			inimigosCaminhoA.clear();
			inimigosCaminhoB.clear();
			Apagao = false;
		}
	}
};