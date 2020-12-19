# CC3K-villain

Chamber Crawler 3000

Project for OOP course

still many bugs to be fixed

## Attention

The program uses escape sequence to clear output before printing something new for each round.

```cpp
std::cout << "\ec";
```

However, this doesn't seems to work with **Win32 Console** on Windows. Since it's easy to switch to **Windows Terminal** on Win 10, I'm not planning to implement this specially for Windows by calling those Windows' Console APIs. 

However, it might be possible for me to introduce ncurses in the future.

## how to build

Change to the project dir and:

```bash
mkdir build
cd build
cmake ..
make 
../cc3k
```

binary file output path has been set to the `PROJECT_SOURECE_DIR` in `CMakeLists.txt`.
