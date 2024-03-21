#include <iostream>
#include <chrono>
#include <ncurses.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../include/defs.hpp"
#include "../include/audio.hpp"
#include "../include/sarge.h"
#define MINIAUDIO_IMPLEMENTATION
#include "../include/miniaudio.hpp"

static char clear_window(WINDOW *playerWindow) {
    wclear(playerWindow);
    waddstr(playerWindow, "End of the video\n");
    waddstr(playerWindow, "Please press 'q' to exit\n");
    wrefresh(playerWindow);
    char option = wgetch(playerWindow);
    while(option != 'q') {
        option = wgetch(playerWindow);
    }
    return option;
}

int main(int argc, char** argv) {
    WINDOW *playerWindow = nullptr;
    std::string mp3Filepath = "";
    std::string mp4Filepath = "";

    Sarge sarge;

    sarge.setArgument("h", "help", "Get help.", false);
    sarge.setArgument("a", "with-audio", "Play the media with audio file.", true);
    sarge.setDescription("C++ program that converts media files such .mp4 into ASCII characters.");
    sarge.setUsage("sarge_test [options] <video_file>");

    if (!sarge.parseArguments(argc, argv))
    {
        std::cerr << "Couldn't parse arguments..." << std::endl;
        return 1;
    }

    if (sarge.exists("help"))
    {
        sarge.printHelp();
        return 1;
    }

    std::string textarg;
    if (sarge.getTextArgument(0, textarg))
    {
        mp4Filepath = textarg;
    }
    else
    {
        sarge.printHelp();
        return 1;
    }

    if (sarge.getFlag("with-audio", mp3Filepath)) {
        if (mp3Filepath == "") {
            sarge.printHelp();
            return 1;
        }
	}

    cv::VideoCapture cap;
    try {
        cap.open(mp4Filepath);

        if (!cap.isOpened()) {
            std::cerr << "Error opening the video file." << std::endl;
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    initscr();
    curs_set(0);    // This hides the cursor

    if(has_colors() != FALSE) {
        start_color();
        init_pair(2, COLOR_BLACK, COLOR_BLUE);
        attron(A_BOLD);
    }
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    

    if((playerWindow = newwin(height, width, 0, 0)) == nullptr) {
        endwin();
        std::cerr << "Error creating the player window." << std::endl;
        return 1;
    }

    char option = '\0';
    bool quit = false;
    while(!quit) {
        keypad(playerWindow, TRUE);

        cv::Mat frame;
        int videoHeight = 0, videoWidth = 0;

        wclear(playerWindow);
        wrefresh(playerWindow);
        double fps = cap.get(cv::CAP_PROP_FPS);
        wmove(playerWindow, 0, 0);
        bool once = false;
        int playerWindowHeight, playerWindowWidth;
        getmaxyx(playerWindow, playerWindowHeight, playerWindowWidth);

        if (mp3Filepath != "") {
            Audio audio(mp3Filepath);
            audio.play();
        }

        for(;;) {
            auto start = std::chrono::high_resolution_clock::now();
            cap >> frame;
            if(frame.empty()) {
                clear_window(playerWindow);
                break;
            }
            cv::resize(frame, frame, cv::Size(playerWindowWidth, playerWindowHeight));
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            cv::Size sz = frame.size();
            videoWidth = sz.width;
            videoHeight = sz.height;
            for(int i = 0; i < videoHeight; ++i) {
                for(int j = 0; j < videoWidth; ++j) {
                    uchar intensity = frame.at<uchar>(i, j);
                    char asciiPixel = pixelToASCII(intensity);
                    mvaddch(i, j, asciiPixel);
                }
            }
            if(!once) {
                once = true;
            }
            refresh();
            auto end = std::chrono::high_resolution_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            napms(1000 / fps - time_span.count());

            nodelay(playerWindow, true);
            option = wgetch(playerWindow);
            nodelay(playerWindow, false);
 
            if(option == 'q' || option == 'Q') {
                quit = true;
                option = '\0';
                cap.release();
                break;
            } else if(option == 'm' || option == 'M') {
                option = clear_window(playerWindow);
                if(option == 'q') {
                    quit = true;
                }
                cap.release();
                break;
            }
        }
        echo();
    }
    // delwin(menuWindow);
    delwin(playerWindow);
    endwin();

    return 0;
}
