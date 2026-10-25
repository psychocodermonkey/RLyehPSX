# Rebranding Artifacts

This document records the completed image-rebranding pass and the remaining DuckStation/R'Lyeh PSX inventory. The detailed tables below retain findings verified against the current repository. Line numbers are historical and should be checked against current source before editing. Upstream attribution, legal notices, compatibility identifiers, and external service identities are not ordinary text replacements.

## Completed image-rebranding pass

The DuckStation-specific logos and application icons have been replaced with the new R'Lyeh PSX/Vaulketh assets. The old tracked binary assets were removed from the working tree and the new assets are present as their replacements.

| Original asset                                      | Replacement asset                                       | Type and role                             |
|-----------------------------------------------------|---------------------------------------------------------|-------------------------------------------|
| `data/resources/images/duck.png`                    | `data/resources/images/vaulketh.png`                    | PNG, 498×498; fullscreen UI logo          |
| `scripts/org.duckstation.DuckStation.png`           | `scripts/dev.rlyeh.rlyehpsx.png`                        | PNG, 512×512; Linux/AppImage/Flatpak icon |
| `src/duckstation-qt/DuckStation.icns`               | `src/RLyehPSX-qt/RLyehPSX.icns`                         | macOS ICNS application icon               |
| `src/duckstation-qt/duckstation-qt.ico`             | `src/RLyehPSX-qt/rlyehpsx-qt.ico`                       | Windows ICO application/updater icon      |
| `src/duckstation-qt/resources/icons/duck.png`       | `src/RLyehPSX-qt/resources/icons/vaulketh.png`          | PNG, 260×260; Qt application/dialog icon  |
| `src/duckstation-qt/resources/icons/duck_64.png`    | `src/RLyehPSX-qt/resources/icons/vaulketh_64.png`       | PNG, 64×64; Qt icon variant               |
| `src/duckstation-qt/resources/icons/duck_128.png`   | `src/RLyehPSX-qt/resources/icons/vaulketh_128.png`      | PNG, 128×128; Qt icon variant             |
| `src/duckstation-qt/resources/icons/UpdateDuck.png` | `src/RLyehPSX-qt/resources/icons/UpdateVaulketh.png`    | PNG, 48×48; updater illustration          |

### Completed reference updates

- Core fullscreen references in `src/core/fullscreen_ui.cpp` and `src/core/imgui_overlays.cpp` now load `images/vaulketh.png`.
- Qt resource registration in `src/RLyehPSX-qt/resources/RLyehPSX-qt.qrc` now lists the Vaulketh assets.
- Qt UI/source references now use `:/icons/vaulketh.png`, `:/icons/vaulketh_64.png`, and `:/icons/UpdateVaulketh.png`.
- Windows references in `duckstation-qt.rc`, the Visual Studio project/filter files, and `src/updater/updater.rc` now use `rlyehpsx-qt.ico`.
- macOS references in `src/RLyehPSX-qt/CMakeLists.txt` and `Info.plist.in` now use `RLyehPSX.icns`.
- AppImage packaging now uses `scripts/dev.rlyeh.rlyehpsx.png`.
- Flatpak packaging now sources the new PNG while retaining the existing installed icon filename and package identity.

### Validation completed

- All replacement assets exist and all Qt `.qrc` entries resolve.
- Qt resource/UI XML files validate successfully.
- No stale image asset references remain in source, packaging, or build configuration outside documentation/build artifacts.
- `git diff --check` passed.
- The macOS preset build completed successfully after removing the stale existing `DuckStation.app` bundle. The rebuilt bundle contains `RLyehPSX.icns` and no longer retains the old `DuckStation.icns` artifact.
- A full Qt dependency rebuild was not required; the earlier direct-build failure was caused by the pre-existing local `uic` execution/toolchain environment.

### After the image pass

