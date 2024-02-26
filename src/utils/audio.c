#include "../../include/utils/audio.h"

void InitAudio()
{
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) != 0)
  {
    HANDLE_ERROR("INIT AUDIO");
  }
}

void QuitAudio()
{
  Mix_CloseAudio();
}

Mix_Music *PlaySong(const char *file)
{
  Mix_Music *music = Mix_LoadMUS(file);
  if (music == NULL)
  {
    HANDLE_ERROR("MUSIC LOAD");
  }
  Mix_PlayMusic(music, -1);
  return music;
}

void EndSong(Mix_Music *music)
{
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

Mix_Chunk *InitChunk(const char *file)
{
  Mix_Chunk *chunk = Mix_LoadWAV(file);
  if (chunk == NULL)
  {
    HANDLE_ERROR("CHUNK INIT");
  }
  return chunk;
}

void EndChunk(Mix_Chunk *chunk)
{
  Mix_HaltChannel(-1);
  Mix_FreeChunk(chunk);
}