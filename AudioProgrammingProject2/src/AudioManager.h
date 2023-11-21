#pragma once
#include <fmod.hpp>
#include<iostream>
#include<vector>
#include <map>
#include"ErrorHandler.h"
#include<glm/glm.hpp>
#include "Vertex.h"
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
	void Load3DAudio(const char* file);

	void Update();


	void PlaySoundFile(const char* _audioFilePath);
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


	void Play3DAudioSound(const char* _audioFilePath);
	void Add3DAudioSource(const char* _audioFilePath, FMOD::Sound* _sound);

	void AddReverbFilterOnChannel(int soundLayer,const char* _audioFilePath);
	void AddLowPassFilterOnChannel(int soundLayer,const char* _audioFilePath);
	void AddHighPassFilterOnChannel(int soundLayer,const char* _audioFilePath);
	void AddDistortionFilterOnChannel(int soundLayer,const char* _audioFilePath);
	void AddChorusPassOnChannel(int soundLayer,const char* _audioFilePath);


	void SetReverbValuesOnChannel(const char* _audioFilePath, float& decay, float& density, float& diffusion);
	void SetLowPassFilterValuesOnChannel(const char* _audioFilePath, float& limit);
	void SetHighPassFilterValuesOnChannel(const char* _audioFilePath, float& limit);
	void SetDistortionLevelFilterValuesOnChannel(const char* _audioFilePath, float& level);
	void SetChorusPassValuesOnChannel(const char* _audioFilePath, float& mix, float& rate, float& depth);

	void SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up);

	void GLMToFMOD(const glm::vec3& in, FMOD_VECTOR& out);
	void FMODToGLM(const FMOD_VECTOR& in, glm::vec3& out);


	void SetSoundPosition(const glm::vec3& modelPosition);
	void SetPositionAttributeonChannel(const char* audioFilename, const glm::vec3& position);

	int AddPolygon(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3& scale);


private:
	FMOD::System* _system = nullptr;
	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;
	FMOD_RESULT _result;
	FMOD::Geometry* m_Geometry;


	bool isStreaming;
	bool isLooping;
	std::map<const char*, AudioSource> LoadedAudioList;
	bool IsChannelPlaying(FMOD_RESULT result, FMOD::Channel* currentChannel);

	

	FMOD::DSP* m_ReverbDSP;
	FMOD::DSP* m_HighPassDSP;
	FMOD::DSP* m_LowPassDSP;
	FMOD::DSP* m_DistortionDSP;
	FMOD::DSP* m_ChorusPassDSP;

	 float MIN_DISTANCE= 0.5f;
	 float MAX_DISTANCE= 10.f;


	 int m_ReverbDSP_layer;
	 int m_HighPassDSP_layer;
	 int m_LowPassDSP_layer;
	 int m_DistortionDSP_layer;
	 int m_ChorusPassDSP_layer;

	 FMOD_VECTOR soundPos = { 0.f, 0.f, 0.f };
	 FMOD_VECTOR soundVel = { 0.f, 0.f, 0.f };

};