Later checkpoints renamed the executable, macOS bundle, supported-build targets, resource bundle, and user-data roots. They also set the macOS app and nested updater bundle IDs to `dev.rlyeh.rlyehpsx` and `dev.rlyeh.rlyehpsx.updater`. Linux Flatpak/application and desktop-entry identifiers, package migration behavior, and third-party UI/service icons remain outside those completed changes.

## Remaining rebranding work gathered from the prior inventory

The remaining work is grouped below. The old `.github` issue templates and workflows are no longer tracked; project-specific release automation will be designed when releases are in scope.

1. **Linux package identity.** Coordinate the desktop entry, AppStream metadata, Flatpak manifest, AppImage packaging, and their references around the proposed `dev.rlyeh.rlyehpsx` ID. A changed Flatpak ID creates a separate application identity.
2. **User-visible branding and public destinations.** Review remaining Qt/fullscreen/updater strings, About and setup text, package metadata, documentation, issue/help/community links, and the public contact address. Distinguish inherited attribution and dependency URLs from active product branding.
3. **Compatibility-sensitive identifiers.** Decide separately whether to retain or rename PINE socket/version strings, shared-memory names, RetroAchievements client identity, and external rcheevos keys. Preserve save-state format identifiers unless an explicit compatibility policy calls for a format change. User-data directories have already been renamed without migration from DuckStation.
4. **Release integration.** The updater's GitHub API URLs now point to `psychocodermonkey/RLyehPSX`, but matching release assets, project-specific Actions, and end-to-end update checks remain deferred. `latest` and `preview` are channel tags; planned Pnakotic public versions are separate.
5. **Localization and platform deferrals.** CMake now selects only the renamed English project catalog; non-English catalogs were removed while translation support and maintenance helpers were retained. Reintroducing other languages is deferred. Windows build tooling and remaining migration-input project files remain outside the active macOS/Linux path.
6. **Attribution review.** Project SPDX headers now use `RLyehPSX`, the repository URL, and `GPL-3.0-only`; the project notice was aligned with GPL v3. Preserve upstream copyright, license, contributor, and lineage material while reviewing remaining third-party notices separately.

The `User-Visible Branding` and `Internal Branding` tables list findings still present in the current files. The `Third-Party Attribution` table remains a preservation inventory. Check historical line numbers against current source before editing.

### Remaining public identity choices

| Artifact | Current value | Proposed or undecided value |
|---|---|---|
| Linux Flatpak/AppID | `org.duckstation.DuckStation` | `dev.rlyeh.rlyehpsx` |
| Linux desktop/AppStream ID | `org.duckstation.DuckStation` | Coordinate with the Flatpak ID |
| Public contact | Inherited upstream addresses in package metadata | Confirm a R'Lyeh PSX address before publishing |
| Windows product metadata | Remaining upstream values | Deferred with Windows tooling |

### High-risk non-legal decision points

<style>
  .rebranding-table-wrap { overflow-x: auto; margin: 0.75rem 0 1rem; }
  .rebranding-table { width: 100%; border-collapse: collapse; table-layout: fixed; }
  .rebranding-table th, .rebranding-table td { padding: 0.3rem 0.45rem; text-align: left; vertical-align: top; overflow-wrap: anywhere; word-break: break-word; }
  .rebranding-table th { font-weight: 600; }
  .rebranding-table th, .rebranding-table td { border: 1px solid currentColor; }
</style>

