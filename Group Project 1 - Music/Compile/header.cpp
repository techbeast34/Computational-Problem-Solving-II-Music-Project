/*********************
 Name: Akshay Desai & Satyendra Emani
 Class: CPET-321
 Date: Sep 20, 2019
 **********************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "header.h"

using namespace std;
/*
 * Displays playlist
 */
void Display(MusicPlaylist *head) {
	int cnt = 1;

	MusicPlaylist *current = head;

	cout << "Playlist: " << endl;

	while (current != NULL) {
		cout << right << setw(4) << cnt++ << ")  ";
		cout << left << current->songName << " | " << current->artist << " | "
				<< current->rank << endl;
		cout << current->yearReleased << " | " << current->decade << " | "
				<< current->perfType << " | " << current->genre << endl;
		cout << "----------------" << endl;
		current = current->nextaddr;
	}

	return;
}

/*
 * Inserts song at given position, prompts user
 * for new song data
 */
MusicPlaylist* insert(MusicPlaylist *head, int pos) {

	MusicPlaylist *current, *previous, *tmp;

	current = head;

	tmp = new MusicPlaylist;
	cout << "Song Name: ";
	getline(cin, tmp->songName);
	cout << "Artist: ";
	getline(cin, tmp->artist);
	cout << "Rank: ";
	cin >> tmp->rank;
	cin.ignore();
	cout << "Year Released: ";
	cin >> tmp->yearReleased;
	cin.ignore();
	tmp->decade = ((tmp->yearReleased / 10) % 10) * 10;
	//Grabs 3rd digit from year, multiply by 10 for the decade
	cout << "Performer Type [(M)ale, (F)emale, (D)uo/Group]: ";
	cin >> tmp->perfType;
	cin.ignore();
	cout << "Genre: ";
	cin >> tmp->genre;
	cin.ignore();

	if (pos == 1) {
		tmp->nextaddr = current;
		head = tmp;
	} else {
		for (int i = 1; i < pos; i++) {
			previous = current;
			current = current->nextaddr;
		}
		tmp->nextaddr = current;
		previous->nextaddr = tmp;
	}
	return (head);
}

/*
 * Deletes song at given position
 */
MusicPlaylist* deleteSong(MusicPlaylist *head, int pos) {
	MusicPlaylist *current, *previous;

	current = head;

	if (pos == 1) {
		head = current->nextaddr;
	} else {
		for (int i = 1; i < pos; i++) {
			previous = current;
			current = current->nextaddr;
		}
		previous->nextaddr = current->nextaddr;
	}
	delete (current);
	return (head);
}

/*
 * Writes playlist to a file
 */
void write(MusicPlaylist *head, string name) {
	MusicPlaylist *current = head;

	ofstream outFile(name.append(".txt").c_str());
	//take the name passed in, append ".txt" to the end

	while (current != NULL) {
		outFile << current->songName << endl;
		outFile << current->artist << endl;
		outFile << current->rank << endl;
		outFile << current->yearReleased << endl;
		outFile << current->decade << endl;
		outFile << current->perfType << endl;
		if(current->nextaddr == NULL){
			outFile << current->genre;
		} else {
			outFile << current->genre << endl;
		}
		current = current->nextaddr;
	}
	outFile.close();
}

/*
 * Reads in a txt file and returns a playlist
 */
MusicPlaylist* read_list(string filename) {
	ifstream inFile;

	inFile.open(filename.c_str());

	if (inFile.fail()) {
		cout << "\nThe file did not successfully open... Program Terminated\n"
				<< endl;
		exit(1);
	}

	MusicPlaylist *current, *head;

	current = new MusicPlaylist;
	head = current;
	do {
		getline(inFile, current->songName);
		getline(inFile, current->artist);
		inFile >> current->rank;
		inFile.ignore();
		inFile >> current->yearReleased;
		inFile.ignore();
		inFile >> current->decade;
		inFile.ignore();
		inFile >> current->perfType;
		inFile.ignore();
		inFile >> current->genre;
		inFile.ignore();

		if (inFile.eof()) {
			current->nextaddr = NULL;
			break;
		} else {
			current->nextaddr = new MusicPlaylist;
			current = current->nextaddr;
		}
	} while (true);
	inFile.close();

	return (head);
}


/*
 * Creates playlist from another playlist based on user input.
 * Songs can be added via rank, decade, performer type, or genre.
 */
