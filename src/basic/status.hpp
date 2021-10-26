#ifndef CHARCTER_STATUS
#define CHARCTER_STATUS

struct CharacterStatus {
    int health;
    int atk;
    int def;
    CharacterStatus() : health(0), atk(0), def(0) {}
    CharacterStatus(int _h, int _a, int _d) : health(_h), atk(_a), def(_d) {}
};

using CStatus = CharacterStatus;

#endif
