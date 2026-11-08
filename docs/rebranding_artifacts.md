# Rebranding Work Remaining

This document tracks open rebranding work. Check current files before editing; paths below identify the work, not a historical inventory. Packaging build failures and dependency upgrades are tracked separately.

## Public repository and project destinations

- Update [README.md](../README.md) to reflect verified Linux build status without implying that AppImage or Flatpak runtime testing is complete. Correct its `RlyehPSX` clone URL and case-sensitive checkout directory to `RLyehPSX`.
- Review [STATE.md](../STATE.md) for the same repository-name casing and obsolete tasks that still call for removing DuckStation logos, names, and links. Keep genuine project lineage and historical development notes accurate.
- Confirm the issue and Discord pages used by [mainwindow.cpp](../src/RLyehPSX-qt/mainwindow.cpp) work before directing public users to them: `https://rlyeh.dev/issues.html` and `https://rlyeh.dev/discord.html`.
- After the GitHub repository is public, verify the `md-images` screenshot URLs and the revision-specific Flatpak manifest URL in [dev.rlyeh.rlyehpsx.metainfo.xml.in](../scripts/dev.rlyeh.rlyehpsx.metainfo.xml.in). Replace the current screenshots when new project images are available.

## Deferred Windows identity

Windows builds remain unsupported until the dedicated CMake/Ninja toolchain work. Preserve the remaining Visual Studio files as migration inputs; do not restore the retired solution as part of rebranding.

- Review DuckStation-named Windows resource and project files under [src/RLyehPSX-qt](../src/RLyehPSX-qt), [src/RLyehPSX-regtest](../src/RLyehPSX-regtest), and [src/updater](../src/updater) when the Windows toolchain is in scope. This includes `duckstation-qt.rc`, the remaining `.vcxproj` files, their filters, and the `.aps` resource file.
- Resolve the old `duckstation-qt` paths in [updater/CMakeLists.txt](../src/updater/CMakeLists.txt), [updater.rc](../src/updater/updater.rc), and [update_rc_version.bat](../src/scmversion/update_rc_version.bat) with that toolchain work. Check Windows resource metadata and copyright rendering during Windows validation.
- Revisit the Stenzek-hosted dependency sources in the deferred [Windows dependency scripts](../scripts/deps) when those builds become active. Select and verify dependency upstreams as part of that work, rather than changing URLs without checking their pins and hashes.

## Remaining internal text

- Review the DuckStation wording in [memmap.cpp](../src/common/memmap.cpp), [cheats.cpp](../src/core/cheats.cpp), and [displaywidget.cpp](../src/RLyehPSX-qt/displaywidget.cpp). The cheats comment may describe an inherited metadata format, so check its meaning before renaming it.
- Update the resource-header comments in [Qt resource.h](../src/RLyehPSX-qt/resource.h) and [updater resource.h](../src/updater/resource.h) when their Windows resource files are addressed.
- Decide whether the `DUCKSTATION-CHANGE` marker in vendored [ImGui](../dep/imgui/src/imgui.cpp) should become a project-owned marker when that dependency is next refreshed. Preserve the meaning of the local modification.

## Attribution boundary

Preserve upstream copyright, SPDX notices, contributor history, and genuine dependency provenance. DuckStation references in [README.md](../README.md), [CONTRIBUTORS.md](../CONTRIBUTORS.md), [RESPECT.md](../RESPECT.md), and the derivation comment in [gsvector_sse.h](../src/common/gsvector_sse.h) document lineage. The DuckStation Libretro entry in vendored rcheevos identifies an external core, not this application's identity.
