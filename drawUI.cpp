#include "DrawUI.hpp"

// ���â�� ������ ������ �°� ����� ���� �Լ�
sf::RectangleShape makeRectangle(sf::RenderWindow& window, float widthRatio, float heightRatio)
{
	// ���� â ũ��
	sf::Vector2u winSize = window.getSize();

	// �簢�� ������ ����
	sf::Vector2f rectSize(winSize.x * widthRatio, winSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::White);
	return rect;

}

// �����̳� ������ �Լ� 
sf::RectangleShape makeRectangle(sf::FloatRect& frameBounds, float widthRatio, float heightRatio, sf::Color color)
{
	// ���� â ũ��
	sf::Vector2f frameSize = frameBounds.size;

	// �簢�� ������ ����
	sf::Vector2f rectSize(frameSize.x * widthRatio, frameSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(color);

	return rect;

}

// ��� ���� - ������ ����
sf::Vector2f getWindowCenterPosition(const sf::RenderWindow& window, const sf::FloatRect& targetBounds)
{
	float centerX = window.getSize().x / 2.f;
	float centerY = window.getSize().y / 2.f;

	float x = centerX - targetBounds.size.x / 2.f;
	float y = centerY - targetBounds.size.y / 2.f;

	return { x, y };
}

// XY �߾����� (��ư�� �ؽ�Ʈ)
sf::Vector2f getCenterPosition(const sf::Vector2f& targetSize, const sf::FloatRect& container)
{
	float x = container.position.x + (container.size.x - targetSize.x) / 2.f;
	float y = container.position.y + (container.size.y - targetSize.y) / 2.f;
	return { x, y };
}

// � ��ü ���� x �� ��� ����
sf::Vector2f getCenterXPosition(sf::Vector2f targetSize,
	const sf::FloatRect& refBounds,
	float y)
{
	float x = refBounds.position.x + (refBounds.size.x - targetSize.x) / 2.f;
	return { x, y };
}

// ���� ����
sf::Vector2f LeftInnerAlign(sf::FloatRect& refBounds, float x_margin)
{
	return { refBounds.position.x + x_margin, refBounds.position.y };
}

// ������ ����
sf::Vector2f RightInnerAlign(sf::Vector2f targetSize, sf::FloatRect& refBounds, float x_margin)
{
	return { refBounds.position.x + refBounds.size.x - targetSize.x - x_margin, refBounds.position.y };
}