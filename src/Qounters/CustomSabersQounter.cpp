#include "Qounters/CustomSabersQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/SaberAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomSabersQounter);

bool QosmeticsQounters::CustomSabersQounter::Enabled = true;
int QosmeticsQounters::CustomSabersQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomSabersQounter::Distance = 0.0f;

void QosmeticsQounters::CustomSabersQounter::Register() {
    QountersMinus::QounterRegistry::Register<QosmeticsQounters::CustomSabersQounter>("Custom Sabers", "Custom Sabers Qounter", "CustomSabersQounterConfig");
}

void QosmeticsQounters::CustomSabersQounter::Start() {
    getLogger().info("Started Sabers Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateSabers();
}

void QosmeticsQounters::CustomSabersQounter::UpdateSabers() {
    std::string activeSaber = Qosmetics::SaberAPI::GetSaberIsCustom().value_or(false) ? "Custom" : "Default";
    basicText->set_text(il2cpp_utils::createcsstr("Sabers: " + activeSaber));
}