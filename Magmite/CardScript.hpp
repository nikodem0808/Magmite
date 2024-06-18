#pragma once

#include "Magmite.hpp"

namespace maingame
{
	struct card_script
	{
		static inline constexpr size_t x_offset = 13;
		static inline constexpr size_t y_offset = 12;
		static inline constexpr size_t sprite_width = 144;
		static inline constexpr size_t sprite_height = 210;
		static inline constexpr size_t x_gap = sprite_width + 8;
		static inline constexpr size_t y_gap = sprite_height + 14;
		static inline constexpr size_t row_size = 12;
		static inline constexpr size_t n_cards = 52;
		static inline constexpr size_t n_backs = 4;
		static inline constexpr size_t n_total = 1;

		enum struct card_type
		{
			hearts = 0,
			spades,
			diamonds,
			clubs,
			back,
		};

		magmite::game* game = nullptr;
		magmite::eid_type id = magmite::invalid_eid;

		size_t value = 1;
		card_type type = card_type::hearts;
		
		card_script(magmite::game& game, magmite::eid_type id);

		void refresh_card_sprite();
		void set_card_sprite(card_type type, size_t value);

		void start();
		void update();
	};
}

