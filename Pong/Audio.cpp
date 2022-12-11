#include "Audio.hpp"

Audio* Audio::m_audio = nullptr;

Audio::Audio()
{
    m_effects_paths[0] = "../res/sounds/effects/hit_paddle.wav";

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        m_audio_opened = false;

        throw Mix_GetError();
    }
    else
    {
        //loadMusics();
        loadEffects();

        m_audio_opened = true;
    }
}

Audio::~Audio()
{
    if (m_audio_opened) {
        Mix_CloseAudio();
    }
}

void Audio::loadMusics()
{
    for (size_t i = 0; i < m_musics.size(); i++) {

        m_musics[i] = Mix_LoadMUS(m_music_path[i].c_str());
        if (m_musics[i] == nullptr)
        {
            throw Mix_GetError();
        }
    }
}

void Audio::loadEffects()
{
    for (size_t i = 0; i < m_effects.size(); i++)
    {
        m_effects[i] = Mix_LoadWAV(m_effects_paths[i].c_str());
        if (m_effects[i] == nullptr)
        {
            throw Mix_GetError();
        }
    }
}

Audio* Audio::GetInstance()
{
	if (m_audio == nullptr) {
		m_audio = new Audio();
	}
	return m_audio;
}

void Audio::PlayMusic(Music _music_type, const int& _loop_flag)
{
    if (m_audio_opened) {
        Mix_Music* music = nullptr;

        switch (_music_type)
        {
        case Music::music_1: {
            music = m_musics[0];
            break;
        }
        default: {

            break;
        }
        }

        if (Mix_PlayMusic(music, _loop_flag) != -1)
        {
            //success
        }
        else
        {
            throw Mix_GetError();
        }
    }
}

void Audio::PlayEffect(EffectType _effect_type)
{
    if (m_audio_opened) {
        Mix_Chunk* effect = nullptr;

        switch (_effect_type)
        {
        case EffectType::hit_paddle: {
            effect = m_effects[0];
            break;
        }
        //case EffectType::score_up: {
        //    effect = m_effects[1];
        //    break;
        //}
        //case EffectType::ball_speed: {
        //    effect = m_effects[2];
        //    break;
        //}
        default: {

            break;
        }
        }

        if (Mix_PlayChannel(-1, effect, 0) != -1)
        {
            //success
        }
        else
        {
            throw Mix_GetError();
        }
    }
}