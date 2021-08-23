#include "Qounters/CustomSabersQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/SaberAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomSabersQounter);

bool QosmeticsQounters::CustomSabersQounter::Enabled = true;
int QosmeticsQounters::CustomSabersQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomSabersQounter::Distance = 0.0f;

float QosmeticsQounters::CustomSabersQounter::FontSize = 35.0f;

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
}

void QosmeticsQounters::CustomSabersQounter::Start() {
    getLogger().info("Started Sabers Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateSabers();
}

void QosmeticsQounters::CustomSabersQounter::UpdateSabers() {
    std::string activeSaber = Qosmetics::SaberAPI::GetSaberIsCustom().value_or(false) ? Qosmetics::SaberAPI::GetActiveSaberDescriptor().value().get_name() : "Default";
    basicText->set_text(il2cpp_utils::createcsstr("Sabers: " + activeSaber));
    basicText->set_fontSize(FontSize);
}