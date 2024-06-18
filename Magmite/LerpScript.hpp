#pragma once

#include "all.def"

namespace maingame
{

	struct lerp_script
	{
		magmite::game* game = nullptr;
		magmite::eid_type id = magmite::invalid_eid;

		magmite::eid_type target_id = magmite::invalid_eid;
		float end_time = NAN;
		sf::Vector2f direction;
		sf::Vector2f destination;

		lerp_script(magmite::game& _game, magmite::eid_type _id, magmite::eid_type _target_id, float duration, sf::Vector2f _destination);
		void update();

	};

}