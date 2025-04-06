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
#include "ResultScreen.hpp"
#include "DrawUIR.hpp"
#include "FileSelectList.hpp"

#include <locale>
#include <windows.h>


#include <iomanip>  // std::hex, std::setw
#include <codecvt>  // wide → utf8 변환 (선택)


void debugPrintSentences(const std::vector<std::vector<std::wstring>>& sentences) {
    for (size_t i = 0; i < sentences.size(); ++i) {
        std::wcout << L"[문장 그룹 " << i << L"]\n";
        for (size_t j = 0; j < sentences[i].size(); ++j) {
            const std::wstring& line = sentences[i][j];
            std::wcout << L"  줄 " << j << L": \"" << line << L"\"\n";
            for (size_t k = 0; k < line.size(); ++k) {
                wchar_t ch = line[k];
                std::wstring type;
                if (ch == L' ')
                    type = L"공백";
                else if (ch == L'\t')
                    type = L"탭";
                else
                    type = L"일반";

                std::wcout << L"    [" << k << L"] '" << (ch == L' ' ? L'공백' : (ch == L'\t' ? L'tap' : ch))
                    << L"' (" << type << L")\n";
            }
        }
    }
}


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

    int fontSize = game.user.fontSize;
    
    
    //// 프로필 이미지 로딩
    //if (game.user.profileTexture.loadFromFile(game.user.profileImagePath)) {
    //    // 로딩 성공
    //}
    //else {
    //    std::wcout << L"프로필 이미지 로딩 실패!" << std::endl;
    //}
    game.selectPath = L"assets/hangleFile/애국가.txt";    

    // 게임 기록 - 일단 임의로 초기화
    game.user.point = 1234;
    game.user.bestWPM = 87.5f;
    game.user.bestAccuracy = 96.2f;
    game.user.totalPlayCount = 12;
    game.user.totalPlayTime = 983.7f;

    // 현제 플레이어의 게임 화면 저장
    //game.currentScene = Scene::MAIN_MENU; // 초기값 줬으므로 필요 x 나중에 복사용으로 남겨뒀음
    
    game.currentScene = Scene::FILE_SELECT; // 초기값 줬으므로 필요 x 나중에 복사용으로 남겨뒀음
    //TYPING_GAME

    // 플레이 타임 기록용(?)
    sf::Clock clock;
    

    // 파일 목록용 테스트 변수
    std::vector<FileOption> fileOptions;
    std::wstring selectMod = L"한글";
    std::vector<std::wstring> typingFilePath;

    typingFilePath = {
            L"C:/Source/IoT-C-2025/Day02/c03.conditional Statements.c",
            L"C:/Source/IoT-C-2025/Day02/c04.loop Statements.c",
            L"C:/Source/IoT-python-2025/day04/py03_module.py",
            L"C:/Source/IoT-python-2025/day02/py02_datastruct.py",
            L"C://Users//Admin//Downloads//TypingTest_EnglishOnly.java",
            L"assets/typing/한글2.txt",
            L"assets/typing/english.txt",
            L"assets/typing/coding.cpp",
            L"assets/typing/coding.cpp",
            L"assets/typing/한글1.txt",

    };

    /* \t 확인용 코드 */
    std::wstring content = loadText(typingFilePath[4]);
    std::vector<std::wstring> lines = splitStrtoVector(content);
    //std::cout << "[DEBUG] typingAreaWith: " << game.typingAreaWidth << '\n';
    game.sentences = wrapAllLinesToPixelWidth(lines, font, game.user.fontSize, game.typingAreaWidth);


    debugPrintSentences(game.sentences);

    // 메인 while 루프
    while (window.isOpen()) 
    {
        //std::wcout << L"[DEBUG] 현재 Scene: ";
        //std::wcout << L"[DEBUG] 현재 Scene: " << static_cast<int>(game.currentScene) << std::endl;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        while (const std::optional event = window.pollEvent())
        {
            //// 리사이즈 이벤트
            //if (event->is < sf::Event::Resized>()) {
            //    const auto* resizeEvent = event->getIf<sf::Event::Resized>();
            //    sf::Vector2u newSize(resizeEvent->size.x, resizeEvent->size.y);
            //    game.windowSize = newSize;
            //    std::wcout << L"[DEBUG] 윈도우 크기 갱신됨: " << newSize.x << L"x" << newSize.y << std::endl;
            //}

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            switch (game.currentScene) {
            case Scene::FILE_SELECT: {
                handleFileClick(game, *event, worldPos, fileOptions, font);
                break;
            }         
            case Scene::TYPING_GAME: 
                // Scene별 입력 처리
                handleInputGame(game, *event);
                break;
            }

        }

        // HOVER 효과
        if (game.currentScene == Scene::FILE_SELECT) {
            hoverText(game, fileOptions, worldPos);
        }
        


        window.clear(sf::Color::White);

        // 씬에 따라 그리기
        switch (game.currentScene) {
        case Scene::MAIN_MENU:
            //renderMenu(window, game);
            break;
        case Scene::FILE_SELECT: {
            renderFileList(window, game, font, fontSize, typingFilePath, fileOptions, selectMod);
            break;
        }
        case Scene::TYPING_GAME: {
            if (game.currentScene == Scene::TYPING_GAME && !game.started) {
                game.startTime = std::chrono::high_resolution_clock::now();     // 게임 시작 시간 저장
                game.started = true;                    // 한 번만 초기화 하도록
            }
            auto now = std::chrono::high_resolution_clock::now();
            float elapsed = std::chrono::duration<float>(now - game.startTime).count();
            game.elapsedSeconds = elapsed;

            if (game.readyToShowResult)
                //game.progress = 100.f;
                game.currentScene = Scene::RESULT;

            renderGame(window, game, font, fontSize);         // UI 렌더링
            updateTypingStats(game, elapsed);           // 실시간 통계 업데이트
            updateGame(game);
            break;
        }
        case Scene::RESULT: {
            //renderResult(window, game);
            std::wcout << L"[DEBUG] 렌더링 RESULT 로 변경합니다." << std::endl;

            bool bRstart = showResultWindow(game, font, fontSize, game.sentences);
            if (bRstart) {
                resetGameResult(game);  // 값 초기화
                game.currentScene = Scene::TYPING_GAME;
            }
            else {
                game.currentScene = Scene::FILE_SELECT;
            }

            break;
        }
        }

        window.display();
    }

    return 0;
}






