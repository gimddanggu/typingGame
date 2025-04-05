// Ÿ�� ���� ���� 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "GameState.hpp"
#include "Scene.hpp"
#include "UIAlign.hpp"
#include "DrawUI.hpp"
#include "FileLoader.hpp"
#include "TextUtil.hpp"
#include "TypingGame.hpp";
#include <locale>
#include <windows.h>


#include <iomanip>  // std::hex, std::setw
#include <codecvt>  // wide �� utf8 ��ȯ (����)



int main() {
    // �α� ��¿�
    //SetConsoleOutputCP(CP_UTF8);               // �ܼ� UTF-8 ����
    std::wcout.imbue(std::locale(""));         // �����ڵ� ������ ����


    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Typing Game");

    GameState game;
    // �α��� �����ϸ� ���� ���� �ʱ�ȭ
    //game.user.nickname = L"Player1";
    //game.user.profileImagePath = "images/profile.png";
    //game.user.loadProfileImage();

    // �׽�Ʈ �� �ӽ� ���� ����
    game.user.id = L"test_user_001";
    game.user.nickname = L"Ÿ�ڸ�����";
    game.user.profileImagePath = L"assets/profile_img/default_avatar.png";

    sf::Image img = loadImg(game.user.profileImagePath);
    game.user.profileTexture = sf::Texture(resizeImageKeepAspect(img));
    
    // ��Ʈ ����
    sf::Font font;
    if (!font.openFromFile("assets/fonts/D2Coding.ttf")) {
        std::wcerr << L"[ERROR] ��Ʈ �ε� ����!" << std::endl;
        return 1;
    }
    
    
    //// ������ �̹��� �ε�
    //if (game.user.profileTexture.loadFromFile(game.user.profileImagePath)) {
    //    // �ε� ����
    //}
    //else {
    //    std::wcout << L"������ �̹��� �ε� ����!" << std::endl;
    //}
    game.selectPath = L"assets/hangleFile/�ֱ���.txt";

    // ���� ��θ� �޾ƿ��� 2���� ���ͷ� ��ȯ�ϴ� ����
    std::wstring content = loadText(game.selectPath);
    std::vector<std::wstring> lines = splitStrtoVector(content);
    auto wrapped = wrapAllLinesToPixelWidth(lines, font, game.user.fontSize, 1280.f);       // �̰� ����� â�� ũ�⸦ �޾ƿ;� �ϴµ�
    game.sentences = wrapped;


    // input, correctMap �ʱ�ȭ
    initUserInputsAndCorrectMap(game);
    

    // ���� ��� - �ϴ� ���Ƿ� �ʱ�ȭ
    game.user.point = 1234;
    game.user.bestWPM = 87.5f;
    game.user.bestAccuracy = 96.2f;
    game.user.totalPlayCount = 12;
    game.user.totalPlayTime = 983.7f;

    // ���� �÷��̾��� ���� ȭ�� ����
    //game.currentScene = Scene::MAIN_MENU; // �ʱⰪ �����Ƿ� �ʿ� x ���߿� ��������� ���ܵ���
    
    game.currentScene = Scene::TYPING_GAME; // �ʱⰪ �����Ƿ� �ʿ� x ���߿� ��������� ���ܵ���
    //TYPING_GAME

    // �÷��� Ÿ�� ��Ͽ�(?)
    sf::Clock clock;
    
    // ���� while ����
    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            switch (game.currentScene) {
            case Scene::TYPING_GAME:
                // Scene�� �Է� ó��
                handleInputGame(game, *event);

            }
        }
    
    

        // �̰� �ѹ� Ȯ���غ��� �� ��(?)
        float elapsed = clock.getElapsedTime().asSeconds();
        //updateGame(game, elapsed);  // GAME ���¿����� ó���ǵ��� ���� �б� ����

        window.clear(sf::Color::White);

        // ���� ���� �׸���
        switch (game.currentScene) {
        case Scene::MAIN_MENU:
            //renderMenu(window, game);
            break;
        case Scene::FILE_SELECT:
            //renderFileSelect(window, game);
            break;
        case Scene::TYPING_GAME: {
            if (game.currentScene == Scene::TYPING_GAME && !game.started) {
                game.startTime = std::chrono::high_resolution_clock::now();     // ���� ���� �ð� ����
                game.started = true;                    // �� ���� �ʱ�ȭ �ϵ���
            }
            auto now = std::chrono::high_resolution_clock::now();
            float elapsed = std::chrono::duration<float>(now - game.startTime).count();
            game.elapsedSeconds = elapsed;
            renderGame(window, game, font, 18);         // UI ������
            updateTypingStats(game, elapsed);           // �ǽð� ��� ������Ʈ
            break;
        }
        case Scene::RESULT:
            //renderResult(window, game);
            break;
        }

        window.display();
    }

    return 0;
}


