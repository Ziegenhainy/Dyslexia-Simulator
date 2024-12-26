#include "Geode/cocos/cocoa/CCGeometry.h"
#include "ccTypes.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

void shuffleString(std::string& str) {
    float dyslexiaChance = Mod::get()->getSettingValue<double>("dyslexia-percent")/100.0f;
    int strSize = str.size();
    int lo = 0;
    std::size_t hi = str.find_first_of('');
    while(hi!=strSize) {
        if (hi==std::string::npos) hi = strSize;
        for (int i = lo; i<hi; i++) {
            if ((float)rand()/RAND_MAX<=dyslexiaChance) {
                int randint = rand()%(hi-lo)+lo;
                const char tmp = str[i];
                str[i] = str[randint];
                str[randint] = tmp;
            }
        }
        if (hi != strSize) {
            lo = ++hi;
            hi = str.find_first_of('', hi);
        }
    }
}

class $modify(HookedCCLabelBMFont, CCLabelBMFont) {
    bool initWithString(char const* str, char const* fntFile, float width, cocos2d::CCTextAlignment alignment, cocos2d::CCPoint imageOffset) {
        std::string cpstr = str == nullptr ? "" : str;
        shuffleString(cpstr);
        if (!CCLabelBMFont::initWithString(cpstr.c_str(), fntFile, width, alignment, imageOffset)) return false;
        return true;
    }

    virtual void setString(char const* newString) {
        std::string cpstr = newString == nullptr ? "" : newString;
        shuffleString(cpstr);
        CCLabelBMFont::setString(cpstr.c_str());
    }

    // virtual void setString(char const* newString, bool needUpdateLabel) {
    //     std::string cpstr = newString == nullptr ? "" : newString;
    //     shuffleString(cpstr);
    //     CCLabelBMFont::setString(cpstr.c_str(), needUpdateLabel);
    // }
};
