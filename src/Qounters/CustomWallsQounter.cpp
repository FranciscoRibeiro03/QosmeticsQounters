#include "Qounters/CustomWallsQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/WallAPI.hpp"

#include "Utils/QountersUtils.hpp"
#include "Utils/TextUtils.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomWallsQounter);

bool QosmeticsQounters::CustomWallsQounter::Enabled = true;
int QosmeticsQounters::CustomWallsQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomWallsQounter::Distance = 2.0f;

float QosmeticsQounters::CustomWallsQounter::FontSize = 35.0f;
bool QosmeticsQounters::CustomWallsQounter::ShowAuthor = false;
bool QosmeticsQounters::CustomWallsQounter::RainbowText = false;
UnityEngine::Color QosmeticsQounters::CustomWallsQounter::TextColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);

void QosmeticsQounters::CustomWallsQounter::Register() {
    QountersMinus::QounterRegistry::Register<QosmeticsQounters::CustomWallsQounter>("Custom Walls", "Custom Walls Qounter", "CustomWallsQounterConfig");
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomWallsQounter>({
        .ptr = &FontSize,
        .field = "FontSize",
        .displayName = "Font Size",
        .helpText = "Select the font size for the Custom Walls Qounter. Default: 35.0",
        .type = QountersMinus::QounterRegistry::ConfigType::Float,
        .floatMin = 0.0f,
    });
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomWallsQounter>({
        .ptr = &ShowAuthor,
        .field = "ShowAuthor",
        .displayName = "Show Author",
        .helpText = "Show the author name on the Custom Walls Qounter?",
        .type = QountersMinus::QounterRegistry::ConfigType::Bool,
    });
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomWallsQounter>({
        .ptr = &RainbowText,
        .field = "RainbowText",
        .displayName = TextUtils::rainbowify("Rainbow") + " Text",
        .helpText = "Make the color of this Qounter " + TextUtils::rainbowify("rainbow") + ". NOTE: Overrides the Text Color config!",
        .type = QountersMinus::QounterRegistry::ConfigType::Bool,
    });
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomWallsQounter>({
        .ptr = &TextColor,
        .field = "TextColor",
        .displayName = "Text Color",
        .helpText = "Select the text color for the Custom Walls Qounter.",
        .type = QountersMinus::QounterRegistry::ConfigType::Color,
    });
}

void QosmeticsQounters::CustomWallsQounter::Start() {
    getLogger().info("Started Walls Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateWalls();
}

void QosmeticsQounters::CustomWallsQounter::UpdateWalls() {
    bool isCustomWall = Qosmetics::WallAPI::GetWallIsCustom().value_or(false);
    std::string activeWall = isCustomWall ? Qosmetics::WallAPI::GetActiveWallDescriptor().value().get_name() : "Default";
    if (ShowAuthor) {
        activeWall += isCustomWall ? " by " + Qosmetics::WallAPI::GetActiveWallDescriptor().value().get_author() : "";
    }
    basicText->set_fontSize(FontSize);
    std::string textToShow = "Walls: " + activeWall;
    QountersUtils::setQounterTextWithColor(basicText, textToShow, TextColor, RainbowText);
}