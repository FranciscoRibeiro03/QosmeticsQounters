#include "Qounters/CustomNotesQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/NoteAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomNotesQounter);

bool QosmeticsQounters::CustomNotesQounter::Enabled = true;
int QosmeticsQounters::CustomNotesQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomNotesQounter::Distance = 1.0f;

float QosmeticsQounters::CustomNotesQounter::FontSize = 35.0f;
bool QosmeticsQounters::CustomNotesQounter::ShowAuthor = false;

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
    QountersMinus::QounterRegistry::RegisterConfig<QosmeticsQounters::CustomNotesQounter>({
        .ptr = &ShowAuthor,
        .field = "ShowAuthor",
        .displayName = "Show Author",
        .helpText = "Show the author name on the Custom Notes Qounter?",
        .type = QountersMinus::QounterRegistry::ConfigType::Bool,
    });
}

void QosmeticsQounters::CustomNotesQounter::Start() {
    getLogger().info("Started Notes Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateNotes();
}

void QosmeticsQounters::CustomNotesQounter::UpdateNotes() {
    bool isCustomNote = Qosmetics::NoteAPI::GetNoteIsCustom().value_or(false);
    std::string activeNote = isCustomNote ? Qosmetics::NoteAPI::GetActiveNoteDescriptor().value().get_name() : "Default";
    if (ShowAuthor) {
        activeNote += isCustomNote ? " by " + Qosmetics::NoteAPI::GetActiveNoteDescriptor().value().get_author() : "";
    }
    basicText->set_text(il2cpp_utils::createcsstr("Notes: " + activeNote));
    basicText->set_fontSize(FontSize);
}