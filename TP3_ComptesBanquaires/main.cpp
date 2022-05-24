#include <iostream>
#include <string>
#include <fstream>

#include "interface.h"

using namespace std;
using namespace interface;

const int TAILLE_MAX{ 1000 };

struct TableCompte
{
	string identifiant;
	string nip;
	float solde;
};

void genererTableCompte(TableCompte tableCompte[])
{
	ifstream monFichier("ListeComptes.txt");

	if (!monFichier.is_open())
	{
		cout << "\n\nErreur! Le fichier n'a pas pus être ouvert.";
		exit(-1);
	}

	for (int i{ 0 }; !monFichier.eof(); i++)
	{
		monFichier >> tableCompte[i].identifiant;
		monFichier >> tableCompte[i].nip;
		monFichier >> tableCompte[i].solde;
	}
}

void verifierFichierTransaction(string numeroCompte)
{
	string fichierTransactions{ numeroCompte + ".transaction" };
	ifstream monFichierTransactions(fichierTransactions);

	if (!monFichierTransactions.is_open())
	{
		ofstream creerFichier(fichierTransactions);
		return;
	}
}

void genererHistoriqueTransactions(string numeroCompte, Transaction transactions[], int& taille)
{
	ifstream monFichierTransactions(numeroCompte + ".transaction");

	for (int i{ 0 }; i < 5; i++)
	{
		monFichierTransactions >> transactions[i].type;
		monFichierTransactions >> transactions[i].montant;
		
		if (transactions[i].type != "")
		{
			taille = i;
		}
	}
}

void trouverUtilisateur(TableCompte tableCompte[], string numeroCompte, string numeroIdentifiantCompte, Compte& compte)
{
	for (int i{ 0 }; i < TAILLE_MAX; i++)
	{
		if (numeroCompte == tableCompte[i].identifiant)
		{
			if (numeroIdentifiantCompte == tableCompte[i].nip)
			{
				compte.numeroCompte = tableCompte[i].identifiant;
				compte.nip = tableCompte[i].nip;
				compte.solde = tableCompte[i].solde;
				return;
			}
			else
			{
				cout << "\n\nErreur! NIP invalide.";
				exit(-2);
			}
		}
	}
	cout << "\n\nErreur! Numéro d'utilisateur introuvable.";
	exit(-3);
}

void modifierBaseDeDonnée(string numeroCompte, int solde)
{
	ifstream monFichier("ListeComptes.txt");
	string ligne;
	string fichier{ "" };

	for (int i{ 0 }; getline(monFichier, ligne); i++)
	{
		if (ligne.substr(0, 6) == numeroCompte)
		{
			fichier += numeroCompte + "\t" + ligne.substr(7, 5) + "\t" + to_string(solde) + "\n";
		}
		else
		{
			fichier += ligne + "\n";
		}
	}
	monFichier.close();
	
	ofstream monFichierSortie("ListeComptes.txt");
	monFichierSortie << fichier;
}

void faireDepot(Compte& compte, float& montant)
{
	afficherInformationCompte(compte);
	obtenirMontant(montant, "déposer");

	if (montant <= 0)
	{
		afficherErreurFond(-5);
	}

	compte.solde += montant;
	afficherDepot(montant);
	system("PAUSE");
}

void faireRetrait(Compte& compte, float& montant)
{
	afficherInformationCompte(compte);
	obtenirMontant(montant, "retirer");

	if (montant <= 0)
	{
		afficherErreurFond(-5);
	}
	if (compte.solde - montant < 0)
	{
		afficherErreurFond(-4);
	}

	compte.solde = compte.solde - montant;
	afficherRetrait(montant);
	system("PAUSE");
}

