#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;

namespace interface {
	struct Compte 
	{
		string numeroCompte;
		string nip;
		int solde;
	};

	struct Transaction 
	{
		string type;
		int montant;
	};


	void obtenirIdentifiants(string& numeroCompte, string& nip);
	void obtenirChoixMenu(int& choix);
	void obtenirMontant(float& montant, string operation);

	void obtenirNumeroCompteTransfert(string& numeroCompteTransfert);
	
	void afficherInformationCompte(const Compte& compte);
	void afficherMenu();
	void afficherSolde(int &solde);
	void afficherDepot(int montant);
	void afficherRetrait(int montant);
	void afficherTransfert(int montant, const string& numeroCompteDestination);
	
	void afficherHistoriqueTransaction(Transaction transactions[], int taille);
	void afficherErreurFond(int situation);
};
