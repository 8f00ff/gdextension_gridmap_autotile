[![GridMapAutoTile GDExtension](https://img.shields.io/badge/GridMapAutoTile-GDExtension-545454?labelColor=%237f00ff)](https://github.com/8f00ff/gdextension_gridmap_autotile)
[![Made with Godot](https://img.shields.io/badge/Godot%20Engine%204.4-478CBF?logo=godotengine&logoColor=fff&style=flat)](https://godotengine.org/releases/4.4/)

[<img src="https://raw.githubusercontent.com/ZoeBijl/QueerCats/refs/heads/main/MorningCoffee/SVG/QueerCatMorningCoffee_Progress.svg" width="48" height="48" alt="Morning Pride Cat"/>](https://github.com/ZoeBijl/QueerCats)

## Overview

Autotiling, sort of...

GridMapAutoTile is an enhanced version of Godot's built-in GridMap node, with autotiling capabilities added on top. It's GridMap, but with a bit of extra magic to help you create somewhat-seamless tile arrangements with minimal effort. For now, it only supports 4 cardinal directions (because, priorities!), but it might just save you from a few hours of tedious tile placement.

## Usage

<!-- ### How it works

- Name your tiles using the `type-bitmask[-variant]` format
- GridMapAutoTile analyzes neighboring tiles and swaps them with the correct variants
- Supports 4 cardinal directions (no diagonals or y-axis layers... yet!) -->

To use GridMapAutoTile, you'll need to create a GridMapAutoTile node in your scene instead of a regular GridMap node. From there, everything works the same way as GridMap, but with the added autotiling magic.

### Naming your MeshLibrary items

To make autotiling work, you'll need to name your MeshLibrary items using a specific scheme:

```
type-bitmask[-variant]
```

- `type` is a string that identifies the type of tile (e.g., "wall", "floor", etc.).
- `bitmask` is a number that defines the tile's connections (see below).
- `variant` is an optional string that identifies a specific variant of the tile.

### Tile Connections & Bitmasks

GridMapAutoTile uses a simple bitmask system to determine how tiles connect. Each cardinal direction gets its own number:

- NORTH (negative Z): `1`
- EAST (positive X): `2`
- SOUTH (positive Z): `4`
- WEST (negative X): `8`

To create tiles with specific connections, just add these numbers together! For example:
- A straight pipe going East to West? That's 2+8=10
- A corner piece connecting North and East? That's 1+2=3
- T-junction open on three sides? Just add the directions you need

### Automatic Rotations

The best part - you only need ONE mesh for each tile type! The system automatically rotates your tiles to match whatever connections are needed.

For consistency, create your base tiles with these orientations:
- Edge tiles: Connecting to the North
- Corner tiles: Connecting to North and East 
- Straight tiles: Connecting North to South
- T-junctions: Connecting in all directions except West

### Placing tiles

To place regular tiles, simply place any tile of the same type, and GridMapAutoTile will autotile it for you. For variants, place the variant tile, and it will be used when autotiling allows for it.

### Compatibility with GridMap

GridMapAutoTile is fully compatible with GridMap, and you can convert back and forth between the two by selecting "Change Type..." on the node. However, be careful when doing so, as this may affect your scene's layout.

**Make sure to backup your scene before making any changes, just in case.**

## TODO

Some of the (ambitiously) planned features:

- Support for diagonal connections
- Support for connections on Y-axis, both above and below
- Improve the autotiling logic to be more in line with how 2D tilemaps work
- Create a UI similar to 2D TileMaps (Terrains) to assign bitmasks and variants, instead of relying on item names in the MeshLibrary

I am planning to tackle them all... when I can muster up the time and motivation. No promises, no timelines, but I'm hoping to get to them eventually.

If you're interested in helping out or [contributing](#contributing) in any way, you are more than welcome!

## Installation

Official binaries coming eventually! For now, see [Building](#Building) section below to run from source.

## Building

For more information, see [Compiling the plugin](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#compiling-the-plugin) sections of Godot's GDExtension C++ example.

### Prerequisites

- `scons`
- `python-toml`

### Steps

`scons platform=<windows|macos|linux|bsd|linuxbsd> target=<editor|release>`

## Changelog

[![GitHub Tag](https://img.shields.io/github/v/tag/8f00ff/gdextension_gridmap_autotile)](https://github.com/8f00ff/gdextension_gridmap_autotile/tags)
[![GitHub Release](https://img.shields.io/github/v/release/8f00ff/gdextension_gridmap_autotile)](https://github.com/8f00ff/gdextension_gridmap_autotile/releases)

See the [CHANGELOG.md](CHANGELOG.md) file for a detailed list of changes.

## Contributing

See the [Contributing Guidelines](CONTRIBUTING.md) for more information.

## License

[![GitHub License](https://img.shields.io/github/license/8f00ff/gdextension_gridmap_autotile)](LICENSE.md)

This project is licensed under [GNU Lesser General Public License (LGPL-3.0)](https://www.gnu.org/licenses/lgpl-3.0.en.html) - see the [LICENSE.md](LICENSE.md) file for details.

The demo project included in this repository is licensed separately under the [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0) license. See the respective [LICENSE](project/LICENSE) file for details.

This project also has specific attribution requirements - see the [Attribution Requirements](CONTRIBUTING.md#attribution-requirements) section of the [Contributing Guidelines](CONTRIBUTING.md).

## Attributions

For attribution information including third-party assets and tools used in this project, see [ATTRIBUTIONS.md](ATTRIBUTIONS.md).
