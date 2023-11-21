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
	_result = _system->init(1,FMOD_INIT_NORMAL,nullptr);
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
}

void AudioManager::LoadSound(const char* audioFilePath)
{
	//Adding Sounds to list
	    FMOD::Sound* newSound=nullptr;
		AddAudioSource(audioFilePath, newSound);
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
void AudioManager::PlaySound(const char* audioFileName)
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