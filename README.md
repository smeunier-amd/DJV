[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://dev.azure.com/darbyjohnston/DJV/_apis/build/status/darbyjohnston.DJV?branchName=master)](https://dev.azure.com/darbyjohnston/DJV/_build/latest?definitionId=1&branchName=master)
[![Build Status](https://travis-ci.org/darbyjohnston/DJV.svg?branch=master)](https://travis-ci.org/darbyjohnston/DJV)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=darbyjohnston_DJV&metric=alert_status)](https://sonarcloud.io/dashboard?id=darbyjohnston_DJV)

DJV
===
DJV provides professional review software for VFX, animation, and film production.
Playback high resolution, high bit-depth, image sequences and videos, with frame
accurate control and color management. Available for Linux, Apple macOS, and
Microsoft Windows. Source code is provided under a BSD style open source license.

* [Download](https://darbyjohnston.github.io/DJV/download.html)
* [Contribute](https://darbyjohnston.github.io/DJV/contributing.html)
* [Documentation](https://darbyjohnston.github.io/DJV/documentation.html)


Building the Code
-----------------

* `git submodule update --init --recursive`
* `.\vcpkg\bootstrap-vcpkg.bat -disableMetrics`
* `.\vcpkg\vcpkg.exe install`
* configure cmake adding `-DCMAKE_TOOLCHAIN_FILE=${workspaceFolder}/vcpkg/scripts/buildsystems/vcpkg.cmake`
* build using cmake

License
-------

DJV is released under a BSD style open source license, see this
[page](https://darbyjohnston.github.io/DJV/legal.html) for details.


Contributing
------------

See this [page](https://darbyjohnston.github.io/DJV/contributing.html) for information on contributing to DJV.
