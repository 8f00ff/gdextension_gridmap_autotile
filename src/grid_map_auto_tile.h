#pragma once

#include <map>

#include <godot_cpp/classes/grid_map.hpp>

#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>

using namespace godot;

#ifdef TOOLS_ENABLED
class GridMapCacheEditorPlugin;
#endif

class GridMapAutoTile : public GridMap {
	GDCLASS(GridMapAutoTile, GridMap);
	
	void set_cell_item(const Vector3i &p_position, int32_t p_item, int32_t p_orientation = 0);
	int32_t get_cell_item(const Vector3i &p_position) const;
	
protected:
	
	static void _bind_methods();
	
	String get_cell_item_name(const int32_t &p_id) const;
	String get_cell_item_name(const Vector3i &p_position) const;
	
	String get_cell_item_type(const int32_t &p_id) const;
	String get_cell_item_type(const Vector3i &p_position) const;
	String get_cell_item_type(const String &p_name) const;
	
	int32_t get_cell_item_bitmask(const int32_t &p_id) const;
	int32_t get_cell_item_bitmask(const Vector3i &p_position) const;
	int32_t get_cell_item_bitmask(const String &p_name) const;
	
	String get_cell_item_variant(const int32_t &p_id) const;
	String get_cell_item_variant(const Vector3i &p_position) const;
	String get_cell_item_variant(const String &p_name) const;
	
	int32_t calculate_bitmask(const Vector3i &p_position, const String &p_type = "") const;
	TypedArray<Vector3i> get_valid_neighbors(const Vector3i &p_position, const String &p_type = "") const;
	
	Dictionary calculate_autotiled_cell(const Vector3i &p_position, const int32_t p_item, const String &variant = "") const;
	
	static const std::map<int32_t, int32_t> ORIENTATIONS[];
	static const std::map<int32_t, Vector3i> DIRECTIONS;
	
	#ifdef TOOLS_ENABLED
	GridMapCacheEditorPlugin *grid_map_cache = nullptr;
	#endif
	
public:
	enum Direction {
		NORTH = 1,
		EAST = 2,
		SOUTH = 4,
		WEST = 8
	};
	
	#ifdef TOOLS_ENABLED
	GridMapCacheEditorPlugin* get_grid_map_cache() const;
	void set_grid_map_cache(GridMapCacheEditorPlugin *p_grid_map_cache = nullptr);
	#endif
};

VARIANT_ENUM_CAST(GridMapAutoTile::Direction);
