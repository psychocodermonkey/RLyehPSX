# Project R’lyeh: GitHub Workflow and Development Roadmap

**Status:** Planning document  
**Date:** October 30, 2026  
**Project:** R’lyeh PSX

## 1. Purpose

Establish a consistent GitHub workflow for managing R’lyeh PSX development, including:

- Development milestones and actionable issues.
- Feature requests, investigations, and design discussions.
- Pull requests, merge commits, and validation records.
- Long-term technical documentation.
- The remaining major development initiatives.

This document captures the agreed direction for organizing development work. It is not itself an implementation plan or authorization to create GitHub resources.

The objective is to improve project organization, preserve engineering decisions, and make development history accessible without introducing unnecessary administrative overhead.

---

## 2. GitHub Development Workflow

### 2.1 General workflow

The intended development process is:

**Milestone → Issue → Development Branch → Pull Request → Validation → Merge**

Each component has a distinct responsibility.

| Component | Responsibility |
|---|---|
| Milestone | Defines a major development objective or deliverable |
| Issue | Tracks actionable work, investigations, decisions, and progress |
| Feature request | Proposes new functionality or capabilities, tracked through GitHub Issues |
| Development branch | Contains implementation work and meaningful commits |
| Pull request | Records integration scope, discussion, and validation |
| Merge commit | Permanently summarizes the integrated changes in Git history |
| Documentation | Describes the current, implemented state of the project |

Not every small change requires a dedicated issue or pull request. The process should remain proportional to the work.

### 2.2 Pull request policy

Substantial feature, migration, refactoring, and maintenance branches should use pull requests when integrating into the appropriate development branch.

**Preferred GitHub merge strategy: Create a merge commit.**

Avoid squash or rebase merging for these integration checkpoints unless there is a specific reason to depart from the standard workflow.

This preserves meaningful development commits and establishes a clear integration point.

A pull request should provide:

- Summary of the work and its purpose.
- Significant implementation changes.
- Related issues and milestone associations.
- Relevant technical decisions.
- Known limitations or deferred work.
- Platform build and functional validation results.
- Problems encountered and their resolution.

Pull requests may be opened and merged by the same maintainer. Their purpose is engineering traceability, not necessarily external approval.

### 2.3 Validation records

Platform validation is a continuous development responsibility, not a milestone that can be permanently completed.

Validation results should be recorded in the relevant pull request, preferably identifying the tested commit or revision.

Examples include:

- macOS build and runtime validation.
- Linux build and runtime validation.
- Game boot and execution smoke tests.
- Graphics renderer verification.
- Audio playback and capture testing.
- Controller input and rumble testing.
- Platform-specific functionality.

Record what was actually tested, including any untested or deferred areas.

A successful build does not automatically imply successful functional validation.

If code changes after validation, determine whether the affected tests need to be repeated.

### 2.4 Merge commit messages

Retain the existing practice of writing detailed, meaningful merge commit messages.

Merge commits should summarize:

- What was integrated.
- Why the changes were necessary.
- Major technical changes.
- Important compatibility or behavioral considerations.
- Validation performed.
- Outstanding limitations where relevant.

**The pull request preserves the development and validation discussion. The merge commit preserves the integration summary in Git itself.**

GitHub pull request discussions and check results are not stored in ordinary Git history. Merge commit messages should therefore remain independently useful.

---

## 3. Issues and Feature Requests

### 3.1 Issue tracking

Migrate actionable roadmap items from planning documents into GitHub Issues.

Issues should be used for:

- Implementation tasks.
- Bugs and regressions.
- Feature requests.
- Technical investigations.
- Dependency upgrades.
- Platform support work.
- Architectural decisions requiring investigation.
- Work discovered during existing migrations.

An issue can evolve as work progresses.

Comments should preserve relevant findings, decisions, alternatives considered, obstacles, and changes in direction.

