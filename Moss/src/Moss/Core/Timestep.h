#pragma once

namespace Moss {


	//这里写了个类，本质就是一个浮点数，只是用了几个函数更可读，在java或者c#就不行，c#写成struct可以达到一样的效果
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : m_Time(time){

		}

		operator float() const { return m_Time; }

		float GetSeconds()const { return m_Time; }
		float GetMilliseconds()const { return m_Time * 1000.0f; }

	private:

		float m_Time;

	};
}
