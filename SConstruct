#!/usr/bin/env python
# pylint: disable-all
import os
import sys
import toml

project_name = "gridmap-autotile"
project_version = "0.1.0-dev"

env = SConscript("godot-cpp/SConstruct")
env.Append(CPPPATH=["src/"])

sources = Glob("src/*.cpp")
sources = sources + Glob("src/editor/*.cpp")
target_path = f"project/addons/{project_name}/"

env["prefix"] = "libgd-"
library_type = f"{env["platform"]}.{env["target"]}.{env["arch"]}"
library_name = f"{env["prefix"]}{project_name}.{env["target"]}.{env["arch"]}"
library_path = env["platform"]

if env["platform"] == "macos":
  library_path = os.path.join(library_path, library_name + ".framework")
else:
  library_name += env["SHLIBSUFFIX"]

gdextension = {
  project_name: {
    "version": "0.1.0"
  },
  "configuration": {
    "entry_symbol": "gridmap_autotile_module_init",
    "compatibility_maximum": "4.4",
    "compatibility_minimum": "4.4",
    "reloadable": True
  },
  "libraries": {
    library_type: os.path.join(library_path, library_name)
  },
  "icons": {
    "GridMapAutoTile": "icons/GridMapAutoTile.svg"
  }
}

library = env.SharedLibrary(
  os.path.join(target_path, gdextension["libraries"][library_type]),
  source=sources,
)

def generate_gdextension_file(target, source, env):
  with open(str(target[0]), 'w') as f:
    f.write(toml.dumps(gdextension))
  return 0

gdextension_file = env.Command(os.path.join(target_path, f"{project_name}.gdextension"), library, generate_gdextension_file)

icons_target = os.path.join(target_path, "icons")
env.Install(
  icons_target, [
    os.path.join("resources/icons", os.path.basename(icon))
    for icon in gdextension["icons"].values()
  ]
)

Default(library, gdextension_file, icons_target)
