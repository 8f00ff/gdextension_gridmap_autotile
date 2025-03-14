#pragma once

#ifdef TOOLS_ENABLED

#include "../grid_map_auto_tile.h"
#include <godot_cpp/classes/editor_plugin.hpp>

namespace std {
	template<>
	struct hash<Vector3i> {
		std::size_t operator()(const Vector3i& v) const {
			return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
		}
	};
}

class GridMapCacheEditorPlugin : public EditorPlugin {
	GDCLASS(GridMapCacheEditorPlugin, EditorPlugin);
	
private:
	GridMapAutoTile *node = nullptr;
	std::unordered_map<Vector3i, std::tuple<uint32_t, uint32_t>> cell_item_cache;
	
protected:
	void _notification(int p_what);
	static void _bind_methods();
	
public:
	void _on_cell_item_set(const Vector3i &p_position, int32_t p_item, int32_t p_orientation);
	virtual bool _handles(Object *p_object) const override;
	void _edit(GridMapAutoTile *p_gridmap);
	
	uint32_t get_cell_item(const Vector3i &p_position) const;
	uint32_t get_cell_item_orientation(const Vector3i &p_position) const;
	bool is_used_cell(const Vector3i &p_position) const;
	
	GridMapCacheEditorPlugin();
	~GridMapCacheEditorPlugin();
};

#endif // TOOLS_ENABLED
