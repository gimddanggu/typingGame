#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// ����� ���� ����ü
struct UserInfo
{
	std::wstring id;
	std::wstring nickname;
	std::wstring rank;
	std::wstring maxTpm;
	std::wstring maxWpm;
	std::wstring playTime;
	std::wstring point;
};


// �̹��� �ε� �� ��������
sf::Image loadImg(std::wstring path);
sf::Image resizeImageKeepAspect(const sf::Image& src, sf::Vector2u targetSize = {200, 200}, sf::Color paddingColor = sf::Color::Transparent);

// UI �ʱ�ȭ �Լ�
void initProfileUI(sf::RenderWindow& window, sf::Font& font,
	sf::Sprite& profileImg, UserInfo info,
	std::vector<std::shared_ptr<sf::Drawable>>& drawables,
	std::vector<sf::Text>& profileTexts,sf::FloatRect& loadButtonBound);