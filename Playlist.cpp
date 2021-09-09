/* Adrian Balbuena
 * Section 9
 * Assignment #4
 * Due: November 13, 2018 */

#include "Playlist.h"
#include "Song.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

Playlist::Playlist() {
    /*
     sets up empty playlist of entries
     */
    strcpy(playlistTitle, " ");
    playlistDuration = 0;
    listOfSongs = new Song[maxSize];
    currentSize = 0;
    maxSize = 5;
}

Playlist::~Playlist() {
    /*
     destructor function for class Playlist
     deallocates the playlist's list of Song objects.
     */
    delete[]listOfSongs;
}

void Playlist::grow() {
    /*
     increases the size of the Playlist's listOfSongs..
     by creating a larger array of entries
     */
    maxSize = currentSize + 5;
    Song* newListOfSongs = new Song[maxSize];

    for (int i = 0; i < currentSize; i++) {
        newListOfSongs[i] = listOfSongs[i];
    }
    delete[]listOfSongs;
    listOfSongs = newListOfSongs;
}

int Playlist::lookup(char *titleOrArtist, int j) const {
    /*
     returns the index listOfSongs which matches the first parameter passed in..
     (looks at titles/artist)
     int j is there so for loop does not return same index multiple times
     */
    for (int i = 0+j; i < currentSize; i++) {
        if (strcmp(listOfSongs[i].getTitle(), titleOrArtist) == 0) {
            return i;
        }
        else if (strcmp(listOfSongs[i].getArtist(), titleOrArtist) == 0) {
            return i;
        }
    }
    return -1;
}

void Playlist::remove(char *removeSong) {
    /*
     Remove a song from the Playlist
     Prompt the user for the name to be removed.
     */
    for(int i = 0; i < currentSize; i++) {
        if (strcmp(removeSong,listOfSongs[i].getTitle()) == 0) {
            /*
         shift each song "down" one position after in the song array,
         thereby deleting the wanted array.
         */
            for (int i = 0; i < currentSize; i++) {
                listOfSongs[i] = listOfSongs[i+1];
                currentSize--;
            }
        }
    }
}

void Playlist::displayPlaylist() const {
    /*
     Display the current directory entries.
     */

    for (int i = 0; i < currentSize; i++) {
        listOfSongs[i].display();
    }
}

void Playlist::updatePlayListTitle(char *newTitle) {
    strcpy(playlistTitle, newTitle);
}

void Playlist::addSong(const char *titleAdd, const char *artistAdd, Genre typeAdd, int durationAdd) {
    //make if statement to grow only when necessary
    listOfSongs[currentSize++].set(titleAdd, artistAdd, typeAdd, durationAdd);
}

int Playlist::getCurrentSize() const {
    return currentSize;
}

int Playlist::getPlaylistDuration() {
    playlistDuration = 0;
    for (int i = 0; i < currentSize; i++) {
        playlistDuration+=listOfSongs[i].getDuration();
    }
    //returned in seconds
    return playlistDuration;
}

Song Playlist::getlistOfSongs(int i) {
    return listOfSongs[i];
}

const char* Playlist::getPlaylistTitle() const {
    return playlistTitle;
}

int Playlist::getMaxSize() {
    return maxSize;
}









