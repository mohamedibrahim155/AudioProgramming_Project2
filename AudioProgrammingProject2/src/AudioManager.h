#pragma once
#include <../fmod/include/fmod.hpp>
#include<iostream>
#include<vector>
#include <map>
#include"ErrorHandler.h"

struct MyChannel
{	
	FMOD::Channel* channel=nullptr;
	float volume=1.0f;
	float pitch=1.0f;
	float pan=0.0f;

};
struct AudioSource
{
	const char* pathName;
	FMOD::Sound* audio;
	MyChannel* mychannel;
};




class AudioManager
{
public:

	~AudioManager();

	void Initialize();
	void Destroy();

	void LoadSound(const char* _audioFilePath);
	void Update();


	void PlaySound(const char* _audioFilePath);
	void AddAudioSource(const char* _audioFilePath,FMOD::Sound* _sound);
	void PauseSound(const char* _audioFilePath);
	void ResumeSound(const char* _audioFilePath);
	void StopSound(const char* _audioFilePath);
	void SetPitch(const char* _audioFilePath, float _pitch);
	void SetVolume(const char* _audioFilePath, float _volume);
	void SetPan(const char* _audioFilePath, float pan);
	bool IsChannelPlaying(const char* _audioFilePath);
	bool IsChannelPaused(const char* _audioFilePath);
	unsigned int  GetAudioLength(const char* _audioFilePath);
	unsigned int  GetCurrentAudioPosition(const char* _audioFilePath);
	void SetIsStreaming(bool _isStreaming);
	void SetIsAudioLooping(bool _isLooping);

private:
	FMOD::System* _system = nullptr;
	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;
	FMOD_RESULT _result;
	bool isStreaming;
	bool isLooping;
	std::map<const char*, AudioSource> LoadedAudioList;
	bool IsChannelPlaying(FMOD_RESULT result, FMOD::Channel* currentChannel);

};

