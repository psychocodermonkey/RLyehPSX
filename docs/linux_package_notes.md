# Linux package build documentation notes

These notes are for the planned cross-platform build documentation. They are not a complete package build guide.

## Flatpak

- The Flatpak manifest is `scripts/flatpak/dev.rlyeh.rlyehpsx.yaml`. It currently targets KDE Platform/SDK 6.11 and the LLVM 21 SDK extension.
- Before running `flatpak-builder` from a fresh checkout, generate the AppStream file with `./scripts/generate-metainfo.sh scripts/flatpak` from the repository root. The manifest installs `scripts/flatpak/dev.rlyeh.rlyehpsx.metainfo.xml`, which is generated from `scripts/dev.rlyeh.rlyehpsx.metainfo.xml.in` and ignored by Git.
- The generator uses `git describe` for the release version. When no usable tag exists, it prints a Git error and falls back to the current commit hash; generation still completes.
- The build host needs `flatpak`, `flatpak-builder`, a Flathub remote, and the manifest's matching KDE runtime, SDK, and LLVM extension. The host's Clang version does not select the compiler inside the Flatpak SDK.
- A headless host can build and inspect the Flatpak, but graphical launch testing needs a desktop session.

## AppImage

- Build the Linux release executable and its `deps` prefix first.
- From the repository root, generate the AppImage with:

  ```sh
  ./scripts/appimage/make-appimage.sh "$PWD" "$PWD/build/release-linux" "$PWD/deps" RLyehPSX-x64
  ```

- The script places its downloaded tools, `RLyehPSX.AppDir`, and `RLyehPSX-x64.AppImage` under `build/appimage/`, which Git ignores.
