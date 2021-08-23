#include "Qounters/CustomWallsQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/WallAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomWallsQounter);

bool QosmeticsQounters::CustomWallsQounter::Enabled = true;
int QosmeticsQounters::CustomWallsQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomWallsQounter::Distance = 2.0f;

float QosmeticsQounters::CustomWallsQounter::FontSize = 35.0f;

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
}

void QosmeticsQounters::CustomWallsQounter::Start() {
    getLogger().info("Started Walls Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateWalls();
}

void QosmeticsQounters::CustomWallsQounter::UpdateWalls() {
    std::string activeNote = Qosmetics::WallAPI::GetWallIsCustom().value_or(false) ? Qosmetics::WallAPI::GetActiveWallDescriptor().value().get_name() : "Default";
    basicText->set_text(il2cpp_utils::createcsstr("Walls: " + activeNote));
    basicText->set_fontSize(FontSize);
}