#pragma once

namespace Draxion
{
	class TimeStamp
	{
	public:
		TimeStamp(float time = 0.0f)
		:
			m_time(time)
		{};
		const float GetTime() const { return m_time; }
		const float GetTime_MilliSeconds() const { return m_time * 1000.0f; }
	
		operator float(){ return m_time; }
	private:
		float m_time;
	};
}