MusicPlaylist* create_playlists(MusicPlaylist *head) {

	MusicPlaylist *current, *returnPlaylist, *tmp;
	returnPlaylist = new MusicPlaylist;

	char menu;
	cout << "Editing playlist " << ": \n";

	cout << "Add songs by: " << endl;
	cout << left << setw(20) << "(R)ank" << setw(20) << "(D)ecade"
			<< setw(20) << "(P)erformer Type" << setw(20) << "(G)enre"
			<< setw(20) << endl; // << "[E]xit and save playlist" << endl;
	cin >> menu;
	menu = toupper(menu);

	while (menu != 'Q') {
		switch (menu) {
		case 'R':
		case 'r': {
			int rank;
			cout << "Enter in the rank: ";
			cin >> rank;
			cin.ignore();

			tmp = new MusicPlaylist;

			current = head;

			while (current->rank != rank) {
				current = current->nextaddr;
			}//Scan until rank desired rank is found

			if (current->rank == rank) {
				tmp->songName = current->songName;
				tmp->artist = current->artist;
				tmp->rank = current->rank;
				tmp->yearReleased = current->yearReleased;
				tmp->decade = current->decade;
				tmp->perfType = current->perfType;
				tmp->genre = current->genre;
				tmp->nextaddr = NULL;
			}//Copy data into new node

			if (returnPlaylist->rank == -1) {

				returnPlaylist = tmp;
				//Check if new playlist is empty, set temporary node as head
			} else {
				MusicPlaylist *tmp2 = new MusicPlaylist;

				tmp2 = returnPlaylist;
				while (tmp2->nextaddr != NULL) {
					tmp2 = tmp2->nextaddr;
				}

				tmp2->nextaddr = tmp;
				//If playlist isn't empty, append new node to the end
			}

			Display(returnPlaylist);
			cout << "Song Added To playlist" << endl;
			cout << "Continue adding by (R)ank or (Q)uit to menu? ";
			cin >> menu;
			cin.ignore();
		}
			break;
		case 'D':
		case 'd': {
			int decade;
			cout << "Enter in the decade(ex. '80' for the 80s): ";
			cin >> decade;
			cin.ignore();
			cout << decade << endl;
			current = head;

			while (current->nextaddr != NULL) {
				tmp = new MusicPlaylist;

				while (current->decade != decade && current->nextaddr != NULL) {
					current = current->nextaddr;
				} //Scan for next song matching decade

				if (current->decade == decade) {
					tmp->songName = current->songName;
					tmp->artist = current->artist;
					tmp->rank = current->rank;
					tmp->yearReleased = current->yearReleased;
					tmp->decade = current->decade;
					tmp->perfType = current->perfType;
					tmp->genre = current->genre;
					tmp->nextaddr = NULL;
				} //Copy data into new node

				if (returnPlaylist->decade == -1) {

					returnPlaylist = tmp;

				} else {
					MusicPlaylist *tmp2 = new MusicPlaylist;

					tmp2 = returnPlaylist;

					while (tmp2->nextaddr != NULL) {
						tmp2 = tmp2->nextaddr;

					}
					if (tmp->decade != -1) {
						tmp2->nextaddr = tmp;
					}

				}//Same logic as before

				if (current->nextaddr != NULL) {
					current = current->nextaddr;
				}//Advance forward in linked list to prevent double adding songs
			}

			menu = 'Q'; //Exit out of create after done
		}
			break;

		case 'P':
		case 'p': {
			char perfType;
			cout << "Enter Performer Type: (F)emale     (M)ale     (D)uo/Group"
					<< endl;
			cin >> perfType;
			cin.ignore();

			current = head;

			while (current->nextaddr != NULL) {
				tmp = new MusicPlaylist;
				while (current->perfType != perfType
						&& current->nextaddr != NULL) {
					current = current->nextaddr;
				}//Same logic, but with performer

				if (current->perfType == perfType) {
					tmp->songName = current->songName;
					tmp->artist = current->artist;
					tmp->rank = current->rank;
					tmp->yearReleased = current->yearReleased;
					tmp->decade = current->decade;
					tmp->perfType = current->perfType;
					tmp->genre = current->genre;
					tmp->nextaddr = NULL;
				}//Same logic

				if (returnPlaylist->perfType == 'X') {

					returnPlaylist = tmp;

				} else {
					MusicPlaylist *tmp2 = new MusicPlaylist;

					tmp2 = returnPlaylist;

					while (tmp2->nextaddr != NULL) {
						tmp2 = tmp2->nextaddr;

					}
					if (tmp->perfType != 'X') {
						tmp2->nextaddr = tmp;
					}

				}//Same logic

				if (current->nextaddr != NULL) {
					current = current->nextaddr;
				}//Same logic
			}

			menu = 'Q';//Exit out of create after done
		}
			break;
		case 'G':
		case 'g': {
			int genre;
			cout << left << setw(20) << "Enter Genre" << endl;
			cout << left << setw(20) << "(1)Latin" << setw(20) << "(2)Country"
					<< setw(20) << "(3)Hip-Hop/Rap" << setw(20) << "(4)Jazz"
					<< endl;
			cout << left << setw(20) << "(5)Dance/Electronic" << setw(20)
					<< "(6)R&B" << setw(20) << "(7)Pop" << setw(20) << "(8)Rock"
					<< endl;
			cin >> genre;
			cin.ignore();
			current = head;

			while (current->nextaddr != NULL) {
				tmp = new MusicPlaylist;
				while (current->genre != genre
						&& current->nextaddr != NULL) {
					current = current->nextaddr;
				} //Same logic

				if (current->genre == genre) {
					tmp->songName = current->songName;
					tmp->artist = current->artist;
					tmp->rank = current->rank;
					tmp->yearReleased = current->yearReleased;
					tmp->decade = current->decade;
					tmp->perfType = current->perfType;
					tmp->genre = current->genre;
					tmp->nextaddr = NULL;
				} //Same logic

				if (returnPlaylist->genre == -1) {

					returnPlaylist = tmp;

				} else {
					MusicPlaylist *tmp2 = new MusicPlaylist;

					tmp2 = returnPlaylist;

					while (tmp2->nextaddr != NULL) {
						tmp2 = tmp2->nextaddr;

					}
					if (tmp->genre != -1) {
						tmp2->nextaddr = tmp;
					}

				} //Same logic

				if (current->nextaddr != NULL) {
					current = current->nextaddr;
				} //Same logic
			}

			menu = 'Q'; //Same logic
		}

			break;

		default:
			cout << "Invalid input, quitting to main menu..." << endl;
			menu = 'Q';

		}
	}
	Display(returnPlaylist);
	return returnPlaylist;

}
