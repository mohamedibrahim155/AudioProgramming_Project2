#include "AudioManager.h"
#include "ErrorHandler.h"



static FMOD_RESULT F_CALLBACK SoundEndCallback(FMOD_CHANNELCONTROL* channelControl, FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void* commandData1, void* commandData2) {
	std::cout << "Sound has ended." << std::endl;
	// You can perform actions here when the sound ends
	return FMOD_OK;
}

void AudioManager::Initialize()
{
	//Creating a FMOD system
	_result = FMOD::System_Create(&_system);
	if (_result!=FMOD_OK)
	{
		std::cout << "Error : Failed to create FMOD system : " << std::endl;
		return;
	}
	//Initializing a FMOD 
	_result = _system->init(10,FMOD_INIT_NORMAL,nullptr);
	if (_result!=FMOD_OK)
	{
		std::cout << "Error : Failed to Iniitialize system " << std::endl;

		_result = _system->close();
		if (_result !=FMOD_OK)
		{
			std::cout << "Error : Failed to Close the system" << std::endl;
		}
		return;
	}

	_result = _system->setGeometrySettings(2000.0f); /// SET GEOMENTRY
	if (_result != FMOD_OK)
	{
		std::cout << "Error : Failed to setGeomentry system " << std::endl;

		_result = _system->close();
		if (_result != FMOD_OK)
		{
			std::cout << "Error : Failed to Close the system" << std::endl;
		}
		return;
	}
	//_result = _system->createGeometry(200, 800, &m_Geometry);  ///CREATE GEOMENTRY

	if (_result != FMOD_OK)
	{
		std::cout << "Error : Failed to Create geomentry system " << std::endl;

		_result = _system->close();
		if (_result != FMOD_OK)
		{
			std::cout << "Error : Failed to Close the system" << std::endl;
		}
		return;
	}


}

void AudioManager::LoadSound(const char* audioFilePath)
{
	//Adding Sounds to list
	    FMOD::Sound* newSound=nullptr;
		AddAudioSource(audioFilePath, newSound);
}

void AudioManager::Load3DAudio(const char* file)
{
	FMOD::Sound* newSound = nullptr;
	Add3DAudioSource(file, newSound);

	FMOD_MODE mode = FMOD_3D | FMOD_LOOP_NORMAL;
	_result = _system->createSound(file, mode, 0, &LoadedAudioList[file].audio);   //Create Sound based on stream type
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to createSound in the allocated filePath  " << std::endl;
		return;
	}

	LoadedAudioList[file].audio->set3DMinMaxDistance(MIN_DISTANCE, MAX_DISTANCE); // SETTING MIN MAX for 3D audio
}

void AudioManager::SetIsStreaming(bool isStreaming)
{
	//Sets audio streaming or not, so user can access
	this->isStreaming = isStreaming;
	
}

void AudioManager::SetIsAudioLooping(bool isLooping)
{
	//Sets audio looping or not, so user can access
	this->isLooping = isLooping;
	
}
void AudioManager::PlaySoundFile(const char* audioFileName)
{
	FMOD_MODE mode = isStreaming ? FMOD_CREATESTREAM : FMOD_DEFAULT;
	_result = _system->createSound(audioFileName, mode, 0, &LoadedAudioList[audioFileName].audio);   //Create Sound based on stream type
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to createSound in the allocated filePath  " << std::endl;
		return;
	}

	if (LoadedAudioList.find(audioFileName)!=LoadedAudioList.end())
	{

		_result = _system->playSound(LoadedAudioList[audioFileName].audio, 0, false, &LoadedAudioList[audioFileName].mychannel->channel); //playing audio in the loaded list

		if (_result != FMOD_OK) {
			std::cout << "Failed to set loop mode: " << std::endl;
			return;
		}
		if (_result!=FMOD_OK)
		{
			std::cout << "Error : Failed to play the sound";
			FMODError(_result, __FILE__, __LINE__);
			_result = LoadedAudioList[audioFileName].audio->release();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to release in Play()   " << std::endl;

			}
			_result = _system->close();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to close system in Play()   " << std::endl;

			}

			_result = _system->release();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to release system  in Play()   " << std::endl;
			}
			return;
		}

		
		FMOD_MODE mode = isLooping ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
		if (IsChannelPlaying(audioFileName))
		{
			_result = LoadedAudioList[audioFileName].mychannel->channel->setMode(mode);				//Looping audio in the channel based on bool
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to loopSound in the allocated filePath  " << std::endl;
				return;
			}
		}
		
	}
}

