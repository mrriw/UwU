#include "UvU.h"



U4 UvU::add(STR nm) {    
  for (int i = 0; i < names.size(); i++)
    if (names[i] == nm)
      return i;

  STR loc = V_DIR + nm + V_EXT;
  
  SDL_AudioSpec spec;
  Uint8* wav;
  Uint32 len;
  if (!SDL_LoadWAV(loc.c_str(), &spec, &wav, &len)) 
    { DBG(("UvU: " + nm + " not found")) return 0; };
    
  U4 vid = (U4)specs.size();
  
  names.push_back(nm);
  specs.push_back(spec);
  wavs.push_back(wav);
  lens.push_back(len);
  
  return vid;
}

void UvU::play(U4 vid) {
  SDL_AudioStream* stream = SDL_CreateAudioStream(&specs[vid], NULL);

  if (!SDL_BindAudioStream(audioDevice, stream))
    return;

  SDL_PutAudioStreamData(stream, wavs[vid], lens[vid]);

  stweams.push_back(stream);
  shQueu.push_back(0);
}


UvU::UvU() {
    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    
    // default
    add("PGW");
}

void UvU::ewnt(SDL_Event* e) {
  
}

void UvU::itwt() {
  std::vector<size_t> to_clean;
  for (size_t i = 0; i < stweams.size(); i++) {
    int queu = SDL_GetAudioStreamQueued(stweams[i]);
    if (queu == shQueu[i]) {
      SDL_DestroyAudioStream(stweams[i]);
      to_clean.push_back(i); }
    shQueu[i] = queu; }

  for (int i = to_clean.size() - 1; i >= 0; i--) {
    stweams.erase(stweams.begin() + to_clean[i]);
    shQueu.erase(shQueu.begin() + to_clean[i]); }
}

UvU::~UvU() {
  for (int i = stweams.size() - 1; i >= 0; i--) {
    SDL_DestroyAudioStream(stweams[i]);
    stweams.erase(stweams.begin() + i);
    shQueu.erase(shQueu.begin() + i); } 
}




/*
void Sound::clean() {

	if (m_repeating) {
		for (size_t i = 0; i < stweams.size(); i++) {
			if (SDL_GetAudioStreamQueued(stweams[i]) < m_wav_data_len)
				SDL_PutAudioStreamData(stweams[i], m_wav_data, (int)m_wav_data_len);
		}

		return;
	}
	

}
*/
