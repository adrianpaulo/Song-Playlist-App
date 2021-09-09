/* Adrian Balbuena
 * Section 9
 * Assignment #4
 * Due: November 13, 2018 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cctype>

class Playlist {
public:
    Playlist();         //setup empty playlist of entries
    ~Playlist();        //deallocate the listOfSongs
    int lookup(char *titleOrArtist, int) const;
    void remove(char *removeSong);      //remove an entry
    void displayPlaylist() const;       //display playlist
    void updatePlayListTitle(char newTitle[20]);
    void addSong(const char* titleAdd, const char* artistAdd, Genre typeAdd, int durationAdd);
    int getCurrentSize() const;     // returns the current size
    int getPlaylistDuration();    //returns the playlist duration
    const char* getPlaylistTitle() const;   //returns playlist title
    Song getlistOfSongs(int);
    int getMaxSize();
    void grow();            //increase maxSize when required

private:
    int maxSize;            //max num of entries
    int currentSize;        //current num of entries
    Song* listOfSongs;      //pointer to the list of entries
    char playlistTitle[21];
    int playlistDuration;
};

#endif