void AudioManager::Play3DAudioSound(const char* audioFileName)
{


	if (LoadedAudioList.find(audioFileName) != LoadedAudioList.end())
	{

		_result = _system->playSound(LoadedAudioList[audioFileName].audio, 0, false, &LoadedAudioList[audioFileName].mychannel->channel); //playing audio in the loaded list

		if (_result != FMOD_OK) {
			std::cout << "Failed to set loop mode: " << std::endl;
			return;
		}
		if (_result != FMOD_OK)
		{
			std::cout << "Error : Failed to play the sound";
			FMODError(_result, __FILE__, __LINE__);
			_result = LoadedAudioList[audioFileName].audio->release();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to release in Play()   " << std::endl;

			}
			_result = _system->close();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to close system in Play()   " << std::endl;

			}

			_result = _system->release();
			if (_result != FMOD_OK)
			{
				FMODError(_result, __FILE__, __LINE__);
				std::cout << "Error: Failed to release system  in Play()   " << std::endl;
			}
			return;
		}

		//SetListenerAttributes(glm::vec3(0), glm::vec3(0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
		 soundVel = { 0.f, 0.f, 0.f };

		_result = LoadedAudioList[audioFileName].mychannel->channel->set3DAttributes(&soundPos, &soundVel);
		if (_result != FMOD_OK)
		{
			FMODError(_result, __FILE__, __LINE__);
			std::cout << "Failed to Play3DAudioSound set3DAttributes : " << std::endl;
			return;
		}

	}
}



//Add and sets audio path in a dictionary
void AudioManager::AddAudioSource(const char* audioFilePath, FMOD::Sound* sound)
{
	AudioSource source;
	source.pathName = audioFilePath;
	source.audio = sound;
	source.mychannel = new MyChannel;
	source.mychannel->channel = nullptr;
	source.mychannel->channel->setPitch(source.mychannel->pitch);
	source.mychannel->channel->setVolume(source.mychannel->volume);
	source.mychannel->channel->setPan(source.mychannel->pan);
	LoadedAudioList[audioFilePath] = source;
}

void AudioManager::Add3DAudioSource(const char* _audioFilePath, FMOD::Sound* _sound)
{
	AudioSource source;
	source.pathName = _audioFilePath;
	source.audio = _sound;
	source.mychannel = new MyChannel;
	source.mychannel->channel = nullptr;
	source.mychannel->channel->setPitch(source.mychannel->pitch);
	source.mychannel->channel->setVolume(source.mychannel->volume);
	source.mychannel->channel->setPan(source.mychannel->pan);
	LoadedAudioList[_audioFilePath] = source;
}

void AudioManager::AddReverbFilterOnChannel(int soundLayer, const char* _audioFilePath)
{

	_result = _system->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &m_ReverbDSP);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddReverbFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			m_ReverbDSP_layer = soundLayer;
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(soundLayer, m_ReverbDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call AddReverbFilterOnChannel() " << std::endl;
	}
}

void AudioManager::AddLowPassFilterOnChannel(int soundLayer, const char* _audioFilePath)
{
	_result = _system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &m_LowPassDSP);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddLowPassFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	//_result = m_LowPassDSP->setParameterFloat(FMOD_DSP_LOWPASS_CUTOFF, 5000); // SETTING DEFAULT VALUES
	
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddLowPassFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			m_LowPassDSP_layer = soundLayer;
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(soundLayer, m_LowPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call AddLowPassFilterOnChannel() " << std::endl;
	}
}

