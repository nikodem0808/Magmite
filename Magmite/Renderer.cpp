
#include "all.def"

namespace magmite
{
	void renderer::render(sf::RenderTarget& render_target)
	{
		sprite.setPosition(parent().transform().position);
		render_target.draw(sprite);
	}
}


