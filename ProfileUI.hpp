#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include <vector>
#include <memory>
#include <string>

struct ProfileUI {
	sf::Text title;
	sf::Text loadBtnLabel;
	sf::Sprite imgSprite;
	sf::RectangleShape frame;
	sf::RectangleShape info;
	sf::RectangleShape img;
	sf::RectangleShape loadBtn;
	sf::Sprite backBtn;

	std::vector<sf::Text> labelTexts;
	std::vector<sf::Text> valueTexts;


	ProfileUI(const sf::Font& font, const sf::Texture& texture, const sf::Texture& btnTexture) : title(font), loadBtnLabel(font), imgSprite(texture), backBtn(btnTexture) {}
};

void initProfile(sf::RenderWindow& window, GameState& game, const sf::Font& font, ProfileUI& ui);

void renderProfile(sf::RenderWindow& window, ProfileUI& ui);

void profileHandeler(sf::RenderWindow& window, GameState& game, ProfileUI& ui, const std::optional<sf::Event>& event);
