# Rebranding Artifacts

This document records the completed image-rebranding pass and preserves the remaining DuckStation/R'Lyeh PSX inventory for future rebranding work. The detailed inventory below was gathered from the repository and remains intentionally conservative: upstream attribution, legal notices, compatibility identifiers, and external service identities are not treated as ordinary text replacements.

## Completed image-rebranding pass

The DuckStation-specific logos and application icons have been replaced with the new R'Lyeh PSX/Vaulketh assets. The old tracked binary assets were removed from the working tree and the new assets are present as their replacements.

| Original asset                                      | Replacement asset                                       | Type and role                             |
|-----------------------------------------------------|---------------------------------------------------------|-------------------------------------------|
| `data/resources/images/duck.png`                    | `data/resources/images/vaulketh.png`                    | PNG, 498×498; fullscreen UI logo          |
| `scripts/org.duckstation.DuckStation.png`           | `scripts/dev.rlyeh.rlyehpsx.png`                        | PNG, 512×512; Linux/AppImage/Flatpak icon |
| `src/duckstation-qt/DuckStation.icns`               | `src/duckstation-qt/RLyehPSX.icns`                      | macOS ICNS application icon               |
| `src/duckstation-qt/duckstation-qt.ico`             | `src/duckstation-qt/rlyehpsx-qt.ico`                    | Windows ICO application/updater icon      |
| `src/duckstation-qt/resources/icons/duck.png`       | `src/duckstation-qt/resources/icons/vaulketh.png`       | PNG, 260×260; Qt application/dialog icon  |
| `src/duckstation-qt/resources/icons/duck_64.png`    | `src/duckstation-qt/resources/icons/vaulketh_64.png`    | PNG, 64×64; Qt icon variant               |
| `src/duckstation-qt/resources/icons/duck_128.png`   | `src/duckstation-qt/resources/icons/vaulketh_128.png`   | PNG, 128×128; Qt icon variant             |
| `src/duckstation-qt/resources/icons/UpdateDuck.png` | `src/duckstation-qt/resources/icons/UpdateVaulketh.png` | PNG, 48×48; updater illustration          |

### Completed reference updates

- Core fullscreen references in `src/core/fullscreen_ui.cpp` and `src/core/imgui_overlays.cpp` now load `images/vaulketh.png`.
- Qt resource registration in `src/duckstation-qt/resources/duckstation-qt.qrc` now lists the Vaulketh assets.
- Qt UI/source references now use `:/icons/vaulketh.png`, `:/icons/vaulketh_64.png`, and `:/icons/UpdateVaulketh.png`.
- Windows references in `duckstation-qt.rc`, the Visual Studio project/filter files, and `src/updater/updater.rc` now use `rlyehpsx-qt.ico`.
- macOS references in `src/duckstation-qt/CMakeLists.txt` and `Info.plist.in` now use `RLyehPSX.icns`.
- AppImage packaging now uses `scripts/dev.rlyeh.rlyehpsx.png`.
- Flatpak packaging now sources the new PNG while retaining the existing installed icon filename and package identity.

### Validation completed

- All replacement assets exist and all Qt `.qrc` entries resolve.
- Qt resource/UI XML files validate successfully.
- No stale image asset references remain in source, packaging, or build configuration outside documentation/build artifacts.
- `git diff --check` passed.
- The macOS preset build completed successfully after removing the stale existing `DuckStation.app` bundle. The rebuilt bundle contains `RLyehPSX.icns` and no longer retains the old `DuckStation.icns` artifact.
- A full Qt dependency rebuild was not required; the earlier direct-build failure was caused by the pre-existing local `uic` execution/toolchain environment.

### Deliberately unchanged during the image pass

- Executable name: `DuckStation`
- macOS bundle name: `DuckStation.app`
- Flatpak/application identifiers
- Desktop-entry filenames and identifiers
- Package upgrade/migration behavior
- User-data directories
- Third-party UI/service icons such as Qt, GitHub, Discord, controller, and system icons

## Remaining rebranding work gathered from the prior inventory

The following work is not complete and is preserved in the detailed tables below.

1. **Approve canonical public identity values.** Confirm product spelling, executable stem, reverse-DNS ID, support URL, contact address, updater URL, Flatpak/AppID, macOS bundle identifier, and Windows product name.
2. **Resolve compatibility-sensitive identifiers.** Decide policy for save-state magic/version/header identity, PINE socket/version names, shared-memory names, IPC/service names, updater destinations, and persistent user-data roots. Any user-data rename needs discovery/migration behavior.
3. **Rename build and package identity together.** Coordinate CMake/MSBuild targets, solution/project paths, resource bundle names, bundle identifiers, Flatpak/AppStream/desktop IDs, CI artifacts, and updater packaging.
4. **Update remaining user-visible branding.** Replace source-language UI strings, About/version/window text, documentation, issue forms, public links, and generated metadata; then regenerate translation catalogs through the normal workflow.
5. **Review external integrations.** Decide whether Discord Rich Presence, RetroAchievements, rcheevos compatibility keys, updater endpoints, and other external identities remain inherited, migrate, or receive new registrations.
6. **Perform legal and attribution review last.** Preserve copyright, license, contributor, and upstream-lineage material unless an approved legal decision calls for additive project attribution or another explicit change.

The existing `User-Visible Branding`, `Internal Branding`, and `Third-Party Attribution` sections retain the full file-by-file findings, line numbers, classifications, and risk notes used to execute these future steps.

### Rebranding Translation table

| Artifact          | Old Value                        | New Value                               |
|-------------------|----------------------------------|-----------------------------------------|
| Project Name      | DuckStation                      | R'Lyeh PSX                              |
| Executable stem   | duckstation                      | rlyehpsx                                |
| DNS Identifier    | org.duckstation                  | dev.rlyeh.rlyehpsx                      |
| Site              | https://www.duckstation.org      | https://psx.rlyeh.dev                   |
| Repo              | github.com/stenzek/duckstation   | github.com/psychocodermonkey/RLyehPSX   |
| Support Email     | ?                                | support@rlyeh.dev                       |
| Updater URL       | ?                                | ?                                       |
| Flatpak/AppID     | org.duckstation.DuckStation      |dev.rlyeh.rlyehpsx                       |
| macOS Bundle      | org.duckstation.DuckStation      |dev.rlyeh.rlyehpsx                       |
| Windows Product   | DuckStation                      | RLyehPSX                                |

### Recommended rename order

