# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- New node GridMapAutoTile that extends GridMap with autotiling capabilities
- Support for special naming scheme in MeshLibrary: `type-bitmask[-variant]`
- Autotiling logic for 4 cardinal directions using bitmasks to define tile types and connections
- Automatic rotation of tiles to match equivalent bitmasks
- SConstruct build configuration
- Initial project structure

[unreleased]: https://github.com/8f00ff/gdextension_gridmap_autotile/compare/v0.1.0-dev...HEAD
