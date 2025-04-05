// 타자 게임 메인 
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
#include <codecvt>  // wide → utf8 변환 (선택)



int main() {
    // 로그 출력용
    //SetConsoleOutputCP(CP_UTF8);               // 콘솔 UTF-8 설정
    std::wcout.imbue(std::locale(""));         // 유니코드 로케일 설정


    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Typing Game");

    GameState game;
    // 로그인 성공하면 유저 정보 초기화
    //game.user.nickname = L"Player1";
    //game.user.profileImagePath = "images/profile.png";
    //game.user.loadProfileImage();

    // 테스트 용 임시 유저 정보
    game.user.id = L"test_user_001";
    game.user.nickname = L"타자마스터";
    game.user.profileImagePath = L"assets/profile_img/default_avatar.png";

    sf::Image img = loadImg(game.user.profileImagePath);
    game.user.profileTexture = sf::Texture(resizeImageKeepAspect(img));
    
    // 폰트 설정
    sf::Font font;
    if (!font.openFromFile("assets/fonts/D2Coding.ttf")) {
        std::wcerr << L"[ERROR] 폰트 로드 실패!" << std::endl;
        return 1;
    }
    
    
    //// 프로필 이미지 로딩
    //if (game.user.profileTexture.loadFromFile(game.user.profileImagePath)) {
    //    // 로딩 성공
    //}
    //else {
    //    std::wcout << L"프로필 이미지 로딩 실패!" << std::endl;
    //}
    game.selectPath = L"assets/hangleFile/애국가.txt";

    // 파일 경로를 받아오면 2차원 벡터로 변환하는 과정
    std::wstring content = loadText(game.selectPath);
    std::vector<std::wstring> lines = splitStrtoVector(content);
    auto wrapped = wrapAllLinesToPixelWidth(lines, font, game.user.fontSize, 1280.f);       // 이건 노란색 창의 크기를 받아와야 하는데
    game.sentences = wrapped;


    // input, correctMap 초기화
    initUserInputsAndCorrectMap(game);
    

    // 게임 기록 - 일단 임의로 초기화
    game.user.point = 1234;
    game.user.bestWPM = 87.5f;
    game.user.bestAccuracy = 96.2f;
    game.user.totalPlayCount = 12;
    game.user.totalPlayTime = 983.7f;

    // 현제 플레이어의 게임 화면 저장
    //game.currentScene = Scene::MAIN_MENU; // 초기값 줬으므로 필요 x 나중에 복사용으로 남겨뒀음
    
    game.currentScene = Scene::TYPING_GAME; // 초기값 줬으므로 필요 x 나중에 복사용으로 남겨뒀음
    //TYPING_GAME

    // 플레이 타임 기록용(?)
    sf::Clock clock;
    
    // 메인 while 루프
    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            switch (game.currentScene) {
            case Scene::TYPING_GAME:
                // Scene별 입력 처리
                handleInputGame(game, *event);

            }
        }
    
    

        // 이건 한번 확인해봐야 될 듯(?)
        float elapsed = clock.getElapsedTime().asSeconds();
        //updateGame(game, elapsed);  // GAME 상태에서만 처리되도록 내부 분기 가능

        window.clear(sf::Color::White);

        // 씬에 따라 그리기
        switch (game.currentScene) {
        case Scene::MAIN_MENU:
            //renderMenu(window, game);
            break;
        case Scene::FILE_SELECT:
            //renderFileSelect(window, game);
            break;
        case Scene::TYPING_GAME: {
            if (game.currentScene == Scene::TYPING_GAME && !game.started) {
                game.startTime = std::chrono::high_resolution_clock::now();     // 게임 시작 시간 저장
                game.started = true;                    // 한 번만 초기화 하도록
            }
            auto now = std::chrono::high_resolution_clock::now();
            float elapsed = std::chrono::duration<float>(now - game.startTime).count();
            game.elapsedSeconds = elapsed;
            renderGame(window, game, font, 18);         // UI 렌더링
            updateTypingStats(game, elapsed);           // 실시간 통계 업데이트
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