void trouverCompteTransfert(TableCompte tableCompte[], string numeroCompteTransfert, Compte& compteTransfert)
{
	for (int i{ 0 }; i < TAILLE_MAX; i++)
	{
		if (numeroCompteTransfert == tableCompte[i].identifiant)
		{
			compteTransfert.numeroCompte = tableCompte[i].identifiant;
			compteTransfert.nip = tableCompte[i].nip;
			compteTransfert.solde = tableCompte[i].solde;
			return;
		}
	}
}

void verifierCompteTransfert(string numeroCompteTransfert)
{
	ifstream monFichier("ListeComptes.txt");
	string ligne;

	for (int i{ 0 }; getline(monFichier, ligne); i++)
	{
		if (ligne.substr(0, 6) == numeroCompteTransfert)
		{
			ofstream tempFichier(numeroCompteTransfert + ".transaction");
			tempFichier.close();
			return;
		}
	}
	cout << "Le compte du destinataire n'existe pas!";
	exit(-6);
}

void faireTransfert(string& numeroCompteTransfert, Compte& compte, float& montant, TableCompte tableCompte[])
{
	afficherInformationCompte(compte);
	obtenirNumeroCompteTransfert(numeroCompteTransfert);
	verifierCompteTransfert(numeroCompteTransfert);
	obtenirMontant(montant, "transférer");

	if (montant <= 0)
	{
		afficherErreurFond(-5);
	}
	if (compte.solde - montant < 0)
	{
		afficherErreurFond(-4);
	}

	compte.solde = compte.solde - montant;
	Compte compteTransfert;
	trouverCompteTransfert(tableCompte, numeroCompteTransfert, compteTransfert);
	modifierBaseDeDonnée(numeroCompteTransfert, compteTransfert.solde + montant);
	afficherTransfert(montant, numeroCompteTransfert);
	system("PAUSE");
}

void ecrireTransaction(string numeroCompte, string type, float montant)
{
	ifstream monFichierTransaction(numeroCompte + ".transaction");
	string fichier;
	string ligne;

	for (int i{ 0 }; getline(monFichierTransaction, ligne); i++)
	{
		fichier += ligne + "\n";
	}
	fichier = type + to_string(int(montant)) + "\n" + fichier;
	monFichierTransaction.close();

	ofstream monFichierSortie(numeroCompte + ".transaction");
	monFichierSortie << fichier;
}

int main(void)
{
	setlocale(0, "");
	
	Transaction transactions[TAILLE_MAX];
	Compte compte;

	TableCompte tableCompte[TAILLE_MAX];
	genererTableCompte(tableCompte);

	string numeroCompte;
	string nip;
	string numeroCompteTransfert;
	obtenirIdentifiants(numeroCompte, nip);
	trouverUtilisateur(tableCompte, numeroCompte, nip, compte);
	verifierFichierTransaction(numeroCompte);

	int choix;
	float montant{ 0 };
	while (true)
	{
		afficherInformationCompte(compte);
		afficherMenu();
		obtenirChoixMenu(choix);

		switch (choix)
		{
		case 1:
			afficherSolde(compte.solde);
			system("PAUSE");
			break;
		case 2:
			faireDepot(compte, montant);
			ecrireTransaction(numeroCompte, "Dépôt\t", montant);
			break;
		case 3:
			faireRetrait(compte, montant);
			ecrireTransaction(numeroCompte, "Retrait\t", montant);
			break;
		case 4:
			faireTransfert(numeroCompteTransfert, compte, montant, tableCompte);
			ecrireTransaction(numeroCompte, "Transfert\t-", montant);
			ecrireTransaction(numeroCompteTransfert, "Transfert\t+", montant);
			break;
		case 5:
			int taille;
			afficherInformationCompte(compte);
			genererHistoriqueTransactions(numeroCompte, transactions, taille);
			afficherHistoriqueTransaction(transactions, taille);
			system("PAUSE");
			break;
		case 6:
			cout << "À la prochaine!";
			exit(0);
		}
		modifierBaseDeDonnée(numeroCompte, compte.solde);
	}
}