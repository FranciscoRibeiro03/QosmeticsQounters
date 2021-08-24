#include "Utils/QountersUtils.hpp"
#include "Utils/TextUtils.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

void QountersUtils::setQounterTextWithColor(TMPro::TextMeshProUGUI* basicText, std::string text, UnityEngine::Color color, bool forceRainbow = false) {
    if (TextUtils::shouldRainbow(text) || forceRainbow) {
        basicText->set_text(il2cpp_utils::newcsstr(TextUtils::rainbowify(text)));
    } else {
        basicText->set_text(il2cpp_utils::newcsstr(text));
        basicText->set_color(color);
    }
}