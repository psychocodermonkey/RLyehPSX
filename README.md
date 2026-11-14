# R'Lyeh PSX

<p align="center">
  <img src="data/resources/images/vaulketh.png" alt="Vaul'keth, the R'Lyeh PSX mascot" width="300" />
</p>

[What you can do](#what-you-can-do) · [Project status](#project-status) · [Getting started](#getting-started) · [Building](#building) · [Project lineage and licensing](#project-lineage-and-licensing)

R'Lyeh PSX is an experimental PlayStation emulator derived from the GPL-licensed [DuckStation-GPL](https://github.com/Trixarian/duckstation-gpl) codebase. This independent project is focused on maintaining and evolving that foundation across platforms.

The project is in active development. Expect incomplete functionality and regressions; build and runtime validation are ongoing. R'Lyeh PSX does not currently provide a supported Windows build.

## What you can do

R'Lyeh PSX features:

- Game library management.
- Desktop and BigScreen UI Modes.
- Memory card and save state management.
- Controller and DualShock controller support.
- Connect to RetroAchievements (in progress).

## Project status

| Platform | Current state |
| --- | --- |
| macOS | Debug build and application launch have been validated. |
| Linux | Debug build and game launch have been validated; platform integration and packaging remain in progress. |
| Windows | Build support is deferred while the macOS and Linux paths stabilize. |
| Android | Research and planning only. |

Recent development has included an SDL3 migration, dependency updates, replacement of the audio-stream and software-rasterizer subsystems, and the R'Lyeh PSX identity migration. The Git history records those changes and their validation. The [development workflow](docs/developer/process/development_workflow.md) and [dependency inventory](docs/developer/dependencies/vendored_dependencies.md) provide more technical context.

## Getting started

Source builds are the documented way to run the current development version. See [Building](#building) for the platform guides.

You need a PlayStation BIOS image to run games. R'Lyeh PSX does not include one. After launching the application, use the setup wizard to select your BIOS directory and add your game library.

## Building

The dependency scripts build third-party components into a local `deps/` directory. See the platform guides for prerequisites, commands, and build output:

- [Build on macOS](docs/developer/building/macos.md)
- [Build on Linux](docs/developer/building/linux.md)

Windows builds are [not yet supported](docs/developer/building/windows_build_documentation.md).

## Project lineage and licensing

R'Lyeh PSX is an independent fork of DuckStation-GPL. The original DuckStation and DuckStation-GPL contributors deserve credit for the architecture, design, and implementation that form the foundation of this repository. Much of the current codebase originated from their work.

R'Lyeh PSX is not the official DuckStation project and is not affiliated with, endorsed by, or supported by the DuckStation developers. Issues introduced by this fork should be reported to this project, not upstream.

R'Lyeh PSX is subject to the terms of its [license](LICENSE). Preserve the applicable third-party licenses, notices, and contributor attribution when redistributing the project.

"PlayStation" and "PSX" are trademarks of Sony Interactive Entertainment. R'Lyeh PSX is not affiliated with Sony Interactive Entertainment.

## AI Usage

AI tools are used in this project as development support for understanding the codebase, tracking build nuances, reviewing changes, investigating issues, and improving documentation.

AI-generated output is not treated as authoritative. Contributions are expected to be reviewed, tested, and understood by the person submitting them. AI may be used by contributors, but it must be used as tooling, not as a substitute for engineering judgment.

This project allows AI-assisted work. It does not accept unchecked AI-generated code, broad automated rewrites, or changes that the contributor cannot explain and maintain.
