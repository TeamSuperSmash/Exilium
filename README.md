# Exilium
A horror game by Team ACube, final year project of the course.

## Table of Content
* [Repository Settings](https://gitlab.com/TeamACube/Exilium/blob/master/README.md#repository-settings)
* [How to properly use this repository?](https://gitlab.com/TeamACube/Exilium/blob/master/README.md#how-to-properly-use-this-repository)
* [LFS File Locking](https://gitlab.com/TeamACube/Exilium/blob/master/README.md#lfs-file-locking)
* [Writing Issues](https://gitlab.com/TeamACube/Exilium/blob/master/README.md#writing-issues)

## Repository Settings
**GitLab** is the active repository; **GitHub** is mirrored from GitLab.

[<img src="https://drive.google.com/uc?export=download&id=1iHP-Mri5FMRWEY3OYEb_NG60TKcbB_V2" width="100" height="100" />](https://gitlab.com/TeamACube/Exilium)
[<img src="https://drive.google.com/uc?export=download&id=1Qjvn1wirQhzU-hQbYoD6x8cJMEvqcwRS" width="100" height="100" />](https://github.com/TeamSuperSmash/Exilium)

## How to properly use this repository?
1. Download **[Git](https://git-scm.com/)** and install. Follow this **[LINK](https://support.codebasehq.com/articles/getting-started/git-on-windows#installing-git)** for the installation settings. *(SSH setup is not necessary)*
2. Download **[GitKraken](https://www.gitkraken.com/)** / **[GitHub Desktop](https://desktop.github.com/)** and install.
3. Download **[Git LFS](https://git-lfs.github.com/)** and install.
4. Use the desired client to clone the repository using **HTTPS URL** above.
5. After cloning, **pull** from `origin` remote to get all the LFS files.
6. Make sure to **checkout** a new `feature-branch` before you work on a feature to avoid direct conflict.

## LFS File Locking
Please follow this **[link](https://docs.gitlab.com/ee/workflow/lfs/manage_large_binaries_with_git_lfs.html#file-locking)** to understand how to handle **binary files with LFS**.

### \***NEW**\* LFS-GUI
A submodule called **[LFS-GUI](https://github.com/FattyMieo/LFS-GUI)** has been installed in this repository.

This will help visualizing the workflow, feel free to go to the link for quick tutorial.

## Writing Issues
This is a template for writing **[Issues](https://gitlab.com/TeamACube/Exilium/issues)**
```
## Summary

(Summarize the bug encountered concisely)


## Steps to reproduce

(How one can reproduce the issue - this is very important)


## Example Project

(If possible, please create an example project here on GitLab.com that exhibits the problematic behaviour, and link to it here in the bug report)

(If you are using an older version of GitLab, this will also determine whether the bug has been fixed in a more recent version)


## What is the current bug behavior?

(What actually happens)


## What is the expected correct behavior?

(What you should see instead)


## Relevant logs and/or screenshots

(Paste any relevant logs - please use code blocks (```) to format console output,
logs, and code as it's very hard to read otherwise.)


## Possible fixes

(If you can, link to the line of code that might be responsible for the problem)
```