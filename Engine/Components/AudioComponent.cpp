#include "AudioComponent.h"
#include "Engine.h"


namespace Ethrl
{
	AudioComponent::~AudioComponent()
	{
		Stop();
	}

	void AudioComponent::Initialize()
	{
		if (play_on_start)
		{
			Play();
		}
	}

	void AudioComponent::Update()
	{
	}

	void AudioComponent::Play()
	{
		m_channel.Stop();
		m_channel = g_audioSystem.PlayAudio(sound_name, volume, pitch, loop);
	}

	void AudioComponent::Stop()
	{
		m_channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, sound_name);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, play_on_start);
		READ_DATA(value, loop);

		g_audioSystem.AddAudio(sound_name, sound_name);

		return true;
	}
}

