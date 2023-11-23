#pragma once

#include "AudioManager.h"


struct AudioId
{
	AudioId(const std::string& _audioPath, const glm::vec3& _position)
		: audioPath(_audioPath), modelPosition(_position)
	{
	}

	std::string audioPath;
	glm::vec3 modelPosition;
};
class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();

	void LoadAudios();
	void LoadModelAudio(const glm::vec3& modelPosition);
	void LoadModelAudio(AudioId& audio);
	void PlayAudio(AudioId& audio);
	void SetVolume(AudioId& audio, const float& volume);
	void UpdateListenerPosition(const glm::vec3& camPos, const glm::vec3& camFront, const glm::vec3 camUp , const float& ModelposX);

	void AddPolygonToManager(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3 scale = { 1.0f,1.0f,1.0f });
	void AddPolygonToManagerWithRotation(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3 scale = { 1.0f,1.0f,1.0f }, const glm::vec3 up = { 0.0f,1.0f,0.0f }, const glm::vec3 forward = {0.0f,0.0f,1.0f} );




	void AddDSP(const char* audioPath);
	void SetDSP(const char* audioPath);

	void UpdatePositionOnChannel(AudioId& audio, const glm::vec3 position);


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


	glm::vec3 m_Velocity;
};

