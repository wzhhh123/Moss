#pragma once

namespace Moss {


	//����д�˸��࣬���ʾ���һ����������ֻ�����˼����������ɶ�����java����c#�Ͳ��У�c#д��struct���Դﵽһ����Ч��
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
