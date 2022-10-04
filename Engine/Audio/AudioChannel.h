#pragma once

namespace FMOD
{
	// ! forward declare FMOD Channel
	class Channel;
}

namespace Ethrl
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		float GetPitch();

		void SetVolume(float volume);
		float GetVolume();

	private:
		FMOD::Channel* m_channel{ nullptr };
	};
}