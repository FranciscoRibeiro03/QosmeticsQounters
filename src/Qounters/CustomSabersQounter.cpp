#include "Qounters/CustomSabersQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/SaberAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomSabersQounter);

bool QosmeticsQounters::CustomSabersQounter::Enabled = true;
int QosmeticsQounters::CustomSabersQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomSabersQounter::Distance = 0.0f;

float QosmeticsQounters::CustomSabersQounter::FontSize = 35.0f;
bool QosmeticsQounters::CustomSabersQounter::ShowAuthor = false;

void QosmeticsQounters::CustomSabersQounter::Register() {
    QountersMinus::QounterRegistry::Register<QosmeticsQounters::CustomSabersQounter>("Custom Sabers", "Custom Sabers Qounter", "CustomSabersQounterConfig");
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomSabersQounter>({
        .ptr = &FontSize,
        .field = "FontSize",
        .displayName = "Font Size",
        .helpText = "Select the font size for the Custom Sabers Qounter. Default: 35.0",
        .type = QountersMinus::QounterRegistry::ConfigType::Float,
        .floatMin = 0.0f,
    });
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomSabersQounter>({
        .ptr = &ShowAuthor,
        .field = "ShowAuthor",
        .displayName = "Show Author",
        .helpText = "Show the author name on the Custom Sabers Qounter?",
        .type = QountersMinus::QounterRegistry::ConfigType::Bool,
    });
}

void QosmeticsQounters::CustomSabersQounter::Start() {
    getLogger().info("Started Sabers Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateSabers();
}

void QosmeticsQounters::CustomSabersQounter::UpdateSabers() {
    bool isCustomSaber = Qosmetics::SaberAPI::GetSaberIsCustom().value_or(false);
    std::string activeSaber = isCustomSaber ? Qosmetics::SaberAPI::GetActiveSaberDescriptor().value().get_name() : "Default";
    if (ShowAuthor) {
        activeSaber += isCustomSaber ? " by " + Qosmetics::SaberAPI::GetActiveSaberDescriptor().value().get_author() : "";
    }
    basicText->set_text(il2cpp_utils::createcsstr("Sabers: " + activeSaber));
    basicText->set_fontSize(FontSize);
}