void AudioManager::AddHighPassFilterOnChannel(int soundLayer, const char* _audioFilePath)
{
	_result = _system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &m_HighPassDSP);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddHighPassFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	//_result = m_HighPassDSP->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, 500); // SETTING DEFAULT VALUES

	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddHighPassFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			m_HighPassDSP_layer = soundLayer;
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(soundLayer, m_HighPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call AddHighPassFilterOnChannel() " << std::endl;
	}
}

void AudioManager::AddDistortionFilterOnChannel(int soundLayer, const char* _audioFilePath)
{
	_result = _system->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &m_DistortionDSP);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddDistortionFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
//	_result = m_DistortionDSP->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 1.0f); // SETTING DEFAULT VALUES

	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddDistortionFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			m_DistortionDSP_layer = soundLayer;
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(soundLayer, m_DistortionDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call AddDistortionFilterOnChannel() " << std::endl;
	}
}

void AudioManager::AddChorusPassOnChannel(int soundLayer, const char* _audioFilePath)
{
	_result = _system->createDSPByType(FMOD_DSP_TYPE_CHORUS, &m_ChorusPassDSP);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddDistortionFilterOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	//_result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_MIX, 50.f); // SETTING DEFAULT VALUES
	//_result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_RATE, 0.8f); // SETTING DEFAULT VALUES
	//_result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_DEPTH, 3.f); // SETTING DEFAULT VALUES

	
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			m_ChorusPassDSP_layer = soundLayer;
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(soundLayer, m_ReverbDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call AddDistortionFilterOnChannel() " << std::endl;
	}
}

void AudioManager::SetReverbValuesOnChannel(const char* _audioFilePath, float& decay, float& density, float& diffusion)
{
	FMOD_RESULT result;

	// Concert Hall, settings, decay 3900ms, density, diffusion set to 100

	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DECAYTIME, decay);
	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DENSITY, density);
	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DIFFUSION, diffusion);

	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetReverbValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(m_ReverbDSP_layer, m_ChorusPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetReverbValuesOnChannel() " << std::endl;
	}

}

void AudioManager::SetLowPassFilterValuesOnChannel(const char* _audioFilePath, float& limit)
{
	FMOD_RESULT result = m_LowPassDSP->setParameterFloat(FMOD_DSP_LOWPASS_CUTOFF, limit);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetLowPassFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}

	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(m_LowPassDSP_layer, m_LowPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetLowPassFilterValuesOnChannel() " << std::endl;
	}
}

void AudioManager::SetHighPassFilterValuesOnChannel(const char* _audioFilePath, float& limit)
{
	FMOD_RESULT result = m_HighPassDSP->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, limit);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetHighPassFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}

	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(m_HighPassDSP_layer, m_HighPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetHighPassFilterValuesOnChannel() " << std::endl;
	}
}

void AudioManager::SetDistortionLevelFilterValuesOnChannel(const char* _audioFilePath, float& level)
{
	FMOD_RESULT result = m_DistortionDSP->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, level);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetDistortionLevelFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}

	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(m_DistortionDSP_layer, m_DistortionDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetDistortionLevelFilterValuesOnChannel() " << std::endl;
	}
}

void AudioManager::SetChorusPassValuesOnChannel(const char* _audioFilePath, float& mix, float& rate, float& depth)
{
	FMOD_RESULT result;
	result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_MIX, mix);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetDistortionLevelFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_RATE, rate);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetDistortionLevelFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}
	result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_CHORUS_DEPTH, depth);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetDistortionLevelFilterValuesOnChannel in the allocated filePath  " << std::endl;
		return;
	}

	if (LoadedAudioList.find(_audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[_audioFilePath].mychannel)
		{
			LoadedAudioList[_audioFilePath].mychannel->channel->addDSP(m_ChorusPassDSP_layer, m_ChorusPassDSP);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetDistortionLevelFilterValuesOnChannel() " << std::endl;
	}
}

void AudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
{
	FMOD_VECTOR fmodPosition;
	FMOD_VECTOR fmodVelocity;
	FMOD_VECTOR fmodForward;
	FMOD_VECTOR fmodUp;

	GLMToFMOD(position, fmodPosition);
	GLMToFMOD(velocity, fmodVelocity);
	GLMToFMOD(forward, fmodForward);
	GLMToFMOD(up, fmodUp);

	FMOD_RESULT result = _system->set3DListenerAttributes(0, &fmodPosition, &fmodVelocity, &fmodForward, &fmodUp);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to SetListenerAttributes in the allocated filePath  " << std::endl;
		return;
	}


	float direct, reverb;
	FMOD_VECTOR origin;

	GLMToFMOD(glm::vec3(0.f), origin);
	_system->getGeometryOcclusion(&origin, &fmodPosition, &direct, &reverb);
	printf("ListenerPosition: %.2f, %.2f, %.2f | direct: %.4f, reverb: %.4f\n", position.x, position.y, position.z, direct, reverb);
}

void AudioManager::GLMToFMOD(const glm::vec3& in, FMOD_VECTOR& out)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}
void AudioManager::FMODToGLM(const FMOD_VECTOR& in, glm::vec3& out)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}

int AudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position, const glm::vec3& scale)
{
	
	int index;
	_result = _system->createGeometry(200, 800, &m_Geometry);  ///CREATE GEOMENTRY
	// Add the polygon
	int numVertices = vertices.size();
	FMOD_VECTOR* fmodVertices = (FMOD_VECTOR*)malloc(sizeof(FMOD_VECTOR) * numVertices);
	for (int i = 0; i < numVertices; i++) {
		GLMToFMOD(vertices[i].Position, fmodVertices[i]);
	}

	_result = m_Geometry->addPolygon(direct, reverb, doublesided, numVertices, fmodVertices, &index);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddPolygon in the allocated filePath  " << std::endl;
		return -1;
	}

	// Set the position
	FMOD_VECTOR fmodPosition;
	GLMToFMOD(position, fmodPosition);
	_result = m_Geometry->setPosition(&fmodPosition);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddPolygon -> setPosition in the allocated filePath  " << std::endl;
		return-1;
	}

	FMOD_VECTOR fmodScale;
	GLMToFMOD(scale, fmodScale);
	_result = m_Geometry->setScale(&fmodScale);
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		std::cout << "Error: Failed to AddPolygon -> setScale in the allocated filePath  " << std::endl;
		return-1;
	}

	

	m_Geometry->setActive(true);

	return index;
}

void AudioManager::SetSoundPosition(const glm::vec3& modelPosition)
{
	GLMToFMOD(modelPosition, soundPos);
}

// Pause audio based on the file name ( if the file exist in the dictionary)
void AudioManager::PauseSound(const char* audioFileName)
{
	if (LoadedAudioList.find(audioFileName) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFileName].mychannel)
		{
			_result = LoadedAudioList[audioFileName].mychannel->channel->setPaused(true);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call PauseSound() " << std::endl;
	}
}

// Resume audio based on the file name ( if the file exist in the dictionary)
void AudioManager::ResumeSound(const char* audioFileName)
{
	if (LoadedAudioList.find(audioFileName) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFileName].mychannel)
		{
			_result = LoadedAudioList[audioFileName].mychannel->channel->setPaused(false);	
		}	
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call ResumeSound() " << std::endl;
	}
}

// Stop audio based on the file name ( if the file exist in the dictionary)
void AudioManager::StopSound(const char* audioFileName)
{
	if (LoadedAudioList.find(audioFileName) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFileName].mychannel)
		{
				_result = LoadedAudioList[audioFileName].mychannel->channel->stop();
				_result = LoadedAudioList[audioFileName].audio->release();
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call StopSound() " << std::endl;
	}
}

// Set Pitch audio based on the file name ( if the file exist in the dictionary)
void  AudioManager:: SetPitch(const char* audioFilePath, float pitch)
{
	if (LoadedAudioList.find(audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFilePath].mychannel)
		{
				_result = LoadedAudioList[audioFilePath].mychannel->channel->setPitch(pitch);

			
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetPitch() " << std::endl;
	}
}

