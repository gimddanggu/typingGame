#include "DrawUI.hpp"

// 결과창을 윈도우 비율에 맞게 만들기 위한 함수
sf::RectangleShape makeRectangle(sf::RenderWindow& window, float widthRatio, float heightRatio)
{
	// 현재 창 크기
	sf::Vector2u winSize = window.getSize();

	// 사각형 사이즈 조절
	sf::Vector2f rectSize(winSize.x * widthRatio, winSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::White);
	return rect;

}

// 컨테이너 생성용 함수 
sf::RectangleShape makeRectangle(sf::FloatRect& frameBounds, float widthRatio, float heightRatio, sf::Color color)
{
	// 현재 창 크기
	sf::Vector2f frameSize = frameBounds.size;

	// 사각형 사이즈 조절
	sf::Vector2f rectSize(frameSize.x * widthRatio, frameSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(color);

	return rect;

}

// 가운데 정렬 - 윈도우 기준
sf::Vector2f getWindowCenterPosition(const sf::RenderWindow& window, const sf::FloatRect& targetBounds)
{
	float centerX = window.getSize().x / 2.f;
	float centerY = window.getSize().y / 2.f;

	float x = centerX - targetBounds.size.x / 2.f;
	float y = centerY - targetBounds.size.y / 2.f;

	return { x, y };
}

// XY 중앙정렬 (버튼에 텍스트)
sf::Vector2f getCenterPosition(const sf::Vector2f& targetSize, const sf::FloatRect& container)
{
	float x = container.position.x + (container.size.x - targetSize.x) / 2.f;
	float y = container.position.y + (container.size.y - targetSize.y) / 2.f;
	return { x, y };
}

// 어떤 객체 기준 x 축 가운데 정렬
sf::Vector2f getCenterXPosition(sf::Vector2f targetSize,
	const sf::FloatRect& refBounds,
	float y)
{
	float x = refBounds.position.x + (refBounds.size.x - targetSize.x) / 2.f;
	return { x, y };
}

// 왼쪽 정렬
sf::Vector2f LeftInnerAlign(sf::FloatRect& refBounds, float x_margin)
{
	return { refBounds.position.x + x_margin, refBounds.position.y };
}

// 오른쪽 정렬
sf::Vector2f RightInnerAlign(sf::Vector2f targetSize, sf::FloatRect& refBounds, float x_margin)
{
	return { refBounds.position.x + refBounds.size.x - targetSize.x - x_margin, refBounds.position.y };
}