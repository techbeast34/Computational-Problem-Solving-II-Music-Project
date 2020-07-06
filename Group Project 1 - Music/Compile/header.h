/*********************
Name: Akshay Desai & Satyendra Emani
Class: CPET-321
Date: Sep 20, 2019
**********************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

struct MusicPlaylist{
	string songName;
	string artist;
	int rank = -1;
	int yearReleased = -1;
	int decade = -1;
	char perfType = 'X';
	int genre = -1;
	MusicPlaylist *nextaddr = NULL;
};
//Default values that likely won't exist, this helps in checking if a list
//is empty

void Display(MusicPlaylist *head);
MusicPlaylist* insert(MusicPlaylist *head, int pos);
MusicPlaylist* deleteSong(MusicPlaylist *head, int pos);
void write(MusicPlaylist *head, string filename);
void display_playlist(MusicPlaylist *head);
MusicPlaylist* read_list(string filename);
MusicPlaylist* create_playlists(MusicPlaylist *head);
