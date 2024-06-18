
#include "all.def"

namespace magmite
{
	void behaviour::init() { if (_init_fn != nullptr) _init_fn(); }
	void behaviour::start() { if (_start_fn != nullptr) _start_fn(); }
	void behaviour::update() { if (_update_fn != nullptr) _update_fn(); }
	void behaviour::deinit() { if (_deinit_fn != nullptr) _deinit_fn(); }

	behaviour::~behaviour()
	{
		if (_destroy_fn != nullptr) _destroy_fn();
	}
}

