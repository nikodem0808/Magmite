#pragma once

#include <functional>

#include "all.fwd"
#include "Component.dcl"

namespace magmite
{
	struct behaviour : component
	{
		static inline constexpr size_t type_id = 1;

	private:

		void* instance = nullptr;

		std::function<void()>
			_init_fn,
			_start_fn,
			_update_fn,
			_deinit_fn,
			_destroy_fn;

	public:
		void init();
		void start();
		void update();
		void deinit();

		template <typename T>
		T& get_as();

		template <typename T, typename... Args>
		void bind(Args&&... args);

		~behaviour();
	};
}
