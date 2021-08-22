#include "Qounters/CustomNotesQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"
#include "qosmetics-api/shared/NoteAPI.hpp"

DEFINE_TYPE(QosmeticsQounters, CustomNotesQounter);

bool QosmeticsQounters::CustomNotesQounter::Enabled = true;
int QosmeticsQounters::CustomNotesQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QosmeticsQounters::CustomNotesQounter::Distance = 1.0f;

void QosmeticsQounters::CustomNotesQounter::Register() {
    QountersMinus::QounterRegistry::Register<QosmeticsQounters::CustomNotesQounter>("Custom Notes", "Custom Notes Qounter", "CustomNotesQounterConfig");
}

void QosmeticsQounters::CustomNotesQounter::Start() {
    getLogger().info("Started Notes Qounter!");
    srand((unsigned int)time(0));
    CreateBasicText("");
    UpdateNotes();
}

void QosmeticsQounters::CustomNotesQounter::UpdateNotes() {
    std::string activeNote = Qosmetics::NoteAPI::GetNoteIsCustom().value_or(false) ? "Custom" : "Default";
    basicText->set_text(il2cpp_utils::createcsstr("Notes: " + activeNote));
}