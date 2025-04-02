// ui �ʱ�ȭ �Լ� initUI()
#include <SFML/Graphics.hpp>

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

// � ��ü ���� x �� ��� ����
sf::Vector2f getCenterXPosition(sf::Vector2f targetSize,
	const sf::FloatRect& refBounds,
	float y)
{
	float x = refBounds.position.x + (refBounds.size.x - targetSize.x) / 2.f;
	return { x, y };
}

// ���� ����
sf::Vector2f LeftInnerAlign(sf::FloatRect& refBounds, float x_margin = 0.f)
{
	return { refBounds.position.x + x_margin, refBounds.position.y };
}

// ������ ����
sf::Vector2f RightInnerAlign(sf::Vector2f targetSize, sf::FloatRect& refBounds, float x_margin = 0.f)
{
	return { refBounds.position.x + refBounds.size.x - targetSize.x - x_margin, refBounds.position.y };
}

void initContainer(sf::RenderWindow& window)
{
	sf::RectangleShape profileBox_Frame = makeRectangle(window, 0.5f, 0.5f);

	// ���� ��ü
	sf::FloatRect frameBound = profileBox_Frame.getGlobalBounds();
	profileBox_Frame.setPosition(getWindowCenterPosition(window, frameBound));			// �����츦 �߽����� �߾�����
	frameBound = profileBox_Frame.getGlobalBounds();


	// ������ ���� �����̳� ����
	sf::RectangleShape profileBox_Title = makeRectangle(frameBound, 0.4f, 0.1f, sf::Color::Red);
	sf::RectangleShape profileBox_Image = makeRectangle(frameBound, 0.3f, 0.5f, sf::Color::Green);
	sf::RectangleShape profileBox_info = makeRectangle(frameBound, 0.5f, 0.6f, sf::Color::Yellow);
	sf::RectangleShape profileBox_info_label;
	sf::RectangleShape profileBox_info_value;


	// ���� frame
	sf::Vector2f TitleSize = profileBox_Title.getSize();
	sf::FloatRect profileBox_Title_Bound = profileBox_Title.getGlobalBounds();
	sf::Vector2f titlePos = getCenterXPosition(TitleSize, frameBound, frameBound.position.y);	// ������ ������ �������� �߾� ����

	// �̹��� frame
	sf::Vector2f imgSize = profileBox_Image.getSize();
	sf::FloatRect profileBox_Image_Bound = profileBox_Image.getGlobalBounds();
	sf::Vector2f imgPos = LeftInnerAlign(frameBound, 30.f);										// ������ ������ �������� ���� ����

	// ���� �Է� frame
	sf::Vector2f infoSize = profileBox_info.getSize();
	sf::FloatRect profileBox_info_Bound = profileBox_info.getGlobalBounds();
	sf::Vector2f infoPos = RightInnerAlign(infoSize, frameBound, 30.f);							// ������ ������ �������� ������ ����

	// ��ġ ����
	profileBox_Image.setPosition({ imgPos.x, imgPos.y + 90.0f });	// ���� ���� ��
	profileBox_info.setPosition({ infoPos.x, infoPos.y + 90.0f });	// ������ ���� ��
	profileBox_Title.setPosition(titlePos);
}