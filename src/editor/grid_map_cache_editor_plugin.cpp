#include "grid_map_cache_editor_plugin.h"

#include <godot_cpp/core/print_string.hpp> // DEBUG

#include <unordered_map>

#ifdef TOOLS_ENABLED

void GridMapCacheEditorPlugin::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			if (node != nullptr && !node->is_connected("cell_item_set", Callable(this, "_on_cell_item_set"))) {
				node->connect("cell_item_set", Callable(this, "_on_cell_item_set"));
				node->set_grid_map_cache(this);
			}
		} break;
		case NOTIFICATION_EXIT_TREE: {
			if (node != nullptr && node->is_connected("cell_item_set", Callable(this, "_on_cell_item_set"))) {
				node->disconnect("cell_item_set", Callable(this, "_on_cell_item_set"));
				node->set_grid_map_cache(nullptr);
			}
		} break;
	}
}

bool GridMapCacheEditorPlugin::_handles(Object *p_object) const {
	return p_object->is_class("GridMapAutoTile");
}

void GridMapCacheEditorPlugin::_edit(GridMapAutoTile *p_gridmap) {
	if (node != nullptr && node->is_connected("cell_item_set", Callable(this, "_on_cell_item_set"))) {
		node->disconnect("cell_item_set", Callable(this, "_on_cell_item_set"));
		node->set_grid_map_cache(nullptr);
	}
	
	node = p_gridmap;
	
	if (node != nullptr && !node->is_connected("cell_item_set", Callable(this, "_on_cell_item_set"))) {
		node->connect("cell_item_set", Callable(this, "_on_cell_item_set"));
		node->set_grid_map_cache(this);
	}
}

void GridMapCacheEditorPlugin::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_cell_item_set", "position", "item", "orientation"), &GridMapCacheEditorPlugin::_on_cell_item_set);
	
	ClassDB::bind_method(D_METHOD("get_cell_item", "position"), &GridMapCacheEditorPlugin::get_cell_item);
	ClassDB::bind_method(D_METHOD("get_cell_item_orientation", "position"), &GridMapCacheEditorPlugin::get_cell_item_orientation);
	ClassDB::bind_method(D_METHOD("is_used_cell", "position"), &GridMapCacheEditorPlugin::is_used_cell);
}

void GridMapCacheEditorPlugin::_on_cell_item_set(const Vector3i &p_position, int32_t p_item, int32_t p_orientation) {
	if (p_item == -1) {
		cell_item_cache.erase(p_position);
	} else {
		cell_item_cache[p_position] = std::tuple<int32_t, int32_t>(p_item, p_orientation);
	}
}

uint32_t GridMapCacheEditorPlugin::get_cell_item(const Vector3i &p_position) const {
	return std::get<0>(cell_item_cache.at(p_position));
}

uint32_t GridMapCacheEditorPlugin::get_cell_item_orientation(const Vector3i &p_position) const {
	return std::get<1>(cell_item_cache.at(p_position));
}

bool GridMapCacheEditorPlugin::is_used_cell(const Vector3i &p_position) const {
	return cell_item_cache.count(p_position) > 0;
}

GridMapCacheEditorPlugin::GridMapCacheEditorPlugin() {}
GridMapCacheEditorPlugin::~GridMapCacheEditorPlugin() {}

#endif // TOOLS_ENABLED
