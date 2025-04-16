#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "ProfileUI.hpp"
#include "DrawUIR.hpp"
#include "DrawUI.hpp"
#include "UIAlign.hpp"
#include "GameState.hpp"
#include "Scene.hpp"
#include "StringFormat.hpp"


void initProfile(sf::RenderWindow& window, GameState& game, const sf::Font& font, ProfileUI& ui) {

	// 프로필 프레임 생성
	sf::RectangleShape frame = makeRectangleR(window, 0.5f, 0.5f, sf::Color::Transparent, sf::Color::Black, 3.f);
	sf::FloatRect frameBound = frame.getGlobalBounds();
	sf::Vector2f framePos = getWindowCenterPosition(window, frameBound);

	frame.setPosition(framePos);			// 윈도우를 중심으로 중앙정렬
	frameBound = frame.getGlobalBounds();

	// title 프레임 생성
	sf::RectangleShape titleFrame = makeRectangleR(frameBound, 0.4f, 0.15f, sf::Color::Red);
	sf::Vector2f titlePos = getCenterXPosition(titleFrame.getSize(), frameBound, 10.f);
	sf::Vector2f titleSize = titleFrame.getSize();
	titleFrame.setPosition(titlePos);
	// text 넣기
	sf::Text titleTex(font, L"프로필", 35);
	titleTex.setFillColor(sf::Color::Black);
	AlignTextCenter(titleTex, titleFrame.getGlobalBounds());


	// 이미지 프레임 생성
	sf::RectangleShape imageFrame = makeRectangleR(frameBound, 0.3f, 0.5f, sf::Color::Green);
	sf::Vector2f imageSize = imageFrame.getSize();
	sf::Vector2f imgPos = LeftInnerAlign(frameBound, 30.f);						// 프로필 프래임 기준으로 왼쪽 정렬
	imageFrame.setPosition({ imgPos.x, titlePos.y + titleSize.y + 30 });
	imgPos = imageFrame.getPosition();
	// 이미지 넣기
	// game에서 texture 를 받아올 것임
	ui.imgSprite.setScale(setSpriteScale(imageSize, game.user.profileTexture));
	ui.imgSprite.setPosition(imgPos);


	// 버튼 프레임 생성
	sf::RectangleShape loadButtonFrame = makeRectangleR(frameBound, 0.3f, 0.12f, sf::Color::Cyan);
	loadButtonFrame.setPosition({ imgPos.x, imgPos.y + imageSize.y + 15 });
	loadButtonFrame.setFillColor(sf::Color::Black);
	// 버튼 라벨 
	sf::Text loadButtonlabel(font, L"프로필 이미지 선택", 20);
	AlignTextCenter(loadButtonlabel, loadButtonFrame.getGlobalBounds());

	// 스텟 창 프레임 생성
	sf::RectangleShape infoFrame = makeRectangleR(frameBound, 0.5f, 0.65f, sf::Color::Transparent, sf::Color::Yellow, 3.f);
	sf::Vector2f InfoPos = RightInnerAlign(infoFrame.getSize(), frameBound, 30.f);
	infoFrame.setPosition({ InfoPos.x, titlePos.y + titleSize.y + 30 });
	sf::FloatRect infoBounds = infoFrame.getGlobalBounds();

	// 스텟 - 라벨
	sf::RectangleShape infoLabelFrame = makeRectangleR(infoBounds, 0.45f, 1, sf::Color::Blue);
	sf::Vector2f infoLabelPos = LeftInnerAlign(infoBounds);
	infoLabelFrame.setPosition(infoLabelPos);
	// 스텟 - 값
	sf::RectangleShape infoValFrame = makeRectangleR(infoBounds, 0.55f, 1.f, sf::Color::Red);
	sf::Vector2f infoValPos = RightInnerAlign(infoValFrame.getSize(), infoBounds);
	infoValFrame.setPosition(infoValPos);

	// 라벨
	std::vector<std::wstring> infoLabelT = { L"ID", L"닉네임", L"랭킹", L"최고 타수", L"최고 WPM", L"플레이 타임", L"포인트" };
	std::vector<std::wstring> infoValT = {
	game.user.id,												// ID
	game.user.nickname,											// 닉네임
	formatInt(game.user.ranking, L"위"),						// 3 위
	formatRoundedInt(game.user.bestTPM, L"타수"),				// 340
	formatFloat(game.user.bestWPM, 1, L"WPM"),					// 30.2 WPM
	formatInt(game.user.totalPlayTime, L"초"),					// 532.25 초
	formatInt(game.user.point, L"점")							// 250 점
	};
	
	float startLX = infoLabelPos.x + 15; // 라벨
	float startLY = infoLabelPos.y;

	for (int i = 0; i < infoLabelT.size(); i++) {
		sf::Text labelText(font, infoLabelT[i], 22);
		labelText.setPosition({ startLX, startLY });
		labelText.setFillColor(sf::Color::Black);
		ui.labelTexts.push_back(labelText);

		sf::Text valText(font, infoValT[i], 22);
		AlignTextXCenter(valText, infoValFrame.getGlobalBounds()); // 텍스트를 X 축 기준으로 중앙 정렬
		float valTextPosX = valText.getPosition().x;
		valText.setPosition({ valTextPosX, startLY });
		valText.setFillColor(sf::Color::Black);
		ui.valueTexts.push_back(valText);

		auto bounds = labelText.getLocalBounds();
		startLY += bounds.size.y + bounds.position.y + 10;  // 보정 포함
	}

	

	ui.frame = frame;
	ui.img = imageFrame;
	ui.loadBtn = loadButtonFrame;
	ui.info = infoFrame;
	ui.title = titleTex;
	ui.loadBtnLabel = loadButtonlabel;



}

void renderProfile(sf::RenderWindow& window, ProfileUI& ui) {
	window.clear(sf::Color::White);
	window.draw(ui.frame);
	window.draw(ui.img);
	window.draw(ui.info);
	window.draw(ui.loadBtn);
	window.draw(ui.title);
	window.draw(ui.loadBtnLabel);
	window.draw(ui.imgSprite);
	window.draw(ui.backBtn);

	for (auto& label : ui.labelTexts) {
		window.draw(label);
	}

	for (auto& val : ui.valueTexts) {
		window.draw(val);
	}

}

void profileHandeler(sf::RenderWindow& window, GameState& game, ProfileUI& ui, const std::optional<sf::Event>& event) {
	if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (mouse->button == sf::Mouse::Button::Left) {
			sf::Vector2f clickPos = window.mapPixelToCoords({ mouse->position.x, mouse->position.y });
			// 이미지 선택 이벤트
			if (ui.loadBtn.getGlobalBounds().contains(clickPos)) {
				game.currentScene = Scene::PROFILE_SELECT;
				std::cout << "image Select" << std::endl;
			}

			// 뒤로가기 버튼 이벤트
			if (ui.backBtn.getGlobalBounds().contains(clickPos)) {
				game.currentScene = Scene::MAIN_MENU;
				std::cout << "main_menu" << std::endl;
			}

		}
	}
}