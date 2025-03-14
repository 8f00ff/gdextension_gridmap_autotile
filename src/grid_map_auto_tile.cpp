#include "grid_map_auto_tile.h"

#include "editor/grid_map_cache_editor_plugin.h"

#include <godot_cpp/core/print_string.hpp> // DEBUG

#include <godot_cpp/classes/mesh_library.hpp>

const std::map<int32_t, int32_t> GridMapAutoTile::ORIENTATIONS[] = {
	{{0, 0}},
	{{1, 0}, {2, 22}, {4, 10}, {8, 16}},
	{{3, 16}, {6, 0}, {9, 10}, {12, 22}},
	{{5, 0}, {10, 16}},
	{{7, 0}, {11, 16}, {13, 10}, {14, 22}},
	{{15, 0}}
};

const std::map<int, Vector3i> GridMapAutoTile::DIRECTIONS = {
	{NORTH, Vector3i(0, 0, -1)},
	{EAST, Vector3i(1, 0, 0)},
	{SOUTH, Vector3i(0, 0, 1)},
	{WEST, Vector3i(-1, 0, 0)}
};

void GridMapAutoTile::set_cell_item(const Vector3i &p_position, int32_t p_item, int32_t p_orientation) {
	String type = "";
	if (p_item == INVALID_CELL_ITEM) {
		#ifdef TOOLS_ENABLED
		if (grid_map_cache != nullptr && grid_map_cache->is_used_cell(p_position)) {
			uint32_t id = grid_map_cache->get_cell_item(p_position);
			type = get_cell_item_type(id);
		} else {
			type = get_cell_item_type(p_position);
		}
		#elif
		type = get_cell_item_type(p_position);
		#endif
	} else {
		type = get_cell_item_type(p_item);
	}
	
	String variant = get_cell_item_variant(p_item);
	if (p_item != INVALID_CELL_ITEM) {
		Dictionary target = calculate_autotiled_cell(p_position, p_item, variant);
		if (target.has("item")) {
			p_item = target["item"];
		}
		if (target.has("orientation")) {
			p_orientation = target["orientation"];
		}
	}
	
	GridMap::set_cell_item(p_position, p_item, p_orientation);
	emit_signal("cell_item_set", p_position, p_item, p_orientation);
	
	TypedArray<Vector3i> valid_neighbors = get_valid_neighbors(p_position, type);
	for (int i = 0; i < valid_neighbors.size(); i++) {
		Vector3i neighbor_position = valid_neighbors[i];
		int32_t neighbor_item = get_cell_item(neighbor_position);
		int32_t neighbor_orientation = get_cell_item_orientation(neighbor_position);
		String neighbor_variant = get_cell_item_variant(neighbor_item);
		
		Dictionary target = calculate_autotiled_cell(neighbor_position, neighbor_item, neighbor_variant);
		if (target.has("item")) {
			neighbor_item = target["item"];
		}
		if (target.has("orientation")) {
			neighbor_orientation = target["orientation"];
		}
		
		GridMap::set_cell_item(neighbor_position, neighbor_item, neighbor_orientation);
		emit_signal("cell_item_set", neighbor_position, neighbor_item, neighbor_orientation);
	}
}

int32_t GridMapAutoTile::get_cell_item(const Vector3i &p_position) const {
	return GridMap::get_cell_item(p_position);
}

String GridMapAutoTile::get_cell_item_name(const Vector3i &p_position) const {
	int32_t id = get_cell_item(p_position);
	if (id == INVALID_CELL_ITEM) {
		return "";
	}
	String name = get_mesh_library()->get_item_name(id);
	return name;
}

String GridMapAutoTile::get_cell_item_type(const String &p_name) const {
	PackedStringArray name_data = p_name.split("-");
	String type = name_data[0];
	return type;
}

String GridMapAutoTile::get_cell_item_type(const int32_t &p_id) const {
	if (p_id == INVALID_CELL_ITEM) {
		return "";
	}
	String name = get_mesh_library()->get_item_name(p_id);
	return get_cell_item_type(name);
}

String GridMapAutoTile::get_cell_item_type(const Vector3i &p_position) const {
	int32_t id = get_cell_item(p_position);
	if (id == INVALID_CELL_ITEM) {
		return "";
	}
	return get_cell_item_type(id);
}

int32_t GridMapAutoTile::get_cell_item_bitmask(const String &p_name) const {
	PackedStringArray name_data = p_name.split("-");
	int32_t bitmask = name_data[1].to_int();
	return bitmask;
}

int32_t GridMapAutoTile::get_cell_item_bitmask(const int32_t &p_id) const {
	if (p_id == INVALID_CELL_ITEM) {
		return -1;
	}
	String name = get_mesh_library()->get_item_name(p_id);
	return get_cell_item_bitmask(name);
}

