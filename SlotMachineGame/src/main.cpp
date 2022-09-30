#include <game.h>
#include <filesystem>
using namespace oct;
using namespace glm;
auto main()->int
{
	return game::run();
}
std::vector<card> deck;
void game::load()
{
	// Loading cards
	std::string cardsPath = "assets/cards";
	uint32_t id = 0;
	for (const auto& entry : std::filesystem::directory_iterator(cardsPath))
	{
		std::string path = entry.path().string();
		std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
		std::string extension = base_filename.substr(base_filename.find_last_of(".") + 1);
		if (extension == "png")
		{
			std::string::size_type const p(base_filename.find_last_of('.'));
			std::string name = base_filename.substr(0, p);
			deck.push_back(card(name, path, id++));
		}
	}
	game::machine = new slot_machine();
	for (auto& reel : game::machine->reels)
		reel.attach_deck(deck);
	sound::load_sound("assets/sounds/score.wav");
	render_cmd::set_clear_color(0.2078431372549019607843137254902f, 0.2078431372549019607843137254902f, 0.2078431372549019607843137254902f, 1.0f);
}
void game::rendering()
{
	render_cmd::clear();
	renderer2d::begin_projection();
	//renderer2d::draw_quad(vec3(x, 0.0f, -5.0f), vec2(1.0f, 1.0f), vec4(0.1f, 0.1f, 0.2f, 1.0f));
	renderer2d::draw(game::machine);
	renderer2d::end_projection();
}
void game::integration(float dt)
{
	for (auto& reel : game::machine->reels)
		reel.integrate(dt);
}