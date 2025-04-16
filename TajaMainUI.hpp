#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "GameState.hpp"

struct MenuButton {
    sf::RectangleShape box;
    sf::Text label;
    std::function<void()> onClick;


    // Text는 기본 생성자가 없으므로 : 초기화로 font 를 줘야 한다.
    MenuButton(const sf::Font& font) : label(font) {

    }

    bool contains(const sf::Vector2f& MousePoint) const;


    // 텍스트 버튼안에 정렬
    void setBtnPos(float padding = 0.f);

};

struct TajaMenuUI {
    std::vector<MenuButton> mainMenuButtons;
    MenuButton logoutButton;
    sf::Sprite profileSprite;
    sf::Text nicknameText;

    TajaMenuUI(const sf::Font& font, const sf::Texture& texture) : logoutButton(font), profileSprite(texture), nicknameText(font) {}
};

void drawBtn(sf::RenderWindow& window, MenuButton& btn);

// 호버효과
void menuHover(std::vector<MenuButton>& buttons, sf::Vector2f mousePos);

void logoutHover(MenuButton& button, sf::Vector2f mousePos);

void initTajaMenu(sf::RenderWindow& window, GameState& game, sf::Font& font, TajaMenuUI& ui);

void tajaMenuHandeler(sf::RenderWindow& window, GameState& game, TajaMenuUI& ui, const std::optional<sf::Event>& event);

void renderTajaMenu(sf::RenderWindow& window, TajaMenuUI& ui);