int32_t GridMapAutoTile::get_cell_item_bitmask(const Vector3i &p_position) const {
	int32_t id = get_cell_item(p_position);
	if (id == INVALID_CELL_ITEM) {
		return INVALID_CELL_ITEM;
	}
	return get_cell_item_bitmask(id);
}

String GridMapAutoTile::get_cell_item_variant(const String &p_name) const {
	PackedStringArray name_data = p_name.split("-");
	String variant = "";
	if (name_data.size() >= 3) {
		variant = name_data[2];
	}
	return variant;
}

String GridMapAutoTile::get_cell_item_variant(const int32_t &p_id) const {
	if (p_id == INVALID_CELL_ITEM) {
		return "";
	}
	String name = get_mesh_library()->get_item_name(p_id);
	return get_cell_item_variant(name);
}

String GridMapAutoTile::get_cell_item_variant(const Vector3i &p_position) const {
	int32_t id = get_cell_item(p_position);
	if (id == INVALID_CELL_ITEM) {
		return "";
	}
	return get_cell_item_variant(id);
}

int32_t GridMapAutoTile::calculate_bitmask(const Vector3i &p_position, const String &p_type) const {
	String type = p_type;
	if (type.is_empty()) {
		type = get_cell_item_type(p_position);
	}
	int32_t bitmask = 0;
	
	for (const auto& pair : DIRECTIONS) {
		int32_t check_bitmask = pair.first;
		Vector3i check_position = p_position + pair.second;
		String check_type = get_cell_item_type(check_position);
		if (check_type == type) {
			bitmask |= check_bitmask;
		}
	}
	
	return bitmask;
}

TypedArray<Vector3i> GridMapAutoTile::get_valid_neighbors(const Vector3i &p_position, const String &p_type) const {
	String type = p_type;
	if (type.is_empty()) {
		type = get_cell_item_type(p_position);
	}
	TypedArray<Vector3i> valid_neighbors = TypedArray<Vector3i>();
	if (type.is_empty()) {
		return valid_neighbors;
	}
	
	for (const auto& pair : DIRECTIONS) {
		int32_t check_bitmask = pair.first;
		Vector3i check_position = p_position + pair.second;
		String check_type = get_cell_item_type(check_position);
		if (check_type == type) {
			valid_neighbors.append(check_position);
		}
	}
	
	return valid_neighbors;
}

Dictionary GridMapAutoTile::calculate_autotiled_cell(const Vector3i &p_position, const int32_t p_item, const String &variant) const {
	String type = get_cell_item_type(p_item);
	if (type.is_empty()) {
		return Dictionary();
	}
	int32_t bitmask = calculate_bitmask(p_position, type);
	int32_t target_item = INVALID_CELL_ITEM;
	int32_t target_orientation = 0;
	
	for (const auto& group : ORIENTATIONS) {
		if (group.find(bitmask) != group.end()) {
			for (const auto& pair : group) {
				int32_t equivalent = pair.first;
				String target_name = type + String("-") + itos(equivalent);
				String target_name_variant = target_name;
				if (!variant.is_empty()) {
					target_name_variant = type + String("-") + itos(equivalent) + String("-") + variant;
				}
				target_item = get_mesh_library()->find_item_by_name(target_name_variant);
				if (target_item == INVALID_CELL_ITEM) {
					target_item = get_mesh_library()->find_item_by_name(target_name);
				}
				if (target_item != INVALID_CELL_ITEM) {
					target_orientation = group.at(bitmask);
					break;
				}
			}
			if (target_item != INVALID_CELL_ITEM) {
				break;
			}
		}
	}
	
	Dictionary target = Dictionary();
	target["item"] = target_item;
	target["orientation"] = target_orientation;
	return target;
}

void GridMapAutoTile::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_cell_item", "position", "item", "orientation"), &GridMapAutoTile::set_cell_item, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_cell_item", "position"), &GridMapAutoTile::get_cell_item);
	
	BIND_ENUM_CONSTANT(NORTH);
	BIND_ENUM_CONSTANT(WEST);
	BIND_ENUM_CONSTANT(SOUTH);
	BIND_ENUM_CONSTANT(EAST);
	
	ADD_SIGNAL(MethodInfo("cell_item_set", PropertyInfo(Variant::VECTOR3I, "position"), PropertyInfo(Variant::INT, "item"), PropertyInfo(Variant::INT, "orientation")));
}

#ifdef TOOLS_ENABLED
GridMapCacheEditorPlugin* GridMapAutoTile::get_grid_map_cache() const {
	return grid_map_cache;
}

void GridMapAutoTile::set_grid_map_cache(GridMapCacheEditorPlugin *p_grid_map_cache) {
	grid_map_cache = p_grid_map_cache;
}
#endif