1. Decide the remaining canonical public values first: product spelling, executable stem, reverse-DNS application ID, support URL, contact address, and whether legacy user data must migrate.
2. Resolve high-risk compatibility surfaces: save-state magic/version policy, PINE socket/version identity, shared-memory name, updater endpoints, Discord asset/application identity, RetroAchievements client identity, and external rcheevos keys.
3. Rename build graph and package identity together: CMake/MSBuild targets, solution/project paths, resource manifests, bundle IDs, Flatpak/AppStream/desktop IDs, CI artifacts, and updater packaging.
4. Replace application icons and duck-logo assets, then update all Qt/fullscreen/resource references.
5. Update source-language UI and documentation, regenerate translation catalogs through the normal translation workflow, and verify window titles/About/version text on each platform.
6. Preserve and re-audit copyright, license, contributor, and lineage material last; only additive project attribution should be considered without legal review.

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
      <td><code>.github/workflows/rolling-release.yml</code></td>
      <td>292, 295, 298, 305</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
    </tr>
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
      <td><code>duckstation</code></td>
      <td><code>src/core/settings.cpp</code></td>
      <td>873</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/core/system.cpp</code></td>
      <td>5871-5872</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>stenzek</code>, <code>duckstation</code></td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td>31</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
    </tr>
    <tr>
      <td><code>stenzek</code>, <code>duckstation</code>, <code>https://api.github.com/repos/stenzek/duckstation/tags</code>, <code>https://api.github.com/repos/stenzek/duckstation/releases/tags/{}</code>, <code>https://api.github.com/repos/stenzek/duckstation/compare/{}...{}</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td>58-60</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
    </tr>
    <tr>
      <td><code>My Documents\\DuckStation</code>, <code>$XDG_CONFIG_HOME/duckstation</code>, <code>~/.local/share/duckstation</code>, <code>Library/Application Support/DuckStation</code></td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>557, 562, 566, 570, 574, 583, 587</td>
      <td>Persistent user-data roots contain settings, save states, memory cards, covers, and other user content; changing them requires a discovery/migration policy.</td>
    </tr>
    <tr>
      <td><code>stenzek</code>, <code>duckstation</code></td>
      <td><code>src/updater/Info.plist.in</code></td>
      <td>10</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
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
- No DuckStation-specific telemetry or crash-reporting identifier was found. Discord Rich Presence and RetroAchievements are external integrations, not telemetry, but their client/asset identities are inventoried below.
- No standalone splash-screen file was found. Duck logos are used in setup, fullscreen, About, updater, and window-icon surfaces and therefore function as splash/brand imagery.
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
      <td>7047, 7049, 7051</td>
      <td>User-facing link or service destination requires a confirmed R'Lyeh endpoint or an intentional upstream reference.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>https://www.duckstation.org/issues.html</code>, <code>https://www.duckstation.org/discord.html</code></td>
      <td><code>src/duckstation-qt/mainwindow.cpp</code></td>
      <td>1411, 1416, 1421, 2894</td>
      <td>User-facing link or service destination requires a confirmed R'Lyeh endpoint or an intentional upstream reference.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>https://www.duckstation.org/runtime-resources/fonts/</code></td>
      <td><code>src/duckstation-qt/qttranslations.cpp</code></td>
      <td>64</td>
      <td>User-facing link or service destination requires a confirmed R'Lyeh endpoint or an intentional upstream reference.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/issues?q=is%3Aissue+sort%3Aupdated-desc+</code>, <code>https://github.com/stenzek/duckstation#libcrypt-protection-and-sbi-files</code></td>
      <td><code>.github/ISSUE_TEMPLATE/bug_report.yml</code></td>
      <td>2, 9, 15, 17, 58, 60, 66, 68, 82, 84</td>
      <td>Repository issue form contains public-facing DuckStation wording or upstream links.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/issues?q=is%3Aissue+sort%3Aupdated-desc+</code></td>
      <td><code>.github/ISSUE_TEMPLATE/feature_request.yml</code></td>
      <td>2, 9, 12</td>
      <td>Repository issue form contains public-facing DuckStation wording or upstream links.</td>
      <td>Low</td>
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
      <td><code>src/duckstation-qt/aboutdialog.cpp</code></td>
      <td>45, 59, 79</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/achievementlogindialog.cpp</code></td>
      <td>24</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/achievementsettingswidget.cpp</code></td>
      <td>47, 65, 69</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/advancedsettingswidget.cpp</code></td>
      <td>198</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td>119</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.cpp</code></td>
      <td>570</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/controllersettingswindow.cpp</code></td>
      <td>305, 317</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/displaywidget.cpp</code></td>
      <td>137</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/mainwindow.cpp</code></td>
      <td>2891</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>197, 456, 459, 602, 605, 2261</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/qtprogresscallback.cpp</code></td>
      <td>17</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/qttranslations.cpp</code></td>
      <td>120, 369, 374, 379</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/resource.h</code></td>
      <td>3</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/settingswindow.cpp</code></td>
      <td>93, 135, 162, 288, 306, 314, 327</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/setupwizarddialog.cpp</code></td>
      <td>47, 63, 147-148</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code>, <code>duckstation</code>, <code>Stenzek</code></td>
      <td><code>src/duckstation-qt/translations/create-update-and-edit-language.bat</code></td>
      <td>2-3, 5-6, 24</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_de.ts</code></td>
      <td>8-9, 13, 23-24, 43, 48, 68, 93, 268, 283-284, 326-327, 331-332, 1021-1022, 1866-1867, 2468-2469, 3893, 4093, 5009-5010, 6109-6110, 6464, 6799, 6804, 7465-7466, 8740-8741, 8745-8746, 8750, 10694, 10878-10879, 11661-11662, 12900, 13082-13083, 13112-13113, 13212, 13250, 13255, 13275, 13320, 13351, 13391, 13443, 13448, 13465, 13467</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;DuckStation</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es-ES.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 88-89, 283-284, 303-304, 308-309, 942-943, 2063-2064, 2390-2391, 3981-3982, 4194-4195, 5747-5748, 6391-6392, 6511-6512, 6636, 7532-7533, 8732-8733, 8737-8738, 8742-8743, 12049, 12395-12396, 12585-12586, 13422-13423, 15135-15136, 15430-15431, 15470, 15565-15566, 15575-15576, 15639-15640, 15644-15645, 15664-15665, 15709-15710, 15740-15741, 15780-15781, 15832, 15835, 15841, 15844, 15860, 15862-15863, 15865, 16182, 16189</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;DuckStation</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 88-89, 283-284, 303-304, 308-309, 863-864, 2074-2075, 2401-2402, 3992-3993, 4205-4206, 5762-5763, 6402-6403, 6989-6990, 7218-7219, 7273-7274, 8752-8753, 8757-8758, 8762-8763, 12427-12428, 12667-12668, 13444-13445, 15161-15162, 15491-15492, 15531, 15621-15622, 15636-15637, 15700-15701, 15705-15706, 15725-15726, 15770-15771, 15801-15802, 15841-15842, 15893, 15896, 15902, 15905, 15921, 15923-15924, 15926, 16238, 16245</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>Duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>; plus 1 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_fr.ts</code></td>
      <td>8-9, 13-14, 23-24, 43, 48, 68, 88, 268-269, 283-284, 303-304, 308-309, 1021-1022, 1868-1869, 2470-2471, 3905, 4119-4120, 5037-5038, 6136-6137, 6491, 6826-6827, 6831, 7492-7493, 8767-8768, 8772-8773, 8777, 10723-10724, 11020-11021, 11701-11702, 12935-12936, 13117-13118, 13147-13148, 13247-13248, 13285, 13290, 13310, 13355, 13386, 13426, 13478, 13483, 13500, 13502</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>; plus 1 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_he.ts</code></td>
      <td>8-9, 13-14, 23-24, 43, 48, 68, 88, 268, 283, 326, 331, 1020, 1865, 2467, 3888, 4088, 5015, 6101-6102, 6456, 6791, 6796, 7457, 8732, 8737, 8742, 10684, 10883, 11652, 12886-12887, 13068-13069, 13098, 13198, 13236, 13241, 13261, 13306, 13337, 13377, 13429, 13434, 13451, 13453</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, , <code>Duckstation</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>; plus 2 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_id.ts</code></td>
      <td>13, 33, 38, 43, 48, 68, 88, 306, 326, 331, 773, 2055-2056, 2377, 3940, 4153, 6183, 6188, 6193, 7257, 7537, 7612, 7732, 7963, 12291-12292, 12377-12378, 12801-12802, 14966, 15232-15233, 15327-15328, 15377, 15382, 15480-15481, 15485-15486, 15500-15501, 15540-15541, 15545-15546, 15555-15556, 15653, 15656, 15662, 15665, 15671, 15673-15674, 15676</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>; plus 2 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_it.ts</code></td>
      <td>8-9, 13, 23, 25, 44-45, 49-50, 69-70, 94-95, 277-278, 292-293, 335-336, 340-341, 1020-1021, 1891-1892, 2378-2379, 2591-2592, 4148-4149, 4370-4371, 5359-5360, 6442-6443, 6792-6793, 7124-7125, 7129-7130, 7780-7781, 7944-7945, 7969-7970, 9373-9374, 9378-9379, 9383-9384, 12606, 12903-12904, 13635-13636, 15578-15579, 15798-15799, 15846-15847, 15964-15965, 15983-15984, 16056-16057, 16061-16062, 16081-16082, 16126-16127, 16157-16158, 16197-16198, 16249-16250, 16254, 16257, 16273, 16275-16276, 16278</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, ; plus 3 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ja.ts</code></td>
      <td>8-9, 13-14, 23-24, 43, 48-49, 68-69, 88-89, 265-266, 291-292, 311-312, 316-317, 979-980, 2196-2197, 2681-2682, 2894-2895, 4545-4546, 4775-4776, 5754-5755, 6856-6857, 7516-7517, 7521-7522, 8126-8127, 8308, 8348-8349, 9805-9806, 9810-9811, 9815, 13596-13597, 13921-13922, 14638-14639, 16613-16614, 16877-16878, 16925-16926, 17043-17044, 17062-17063, 17135-17136, 17140-17141, 17160-17161, 17205-17206, 17236-17237, 17276-17277, 17328, 17331, 17337, 17340, 17356, 17358-17359, 17361</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>, ; plus 3 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ko.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 88-89, 267-268, 293-294, 313-314, 318-319, 987-988, 1879-1880, 2451-2452, 3909-3910, 4121-4122, 5037-5038, 6139-6140, 6494-6495, 6829-6830, 6834-6835, 7566-7567, 8786-8787, 8791-8792, 8796-8797, 10725-10726, 11042-11043, 11703-11704, 12939-12940, 13125-13126, 13155-13156, 13255-13256, 13293-13294, 13298-13299, 13318, 13363-13364, 13394-13395, 13434-13435, 13486-13487, 13491, 13494, 13510, 13512-13513, 13515</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_nl.ts</code></td>
      <td>8, 13, 23, 43, 48, 68, 88, 268, 283, 326, 331, 1021, 1867, 2469, 3894, 4094, 5016, 6108, 6463, 6798, 6803, 7464, 8739, 8744, 8749, 10693, 10995, 11661-11662, 12895, 13077, 13107, 13207, 13245, 13250, 13270, 13315, 13346, 13386, 13438, 13443, 13460, 13462</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>; plus 1 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pl.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 88-89, 284-285, 304-305, 309-310, 887-888, 2018-2019, 2345-2346, 3931-3932, 4144-4145, 5751-5752, 6421-6422, 7013-7014, 7043, 7223-7224, 8669-8670, 8674-8675, 8679-8680, 12114-12115, 12397-12398, 13131-13132, 14936-14937, 15200-15201, 15240-15241, 15330-15331, 15345-15346, 15414-15415, 15419-15420, 15439-15440, 15484-15485, 15515-15516, 15555-15556, 15607, 15610, 15616, 15619, 15635, 15637-15638, 15640</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>; plus 1 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-BR.ts</code></td>
      <td>8, 13-14, 23-24, 43-44, 48, 68-69, 88-89, 283-284, 303-304, 308-309, 939-940, 2075-2076, 2407, 4004, 4216-4217, 5806, 6391-6392, 6501-6502, 6621-6622, 7511-7512, 8795-8796, 8800-8801, 8805-8806, 12741-12742, 13014, 13476-13477, 13774, 13781, 15497-15498, 15822, 15862, 15957-15958, 15967-15968, 16031-16032, 16036-16037, 16056-16057, 16101-16102, 16132-16133, 16172-16173, 16224, 16227, 16233, 16236, 16252, 16254-16255, 16607, 16614</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>; plus 1 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-PT.ts</code></td>
      <td>8-9, 13-14, 23-24, 43, 48, 68, 88, 263, 283-284, 326-327, 331, 1021-1022, 1866-1867, 2468-2469, 3893, 4093, 5015-5016, 6107-6108, 6462, 6797, 6802, 7463-7464, 8738-8739, 8743-8744, 8748, 10692-10693, 10989-10990, 11655-11656, 12894-12895, 13076-13077, 13106, 13206, 13244, 13249, 13269, 13314, 13345, 13385, 13437, 13442, 13459, 13461</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, , <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;По</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ru.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 88-89, 286-287, 306-307, 311-312, 982-983, 2097-2098, 2426-2427, 4027-4028, 4240-4241, 5799-5800, 6446-6447, 6567-6568, 6696-6697, 7086, 7651-7652, 8977-8978, 8982-8983, 8987-8988, 12706-12707, 12967-12968, 13746-13747, 15474-15475, 15772-15773, 15812-15813, 15907-15908, 15917-15918, 15982-15983, 15987-15988, 16007-16008, 16052-16053, 16083-16084, 16123-16124, 16175, 16178, 16184, 16187, 16203, 16205-16206, 16208, 16524, 16531</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/blob/master/CONTRIBUTORS.md</code>; plus 3 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_tr.ts</code></td>
      <td>8-9, 13-14, 23-24, 43-44, 48-49, 68-69, 93, 273-274, 288-289, 331-332, 336-337, 1038-1039, 1879-1880, 2481-2482, 3864-3865, 4076-4077, 5003-5004, 6087-6088, 6447-6448, 6782-6783, 7434-7435, 8720-8721, 8725-8726, 8730-8731, 10664-10665, 10854, 10956-10957, 11647-11648, 13092-13093, 13278-13279, 13303, 13413-13414, 13446-13447, 13451-13452, 13471-13472, 13516-13517, 13547-13548, 13587-13588, 13639-13640, 13644, 13647, 13663, 13665-13666, 13668</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>Duckstation</code>, <code>duckstation</code>, ; plus 3 variants</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_zh-CN.ts</code></td>
      <td>8-9, 18-19, 23-24, 38-39, 43-44, 145-146, 150-151, 222-223, 277-278, 330-331, 760-761, 2121-2122, 2452-2453, 4062-4063, 4340-4341, 5780-5781, 5824-5825, 6632-6633, 6770-6771, 7516-7517, 7555-7556, 8238-8239, 8308-8309, 11186-11187, 13184-13185, 13828-13829, 13871-13872, 14145, 14152, 16247-16248, 16577-16578, 16617-16618, 16682-16683, 16722-16723, 16827, 16829-16830, 16832, 16865-16866, 16880-16881, 16889-16890, 16916-16917, 16941-16942, 16961, 16964, 16990-16991, 17010, 17013, 17035-17036, 17046-17047, 17388, 17395</td>
      <td>Localized or source-language user-facing DuckStation text; update through the translation workflow to avoid catalog drift.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/vcruntimecheck.cpp</code></td>
      <td>84, 89</td>
      <td>User-visible application name, dialog text, error text, log text, or version label.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code>, <code>org.duckstation</code>, <code>duckstation</code></td>
      <td><code>scripts/org.duckstation.DuckStation.desktop</code></td>
      <td>3, 6-8</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/aboutdialog.ui</code></td>
      <td>14, 101</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/achievementlogindialog.ui</code></td>
      <td>69</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/biossettingswidget.ui</code></td>
      <td>126</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_guncon.ui</code></td>
      <td>279, 585-586</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_justifier.ui</code></td>
      <td>279, 585-586</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_mouse.ui</code></td>
      <td>70, 275-276</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code></td>
      <td><code>src/duckstation-qt/controllersettingswindow.ui</code></td>
      <td>20, 23, 143</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/coverdownloaddialog.ui</code></td>
      <td>38</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/debuggerwindow.ui</code></td>
      <td>481</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/interfacesettingswidget.ui</code></td>
      <td>251</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code></td>
      <td><code>src/duckstation-qt/mainwindow.ui</code></td>
      <td>17, 20, 428, 437, 446, 468, 477, 481, 932</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/settingswindow.ui</code></td>
      <td>20</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Safe Rename</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation#downloading-and-running&quot;&gt;https://github.com/stenzek/duckstation#downloading-and-running&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;By</code></td>
      <td><code>src/duckstation-qt/setupwizarddialog.ui</code></td>
      <td>14, 50, 136, 292, 402, 567</td>
      <td>User-facing Qt or desktop-entry label/reference using DuckStation branding.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code></td>
      <td><code>AGENTS.md</code></td>
      <td>3, 98</td>
      <td>Current R'Lyeh PSX project branding; retained as the intended destination identity.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code>, <code>PsychoCoderMonkey</code></td>
      <td><code>CONTRIBUTORS.md</code></td>
      <td>3, 9</td>
      <td>Current R'Lyeh PSX project branding; retained as the intended destination identity.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code>, <code>psychocodermonkey</code>, <code>RlyehPSX</code></td>
      <td><code>README.md</code></td>
      <td>1, 27, 31, 37, 74, 82</td>
      <td>Current R'Lyeh PSX project branding; retained as the intended destination identity.</td>
      <td>Low</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R’Lyeh PSX</code>, <code>RlyehPSX</code>, <code>psychocodermonkey</code>, <code>https://github.com/psychocodermonkey/RlyehPSX</code>, <code>R'Lyeh PSX</code></td>
      <td><code>STATE.md</code></td>
      <td>1, 9, 99, 123</td>
      <td>Current R'Lyeh PSX project branding; retained as the intended destination identity.</td>
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
      <td><code>org.duckstation</code>, <code>DuckStation</code></td>
      <td><code>.github/workflows/rolling-release.yml</code></td>
      <td>292, 295, 298, 305</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
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
      <td><code>DuckStation</code>, <code>duckstation</code></td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>557, 562, 566, 570, 574, 583, 587</td>
      <td>Persistent user-data roots contain settings, save states, memory cards, covers, and other user content; changing them requires a discovery/migration policy.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation-qt.rcc</code></td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>501</td>
      <td>Runtime resource bundle filename tied to the Qt executable/target identity.</td>
      <td>Medium</td>
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
      <td>Needs Human Decision</td>
      <td><code>duckstation</code></td>
      <td><code>src/core/settings.cpp</code></td>
      <td>873</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/core/system.cpp</code></td>
      <td>5871-5872</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>stenzek</code>, <code>duckstation</code></td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td>31</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>stenzek</code>, <code>duckstation</code>, <code>https://api.github.com/repos/stenzek/duckstation/tags</code>, <code>https://api.github.com/repos/stenzek/duckstation/releases/tags/{}</code>, <code>https://api.github.com/repos/stenzek/duckstation/compare/{}...{}</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td>58-60</td>
      <td>Runtime, IPC, service, log, updater, or external-integration identifier with compatibility or migration implications.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Needs Human Decision</td>
      <td><code>stenzek</code>, <code>duckstation</code></td>
      <td><code>src/updater/Info.plist.in</code></td>
      <td>10</td>
      <td>Published application/package identifier affects installs, upgrades, desktop integration, and platform identity.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>.github/workflows/rolling-release.yml</code></td>
      <td>60, 68, 78, 84, 89, 100, 106, 148, 156, 166, 172, 177, 188, 194, 239, 246, 259, 265, 303, 332, 369, 376, 388-390, 396, 421-427, 438-444</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>CMakeLists.txt</code></td>
      <td>2, 9, 25, 35, 112, 117</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>CMakeModules/DuckStationBuildOptions.cmake</code></td>
      <td><code>CMakeModules/DuckStationBuildOptions.cmake</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>CMakeModules/DuckStationBuildSummary.cmake</code></td>
      <td>28, 36, 38, 46, 48</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>CMakeModules/DuckStationBuildSummary.cmake</code></td>
      <td><code>CMakeModules/DuckStationBuildSummary.cmake</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>CMakeModules/DuckStationDependencies.cmake</code></td>
      <td><code>CMakeModules/DuckStationDependencies.cmake</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>CMakeModules/DuckStationUtils.cmake</code></td>
      <td><code>CMakeModules/DuckStationUtils.cmake</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>stenzek</code></td>
      <td><code>RESPECT.md</code></td>
      <td>7</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>data/resources/thirdparty.html</code></td>
      <td>5</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>duckstation.sln</code></td>
      <td>18, 45</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation.sln</code></td>
      <td><code>duckstation.sln</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
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
      <td><code>duckstation</code>, <code>DuckStation</code>, <code>github.com/psychocodermonkey</code>, <code>https://github.com/psychocodermonkey/RLyehPSX-ext-qt-minimal/releases/download/linux/linuxdeploy-x86_64.AppImage</code>, <code>https://github.com/psychocodermonkey/RLyehPSX-ext-qt-minimal/releases/download/linux/linuxdeploy-plugin-qt-x86_64.AppImage</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>45, 54-55, 90, 95, 146</td>
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
      <td><code>duckstation</code></td>
      <td><code>scripts/generate_update_fa_glyph_ranges.py</code></td>
      <td>9</td>
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
      <td><code>duckstation</code></td>
      <td><code>src/CMakeLists.txt</code></td>
      <td>11, 15, 19</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/bios.cpp</code></td>
      <td>408</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/cpu_code_cache.cpp</code></td>
      <td>196</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/host.cpp</code></td>
      <td>268</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/system.cpp</code></td>
      <td>361, 429</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/duckstation-qt/CMakeLists.txt</code></td>
      <td>151-167, 170-173, 176, 178, 181-182, 187, 195, 204, 206, 216, 222, 230-231, 234, 240, 243, 254, 259-261, 263-266, 272, 274-275, 278, 285, 289</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/CMakeLists.txt</code></td>
      <td><code>src/duckstation-qt/CMakeLists.txt</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code>, <code>stenzek</code></td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td>27, 41</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>stenzek</code></td>
      <td><code>src/duckstation-qt/aboutdialog.cpp</code></td>
      <td>40</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/aboutdialog.cpp</code></td>
      <td><code>src/duckstation-qt/aboutdialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/aboutdialog.h</code></td>
      <td><code>src/duckstation-qt/aboutdialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/aboutdialog.ui</code></td>
      <td><code>src/duckstation-qt/aboutdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementlogindialog.cpp</code></td>
      <td><code>src/duckstation-qt/achievementlogindialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementlogindialog.h</code></td>
      <td><code>src/duckstation-qt/achievementlogindialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementlogindialog.ui</code></td>
      <td><code>src/duckstation-qt/achievementlogindialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/achievementsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/achievementsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/achievementsettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/achievementsettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/advancedsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/advancedsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/advancedsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/advancedsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/advancedsettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/advancedsettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/audioexpansionsettingsdialog.ui</code></td>
      <td><code>src/duckstation-qt/audioexpansionsettingsdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/audiosettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/audiosettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/audiosettingswidget.h</code></td>
      <td><code>src/duckstation-qt/audiosettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/audiosettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/audiosettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/audiostretchsettingsdialog.ui</code></td>
      <td><code>src/duckstation-qt/audiostretchsettingsdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/autoupdaterdialog.h</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/autoupdaterdialog.ui</code></td>
      <td><code>src/duckstation-qt/autoupdaterdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/biossettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/biossettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/biossettingswidget.h</code></td>
      <td><code>src/duckstation-qt/biossettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/biossettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/biossettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.cpp</code></td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.h</code></td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.ui</code></td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.cpp</code></td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.h</code></td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.ui</code></td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/collapsiblewidget.cpp</code></td>
      <td><code>src/duckstation-qt/collapsiblewidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/collapsiblewidget.h</code></td>
      <td><code>src/duckstation-qt/collapsiblewidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/colorpickerbutton.cpp</code></td>
      <td><code>src/duckstation-qt/colorpickerbutton.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/colorpickerbutton.h</code></td>
      <td><code>src/duckstation-qt/colorpickerbutton.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/consolesettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/consolesettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/consolesettingswidget.h</code></td>
      <td><code>src/duckstation-qt/consolesettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/consolesettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/consolesettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_analog_controller.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_analog_controller.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_analog_joystick.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_analog_joystick.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_digital_controller.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_digital_controller.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_guncon.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_guncon.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_justifier.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_justifier.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_mouse.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_mouse.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_negcon.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_negcon.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidget_negconrumble.ui</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidget_negconrumble.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.cpp</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.h</code></td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllerledsettingsdialog.ui</code></td>
      <td><code>src/duckstation-qt/controllerledsettingsdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllermacroeditwidget.ui</code></td>
      <td><code>src/duckstation-qt/controllermacroeditwidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllermacrowidget.ui</code></td>
      <td><code>src/duckstation-qt/controllermacrowidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllersettingswindow.cpp</code></td>
      <td><code>src/duckstation-qt/controllersettingswindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllersettingswindow.h</code></td>
      <td><code>src/duckstation-qt/controllersettingswindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllersettingswindow.ui</code></td>
      <td><code>src/duckstation-qt/controllersettingswindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/controllersettingwidgetbinder.h</code></td>
      <td><code>src/duckstation-qt/controllersettingwidgetbinder.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/coverdownloaddialog.cpp</code></td>
      <td><code>src/duckstation-qt/coverdownloaddialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/coverdownloaddialog.h</code></td>
      <td><code>src/duckstation-qt/coverdownloaddialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/coverdownloaddialog.ui</code></td>
      <td><code>src/duckstation-qt/coverdownloaddialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggeraddbreakpointdialog.ui</code></td>
      <td><code>src/duckstation-qt/debuggeraddbreakpointdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggermodels.cpp</code></td>
      <td><code>src/duckstation-qt/debuggermodels.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggermodels.h</code></td>
      <td><code>src/duckstation-qt/debuggermodels.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggerwindow.cpp</code></td>
      <td><code>src/duckstation-qt/debuggerwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggerwindow.h</code></td>
      <td><code>src/duckstation-qt/debuggerwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/debuggerwindow.ui</code></td>
      <td><code>src/duckstation-qt/debuggerwindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/displaywidget.cpp</code></td>
      <td><code>src/duckstation-qt/displaywidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/displaywidget.h</code></td>
      <td><code>src/duckstation-qt/displaywidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/duckstation-qt.aps</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.aps</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>github.com/psychocodermonkey</code>, <code>duckstation</code>, <code>https://github.com/psychocodermonkey/RLyehPSX</code>, <code>DuckStation</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.rc</code></td>
      <td>70-71, 73, 75-76</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/duckstation-qt.rc</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.rc</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj</code></td>
      <td>215, 268, 274, 277, 280, 283, 286, 289, 292, 295, 298, 301, 304, 307, 310, 313, 348-349</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj.filters</code></td>
      <td>297, 303, 308, 311, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj.filters</code></td>
      <td><code>src/duckstation-qt/duckstation-qt.vcxproj.filters</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/emptygamelistwidget.ui</code></td>
      <td><code>src/duckstation-qt/emptygamelistwidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/emulationsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/emulationsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/emulationsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/emulationsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/emulationsettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/emulationsettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/foldersettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/foldersettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/foldersettingswidget.h</code></td>
      <td><code>src/duckstation-qt/foldersettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/foldersettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/foldersettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistmodel.cpp</code></td>
      <td><code>src/duckstation-qt/gamelistmodel.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistmodel.h</code></td>
      <td><code>src/duckstation-qt/gamelistmodel.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.cpp</code></td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.h</code></td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistwidget.cpp</code></td>
      <td><code>src/duckstation-qt/gamelistwidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistwidget.h</code></td>
      <td><code>src/duckstation-qt/gamelistwidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamelistwidget.ui</code></td>
      <td><code>src/duckstation-qt/gamelistwidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamesummarywidget.cpp</code></td>
      <td><code>src/duckstation-qt/gamesummarywidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamesummarywidget.h</code></td>
      <td><code>src/duckstation-qt/gamesummarywidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/gamesummarywidget.ui</code></td>
      <td><code>src/duckstation-qt/gamesummarywidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/graphicssettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/graphicssettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/graphicssettingswidget.h</code></td>
      <td><code>src/duckstation-qt/graphicssettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/graphicssettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/graphicssettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.h</code></td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/inputbindingdialog.cpp</code></td>
      <td><code>src/duckstation-qt/inputbindingdialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/inputbindingdialog.h</code></td>
      <td><code>src/duckstation-qt/inputbindingdialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/inputbindingdialog.ui</code></td>
      <td><code>src/duckstation-qt/inputbindingdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/inputbindingwidgets.cpp</code></td>
      <td><code>src/duckstation-qt/inputbindingwidgets.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/inputbindingwidgets.h</code></td>
      <td><code>src/duckstation-qt/inputbindingwidgets.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/interfacesettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/interfacesettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/interfacesettingswidget.h</code></td>
      <td><code>src/duckstation-qt/interfacesettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/interfacesettingswidget.ui</code></td>
      <td><code>src/duckstation-qt/interfacesettingswidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/logwindow.cpp</code></td>
      <td><code>src/duckstation-qt/logwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/logwindow.h</code></td>
      <td><code>src/duckstation-qt/logwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/mainwindow.cpp</code></td>
      <td><code>src/duckstation-qt/mainwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/mainwindow.h</code></td>
      <td><code>src/duckstation-qt/mainwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/mainwindow.ui</code></td>
      <td><code>src/duckstation-qt/mainwindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.cpp</code></td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.h</code></td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.ui</code></td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memoryscannerwindow.cpp</code></td>
      <td><code>src/duckstation-qt/memoryscannerwindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memoryscannerwindow.h</code></td>
      <td><code>src/duckstation-qt/memoryscannerwindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memoryscannerwindow.ui</code></td>
      <td><code>src/duckstation-qt/memoryscannerwindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memoryviewwidget.cpp</code></td>
      <td><code>src/duckstation-qt/memoryviewwidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/memoryviewwidget.h</code></td>
      <td><code>src/duckstation-qt/memoryviewwidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/pch.cpp</code></td>
      <td><code>src/duckstation-qt/pch.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/pch.h</code></td>
      <td><code>src/duckstation-qt/pch.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/postprocessingchainconfigwidget.ui</code></td>
      <td><code>src/duckstation-qt/postprocessingchainconfigwidget.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.cpp</code></td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.h</code></td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qt.conf</code></td>
      <td><code>src/duckstation-qt/qt.conf</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qt.conf.win</code></td>
      <td><code>src/duckstation-qt/qt.conf.win</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qt5.natvis</code></td>
      <td><code>src/duckstation-qt/qt5.natvis</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qthost.h</code></td>
      <td><code>src/duckstation-qt/qthost.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtkeycodes.cpp</code></td>
      <td><code>src/duckstation-qt/qtkeycodes.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtprogresscallback.cpp</code></td>
      <td><code>src/duckstation-qt/qtprogresscallback.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtprogresscallback.h</code></td>
      <td><code>src/duckstation-qt/qtprogresscallback.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtthemes.cpp</code></td>
      <td><code>src/duckstation-qt/qtthemes.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qttranslations.cpp</code></td>
      <td><code>src/duckstation-qt/qttranslations.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtutils.cpp</code></td>
      <td><code>src/duckstation-qt/qtutils.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/qtutils.h</code></td>
      <td><code>src/duckstation-qt/qtutils.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resource.h</code></td>
      <td><code>src/duckstation-qt/resource.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/analog_controller.svg</code></td>
      <td>179-180</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/analog_controller.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/analog_controller.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/analog_joystick.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/analog_joystick.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/analog_joystick.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/digital_controller.svg</code></td>
      <td>111-112</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/digital_controller.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/digital_controller.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/guncon.svg</code></td>
      <td>324-325</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/guncon.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/guncon.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/justifier.svg</code></td>
      <td>2</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/justifier.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/justifier.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/mouse.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/mouse.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/mouse.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/controllers/negcon.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/controllers/negcon.svg</code></td>
      <td><code>src/duckstation-qt/resources/controllers/negcon.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/duckstation-qt.qrc</code></td>
      <td><code>src/duckstation-qt/resources/duckstation-qt.qrc</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/generate.sh</code></td>
      <td><code>src/duckstation-qt/resources/generate.sh</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/IssueTracker.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/IssueTracker.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/QT.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/QT.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/address-book-new-22.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/address-book-new-22.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/address-book-new-22@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/address-book-new-22@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/antialias-icon.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/antialias-icon.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/antialias-icon@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/antialias-icon@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-development.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-development.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-development@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-development@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-graphics.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-graphics.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-graphics@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-graphics@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-internet.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-internet.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-other.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-other.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-other@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-other@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-system-24.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-system-24.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-system-24@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-system-24@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-system.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-system.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/applications-system@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/applications-system@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/audio-card.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/audio-card.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/audio-card@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/audio-card@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/index.theme</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/index.theme</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/alert-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/alert-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-down-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-down-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-left-right-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-left-right-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-up-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-up-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/artboard-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/artboard-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/cheats-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/cheats-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/checkbox-multiple-blank-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/checkbox-multiple-blank-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/chip-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/chip-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/chip-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/chip-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/close-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/close-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-digital-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-digital-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-digital-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-strike-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-strike-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/controller-strike-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-into-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-into-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-out-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-out-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-over-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-step-over-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-toggle-breakpoint.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-toggle-breakpoint.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-trace-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debug-trace-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-clear-breakpoint.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-clear-breakpoint.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-dump-address.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-dump-address.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-address.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-address.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-cursor.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-cursor.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-pc.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/debugger-go-to-pc.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/disc-eject-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/disc-eject-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/disc-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/disc-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/door-open-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/door-open-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/download-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/download-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/eject-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/eject-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/emulation-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/emulation-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/emulation-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-list-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-list-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-music-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-music-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-reduce-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-reduce-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-search-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-search-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-settings-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-settings-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-unknow-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/file-unknow-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/filter-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/filter-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/flashlight-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/flashlight-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-open-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-open-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-reduce-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-reduce-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-settings-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/folder-settings-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/fullscreen-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/fullscreen-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/function-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/function-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/global-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/global-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/guncon-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/guncon-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/image-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/image-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/information-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/information-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/joystick-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/joystick-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/joystick-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/keyboard-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/keyboard-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/layout-grid-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/layout-grid-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/lightbulb-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/lightbulb-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/list-check.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/list-check.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/mag-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/mag-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/memcard-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/memcard-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/minus-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/minus-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/mouse-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/mouse-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/negcon-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/negcon-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/negcon-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/paint-brush-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/paint-brush-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/pause-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/pause-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-circle-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-circle-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-list-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/play-list-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/price-tag-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/price-tag-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/refresh-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/refresh-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/restart-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/restart-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/save-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/save-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/screenshot-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/screenshot-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/settings-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/settings-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/shut-down-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/shut-down-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sparkle-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sparkle-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sparkle-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sun-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sun-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/sun-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/trash-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/trash-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/trophy-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/trophy-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/tv-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/tv-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/volume-up-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/volume-up-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/window-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/window-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/camera-photo.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/camera-photo.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/camera-photo@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/camera-photo@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/camera-video.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/camera-video.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/camera-video@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/camera-video@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/conical-flask-red.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/conical-flask-red.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/conical-flask-red@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/conical-flask-red@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/cover-placeholder.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/cover-placeholder.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-execute-from-cursor.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-execute-from-cursor.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-execute-to-cursor.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-execute-to-cursor.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-pc.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-pc.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-pc@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-pc@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-run-cursor.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-run-cursor.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-run.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-run.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-instruction.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-instruction.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-into-instruction.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-into-instruction.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-into.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-into.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-out.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-out.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-over.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-step-over.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/debug-trace.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/debug-trace.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/discord.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/discord.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-new.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-new.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-new@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-new@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-open.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-open.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-open@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-open@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-save.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-save.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/document-save@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/document-save@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/drive-optical.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/drive-optical.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/drive-optical@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/drive-optical@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/drive-removable-media.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/drive-removable-media.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/drive-removable-media@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/drive-removable-media@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/edit-clear-16.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/edit-clear-16.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/edit-clear-16@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/edit-clear-16@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/edit-find.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/edit-find.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/emblem-person-blue.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/emblem-person-blue.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/emblem-person-blue@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/emblem-person-blue@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-eu@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-jp@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-other.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-other.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-other@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-other@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-uc@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-us.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-us.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-us.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-us.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flag-us@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flag-us@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/de.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/de.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/de@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/de@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/en.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/en.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/en@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/en@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/es-ES.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/es-ES.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/es-ES@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/es-ES@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/fr.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/fr.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/fr@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/fr@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/he.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/he.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/he@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/he@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/id.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/id.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/id@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/id@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/it.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/it.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/it@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/it@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ja.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ja.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ja@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ja@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ko.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ko.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ko@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ko@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/nl.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/nl.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/nl@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/nl@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pl.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pl.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pl@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pl@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-BR.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-BR.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-BR@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-BR@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-PT.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-PT.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-PT@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/pt-PT@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ru.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ru.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/ru@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/ru@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/tr.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/tr.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/tr@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/tr@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/zh-CN.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/zh-CN.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/flags/zh-CN@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/flags/zh-CN@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/folder-open.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/folder-open.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/folder-open@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/folder-open@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/github.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/github.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/go-down-16.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/go-down-16.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/go-down-16@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/go-down-16@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/go-up-16.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/go-up-16.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/go-up-16@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/go-up-16@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/input-gaming.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/input-gaming.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/input-gaming@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/input-gaming@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/list-add.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/list-add.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/list-add@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/list-add@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/list-remove.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/list-remove.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/list-remove@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/list-remove@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-2.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-2.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-24.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-24.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-24@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-24@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-2@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash-2@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-flash@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-flash@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-24.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-24.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-24@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-24@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-gear-24.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-gear-24.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-gear-24@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical-gear-24@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-optical@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-optical@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-pause.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-pause.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-pause@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-pause@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-start.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-start.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-start@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-playback-start@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-record.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-record.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/media-record@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/media-record@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/multimedia-player.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/multimedia-player.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/multimedia-player@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/multimedia-player@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/preferences-desktop-keyboard-shortcuts.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/preferences-desktop-keyboard-shortcuts.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/preferences-desktop-keyboard-shortcuts@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/preferences-desktop-keyboard-shortcuts@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/preferences-system.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/preferences-system.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/preferences-system@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/preferences-system@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/process-stop.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/process-stop.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/process-stop@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/process-stop@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/software-update-available.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/software-update-available.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/software-update-available@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/software-update-available@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-0.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-0.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-1.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-1.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-2.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-2.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-3.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-3.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-4.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-4.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/star-5.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/star-5.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-file-manager.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-file-manager.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-file-manager@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-file-manager@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-search.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-search.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-search@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-search@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-shutdown.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-shutdown.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/system-shutdown@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/system-shutdown@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/trophy.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/trophy.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/trophy@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/trophy@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/update.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/update.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/utilities-system-monitor.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/utilities-system-monitor.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/utilities-system-monitor@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/utilities-system-monitor@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/video-display.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/video-display.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/video-display@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/video-display@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/view-fullscreen.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/view-fullscreen.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/view-fullscreen@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/view-fullscreen@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/view-refresh.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/view-refresh.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/view-refresh@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/icons/view-refresh@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/index.theme</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/index.theme</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/alert-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/alert-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-down-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-down-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-left-right-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-left-right-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-up-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-up-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/artboard-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/artboard-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/cheats-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/cheats-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/checkbox-multiple-blank-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/checkbox-multiple-blank-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/chip-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/chip-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/chip-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/chip-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/close-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/close-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-digital-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-digital-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-digital-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-strike-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-strike-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/controller-strike-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-into-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-into-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-out-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-out-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-over-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-step-over-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-toggle-breakpoint.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-toggle-breakpoint.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-trace-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debug-trace-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-clear-breakpoint.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-clear-breakpoint.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-dump-address.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-dump-address.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-address.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-address.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-cursor.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-cursor.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-pc.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/debugger-go-to-pc.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/disc-eject-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/disc-eject-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/disc-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/disc-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/door-open-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/door-open-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/download-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/download-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/eject-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/eject-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/emulation-line.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/emulation-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/emulation-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-list-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-list-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-music-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-music-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-reduce-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-reduce-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-search-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-search-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-settings-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-settings-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-unknow-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/file-unknow-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/filter-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/filter-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/flashlight-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/flashlight-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-add-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-add-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-open-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-open-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-reduce-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-reduce-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-settings-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/folder-settings-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/fullscreen-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/fullscreen-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/function-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/function-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/global-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/global-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/guncon-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/guncon-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/image-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/image-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/information-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/information-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/joystick-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/joystick-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/joystick-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/keyboard-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/keyboard-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/layout-grid-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/layout-grid-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/lightbulb-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/lightbulb-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/list-check.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/list-check.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/mag-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/mag-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/memcard-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/memcard-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/minus-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/minus-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/mouse-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/mouse-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/negcon-line.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/negcon-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/negcon-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/paint-brush-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/paint-brush-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/pause-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/pause-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-circle-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-circle-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-list-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/play-list-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/price-tag-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/price-tag-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/refresh-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/refresh-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/restart-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/restart-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/save-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/save-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/screenshot-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/screenshot-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/settings-3-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/settings-3-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/shut-down-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/shut-down-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sparkle-fill.svg</code></td>
      <td>1</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sparkle-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sparkle-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>Duckstation</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sun-fill.svg</code></td>
      <td>3</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sun-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/sun-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/trash-fill.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/trash-fill.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/trophy-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/trophy-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/tv-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/tv-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/volume-up-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/volume-up-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/window-2-line.svg</code></td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/window-2-line.svg</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_down_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_left_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_right_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/arrow_up_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/base_icon_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_closed_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_end_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_line_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_more_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/branch_open_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_checked_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_indeterminate_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/checkbox_unchecked_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_horizontal_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/line_vertical_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_checked_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/radio_unchecked_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/style.qss</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/style.qss</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_horizontal_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_move_vertical_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_horizontal_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/toolbar_separator_vertical_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/transparent_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_close_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_grip_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_minimize_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_disabled.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_disabled.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_disabled@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_disabled@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_focus.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_focus.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_focus@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_focus@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_pressed.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_pressed.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_pressed@2x.png</code></td>
      <td><code>src/duckstation-qt/resources/qdarkstyle/window_undock_pressed@2x.png</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/selectdiscdialog.cpp</code></td>
      <td><code>src/duckstation-qt/selectdiscdialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/selectdiscdialog.h</code></td>
      <td><code>src/duckstation-qt/selectdiscdialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/selectdiscdialog.ui</code></td>
      <td><code>src/duckstation-qt/selectdiscdialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/settingswindow.cpp</code></td>
      <td><code>src/duckstation-qt/settingswindow.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/settingswindow.h</code></td>
      <td><code>src/duckstation-qt/settingswindow.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/settingswindow.ui</code></td>
      <td><code>src/duckstation-qt/settingswindow.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/settingwidgetbinder.h</code></td>
      <td><code>src/duckstation-qt/settingwidgetbinder.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/setupwizarddialog.cpp</code></td>
      <td><code>src/duckstation-qt/setupwizarddialog.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/setupwizarddialog.h</code></td>
      <td><code>src/duckstation-qt/setupwizarddialog.h</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/setupwizarddialog.ui</code></td>
      <td><code>src/duckstation-qt/setupwizarddialog.ui</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/translations/create-update-and-edit-language.bat</code></td>
      <td>61</td>
      <td>Translation catalog location/resource identity tied to the existing Qt target name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/create-update-and-edit-language.bat</code></td>
      <td><code>src/duckstation-qt/translations/create-update-and-edit-language.bat</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_de.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_de.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_en.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_en.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es-ES.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es-ES.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_es.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_fr.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_fr.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_he.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_he.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_id.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_id.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_it.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_it.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ja.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ja.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ko.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ko.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_nl.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_nl.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pl.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pl.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-BR.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-BR.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-PT.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_pt-PT.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ru.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_ru.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_tr.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_tr.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_zh-CN.ts</code></td>
      <td><code>src/duckstation-qt/translations/duckstation-qt_zh-CN.ts</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/set-language.bat</code></td>
      <td><code>src/duckstation-qt/translations/set-language.bat</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/translations/update-and-edit-english.bat</code></td>
      <td>6, 10</td>
      <td>Translation catalog location/resource identity tied to the existing Qt target name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/update-and-edit-english.bat</code></td>
      <td><code>src/duckstation-qt/translations/update-and-edit-english.bat</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/translations/update-and-edit-language.bat</code></td>
      <td>8, 12</td>
      <td>Translation catalog location/resource identity tied to the existing Qt target name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/update-and-edit-language.bat</code></td>
      <td><code>src/duckstation-qt/translations/update-and-edit-language.bat</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/translations/update_glyph_ranges.py</code></td>
      <td>65</td>
      <td>Translation catalog location/resource identity tied to the existing Qt target name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/translations/update_glyph_ranges.py</code></td>
      <td><code>src/duckstation-qt/translations/update_glyph_ranges.py</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-qt/update_translations.bat</code></td>
      <td>3-15</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/update_translations.bat</code></td>
      <td><code>src/duckstation-qt/update_translations.bat</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-qt/vcruntimecheck.cpp</code></td>
      <td><code>src/duckstation-qt/vcruntimecheck.cpp</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>duckstation</code></td>
      <td><code>src/duckstation-regtest/CMakeLists.txt</code></td>
      <td>1, 5, 7</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-regtest/CMakeLists.txt</code></td>
      <td><code>src/duckstation-regtest/CMakeLists.txt</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-regtest/duckstation-regtest.vcxproj</code></td>
      <td><code>src/duckstation-regtest/duckstation-regtest.vcxproj</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-regtest/duckstation-regtest.vcxproj.filters</code></td>
      <td><code>src/duckstation-regtest/duckstation-regtest.vcxproj.filters</code></td>
      <td>N/A (filename/path)</td>
      <td>Branded source directory or project/resource filename tied to build and tooling references.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/duckstation-regtest/regtest_host.cpp</code></td>
      <td>64, 499</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>src/duckstation-regtest/regtest_host.cpp</code></td>
      <td><code>src/duckstation-regtest/regtest_host.cpp</code></td>
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
      <td><code>duckstation</code>, <code>DuckStation</code></td>
      <td><code>src/updater/CMakeLists.txt</code></td>
      <td>14, 37</td>
      <td>Project, target, executable, resource, package, workflow, or release-artifact name.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/updater/cocoa_main.mm</code></td>
      <td>57, 62</td>
      <td>Internal application, subsystem, resource, log, or diagnostic identity still uses DuckStation branding.</td>
      <td>Medium</td>
    </tr>
    <tr>
      <td>Probably Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/updater/updater.cpp</code></td>
      <td>37, 217</td>
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
      <td>Safe Rename</td>
      <td><code>github.com/psychocodermonkey</code>, <code>duckstation</code>, <code>https://github.com/stenzek/duckstation/tree/master/scripts/deps</code></td>
      <td><code>data/resources/thirdparty.html</code></td>
      <td>1598</td>
      <td>Internal comment or marker contains the legacy product name.</td>
      <td>Low</td>
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
      <td><code>github.com/psychocodermonkey</code>, <code>duckstation</code>, <code>https://github.com/psychocodermonkey/RLyehPSX\n</code></td>
      <td><code>src/duckstation-regtest/regtest_host.cpp</code></td>
      <td>500</td>
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
      <td>Safe Rename</td>
      <td><code>DuckStation</code></td>
      <td><code>src/updater/updater.cpp</code></td>
      <td>216</td>
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