This provides a durable record of engineering thought processes without requiring commits solely to synchronize planning notes.

### 3.2 Issue scope

Issues should represent reasonably actionable work.

Avoid creating large numbers of speculative issues for ideas that have no defined implementation objective.

A broad initiative may need multiple issues or smaller deliverables. Those can be identified as the scope becomes clearer.

Feature requests should remain distinguishable from confirmed implementation commitments.

### 3.3 Relationship to milestones

Assign issues to the appropriate milestone when their relationship is known.

Some initiatives may produce additional issues, tasks, or subordinate planning objectives during investigation.

The precise GitHub hierarchy and organization can be determined when the milestones are created.

### 3.4 Closing issues

Pull requests should reference related issues.

GitHub's issue-closing keywords may be used where appropriate, but automatic closure depends on GitHub's default-branch behavior. Because R’lyeh uses `dev` as an integration branch, issue closure should be verified rather than assumed.

---

## 4. Documentation Strategy

### 4.1 Purpose of `docs/`

The long-term objective is to turn `docs/` into a useful, maintained **R’lyeh user and developer manual**, authored and navigated through an Obsidian-compatible Markdown vault.

Documentation should describe the project as it currently exists.

**Documentation records implemented truth, not future intentions.**

Incomplete documentation is acceptable. Incorrect or speculative documentation presented as current functionality is not.

### 4.2 Documentation boundaries

| Location | Content |
|---|---|
| `README.md` | Project introduction, current status, supported platforms, downloads, quick start, documentation links |
| `docs/` User Manual | Installation, configuration, controllers, graphics, audio, operation, troubleshooting |
| `docs/` Developer Manual | Cloning, dependencies, build environments, architecture, platform setup, packaging, maintenance |
| GitHub Issues | Plans, investigations, proposed features, decisions in progress, outstanding work |
| Pull Requests | Implementation discussion, integration review, validation results |
| Git history | Source changes and integration history |

### 4.3 README restructuring

The current README contains substantial developer-oriented build information.

Move detailed cloning, dependency installation, build commands, and environment preparation into the developer documentation.

The README should become a user-friendly project entry point that answers:

1. What is R’lyeh PSX?
2. What platforms and functionality are currently supported?
3. How can someone obtain and run it?
4. Where can users and developers find detailed instructions?

The README should accurately communicate the project's development status and limitations.

### 4.4 Obsidian compatibility

The documentation vault should remain useful outside Obsidian.

Prefer portable Markdown, relative links, repository-managed assets, and minimal dependence on Obsidian-specific plugins or features.

### 4.5 Migrating existing planning documents

Existing planning and roadmap documents currently stored in the repository should be reviewed before removal.

- Move actionable outstanding work into GitHub Issues.
- Preserve important technical decisions and implementation facts in the appropriate documentation.
- Retire obsolete planning documents once their useful content has been accounted for.
- Avoid retaining duplicate sources of truth.

A design discussion may originate in an issue, while its final implemented architecture becomes part of the developer manual.

---

## 5. Development Milestones and Feature Roadmap

**The following order is locked as the current working priority order.**

The numbering is intentionally preserved, including milestone **13** immediately following milestone **1**.

This is a roadmap of major initiatives, not a strict dependency graph. Work may overlap where appropriate.

### 1) Rebranding completion

Complete the remaining R’lyeh PSX identity migration.

Potential issues and review areas:

- Remaining inherited application identifiers and branding.
- Platform-specific metadata and application resources.
- Packaging-related naming and identifiers.
- Updater and repository references.
- License, attribution, and provenance verification.
- Final review for obsolete upstream identity artifacts.

The final licensing/provenance review is envisioned as part of this milestone rather than a separate major milestone.

### 13) Implement Pnakotic

Adopt the Pnakotic versioning system within R’lyeh PSX.

**Scheduled after rebranding and before Qt 6.12 migration.**

Potential issues and review areas:

