#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// 윈도우 비율로 사각형 생성
sf::RectangleShape makeRectangle(sf::RenderWindow& window, float widthRatio, float heightRatio);

// 부모 컨테이너 비율로 사각형 생성
sf::RectangleShape makeRectangle(sf::FloatRect& frameBounds, float widthRatio, float heightRatio, sf::Color color);

// 정렬 유틸
sf::Vector2f getWindowCenterPosition(const sf::RenderWindow& window, const sf::FloatRect& targetBounds);
sf::Vector2f getCenterPosition(const sf::Vector2f& targetSize, const sf::FloatRect& container);
sf::Vector2f getCenterXPosition(sf::Vector2f targetSize, const sf::FloatRect& refBounds, float y);
sf::Vector2f LeftInnerAlign(sf::FloatRect& refBounds, float x_margin = 0.f);
sf::Vector2f RightInnerAlign(sf::Vector2f targetSize, sf::FloatRect& refBounds, float x_margin = 0.f);