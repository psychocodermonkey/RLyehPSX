# R'Lyeh PSX

An experimental PlayStation (PS1) emulator project derived from the GPL-licensed [DuckStation-GPL](https://github.com/Trixarian/duckstation-gpl) codebase.

## Project Status

**Early Development - macOS build succeeds - Other platforms are not yet validated.**

R'Lyeh PSX is an independent fork intended for long-term experimentation, maintenance, and feature development. The project is still undergoing dependency modernization, library migration, and validation work, but the macOS build path has been brought to a successful build state.

Recent work includes:

- PlutoVG integration as a first-class dependency.
- PlutoSVG dependency chain modernization.
- Dear ImGui 1.92.x migration work.
- Build system maintenance and cleanup.
- Dependency version updates and validation.

Expect incomplete functionality, regressions, unfinished features, and build failures on unvalidated platforms.

## About

R'Lyeh PSX began as a fork of the GPL-licensed DuckStation-GPL project.

The original DuckStation and DuckStation-GPL contributors deserve full credit for the architecture, design, and implementation of the emulator that serves as the foundation for this repository. The overwhelming majority of the current codebase originated from their work.

This repository exists to support independent experimentation, maintenance, and future development under the R'Lyeh PSX project.

## Relationship to Upstream Projects

R'Lyeh PSX is:

- Derived from the DuckStation-GPL codebase.
- Licensed in accordance with the GPL requirements of the upstream project.
- An independent project.

R'Lyeh PSX is not:

- The official DuckStation project.
- Endorsed by the DuckStation developers.
- Supported by the DuckStation developers.
- Maintained by the DuckStation developers.
- Affiliated with the DuckStation project beyond its GPL heritage.

Questions, bugs, regressions, broken builds, and questionable engineering decisions introduced by this repository belong to R'Lyeh PSX, not upstream.

## Current Goals

Current areas of investigation include:

- Continued modernization of third-party dependencies.
- Dear ImGui compatibility updates.
- Build system improvements.
- Enhanced game library management.
- Multi-disc and M3U workflow improvements.
- Future Android support research.
- Long-term maintainability improvements.

## Building

At the time of writing, the macOS build path is the only validated build path.

Other platform build instructions and support documentation will be updated as the project stabilizes.

## Licensing

R'Lyeh PSX incorporates code derived from GPL-licensed projects and remains subject to the terms of those licenses.

See the repository license files and third-party notices for complete licensing information. Their contributor lists, licenses, copyright notices, and attribution files belong to those projects and should be preserved in place.

## Disclaimer

This repository is currently a development and learning project.

If you are looking for a stable, production-ready PlayStation emulator, this is not it.

At least not yet.

## AI Usage

AI tools are used in this project as development support for understanding the codebase, tracking build nuances, reviewing changes, investigating issues, and improving documentation.

AI-generated output is not treated as authoritative. Contributions are expected to be reviewed, tested, and understood by the person submitting them. AI may be used by contributors, but it must be used as tooling, not as a substitute for engineering judgment.

This project allows AI-assisted work. It does not accept unchecked AI-generated code, broad automated rewrites, or changes that the contributor cannot explain and maintain.
