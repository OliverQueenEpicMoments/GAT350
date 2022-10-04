#include "AudioChannel.h"
#include "fmod.hpp"

namespace Ethrl
{
	bool AudioChannel::IsPlaying()
	{
		if (m_channel == nullptr) return false;

		bool isPlaying;
		m_channel->isPlaying(&isPlaying);

		return isPlaying;
	}

	void AudioChannel::Stop()
	{
		if (IsPlaying()) m_channel->stop();
	}

	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying()) m_channel->setPitch(pitch);
	}

	float AudioChannel::GetPitch()
	{
		float pitch = 0;
		if (IsPlaying()) m_channel->getPitch(&pitch);
		
		return pitch;
	}

	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying()) m_channel->setVolume(volume);
	}

	float AudioChannel::GetVolume()
	{
		float volume = 0;
		if (IsPlaying()) m_channel->getVolume(&volume);

		return volume;
	}
}