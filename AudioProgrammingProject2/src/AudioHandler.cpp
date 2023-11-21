#include "AudioHandler.h"

AudioHandler::AudioHandler()
{
	audioManager = new AudioManager();
	audioManager->Initialize();
}

AudioHandler::~AudioHandler()
{
	audioManager->Destroy();
}

void AudioHandler::LoadAudios()
{
	audioPath = "Audio/boss.mp3";
	audioManager->Load3DAudio(audioPath.c_str());

	audioManager->Play3DAudioSound(audioPath.c_str());

	AddDSP(audioPath.c_str());
}

void AudioHandler::LoadModelAudio(const glm::vec3& modelPosition)
{
	audioPath = "Audio/boss.mp3";
	audioManager->Load3DAudio(audioPath.c_str());
	audioManager->SetSoundPosition(modelPosition);
	audioManager->Play3DAudioSound(audioPath.c_str());

	AddDSP(audioPath.c_str());
}

void AudioHandler::LoadModelAudio(AudioId& audio)
{
	audioManager->Load3DAudio(audio.audioPath.c_str());
	audioManager->SetSoundPosition(audio.modelPosition);

	AddDSP(audio.audioPath.c_str());
}

void AudioHandler::PlayAudio(AudioId& audio)
{
	audioManager->Play3DAudioSound(audio.audioPath.c_str());
}

void AudioHandler::UpdatePosition(const glm::vec3& camPos, const glm::vec3& camFront, const glm::vec3 camUp, const float& ModelposX)
{
	audioManager->SetListenerAttributes(camPos, m_Velocity, camFront, camUp);

//	SetDSP(audioPath.c_str());

	audioManager->Update();
}

void AudioHandler::AddPolygonToManager(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3 scale)
{
	int result = audioManager->AddPolygon(direct, reverb, doublesided, vertices, position, scale);

	if (result == -1)
	{
		std::cout << "Error in addPolygon in AudiHandler..  " << std::endl;
	}
}

void AudioHandler::AddDSP(const char* audioPath)
{
	audioManager->AddReverbFilterOnChannel(0, audioPath);
	audioManager->AddLowPassFilterOnChannel(1, audioPath);
	audioManager->AddHighPassFilterOnChannel(2, audioPath);
	audioManager->AddDistortionFilterOnChannel(3, audioPath);
	audioManager->AddChorusPassOnChannel(4, audioPath);
}

void AudioHandler::SetDSP(const char* audioPath)
{
	audioManager->SetReverbValuesOnChannel(audioPath, gDecayValue, gDensityValue, gDiffusionValue);
	audioManager->SetLowPassFilterValuesOnChannel(audioPath, gLowPassValue);
	audioManager->SetHighPassFilterValuesOnChannel(audioPath, gHighPassValue);
	audioManager->SetDistortionLevelFilterValuesOnChannel(audioPath, gDistortionValue);
	audioManager->SetChorusPassValuesOnChannel(audioPath,gChorusMixValue, gChorusRateValue, gChorusDepthValue);
}