// Set Volume audio based on the file name ( if the file exist in the dictionary)
void  AudioManager::SetVolume(const char* audioFilePath, float volume)
{
	if (LoadedAudioList.find(audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFilePath].mychannel)
		{
				_result = LoadedAudioList[audioFilePath].mychannel->channel->setVolume(volume);
		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetVolume() " << std::endl;
	}
}


// Set Pan audio based on the file name ( if the file exist in the dictionary)
void  AudioManager::SetPan(const char* audioFilePath, float pan)
{
	if (LoadedAudioList.find(audioFilePath) != LoadedAudioList.end())
	{
		if (LoadedAudioList[audioFilePath].mychannel)
		{
			_result = LoadedAudioList[audioFilePath].mychannel->channel->setPan(pan);

		}
	}
	else
	{
		std::cout << "Error : audioFile does not exist to call SetPan() " << std::endl;
	}
}

// return   channel is Playing 
bool  AudioManager::IsChannelPlaying(FMOD_RESULT result, FMOD::Channel* currentChannel)
{
	bool isPlaying;
	result = currentChannel->isPlaying(&isPlaying);

	if (result!=FMOD_OK)
	{
		std::cout << "Error: failed to find if the channel is playing" << std::endl;
		return false;
	}
	
	std::cout << " is playing " << isPlaying<<std::endl;
	return isPlaying;
}

// return   channel is Playing 
bool AudioManager:: IsChannelPlaying(const char* audioFilePath)
{
	bool isPlaying;

	if (LoadedAudioList.find(audioFilePath) == LoadedAudioList.end())
	{
		return false;
	}
	if (!LoadedAudioList[audioFilePath].mychannel )
	{	
		return false;
	}
	if (!LoadedAudioList[audioFilePath].mychannel->channel)
	{
		return false;
	}
	 _result = LoadedAudioList[audioFilePath].mychannel->channel->isPlaying(&isPlaying);

	if (_result != FMOD_OK)
	{	
		return false;
	}
	return isPlaying;
}

// return   channel is Paused 
bool AudioManager::IsChannelPaused(const char* audioFilePath)
{
	bool isPaused;

	if (LoadedAudioList.find(audioFilePath) == LoadedAudioList.end())
	{
		
		return false;
	}
	if (!LoadedAudioList[audioFilePath].mychannel)
	{
		return false;
	}
	if (!LoadedAudioList[audioFilePath].mychannel->channel)
	{
		return false;
	}

	_result = LoadedAudioList[audioFilePath].mychannel->channel->getPaused(&isPaused);

	if (_result != FMOD_OK)
	{
		return false;
	}
	return isPaused;
}

//returns Total audio length
unsigned int  AudioManager::GetAudioLength(const char* audioFilePath)
{
	unsigned int soundLengthMs = 0;

	if (LoadedAudioList[audioFilePath].audio)
	{
		LoadedAudioList[audioFilePath].audio->getLength(&soundLengthMs, FMOD_TIMEUNIT_MS);

	}
	return soundLengthMs;
}
//returns current audio position
unsigned int  AudioManager::GetCurrentAudioPosition(const char* audioFilePath)
{
	unsigned int posiiton = 0;

	if (LoadedAudioList[audioFilePath].audio)
	{
		LoadedAudioList[audioFilePath].mychannel->channel->getPosition(&posiiton, FMOD_TIMEUNIT_MS);
		
	}
	return posiiton;
}

//update audio
void AudioManager::Update()
{

	_result = _system->update();
	if (_result != FMOD_OK)
	{
		FMODError(_result, __FILE__, __LINE__);
		Destroy();
		return;
	}
}


void AudioManager::Destroy()
{
	for (std::map<const char*, AudioSource>::iterator it = LoadedAudioList.begin(); it != LoadedAudioList.end(); ++it)
	{
		it->second.audio->release();
		 it->second.audio=nullptr;
	   if (it->second.mychannel)
	   {
	       it->second.mychannel->channel->stop();

	       delete it->second.mychannel;
	   }
	}
	
	if (_system)
	{
		_system->release();
		_system = nullptr;
	}
}


AudioManager:: ~AudioManager()
{
	Destroy();
	std::cout << "Destroying files in audimanager" << std::endl;
}