<div class="rebranding-table-wrap">
<table class="rebranding-table">
  <thead>
    <tr>
      <th>Current value</th>
      <th>File</th>
      <th>Lines</th>
      <th>Why it is high risk</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>147</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
    </tr>
    <tr>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/flatpak/.gitignore</code></td>
      <td>4</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
    </tr>
    <tr>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td>1, 84-85, 88-89</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
    </tr>
    <tr>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
    </tr>
    <tr>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
    </tr>
    <tr>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
    </tr>
    <tr>
      <td><code>DuckStation</code></td>
      <td><code>src/core/achievements.cpp</code></td>
      <td>3323</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>duckstation</code></td>
      <td><code>src/core/bus.cpp</code></td>
      <td>205</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/core/pine_server.cpp</code></td>
      <td>143, 145, 448</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>SAVE_STATE_MAGIC = 0x43435544</code>, <code>SAVE_STATE_VERSION = 71</code>, <code>SAVE_STATE_HEADER</code></td>
      <td><code>src/core/save_state_version.h</code></td>
      <td>8-10, 15-52</td>
      <td>Save-state magic and version constants define the inherited on-disk serialization format; changing them would break compatibility with existing states.</td>
    </tr>
    <tr>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>dep/rcheevos/src/rc_libretro.c</code></td>
      <td>59-60, 159</td>
      <td>External rcheevos compatibility table keyed to DuckStation settings; renaming would change third-party behavior.</td>
    </tr>
  </tbody>
</table>
</div>

## Negative findings

- No C++ namespace, class, or struct declaration named `DuckStation` was found. Most code symbols are neutral subsystem names.
- No DuckStation-specific telemetry or crash-reporting identifier was found. RetroAchievements is an external integration, not telemetry; its client identity is inventoried below. The remaining Discord item is a community link, not Rich Presence.
- No standalone splash-screen file was found. The active Vaulketh assets serve setup, fullscreen, About, updater, and window-icon surfaces.
- No printable DuckStation string is stored in save states, but the inherited magic/version/header constants are compatibility-sensitive serialization identifiers.

## User-Visible Branding

<div class="rebranding-table-wrap">
<table class="rebranding-table">
  <thead>
    <tr>
      <th>Classification</th>
      <th>Current value</th>
      <th>File path</th>
      <th>Line number(s)</th>
      <th>Explanation</th>
      <th>Risk</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>Stenzek</code>, <code>stenzek</code>, <code>duckstation</code>; plus 5 variants</td>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td>8, 16-19, 22, 26, 34</td>
      <td>Published documentation/package URL, contact, or developer identity requires an approved R'Lyeh destination/value.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>https://www.duckstation.org/discord.html</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code></td>
      <td><code>src/core/fullscreen_ui.cpp</code></td>
      <td>7061, 7063</td>
      <td>User-facing link or service destination requires a confirmed R'Lyeh endpoint or an intentional upstream reference.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>https://www.duckstation.org/issues.html</code>, <code>https://www.duckstation.org/discord.html</code></td>
      <td><code>src/RLyehPSX-qt/mainwindow.cpp</code></td>
      <td>1411, 1416, 1421, 2894</td>
      <td>User-facing link or service destination requires a confirmed R'Lyeh endpoint or an intentional upstream reference.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>data/resources/chtdb.txt</code></td>
      <td>2, 11, 276</td>
      <td>Documentation or package metadata still presents DuckStation as the active product.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/generate-metainfo.sh</code></td>
      <td>10</td>
      <td>Documentation or package metadata still presents DuckStation as the active product.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td>3-4, 7, 11</td>
      <td>Documentation or package metadata still presents DuckStation as the active product.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code></td>
      <td><code>src/core/fullscreen_ui.cpp</code></td>
      <td>1326, 1529, 4534, 5039, 5072, 5077, 5164, 7021, 7027, 7031, 7221, 7353, 7377, 7415, 7517, 7812-7814</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/achievementlogindialog.cpp</code></td>
      <td>24</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/achievementsettingswidget.cpp</code></td>
      <td>47, 65, 69</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/cheatmanagerwindow.cpp</code></td>
      <td>570</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/controllersettingswindow.cpp</code></td>
      <td>305, 317</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/displaywidget.cpp</code></td>
      <td>137</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/mainwindow.cpp</code></td>
      <td>2891</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/qtprogresscallback.cpp</code></td>
      <td>17</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/settingswindow.cpp</code></td>
      <td>93, 135, 162, 288, 306, 314, 327</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/setupwizarddialog.cpp</code></td>
      <td>47, 63, 147-148</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/vcruntimecheck.cpp</code></td>
      <td>84, 89</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>org.duckstation.DuckStation</code> icon ID</td>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td>6</td>
      <td>The display name is already R'Lyeh PSX; the desktop icon ID still follows the old package identity.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/aboutdialog.ui</code></td>
      <td>14, 101</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/achievementlogindialog.ui</code></td>
      <td>69</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/biossettingswidget.ui</code></td>
      <td>126</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/controllersettingswindow.ui</code></td>
      <td>20</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/coverdownloaddialog.ui</code></td>
      <td>38</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/mainwindow.ui</code></td>
      <td>17, 481</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/settingswindow.ui</code></td>
      <td>20</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running</code></td>
      <td><code>src/RLyehPSX-qt/setupwizarddialog.ui</code></td>
      <td>14, 50, 136, 292, 402, 567</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
  </tbody>
