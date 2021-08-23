#pragma once

#include "custom-types/shared/macros.hpp"
#include "qounters-minus/shared/Qounter.hpp"
#include "qounters-minus/shared/QounterRegistry.hpp"

DECLARE_CLASS_CUSTOM(QosmeticsQounters, CustomNotesQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static int Distance;

    static float FontSize;
    static bool ShowAuthor;

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);

    DECLARE_INSTANCE_METHOD(void, UpdateNotes);
)