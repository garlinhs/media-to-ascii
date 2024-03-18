# media to ASCII
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![nCurses](https://img.shields.io/badge/nCurses-6.4-red.svg)](https://en.wikipedia.org/wiki/Ncurses/)
[![OpenCV](https://img.shields.io/badge/OpenCV-4-green.svg)](https://opencv.org/)
[![Linux](https://img.shields.io/badge/Platform-Linux-blue.svg)](https://www.linux.org/)

## Introduction
C++ program that converts media files such .mp4 into ASCII characters.

## Getting started

## Dependencies

Before getting started with media-to-ascii, ensure that you have the following dependencies installed on your Linux system:

- **g++ compiler**

    ```Bash
    sudo apt install g++
    ```

- **CMake**

    ```Bash
    sudo apt install cmake
    ```

- **OpenCV 4**
    
    ```Bash
    sudo apt install libopencv-dev python3-opencv
    ```

- **nCurses 6**

    ```Bash
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```

### Installation
To use media-to-ascii, follow these steps
1. Clone the repository to your local machine:
```Bash
git clone https://www.github.com/garlinhs/media-to-ascii.git
```
2. Step into the repository:
```Bash
cd media-to-ascii
```

3. Compile the project with **make**:
```Bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. Now you will see the executable **media_to_ascii** and you can execute the program

- Without the audio
```Bash
./media_to_ascii ../resource/sample.mp4
```

- Without the audio
```Bash
./media_to_ascii -a ../resource/sample.mp3 ../resource/sample.mp4
```

## Contributing
Contributions are welcome from the community! Wheter it's bug fixes, feature enhancements, or new ideas, feel free to open an issue or submit a pull request.

## Author and Maintainer
- Garlinh Soler
- Email: garlinhs@gmail.com