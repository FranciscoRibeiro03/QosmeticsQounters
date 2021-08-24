#pragma once

#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Color.hpp"

class QountersUtils
{

    public: 
        static void setQounterTextWithColor(TMPro::TextMeshProUGUI* basicText, std::string text, UnityEngine::Color color);

};