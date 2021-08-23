#include "main.hpp"
#include "custom-types/shared/register.hpp"

#include "Qounters/CustomSabersQounter.hpp"
#include "Qounters/CustomNotesQounter.hpp"
#include "Qounters/CustomWallsQounter.hpp"

#include "qosmetics-api/shared/QosmeticsAPI.hpp"

// Idk why, but this is needed
DEFINE_TYPE(QountersMinus, InjectedComponents);
DEFINE_TYPE(QountersMinus, Qounter);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    // Ensure Qounters- is loaded
    getLogger().info("Ensuring Qounters- is loaded");
    Modloader::requireMod("qounters-minus", QOUNTERS_MINUS_VERSION);
    il2cpp_functions::Init();

    // Check if Qosmetics exists. If it doesn't, stop loading the mod (it doesn't make sense to have the mod in this case)
    getLogger().info("Ensuring Qosmetics is loaded");
    Modloader::requireMod("questcosmetics");
    if (!Qosmetics::API::GetExists()) return;

    // Register my own custom type
    getLogger().info("Registering custom types");
    custom_types::Register::AutoRegister();
    getLogger().info("Registering custom qounters");
    QosmeticsQounters::CustomSabersQounter::Register();
    QosmeticsQounters::CustomNotesQounter::Register();
    QosmeticsQounters::CustomWallsQounter::Register();
}