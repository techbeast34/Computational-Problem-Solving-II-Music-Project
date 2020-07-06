/*********************
 Name: Akshay Desai & Satyendra Emani
 Class: CPET-321
 Date: Sep 20, 2019
 **********************/
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>			// needed for file I/O
#include <cstdlib>
using namespace std;
#include "header.h"

int main() {
	ifstream inFile;
	ofstream outFile;

	MusicPlaylist *main_head;
	main_head = read_list("billboard.txt");

	bool inMenu = true;
	int pos = 0;
	while (inMenu) {
		cout << "Music Playlist menu:" << endl;
		cout << left << setw(20) << "(C)reate Playlist" << setw(20) << "(D)isplay" << setw(20) << "(M)odify Playlist" << setw(20) << "(S)ave Playlist" << endl;
		cout << left << setw(20) << "(R)emove Playlist" << setw(20) << "(L)oad Playlist" << setw(20) << "(Q)uit" << endl;
		cout << "Enter option: ";
		char option;
		cin >> option; cin.ignore();
		bool inSubMenu = true;

		switch (option) {
		case 'C':
		case 'c':{
			string name;
			cout << "Enter a name for your new playlist: ";
			getline(cin, name);
			write(create_playlists(main_head), name);
			break;}
		case 'D':
		case 'd':
			Display(main_head);
			break;
		case 'M':
		case 'm':
			cout << left << setw(20) << "(I)nsert/(D)elete" << setw(20)
					<< "(M)ain Menu" << endl;
			while (inSubMenu) {
				char mod;
				cin >> mod;
				switch (mod) {
				case 'I':
				case 'i':
					inSubMenu = false;
					cout << "Enter position: ";
					cin >> pos;
					cin.ignore();
					insert(main_head, pos);
					break;
				case 'D':
				case 'd':
					inSubMenu = false;
					cout << "Enter position: ";
					cin >> pos;
					cin.ignore();
					deleteSong(main_head, pos);
					break;

				case 'M':
				case 'm':
					inSubMenu = false;
					break;
				default:
					cout << "--------------Invalid Input Retry--------------"
						<< endl;
					inSubMenu = true;
			    }
			}
			inMenu = true;
			break;
		case 'S':
		case 's':{
			string name;
			cout << "Enter the name for this playlist: ";
			getline(cin, name);
			write(main_head, name);
			}
			inMenu = true;
			break;
		case 'R':
		case 'r':{
			string name;
			cout << "Enter the name of the playlist you want to remove (no filename extension): ";
			getline(cin, name);
			remove(name.append(".txt").c_str());
			}
			inMenu = true;
			break;
		case 'L':
		case 'l':{
			string name;
			cout << "Enter the name of the playlist you want to load (no filename extension): ";
			getline(cin, name);
			main_head = read_list(name.append(".txt").c_str());
			}
			inMenu = true;
			break;
		case 'Q':
		case 'q':
			cout << "--------------Bye and Thank you---------------" << endl;
			return 0;
		}

	}
	return 0;
}