- Verify the Pnakotic encoding and decoding interface is ready for integration.
- Integrate version generation into the existing build/version infrastructure.
- Establish the intended version display and reporting behavior.
- Verify compatibility with the release/tagging workflow.
- Validate version generation and decoding using known source revisions.

This milestone concerns adopting the existing Pnakotic system, not redesigning its encoding algorithm.

### 2) Qt 6.12 Migration

Migrate the existing Qt infrastructure to Qt 6.12.

Potential issues and review areas:

- Update dependency acquisition and build scripts.
- Resolve API and build-system compatibility changes.
- Review obsolete Qt workarounds.
- Validate application builds on supported development platforms.
- Verify existing Qt frontend functionality before beginning the QML rewrite.

### 3) Dependency version review

Review remaining third-party dependency versions, maintenance status, and upgrade requirements.

Potential issues and review areas:

- Audit currently vendored and externally built dependencies.
- Compare against current supported upstream versions.
- Identify obsolete, unsupported, or problematic dependencies.
- Review compatibility, licensing, and provenance considerations.
- Prioritize upgrades based on risk and benefit.

**Expected outcome:** Additional actionable issues and potentially additional milestones for significant dependency work.

Not every dependency requires upgrading merely because a newer version exists.

### 4) Front-End re-write in Qt/QML

Develop the planned Qt Quick/QML frontend architecture.

Potential issues and review areas:

- Define the frontend architecture and integration boundaries.
- Replace or migrate existing widget-based UI functionality.
- Preserve required emulator core/frontend separation.
- Address desktop interaction, input, settings, and navigation behavior.
- Establish reusable frontend components suitable for additional platforms.
- Validate existing functionality throughout the migration.

The intent is to support a common frontend architecture across desktop and mobile platforms where practical.

### 5) Linux Flatpak development

Establish Flatpak packaging for R’lyeh PSX.

Potential issues and review areas:

- Complete Flatpak identity and packaging migration.
- Review runtime and dependency requirements.
- Establish reproducible Flatpak build procedures.
- Validate installation, execution, data paths, and application integration.
- Investigate Flathub submission requirements.
- Prepare and validate a potential Flathub submission.

This milestone is separate from general build infrastructure because producing a working distributable application is a distinct deliverable.

### 6) Android build

Establish Android as a supported build and execution target.

This is a broad platform initiative expected to require multiple smaller objectives.

Potential issues and review areas:

- Android build environment and dependency integration.
- Qt/QML frontend adaptation for Android.
- Android lifecycle and platform integration.
- Content URI, document-provider, and file-access handling.
- Controller and input support.
- Graphics, audio, and performance validation.
- Packaging and installation.
- Testing on representative Android hardware.

The Android content-access adapter should preserve the intended separation between platform-specific storage handling and the emulator core.

### 7) Build infrastructure

Develop and maintain automated build environments.

Potential issues and review areas:

- GitHub Actions configuration and workflows.
- Local build VM/container environments.
- Automated local builds.
- Build environment maintenance and update procedures.
- Build artifact collection and reporting.
- Reproducible build configuration across supported targets.
- Failure reporting and diagnostics.

The objective is to reduce manual build overhead and provide reliable, repeatable build environments.

### 8) Automated testing implementation

Investigate and incrementally establish useful automated testing.

**Initial scope is exploratory.**

Potential issues and review areas:

- Inventory existing test infrastructure inherited from the codebase.
- Determine which existing tests remain functional and useful.
- Identify high-value regression testing opportunities.
- Evaluate integration with automated build infrastructure.
- Establish an achievable initial automated testing baseline.

Do not delay major development milestones to design an extensive test framework without a demonstrated need.

Focused automated tests may be implemented earlier when development reveals a recurring, expensive, or error-prone manual validation requirement.

**Guiding principle: Automate recurring pain rather than hypothetical pain.**

Automated tests supplement, rather than replace, ongoing manual platform validation.

