#include "Robot_Sounds.h"


Robot_Sounds::Robot_Sounds() {
	workingDir = findWorkingDir();
	loadSound();
}

void Robot_Sounds::loadSound()
{
	//Loading success flag
	bool success = true;

	thrusterOn = Mix_LoadWAV((workingDir + "../Dependencies/assets/sound/thrusterFire.wav").c_str());
	if (thrusterOn == NULL)
	{
		printf("Failed to load thrusterOn effect! SDL_mixer Error: %s\n", Mix_GetError());

	}
	thrusterPowerDown = Mix_LoadWAV((workingDir + "../Dependencies/assets/sound/thrusterPowerDown1.wav").c_str());
	std::cout << workingDir << std::endl;
	if (thrusterPowerDown == NULL)
	{
		printf("Failed to load thrusterPowerDown sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}
}

void Robot_Sounds::turnThrusterOn() {
	Mix_PlayChannel(1, thrusterOn, 0);
}
void Robot_Sounds::turnThrusterOff() {
	Mix_HaltChannel(1);
	Mix_PlayChannel(-1, thrusterPowerDown, 0);
}


void Robot_Sounds::pauseThruster() {
	Mix_Pause(1);
}
void Robot_Sounds::resumeThruster() {
	Mix_Resume(1);

}


std::string Robot_Sounds::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}