#include "ErrorHandler.h"
void FMODError(FMOD_RESULT _result, const char* _file, int _line)
{
	std::cout << "FMOD Error [" << static_cast<int>(_result) << "]: '" << _file << "' at " << _line << std::endl;
}