### 9) `docs/` re-work and documentation migration

Restructure project documentation into an accurate user and developer reference.

Potential issues and review areas:

- Rework the README as a user-friendly introduction and quick-start guide.
- Move detailed build instructions into developer documentation.
- Establish an Obsidian-compatible documentation vault.
- Organize user and developer manual content.
- Migrate useful technical information from existing planning documents.
- Transfer outstanding plans and tasks into GitHub Issues.
- Remove obsolete or redundant documentation.
- Define conventions for keeping documentation aligned with implemented behavior.

The resulting documentation should be authoritative about the current project state.

### 10) Alternate handheld targets

Investigate and establish initial support for additional handheld environments.

Potential issues and review areas:

- Select initial target hardware and operating environments.
- Establish required build configurations.
- Identify platform-specific frontend and input requirements.
- Validate graphics, audio, controllers, and application behavior.
- Document installation and build procedures.
- Identify limitations and ongoing compatibility requirements.

Target selection and support commitments should be based on actual build and hardware validation results.

---

## 6. Continuous Engineering Responsibilities

The following activities are ongoing responsibilities rather than milestones with permanent completion states.

### Platform validation

Perform appropriate build and functional checks throughout development.

Validation coverage should reflect the subsystem changed and the platforms affected.

Record significant validation results in pull requests and integration summaries.

### Regression management

When a recurring regression risk becomes apparent, consider adding a focused automated test as part of the relevant development work.

Do not require an entire testing framework before addressing an individual testing need.

### Documentation accuracy

Keep user and developer documentation aligned with implemented behavior.

When an issue or pull request establishes a durable technical decision, update the relevant documentation if future developers or users need that information.

### Dependency and licensing hygiene

Maintain dependency provenance, licensing compliance, and attribution as part of normal development, even after milestone-specific audits are completed.

---

## 7. GitHub Setup and Migration Checklist

These are planning actions for a future GitHub organization pass, not actions already completed.

- [ ] Review and establish the eleven roadmap milestones in the locked order.
- [ ] Create actionable issues for known outstanding work.
- [ ] Associate issues with their appropriate milestones.
- [ ] Determine which issues should use feature-request, bug, investigation, or maintenance classifications.
- [ ] Establish the preferred pull request structure and validation reporting conventions.
- [ ] Adopt merge commits with detailed integration summaries.
- [ ] Confirm issue-closing behavior when merging into `dev`.
- [ ] Review existing planning documents for migration into issues.
- [ ] Preserve implementation facts and architectural decisions in `docs/`.
- [ ] Begin the README and documentation restructuring under milestone 9.

## 8. Guiding Principles

1. **Ship working software.** Process exists to support engineering, not replace it.
2. **Preserve meaningful history.** Decisions, validation, and integration rationale should remain inspectable.
3. **Keep Git history useful.** Avoid commits whose sole purpose is recording routine validation or synchronizing plans.
4. **Document reality.** User and developer manuals must reflect implemented behavior.
5. **Use issues for evolving work.** Plans, discussions, investigations, and decisions belong where they can develop without unnecessary repository changes.
6. **Test pragmatically.** Maintain continuous manual validation and automate where it provides demonstrable value.
7. **Avoid unnecessary bureaucracy.** Apply the workflow proportionally and allow it to evolve with the project.

---

**Current status:** Roadmap and workflow direction agreed. GitHub milestones, issues, and pull request conventions remain to be established.

Subditi committant. Architectus recognoscat. Antiquus coniungat.

The Subjects shall commit. The Architect shall review. The Old One shall merge.

A few deliberate choices:
- Subditi: The subjects, subordinates, or those under authority.
- Architectus: The Architect.
- Antiquus: The Ancient One. A stylized rendering of the Old One.
- Committant / recognoscat / coniungat: Present subjunctives expressing commands or decrees, essentially “let them commit,” “let him review,” and “let him join.”
