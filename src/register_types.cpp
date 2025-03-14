#ifndef _3D_DISABLED

#include "register_types.h"

#include "grid_map_auto_tile.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#ifdef TOOLS_ENABLED
#include "editor/grid_map_cache_editor_plugin.h"
#endif

using namespace godot;

void initialize_gridmap_autotile_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		GDREGISTER_CLASS(GridMapAutoTile);
	}
	#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		GDREGISTER_CLASS(GridMapCacheEditorPlugin);
		EditorPlugins::add_by_type<GridMapCacheEditorPlugin>();
	}
	#endif
}

void uninitialize_gridmap_autotile_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gridmap_autotile_module_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gridmap_autotile_module);
	init_obj.register_terminator(uninitialize_gridmap_autotile_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}

#endif // _3D_DISABLED
