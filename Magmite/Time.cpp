
#include "all.fwd"


namespace magmite
{

	void time::init()
	{
		_time_scale = 1.0f;
		_delta = 0.016f;
		_game_time = 0.0f;

		_nanos_since_start = 0ULL;

		tp = now();
		t0 = tp;

		while (!scheduled_calls.empty())
		{
			scheduled_calls.pop();
		}
	}

	void time::update()
	{
		auto n = now();
		_delta = (n - tp).count() / 1e9f * _time_scale;
		tp = n;

		_nanos_since_start = (tp - t0).count();
		_game_time = _nanos_since_start / 1e9f;

		while (!scheduled_calls.empty())
		{
			auto& [t, fn] = scheduled_calls.top();
			
			if (t > _game_time)
			{
				break;
			}

			fn();
			scheduled_calls.pop();
		}
	}

	float time::delta()
	{
		return _delta;
	}

	void time::delta(float new_delta)
	{
		_delta = new_delta;
	}

	float time::time_scale()
	{
		return _time_scale;
	}

	void time::time_scale(float new_time_scale)
	{
		_time_scale = new_time_scale;
	}

	float time::game_time()
	{
		return _game_time;
	}

	size_t time::nanos_since_start()
	{
		return _nanos_since_start;
	}
}