</table>
</div>

## Internal Branding

<div class="rebranding-table-wrap">
<table class="rebranding-table">
  <thead>
    <tr>
      <th>Classification</th>
      <th>Current value</th>
      <th>File path</th>
      <th>Line number(s)</th>
      <th>Explanation</th>
      <th>Risk</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>DUCKSTATION</code></td>
      <td><code>dep/imgui/src/imgui.cpp</code></td>
      <td>14238</td>
      <td>Upstream-delta marker used to identify a DuckStation-specific dependency modification.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>147</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/flatpak/.gitignore</code></td>
      <td>4</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td>1, 84-85, 88-89</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td><code>scripts/org.duckstation.DuckStation.metainfo.xml.in</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded package/application filename; coordinate its rename with every build, resource, and packaging reference.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/achievements.cpp</code></td>
      <td>3323</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code></td>
      <td><code>src/core/bus.cpp</code></td>
      <td>205</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/core/pine_server.cpp</code></td>
      <td>143, 145, 448</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>SAVE_STATE_MAGIC = 0x43435544</code>, <code>SAVE_STATE_VERSION = 71</code>, <code>SAVE_STATE_HEADER</code></td>
      <td><code>src/core/save_state_version.h</code></td>
      <td>8-10, 15-52</td>
      <td>Save-state magic and version constants define the inherited on-disk serialization format; changing them would break compatibility with existing states.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>CMakeModules/RLyehPSXBuildSummary.cmake</code></td>
      <td>28, 36, 38, 46, 48</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>scripts/appimage/apprun-hooks/default-to-x11.sh</code></td>
      <td>3</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code>, <code>DuckStation</code>, <code>https://github.com/stenzek/duckstation-ext-qt-minimal/releases/download/linux/linuxdeploy-x86_64.AppImage</code>, <code>https://github.com/stenzek/duckstation-ext-qt-minimal/releases/download/linux/linuxdeploy-plugin-qt-x86_64.AppImage</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>45, 54-55, 89, 94, 146</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>scripts/flatpak/org.duckstation.DuckStation.yaml</code></td>
      <td>14, 40</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>scripts/run_regression_tests.py</code></td>
      <td>62</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/system.cpp</code></td>
      <td>357, 425</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.rc</code></td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.rc</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj</code></td>
      <td>215, 268, 274, 277, 280, 283, 286, 289, 292, 295, 298, 301, 304, 307, 310, 313, 348-349</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj</code></td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj.filters</code></td>
      <td>297, 303, 308, 311, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj.filters</code></td>
      <td><code>src/RLyehPSX-qt/duckstation-qt.vcxproj.filters</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/analog_controller.svg</code></td>
      <td>179-180</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/analog_joystick.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/digital_controller.svg</code></td>
      <td>111-112</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/guncon.svg</code></td>
      <td>324-325</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/justifier.svg</code></td>
      <td>2</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/mouse.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/controllers/negcon.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/controller-digital-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/controller-strike-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/emulation-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/joystick-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/negcon-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/sparkle-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/black/svg/sun-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/controller-digital-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/controller-strike-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/emulation-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/joystick-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/negcon-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/sparkle-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/RLyehPSX-qt/resources/icons/white/svg/sun-fill.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/RLyehPSX-regtest/duckstation-regtest.vcxproj</code></td>
      <td><code>src/RLyehPSX-regtest/duckstation-regtest.vcxproj</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/RLyehPSX-regtest/duckstation-regtest.vcxproj.filters</code></td>
      <td><code>src/RLyehPSX-regtest/duckstation-regtest.vcxproj.filters</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/scmversion/update_rc_version.bat</code></td>
      <td>5-6</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/updater/CMakeLists.txt</code></td>
      <td>14</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/updater/updater.cpp</code></td>
      <td>38</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>stenzek</code>, <code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/updater/updater.manifest</code></td>
      <td>6, 9</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>github.com/psychocodermonkey</code>, <code>duckstation</code>, <code>https://github.com/psychocodermonkey/RLyehPSX</code>, <code>DuckStation</code></td>
      <td><code>src/updater/updater.rc</code></td>
      <td>70-71, 76</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/updater/updater.vcxproj</code></td>
      <td>5</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/updater/updater.vcxproj.filters</code></td>
      <td>7</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/util/cubeb_audio_stream.cpp</code></td>
      <td>112, 302</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/util/media_capture.cpp</code></td>
      <td>2002</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/util/platform_misc_unix.cpp</code></td>
      <td>108</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/util/vulkan_device.cpp</code></td>
      <td>168, 170</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/duckstation/tree/master/scripts/deps</code></td>
      <td><code>data/resources/thirdparty.html</code></td>
      <td>1575</td>
      <td>Inherited FFmpeg build-source attribution; review separately from active product links.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/common/memmap.cpp</code></td>
      <td>858</td>
      <td>Internal comment or marker contains the legacy product name.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/cheats.cpp</code></td>
      <td>231</td>
      <td>Internal comment or marker contains the legacy product name.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/updater/resource.h</code></td>
      <td>3</td>
      <td>Internal comment or marker contains the legacy product name.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>dep/rcheevos/src/rc_libretro.c</code></td>
      <td>59-60, 159</td>
      <td>External rcheevos compatibility table keyed to DuckStation settings; renaming would change third-party behavior.</td>
      <td>High</td>
    </tr>
  </tbody>