This section includes both DuckStation lineage/authorship references and a comprehensive tracked-file index of copyright/license notices. These are classified `Leave Alone` because rebranding must not erase provenance or license obligations.

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
      <td>copyright/authorship text</td>
      <td><code>CMakeModules/ECMFindModuleHelpers.cmake</code></td>
      <td>101, 107, 109</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>CMakeModules/FindWebP.cmake</code></td>
      <td>1-3, 8, 10, 14, 17</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>CMakeModules/FindZstd.cmake</code></td>
      <td>1, 3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>R'Lyeh PSX</code>, <code>https://github.com/psychocodermonkey</code></td>
      <td><code>CONTRIBUTORS.md</code></td>
      <td>1, 5, 13, 17</td>
      <td>Current project lineage statement paired with required upstream attribution.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code>, <code>stenzek</code>, <code>github.com/psychocodermonkey</code>, <code>https://github.com/psychocodermonkey</code></td>
      <td><code>CONTRIBUTORS.md</code></td>
      <td>13</td>
      <td>Historical lineage or inherited authorship statement; changing it could misstate project provenance.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>LICENSE</code></td>
      <td>4, 41, 77, 80, 85, 94, 105, 157, 162, 170, 173, 183, 199, 239, 359, 362, 416-418, 422-423, 426, 442, 473, 586, 592, 603, 632, 635, 655, 665</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>README.md</code></td>
      <td>117</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code>, <code>duckstation</code>, <code>https://github.com/Trixarian/duckstation-gpl</code></td>
      <td><code>README.md</code></td>
      <td>3, 23, 25, 33, 39-43</td>
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
      <td>copyright/authorship text, license notice text</td>
      <td><code>data/LICENSE.txt</code></td>
      <td>4, 41, 77, 80, 85, 94, 105, 157, 162, 170, 173, 183, 199, 239, 359, 362, 416-418, 422-423, 426, 442, 473, 586, 592, 603, 632, 635, 655, 665</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>data/resources/fonts/LICENSE.txt</code></td>
      <td>13-14, 38, 52, 54, 61, 67, 70, 102, 124, 187, 190, 192</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/dolphinfx/crt/CRT-HYLLIAN.glsl</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/dolphinfx/edge-smoothing/DDT.glsl</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/dolphinfx/edge-smoothing/XBR.glsl</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/dolphinfx/pixel-art/PIXELLATE.glsl</code></td>
      <td>2, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/CRT-NewPixie.fx</code></td>
      <td>12, 19, 24, 34-35, 39</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/Deband.fx</code></td>
      <td>5, 14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>data/resources/shaders/reshade/Shaders/FilmGrain2.fx</code></td>
      <td>5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/LUT.fx</code></td>
      <td>6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/UIMask.fx</code></td>
      <td>75, 84, 90</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/anti-aliasing/fxaa.fx</code></td>
      <td>6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/crt/crt-hyllian-sinc.fx</code></td>
      <td>6, 15, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/edge-smoothing/super-xbr.fx</code></td>
      <td>6, 15, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>data/resources/shaders/reshade/Shaders/interpolation/bicubic.fx</code></td>
      <td>6, 15, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>data/resources/thirdparty.html</code></td>
      <td>6, 22-23, 27, 33, 36, 43-46, 53, 56, 60, 63, 74, 78, 91, 100, 106, 114, 123, 129, 139, 151, 159, 168, 178, 184, 194, 204, 249, 282, 292, 310, 338, 369-370, 373-389, 391, 397, 400, 403, 406, 409, 441-442, 450, 454, 462, 466, 481, 492, 496, 539-540, 564, 578, 580, 587, 593, 596, 628, 650, 713, 716, 718, 734, 744, 755, 763, 773, 779, 788, 791, 796, 812, 822, 828, 842, 851, 857, 865, 872, 877, 887, 896, 902, 910, 915, 917, 924, 927, 943, 950, 976-980, 985, 1004, 1021-1022, 1046, 1060, 1062, 1069, 1075, 1078, 1110, 1132, 1195, 1198, 1200, 1221, 1241, 1246, 1249, 1253, 1257, 1260, 1271, 1297, 1302, 1305, 1326, 1333, 1336, 1339, 1356-1357, 1368-1370, 1399, 1408, 1414, 1422, 1426-1428, 1430, 1436-1437, 1446, 1452, 1460, 1482, 1491, 1497, 1506, 1510, 1512, 1522, 1526, 1532, 1534, 1537, 1563, 1569, 1575, 1584, 1590, 1605, 1649, 1722, 1734, 1756, 1887-1888, 2014-2015, 2038, 2048, 2057, 2084-2085, 2109, 2123, 2125, 2132, 2138, 2141, 2173, 2195, 2258, 2261, 2263, 2278, 2284, 2286, 2292, 2295, 2311, 2317, 2319, 2326, 2329, 2340, 2346, 2348, 2351, 2355, 2358, 2370, 2378, 2381, 2385, 2388, 2399, 2423, 2428, 2431, 2439, 2442, 2455-2456, 2465, 2471, 2481, 2490, 2496</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/biscuit/LICENSE.md</code></td>
      <td>1, 7, 10</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/biscuit/README.md</code></td>
      <td>72</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/biscuit/include/biscuit/cpuinfo.hpp</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/biscuit/src/cpuinfo.cpp</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/LICENSE</code></td>
      <td>1, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/cubeb/README.md</code></td>
      <td>7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/include/cubeb/cubeb.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb-internal.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_alsa.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_assert.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_audiounit.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_jack.cpp</code></td>
      <td>2-4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_log.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_log.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_mixer.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_mixer.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_oss.c</code></td>
      <td>2-4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_osx_run_loop.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_osx_run_loop.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_pulse.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_resampler.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_resampler.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_resampler_internal.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_ring_array.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_ringbuffer.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_sndio.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_strings.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_strings.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_tracing.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_triple_buffer.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_utils.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_utils.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_utils_unix.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_utils_win.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_wasapi.cpp</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/src/cubeb_winmm.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/arch.h</code></td>
      <td>1, 11, 14, 22</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/fixed_generic.h</code></td>
      <td>1, 11, 14, 22</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/resample.c</code></td>
      <td>1-2, 11, 14</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/resample_neon.h</code></td>
      <td>1-3, 15, 18, 26</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/resample_sse.h</code></td>
      <td>1-2, 13, 16, 24</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/speex_resampler.h</code></td>
      <td>1, 15, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/cubeb/subprojects/speex/stack_alloc.h</code></td>
      <td>1, 11, 14, 22</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/d3d12ma/include/D3D12MemAlloc.h</code></td>
      <td>2, 11, 17, 29</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/d3d12ma/src/D3D12MemAlloc.cpp</code></td>
      <td>2, 11, 17</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>dep/fast_float/LICENSE-APACHE</code></td>
      <td>12-13, 37, 51, 53, 60, 66, 69, 101, 123, 178, 180</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fast_float/LICENSE-MIT</code></td>
      <td>3, 15, 23</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/fast_float/README.md</code></td>
      <td>237</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/COPYING.LGPLv2.1</code></td>
      <td>4, 48, 121, 133, 155, 286-287, 413-414, 437, 447, 456, 480, 483, 502, 505</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/ac3_parser.h</code></td>
      <td>3-4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/avcodec.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/d3d11va.h</code></td>
      <td>4-5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/dirac.h</code></td>
      <td>2-4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/dxva2.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/jni.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/mediacodec.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/vdpau.h</code></td>
      <td>5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavcodec/videotoolbox.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavfilter/avfilter.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavformat/avformat.h</code></td>
      <td>2, 385</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavformat/avio.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/adler32.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/aes.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/aes_ctr.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/ambient_viewing_environment.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/attributes.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/audio_fifo.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/avassert.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/avstring.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/avutil.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/base64.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/blowfish.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/bprint.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/bswap.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/camellia.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/cast5.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/channel_layout.h</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/common.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/cpu.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/crc.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/csp.h</code></td>
      <td>2-4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/des.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/display.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/dovi_meta.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/downmix_info.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/eval.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/executor.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/hash.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/hdr_dynamic_metadata.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/hdr_dynamic_vivid_metadata.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/hmac.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/hwcontext_d3d12va.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/intfloat.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/lfg.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/log.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/lzo.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/mastering_display_metadata.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/mathematics.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/md5.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/mem.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/murmur3.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/opt.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/pixdesc.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/pixfmt.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/random_seed.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/rational.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/ripemd.h</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/sha.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/sha512.h</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/spherical.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/stereo3d.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/tea.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/time.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/timecode.h</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/tree.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/twofish.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/uuid.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/version.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/video_hint.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libavutil/xtea.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libpostproc/postprocess.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libswresample/swresample.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/ffmpeg/include/libswscale/swscale.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/fmt/CONTRIBUTING.md</code></td>
      <td>6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/LICENSE</code></td>
      <td>1, 11, 17, 27</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/LICENSE.rst</code></td>
      <td>1, 11, 17, 27</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/args.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/base.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/chrono.h</code></td>
      <td>3, 68</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/color.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/compile.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/core.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/format-inl.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/format.h</code></td>
      <td>4, 14, 20, 30</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/os.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/ostream.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/printf.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/ranges.h</code></td>
      <td>3, 8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/std.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/include/fmt/xchar.h</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/src/format.cc</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/fmt/src/os.cc</code></td>
      <td>3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/fmt/support/cmake/JoinPaths.cmake</code></td>
      <td>5, 8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/glad/include/EGL/eglplatform.h</code></td>
      <td>5-6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/glad/include/KHR/khrplatform.h</code></td>
      <td>5, 15, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/include/glad/egl.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/include/glad/gl.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/include/glad/wgl.h</code></td>
      <td>4</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/src/egl.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/src/gl.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>dep/glad/src/wgl.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/LICENSE</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-death-test.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-matchers.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-message.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-param-test.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-printers.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-spi.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-test-part.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest-typed-test.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest_pred_impl.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/gtest_prod.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/custom/gtest-port.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/custom/gtest-printers.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/custom/gtest.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-death-test-internal.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-filepath.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-internal.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-param-util.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-port-arch.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-port.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-string.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/include/gtest/internal/gtest-type-util.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-all.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-death-test.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-filepath.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-internal-inl.h</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-matchers.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-port.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-printers.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-test-part.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest-typed-test.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/googletest/src/gtest_main.cc</code></td>
      <td>1, 8, 11, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/LICENSE.txt</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/docs/CONTRIBUTING.md</code></td>
      <td>9, 76, 80</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>dep/imgui/docs/FONTS.md</code></td>
      <td>587-588</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/imgui/docs/README.md</code></td>
      <td>230</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>dep/imgui/include/IconsEmoji.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/include/IconsFontAwesome5.h</code></td>
      <td>243</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/imgui/include/imconfig.h</code></td>
      <td>95</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/include/imstb_textedit.h</code></td>
      <td>1492, 1499, 1504, 1514-1515, 1519</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/src/imgui.cpp</code></td>
      <td>30, 32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/imgui/src/imgui_demo.cpp</code></td>
      <td>8162</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/src/imgui_draw.cpp</code></td>
      <td>6292, 6481</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/imgui/src/imgui_freetype.cpp</code></td>
      <td>611</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/src/imstb_rectpack.h</code></td>
      <td>592, 599, 604, 614-615, 619</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/src/imstb_truetype.h</code></td>
      <td>5050, 5057, 5062, 5072-5073, 5077</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/imgui/src/stb_sprintf.h</code></td>
      <td>1874, 1881, 1886, 1896-1897, 1901</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/kissfft/src/_kiss_fft_guts.h</code></td>
      <td>2, 8-9, 12</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/kissfft/src/kiss_fft.cpp</code></td>
      <td>2, 8-9, 12</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/kissfft/src/kiss_fftr.cpp</code></td>
      <td>2, 8-9, 12</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/LICENSE.txt</code></td>
      <td>1, 6, 8, 15, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/libchdr/README.md</code></td>
      <td>7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/dr_libs/dr_flac.h</code></td>
      <td>12501-12502, 12506, 12520, 12532</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/libchdr/bitstream.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/libchdr/cdrom.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/libchdr/chd.h</code></td>
      <td>9, 16, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/libchdr/flac.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/include/libchdr/huffman.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/src/libchdr_bitstream.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/src/libchdr_cdrom.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/src/libchdr_chd.c</code></td>
      <td>9, 16, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/src/libchdr_flac.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/libchdr/src/libchdr_huffman.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>LICENSE</code> license/notice document</td>
      <td><code>dep/lzma/LICENSE</code></td>
      <td>Entire file</td>
      <td>Standalone license/notice file; preserve with the distributed component and do not rebrand its contents.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/MiniZip64_info.txt</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/include/ioapi.h</code></td>
      <td>4, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/include/iowin32.h</code></td>
      <td>5, 8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/include/unzip.h</code></td>
      <td>5, 8, 11</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/include/zip.h</code></td>
      <td>5, 8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/src/crypt.h</code></td>
      <td>6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/src/ioapi.c</code></td>
      <td>4, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/src/iowin32.c</code></td>
      <td>5, 8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/src/unzip.c</code></td>
      <td>5, 8, 11, 21, 49, 62, 122-123, 603</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/minizip/src/zip.c</code></td>
      <td>5, 8, 98</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/rainterface/LICENSE</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/rapidyaml/LICENSE.txt</code></td>
      <td>1, 10, 16</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/rcheevos/LICENSE</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/rcheevos/src/rhash/md5.c</code></td>
      <td>2, 34</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/rcheevos/src/rhash/md5.h</code></td>
      <td>2, 34</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/reshadefx/LICENSE.md</code></td>
      <td>1, 5-7, 9</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/GLSL.std.450.h</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_codegen.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_expression.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_lexer.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_module.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_parser.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_preprocessor.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_symbol_table.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/include/effect_token.hpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/reshadefx/include/spirv.hpp</code></td>
      <td>1, 10, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_codegen_glsl.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_codegen_hlsl.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_codegen_spirv.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_expression.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_lexer.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_parser_exp.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_parser_stmt.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_preprocessor.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_symbol_table.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/reshadefx/src/effect_symbol_table_intrinsics.inl</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/riscv-disas/include/riscv-disas.h</code></td>
      <td>4-5, 14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/riscv-disas/src/riscv-disas.c</code></td>
      <td>4-5, 14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/simpleini/LICENCE.txt</code></td>
      <td>3, 12, 18</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/simpleini/include/ConvertUTF.h</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/simpleini/include/SimpleIni.h</code></td>
      <td>191, 200, 206</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/simpleini/src/ConvertUTF.c</code></td>
      <td>2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/LICENCE</code></td>
      <td>6, 12, 14, 21, 24</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/assembler-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/constants-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/disasm-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/instructions-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/location-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/macro-assembler-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch32/operands-aarch32.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/abi-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/assembler-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/constants-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/cpu-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/cpu-features-auditor-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/debugger-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/decoder-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/decoder-constants-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/decoder-visitor-map-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/disasm-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/instructions-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/macro-assembler-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/operands-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/registers-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/simulator-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/aarch64/simulator-constants-aarch64.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/assembler-base-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/code-buffer-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/code-generation-scopes-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/compiler-intrinsics-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/cpu-features.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/globals-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/invalset-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/macro-assembler-interface.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/platform-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/pool-manager-impl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/pool-manager.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/include/vixl/utils-vixl.h</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/assembler-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/constants-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/disasm-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/instructions-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/location-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/macro-assembler-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch32/operands-aarch32.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/assembler-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/assembler-sve-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/cpu-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/cpu-features-auditor-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/debugger-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/decoder-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/disasm-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/instructions-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/logic-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/macro-assembler-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/macro-assembler-sve-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/operands-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/pointer-auth-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/registers-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/aarch64/simulator-aarch64.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/code-buffer-vixl.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/compiler-intrinsics-vixl.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/cpu-features.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vixl/src/utils-vixl.cc</code></td>
      <td>1, 7, 9, 16, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_av1std.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_av1std_decode.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h264std.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h264std_decode.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h264std_encode.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h265std.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h265std_decode.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codec_h265std_encode.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vk_video/vulkan_video_codecs_common.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vk_icd.h</code></td>
      <td>2-4, 6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vk_layer.h</code></td>
      <td>2-4, 6</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vk_mem_alloc.h</code></td>
      <td>2, 11, 17, 30</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vk_platform.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_android.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_beta.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_core.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_directfb.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_fuchsia.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_ggp.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_ios.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_macos.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_metal.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_screen.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_vi.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_wayland.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_win32.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_xcb.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_xlib.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier, copyright/authorship text</td>
      <td><code>dep/vulkan/include/vulkan/vulkan_xlib_xrandr.h</code></td>
      <td>5, 7</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/winpixeventruntime/include/WinPixEventRuntime/PIXEvents.h</code></td>
      <td>1, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/winpixeventruntime/include/WinPixEventRuntime/PIXEventsCommon.h</code></td>
      <td>1, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/winpixeventruntime/include/WinPixEventRuntime/pix3.h</code></td>
      <td>1, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/winpixeventruntime/include/WinPixEventRuntime/pix3_win.h</code></td>
      <td>1, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xbyak/COPYRIGHT</code></td>
      <td>2, 8, 10, 13, 17, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xbyak/readme.md</code></td>
      <td>75</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xxhash/LICENSE</code></td>
      <td>2, 10, 13, 17, 20, 31</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xxhash/include/xxh_x86dispatch.h</code></td>
      <td>3, 11, 14, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xxhash/include/xxhash.h</code></td>
      <td>4, 12, 15, 19, 22</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xxhash/src/xxh_x86dispatch.c</code></td>
      <td>3, 11, 14, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/xxhash/src/xxhash.c</code></td>
      <td>3, 11, 14, 18, 21</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/LICENSE</code></td>
      <td>3-4, 13, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/zydis/README.md</code></td>
      <td>163</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/LICENSE</code></td>
      <td>3-4, 13, 19</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>license notice text</td>
      <td><code>dep/zydis/dependencies/zycore/README.md</code></td>
      <td>29</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Allocator.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Comparison.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Defines.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Format.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/LibC.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Object.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Status.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/String.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Types.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/include/Zycore/Vector.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/src/Allocator.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/src/Format.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/src/String.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/dependencies/zycore/src/Vector.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Decoder.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/DecoderTypes.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Defines.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Disassembler.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Formatter.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/FormatterBuffer.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/DecoderData.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/FormatterATT.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/FormatterBase.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/FormatterIntel.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/SharedData.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Internal/String.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/MetaInfo.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Mnemonic.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Register.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Segment.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/SharedTypes.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/ShortString.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Status.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Utils.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/include/Zydis/Zydis.h</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Decoder.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/DecoderData.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Disassembler.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Formatter.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/FormatterATT.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/FormatterBase.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/FormatterBuffer.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/FormatterIntel.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/MetaInfo.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Mnemonic.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Register.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Segment.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/SharedData.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/String.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Utils.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>dep/zydis/src/Zydis.c</code></td>
      <td>14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>extras/fonts/promptfont.sfd</code></td>
      <td>6, 2848</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>10-11, 16</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/type2-runtime/releases/download/continuous/runtime-x86_64</code></td>
      <td><code>scripts/appimage/make-appimage.sh</code></td>
      <td>105</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/deps/build-dependencies-linux.sh</code></td>
      <td>379</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/cpuinfo/archive/$CPUINFO.tar.gz</code>, <code>https://github.com/stenzek/discord-rpc/archive/$DISCORD_RPC.tar.gz</code>, <code>https://github.com/stenzek/shaderc/archive/$SHADERC.tar.gz</code>, <code>https://github.com/stenzek/soundtouch/archive/$SOUNDTOUCH.tar.gz</code></td>
      <td><code>scripts/deps/build-dependencies-linux.sh</code></td>
      <td>86-87, 90-91</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/cpuinfo/archive/$CPUINFO.tar.gz</code>, <code>https://github.com/stenzek/discord-rpc/archive/$DISCORD_RPC.tar.gz</code>, <code>https://github.com/stenzek/shaderc/archive/$SHADERC.tar.gz</code>, <code>https://github.com/stenzek/soundtouch/archive/$SOUNDTOUCH.tar.gz</code></td>
      <td><code>scripts/deps/build-dependencies-mac.sh</code></td>
      <td>119-120, 123-124</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/deps/build-dependencies-mac.sh</code></td>
      <td>363</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/deps/build-dependencies-windows-arm64.bat</code></td>
      <td>254</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/discord-rpc/archive/%DISCORD_RPC%.zip</code>, <code>https://github.com/stenzek/shaderc/archive/%SHADERC%.zip</code>, <code>https://github.com/stenzek/soundtouch/archive/%SOUNDTOUCH%.zip</code></td>
      <td><code>scripts/deps/build-dependencies-windows-arm64.bat</code></td>
      <td>85, 88-89</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/deps/build-dependencies-windows-x64.bat</code></td>
      <td>251</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/discord-rpc/archive/%DISCORD_RPC%.zip</code>, <code>https://github.com/stenzek/shaderc/archive/%SHADERC%.zip</code>, <code>https://github.com/stenzek/soundtouch/archive/%SOUNDTOUCH%.zip</code></td>
      <td><code>scripts/deps/build-dependencies-windows-x64.bat</code></td>
      <td>83, 86-87</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/shaderc.git</code></td>
      <td><code>scripts/flatpak/modules/22-shaderc.yaml</code></td>
      <td>13</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>scripts/flatpak/modules/22-shaderc.yaml</code></td>
      <td>8</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/cpuinfo.git</code></td>
      <td><code>scripts/flatpak/modules/24-cpuinfo.yaml</code></td>
      <td>19</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/discord-rpc.git</code></td>
      <td><code>scripts/flatpak/modules/25-discord-rpc.yaml</code></td>
      <td>11</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>github.com/psychocodermonkey</code>, <code>https://github.com/stenzek/soundtouch.git</code></td>
      <td><code>scripts/flatpak/modules/26-soundtouch.yaml</code></td>
      <td>18</td>
      <td>Pinned upstream dependency or build-tool URL; this is provenance and an operational source, not product branding.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/bitutils_tests.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/file_system_tests.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/gsvector_yuvtorgb_test.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/path_tests.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/rectangle_tests.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common-tests/string_tests.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/align.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/assert.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/assert.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/binary_reader_writer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/binary_reader_writer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/bitfield.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/bitutils.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/cocoa_tools.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/cocoa_tools.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/crash_handler.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/crash_handler.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/common/dimensional_array.h</code></td>
      <td>2, 11, 17</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/dynamic_library.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/dynamic_library.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/easing.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/error.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/error.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/fastjmp.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/fastjmp.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/fastjmp_arm.asm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/fastjmp_x86.asm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/fifo_queue.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/file_system.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/file_system.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector_formatter.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector_neon.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector_nosimd.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/gsvector_sse.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
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
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/heap_array.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/heterogeneous_containers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/intrin.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/layered_settings_interface.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/layered_settings_interface.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/log.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/log.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/lru_cache.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/md5_digest.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/memmap.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/memmap.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/memory_settings_interface.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/memory_settings_interface.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/minizip_helpers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/path.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/perf_scope.cpp</code></td>
      <td>2-3</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/perf_scope.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/progress_callback.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/progress_callback.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/ryml_helpers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/scoped_guard.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/settings_interface.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/sha1_digest.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/sha1_digest.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/small_string.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/small_string.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/string_util.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/string_util.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>src/common/thirdparty/SmallVector.cpp</code></td>
      <td>5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX license identifier</td>
      <td><code>src/common/thirdparty/SmallVector.h</code></td>
      <td>5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/common/thirdparty/StackWalker.cpp</code></td>
      <td>58, 64, 66, 72, 75</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/common/thirdparty/StackWalker.h</code></td>
      <td>14, 20, 22, 28, 31</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/threading.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/threading.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/timer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/timer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/common/windows_headers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/achievements.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/achievements.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/achievements_private.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/analog_controller.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/analog_controller.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/analog_joystick.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/analog_joystick.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/bios.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/bios.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/bus.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/bus.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cdrom.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cdrom.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cdrom_async_reader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cdrom_async_reader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cheats.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cheats.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/controller.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/controller.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_code_cache.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_code_cache.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_code_cache_private.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_core.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_core.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_core_private.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_disasm.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_disasm.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_aarch32.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_aarch32.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_aarch64.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_aarch64.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_riscv64.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_riscv64.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_x64.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_newrec_compiler_x64.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_pgxp.cpp</code></td>
      <td>1-2, 5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_pgxp.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator_aarch32.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator_aarch64.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator_generic.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_code_generator_x64.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_register_cache.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_register_cache.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_thunks.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_recompiler_types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_types.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/cpu_types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/digital_controller.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/digital_controller.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/dma.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/dma.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/fullscreen_ui.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/fullscreen_ui.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/game_database.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/game_database.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/game_list.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/game_list.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gdb_server.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gdb_server.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_backend.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_backend.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_commands.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_hw.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_hw.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_hw_shadergen.cpp</code></td>
      <td>1-2, 215, 224, 230, 390, 399, 405</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_hw_shadergen.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_shadergen.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_shadergen.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_backend.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_backend.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_rasterizer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_rasterizer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_rasterizer.inl</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code></td>
      <td><code>src/core/gpu_sw_rasterizer.inl</code></td>
      <td>743</td>
      <td>Authorship/derivation comment records the origin of inherited implementation work.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_sw_rasterizer_avx2.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gpu_types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gte.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gte.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/gte_types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/guncon.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/guncon.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/host.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/host.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/host_interface_progress_callback.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/host_interface_progress_callback.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/hotkeys.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/imgui_overlays.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/imgui_overlays.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/input_types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/interrupt_controller.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/interrupt_controller.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/justifier.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/justifier.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/mdec.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/mdec.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/memory_card.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/memory_card.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/memory_card_image.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/memory_card_image.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/core/mips_encoder.h</code></td>
      <td>5, 14, 20</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/multitap.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/multitap.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/negcon.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/negcon.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/negcon_rumble.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/negcon_rumble.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pad.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pad.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pcdrv.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pcdrv.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pch.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pch.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pine_server.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/pine_server.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/playstation_mouse.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/playstation_mouse.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/psf_loader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/psf_loader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/save_state_version.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/settings.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/settings.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/shader_cache_version.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/sio.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/sio.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/spu.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/spu.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/system.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/system.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/texture_replacements.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/texture_replacements.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/timers.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/timers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/timing_event.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/timing_event.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/core/types.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/Info.plist.in</code></td>
      <td>40</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/aboutdialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/aboutdialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/achievementlogindialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/achievementlogindialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/achievementsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/achievementsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/advancedsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/advancedsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/audiosettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/audiosettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/autoupdaterdialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/autoupdaterdialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/biossettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/biossettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/cheatcodeeditordialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/cheatmanagerwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/colorpickerbutton.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/colorpickerbutton.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/consolesettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/consolesettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllerbindingwidgets.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllerglobalsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllersettingswindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllersettingswindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/controllersettingwidgetbinder.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/coverdownloaddialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/coverdownloaddialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/debuggermodels.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/debuggermodels.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/debuggerwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/debuggerwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/displaywidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/displaywidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/duckstation-qt.rc</code></td>
      <td>74</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/emulationsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/emulationsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/foldersettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/foldersettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistmodel.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistmodel.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistrefreshthread.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistwidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamelistwidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamesummarywidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/gamesummarywidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/graphicssettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/graphicssettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/hotkeysettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/inputbindingdialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/inputbindingdialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/inputbindingwidgets.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/inputbindingwidgets.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/interfacesettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/interfacesettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/logwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/logwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/mainwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/mainwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memorycardeditorwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memorycardsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memoryscannerwindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/memoryscannerwindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/pch.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/pch.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/postprocessingsettingswidget.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/qt5.natvis</code></td>
      <td>5</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qthost.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qthost.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtkeycodes.cpp</code></td>
      <td>1-2, 171</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtprogresscallback.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtprogresscallback.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtthemes.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qttranslations.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtutils.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/qtutils.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/add-line.svg</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-down-line.svg</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/arrow-up-line.svg</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/mag-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/black/svg/minus-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/add-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-down-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/arrow-up-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/mag-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/duckstation-qt/resources/icons/white/svg/minus-line.svg</code></td>
      <td>32</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/selectdiscdialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/selectdiscdialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/settingswindow.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/settingswindow.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/settingwidgetbinder.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/setupwizarddialog.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/setupwizarddialog.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-qt/vcruntimecheck.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/duckstation-regtest/regtest_host.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/scmversion/scmversion.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text, license notice text</td>
      <td><code>src/updater/Info.plist.in</code></td>
      <td>15-16</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/cocoa_main.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/cocoa_progress_callback.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/cocoa_progress_callback.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/updater.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/updater.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>copyright/authorship text</td>
      <td><code>src/updater/updater.rc</code></td>
      <td>74</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/win32_main.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/win32_progress_callback.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/updater/win32_progress_callback.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/audio_stream.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td><code>DuckStation</code></td>
      <td><code>src/util/audio_stream.cpp</code></td>
      <td>967</td>
      <td>Authorship/derivation comment records the origin of inherited implementation work.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/audio_stream.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice</td>
      <td><code>src/util/audio_stream_channel_maps.inl</code></td>
      <td>1</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_bin.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_chd.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_cue.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_ecm.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_hasher.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_hasher.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_m3u.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_mds.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_memory.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_pbp.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_image_ppf.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_subchannel_replacement.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cd_subchannel_replacement.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/compress_helpers.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/compress_helpers.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cubeb_audio_stream.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cue_parser.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/cue_parser.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_pipeline.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_pipeline.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_stream_buffer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_stream_buffer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_texture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d11_texture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_builders.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_builders.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_descriptor_heap_manager.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_descriptor_heap_manager.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_pipeline.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_pipeline.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_stream_buffer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_stream_buffer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_texture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d12_texture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d_common.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/d3d_common.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/dinput_source.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/dinput_source.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_framebuffer_manager.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_shader_cache.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_shader_cache.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_texture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/gpu_texture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/host.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/host.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader_curl.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader_curl.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader_winhttp.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/http_downloader_winhttp.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/image.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/image.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_animated.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_fullscreen.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_fullscreen.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_glyph_ranges.inl</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_manager.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/imgui_manager.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/ini_settings_interface.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/ini_settings_interface.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/input_manager.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/input_manager.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/input_source.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/input_source.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/iso_reader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/iso_reader.h</code></td>
      <td>1-2, 84</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/media_capture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/media_capture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/metal_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/metal_device.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/metal_layer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/metal_stream_buffer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/metal_stream_buffer.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_agl.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_agl.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl_wayland.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl_wayland.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl_x11.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_egl_x11.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_wgl.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_context_wgl.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_loader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_pipeline.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_pipeline.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_stream_buffer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_stream_buffer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_texture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/opengl_texture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/page_fault_handler.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/page_fault_handler.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/pch.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/pch.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/platform_misc.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/platform_misc_mac.mm</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/platform_misc_unix.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/platform_misc_win32.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader_fx.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader_fx.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader_glsl.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/postprocessing_shader_glsl.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/sdl_audio_stream.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/sdl_input_source.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/sdl_input_source.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/shadergen.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/shadergen.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/sockets.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/sockets.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/state_wrapper.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/state_wrapper.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_builders.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_builders.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_device.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_device.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_entry_points.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_entry_points.inl</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_loader.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_loader.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_pipeline.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_pipeline.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_stream_buffer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_stream_buffer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_swap_chain.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_swap_chain.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_texture.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/vulkan_texture.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/wav_writer.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/wav_writer.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/win32_raw_input_source.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/win32_raw_input_source.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/window_info.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/window_info.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/xinput_source.cpp</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
      <td>High</td>
    </tr>
    <tr>
      <td>Leave Alone</td>
      <td>SPDX copyright notice, SPDX license identifier</td>
      <td><code>src/util/xinput_source.h</code></td>
      <td>1-2</td>
      <td>Copyright, license, or authorship notice. Preserve unless legal review confirms an additive correction; rebranding is not grounds for removal.</td>
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
| `RLyehPSX.icns` | macOS ICNS | `src/duckstation-qt/RLyehPSX.icns` | macOS application icon |
| `rlyehpsx-qt.ico` | Windows ICO, seven embedded images | `src/duckstation-qt/rlyehpsx-qt.ico` | Windows application/updater icon |
| `vaulketh.png` | PNG, 260×260 RGBA | `src/duckstation-qt/resources/icons/vaulketh.png` | Qt application/dialog icon |
| `vaulketh_64.png` | PNG, 64×64 RGBA | `src/duckstation-qt/resources/icons/vaulketh_64.png` | Qt icon variant |
| `vaulketh_128.png` | PNG, 128×128 RGBA | `src/duckstation-qt/resources/icons/vaulketh_128.png` | Qt icon variant |
| `UpdateVaulketh.png` | PNG, 48×48 RGBA | `src/duckstation-qt/resources/icons/UpdateVaulketh.png` | Qt updater illustration |

The former DuckStation image files and their source/build references have been removed or replaced. The remaining `org.duckstation.DuckStation` icon filename in the Flatpak install destination is intentional because package/application identity was outside the scope of this pass.

## Review notes

- `README.md`, `CONTRIBUTORS.md`, `RESPECT.md`, and portions of `STATE.md` intentionally describe project lineage. Those upstream names are attribution, not stale active-product branding.
- URLs under `github.com/psychocodermonkey` in dependency build scripts point to dependency forks or build tools. Repointing them without matching artifacts and hashes would break dependency acquisition.
- Translation catalogs contain both visible strings and internal source-location paths. Rename source text first, then regenerate catalogs; blind replacement risks stale or invalid translation metadata.
- External identifiers may be owned outside this repository. A new reverse-DNS ID, Discord application/assets, updater release source, package listing, and support endpoints must exist before corresponding references can safely change.
- The save-state magic `0x43435544` and current version `71` should not be changed merely for branding. Any format-identity change needs an explicit backward-compatibility and migration policy.
