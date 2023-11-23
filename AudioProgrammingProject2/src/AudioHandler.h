#pragma once

#include "AudioManager.h"

enum  DSPType
{
	REVERB = 0,
	LOWPASS = 1,
	HIGHPASS = 2,
	DISTORTION = 3,
	CHORUS = 4

};

struct AudioId
{
	AudioId(const std::string& _audioPath, const glm::vec3& _position)
		: audioPath(_audioPath), modelPosition(_position)
	{
	}

	void setOrder(int layer1,int layer2, int layer3, int layer4, int layer5)
	{
		order[0] = layer1;
		order[1] = layer2;
		order[2] = layer3;
		order[3] = layer4;
		order[4] = layer5;
	}
	float setVolume(float _volume) 
	{
		this->volume = _volume;
		return volume;
	}
	std::string audioPath;
	glm::vec3 modelPosition;
	float volume = 1.0f;
	int order[5] = { REVERB,LOWPASS,HIGHPASS,DISTORTION,CHORUS };
};




class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();

	void LoadAudios();
	void LoadModelAudio(const glm::vec3& modelPosition);
	void LoadModelAudio(AudioId& audio, bool isLooping = true);
	void PlayAudio(AudioId& audio);
	void SetVolume(AudioId& audio, const float& volume);
	void UpdateListenerPosition(const glm::vec3& camPos, const glm::vec3& camFront, const glm::vec3 camUp , const float& ModelposX);

	void AddPolygonToManager(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3 scale = { 1.0f,1.0f,1.0f });
	void AddPolygonToManagerWithRotation(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3 scale = { 1.0f,1.0f,1.0f }, const glm::vec3 up = { 0.0f,1.0f,0.0f }, const glm::vec3 forward = {0.0f,0.0f,1.0f} );




	void AddDSP(const char* audioPath);
	void AddDSPBasedOnTypeAndOrder(const char* audioPath, const DSPType& type, const int order);
	void SetDSP(const char* audioPath);
	void SetDSPBasedOnType(const char* audioPath, const DSPType& type,  float& value,  float value2 = 1.0f,  float value3 = 1.0f);

	void UpdatePositionOnChannel(AudioId& audio, const glm::vec3 position, const glm::vec3 velocity = {1,1,1});


	float gDecayValue = .1f;
	float gDensityValue = 1.5f;
	float gDiffusionValue = 0.5f;

	float gLowPassValue = 500.f;
	float gHighPassValue = 5000.f;

	float gDistortionValue = 0.9f;

	float gChorusMixValue = 500.f;
	float gChorusRateValue = 1.0f;
	float gChorusDepthValue = 7.f;

	AudioManager* audioManager;
private:


	std::string audioPath;


	glm::vec3 m_Velocity = {0,0 ,0 };
};

