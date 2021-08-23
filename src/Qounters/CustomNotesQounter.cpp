#include "Qounters/CustomNotesQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/NoteAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomNotesQounter);

bool QosmeticsQounters::CustomNotesQounter::Enabled = true;
int QosmeticsQounters::CustomNotesQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomNotesQounter::Distance = 1.0f;

float QosmeticsQounters::CustomNotesQounter::FontSize = 35.0f;

void QosmeticsQounters::CustomNotesQounter::Register() {
    QountersMinus::QounterRegistry::Register<QosmeticsQounters::CustomNotesQounter>("Custom Notes", "Custom Notes Qounter", "CustomNotesQounterConfig");
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomNotesQounter>({
        .ptr = &FontSize,
        .field = "FontSize",
        .displayName = "Font Size",
        .helpText = "Select the font size for the Custom Notes Qounter. Default: 35.0",
        .type = QountersMinus::QounterRegistry::ConfigType::Float,
        .floatMin = 0.0f,
    });
}

void QosmeticsQounters::CustomNotesQounter::Start() {
    getLogger().info("Started Notes Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateNotes();
}

void QosmeticsQounters::CustomNotesQounter::UpdateNotes() {
    std::string activeNote = Qosmetics::NoteAPI::GetNoteIsCustom().value_or(false) ? Qosmetics::NoteAPI::GetActiveNoteDescriptor().value().get_name() : "Default";
    basicText->set_text(il2cpp_utils::createcsstr("Notes: " + activeNote));
    basicText->set_fontSize(FontSize);
}