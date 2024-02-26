#ifndef AUDIO_H
#define AUDIO_H

#include "../common.h"

void InitAudio();
void QuitAudio();
Mix_Music *PlaySong(const char *file);
void EndSong(Mix_Music *music);
Mix_Chunk *InitChunk(const char *file);
void EndChunk(Mix_Chunk *chunk);

#endif