</table>
</div>

## Third-Party Attribution
This section retains specific lineage and dependency references that need context during rebranding. The repetitive index of copyright, SPDX, and license notices was removed from this artifact inventory.
<div class="rebranding-table-wrap">
<table class="rebranding-table">
  <thead>
    <tr>
      <th>Classification</th>
      <th>Current value</th>
      <th>File path</th>
      <th>Line number(s)</th>
      <th>Explanation</th>
      <th>Risk</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code></td>
      <td><code>CONTRIBUTORS.md</code></td>
      <td>1, 5, 13, 17</td>
      <td>Current project lineage statement paired with required upstream attribution.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code>, <code>stenzek</code></td>
      <td><code>CONTRIBUTORS.md</code></td>
      <td>13</td>
      <td>Historical lineage or inherited authorship statement; changing it could misstate project provenance.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/Trixarian/duckstation-gpl</code></td>
      <td><code>README.md</code></td>
      <td>11, 47, 49, 57, 63-67</td>
      <td>Historical lineage or inherited authorship statement; changing it could misstate project provenance.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code></td>
      <td><code>README.md</code></td>
      <td>9, 23, 45, 115</td>
      <td>Current project lineage statement paired with required upstream attribution.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code></td>
      <td><code>RESPECT.md</code></td>
      <td>1</td>
      <td>Historical lineage or inherited authorship statement; changing it could misstate project provenance.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code></td>
      <td><code>STATE.md</code></td>
      <td>5</td>
      <td>Historical lineage or inherited authorship statement; changing it could misstate project provenance.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R’Lyeh PSX</code></td>
      <td><code>STATE.md</code></td>
      <td>5</td>
      <td>Current project lineage statement paired with required upstream attribution.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/type2-runtime/releases/download/continuous/runtime-x86_64</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>104</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/shaderc/archive/%SHADERC%.zip</code>, <code>https://github.com/stenzek/soundtouch/archive/%SOUNDTOUCH%.zip</code></td>
      <td><code>scripts/deps/build-dependencies-windows-arm64.bat</code></td>
      <td>86-87</td>
      <td>Inherited Windows dependency sources; this build path is deferred migration input.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/shaderc/archive/%SHADERC%.zip</code>, <code>https://github.com/stenzek/soundtouch/archive/%SOUNDTOUCH%.zip</code></td>
      <td><code>scripts/deps/build-dependencies-windows-x64.bat</code></td>
      <td>84-85</td>
      <td>Inherited Windows dependency sources; this build path is deferred migration input.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/shaderc.git</code></td>
      <td><code>scripts/flatpak/modules/22-shaderc.yaml</code></td>
      <td>13</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/cpuinfo.git</code></td>
      <td><code>scripts/flatpak/modules/24-cpuinfo.yaml</code></td>
      <td>19</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>https://github.com/stenzek/soundtouch.git</code></td>
      <td><code>scripts/flatpak/modules/26-soundtouch.yaml</code></td>
      <td>18</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code></td>
      <td><code>src/common/gsvector_sse.h</code></td>
      <td>5</td>
      <td>Authorship/derivation comment records the origin of inherited implementation work.</td>
      <td>High</td>
    </tr>
  </tbody>
