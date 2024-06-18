#pragma once

#include <chrono>
#include <queue>
#include <functional>


namespace magmite
{
	struct time
	{
	private:
		using task = std::pair<float, std::function<void()>>;

		struct schedule_comparer
		{
			bool operator()(task& a, task& b)
			{
				return a.first > b.first;
			}
		};

		float _delta = 0.016f;
		float _time_scale = 1.0f;
		float _game_time = 0.0f;

		size_t _nanos_since_start = 0ULL;

		std::chrono::steady_clock::time_point t0{};
		std::chrono::steady_clock::time_point tp{};

		std::priority_queue<
			std::pair<float, std::function<void()>>,
			std::vector<std::pair<float, std::function<void()>>>,
			schedule_comparer
		> scheduled_calls;

	public:
		void init();
		void update();

		float delta();
		void delta(float new_delta);

		float time_scale();
		void time_scale(float new_time_scale);

		float game_time();
		size_t nanos_since_start();

		inline auto now() { return std::chrono::steady_clock::now(); }

		template <typename FN>
		void schedule(float delay, FN&& fn)
		{
			scheduled_calls.emplace(game_time + delay, fn);
		}
	};
}

