//Auteur: Adam Ruest

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>

#include "interface.h"

void interface::obtenirIdentifiants(string& numeroCompte, string& nip)
{
	cout << "Votre num�ro de compte: ";
	cin >> numeroCompte;
	cout << "Votre num�ro d'identification personnel (NIP): ";
	cin >> nip;
}

void interface::obtenirChoixMenu(int& choix) 
{
	do
	{
		cout << "\n\nVotre choix: ";
		cin >> choix;
	}
	while (choix < 1 || choix > 6);
}

void interface::obtenirMontant(float& montant, string operation)
{
	cout << "\nQuel montant voulez-vous " + operation + ": ";
	cin >> montant;
	montant = montant * 100;
}

void interface::obtenirNumeroCompteTransfert(string& numeroCompteTransfert)
{
	cout << "\nVeuillez �crire le num�ro de compte dans lequel vous souhaitez transf�rer de l'argent: ";
	cin >> numeroCompteTransfert;
}

void interface::afficherInformationCompte(const interface::Compte& compte)
{
	system("cls");
	cout << "Utilisateur: " << compte.numeroCompte << "\n";
	cout << setfill('-') << setw(50) << "-";
}

void interface::afficherMenu()
{
	cout << "\n1: Afficher le solde\n";
	cout << "2: D�pot\n";
	cout << "3: Retrait\n";
	cout << "4: Transfert\n";
	cout << "5: Afficher l'historique de transaction\n";
	cout << "6: Quitter";
}

void interface::afficherSolde(int &solde)
{
	cout << "Votre solde: " << float(solde) / 100 << "$\n";
}

void interface::afficherDepot(int montant)
{
	cout << "Le d�p�t de " << float(montant) / 100 << "$ � �t� fait avec succ�s!\n";
}

void interface::afficherRetrait(int montant)
{
	cout << "Le retrait de " << float(montant) / 100 << "$ � �t� effectu� avec succ�s!\n";
}

void interface::afficherTransfert(int montant, const string& numeroCompteDestination)
{
	cout << "Le transfert de " << float(montant) / 100 << "$ vers le compte " + numeroCompteDestination + " � �t� effectu� avec succ�s!\n";
}

void interface::afficherHistoriqueTransaction(interface::Transaction transactions[], int taille)
{
	cout << "\n" << setfill(' ') << setw(10) << "Type" << setw(10) << "Montant\n";

	for (int i{ 0 }; i < 5 && i <= taille; i++)
	{
		cout << setw(10) << transactions[i].type << setw(8) << float(transactions[i].montant) / 100 << "$\n";
	}
}

void interface::afficherErreurFond(int situation)
{
	if (situation == -4)
	{
		cout << "Vous n'avez pas assez d'argent.\n";
		exit(-4);
	} 
	else if (situation == -5)
	{
		cout << "Operation interdite.\n";
		exit(-5);
	}
}