</table>
</div>
## Assets

The image pass is complete. The following assets are now active:

| Asset | Type and dimensions | Location | Role |
|---|---|---|---|
| `vaulketh.png` | PNG, 498×498 RGBA | `data/resources/images/vaulketh.png` | Fullscreen UI logo |
| `dev.rlyeh.rlyehpsx.png` | PNG, 512×512 RGBA | `scripts/dev.rlyeh.rlyehpsx.png` | Linux desktop/AppImage/Flatpak icon |
| `RLyehPSX.icns` | macOS ICNS | `src/RLyehPSX-qt/RLyehPSX.icns` | macOS application icon |
| `rlyehpsx-qt.ico` | Windows ICO, seven embedded images | `src/RLyehPSX-qt/rlyehpsx-qt.ico` | Windows application/updater icon |
| `vaulketh.png` | PNG, 260×260 RGBA | `src/RLyehPSX-qt/resources/icons/vaulketh.png` | Qt application/dialog icon |
| `vaulketh_64.png` | PNG, 64×64 RGBA | `src/RLyehPSX-qt/resources/icons/vaulketh_64.png` | Qt icon variant |
| `vaulketh_128.png` | PNG, 128×128 RGBA | `src/RLyehPSX-qt/resources/icons/vaulketh_128.png` | Qt icon variant |
| `UpdateVaulketh.png` | PNG, 48×48 RGBA | `src/RLyehPSX-qt/resources/icons/UpdateVaulketh.png` | Qt updater illustration |

The former DuckStation image files and their source/build references have been removed or replaced. The remaining `org.duckstation.DuckStation` icon filename in the Flatpak install destination is intentional because package/application identity was outside the scope of this pass.

## Review notes

- `README.md`, `CONTRIBUTORS.md`, `RESPECT.md`, and portions of `STATE.md` intentionally describe project lineage. Those upstream names are attribution, not stale active-product branding.
- Some AppImage, Flatpak, and deferred Windows dependency files still name upstream download sources. Review those URLs alongside the relevant package versions and hashes before changing them.
- If other languages are reintroduced, review source text before regenerating catalogs; blind replacement risks stale or invalid translation metadata.
- External identifiers may be owned outside this repository. The macOS bundle IDs and updater GitHub API source have been updated; Linux package listing, update assets, community links, and support endpoints still need decisions before publication.
- The save-state magic `0x43435544` and current version `71` should not be changed merely for branding. Any format-identity change needs an explicit backward-compatibility and migration policy.
