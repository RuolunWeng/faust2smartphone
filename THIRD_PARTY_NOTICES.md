# Third-Party Notices

faust2smartphone contains, adapts, generates, or interfaces with components
from the Faust ecosystem and other projects. The root BSD 3-Clause License
applies only to original faust2smartphone code for which Ruolun Weng holds the
applicable rights.

Third-party and jointly authored material remains subject to its own copyright
and license terms. When a file contains its own notice, that file-level notice
takes precedence over the repository-level license.

## Faust / GRAME-CNCM

faust2smartphone is built on [Faust](https://github.com/grame-cncm/faust),
developed by GRAME-CNCM and contributors. This repository includes or adapts
Faust API and architecture code, including files under:

- `install/api-allen/`
- `install/faust/`
- `install/motion/`
- generated `DspFaust.*` files in the mobile templates

These files carry their own notices. Some are sample architecture code that
permits derived works under terms of the distributor's choice. Others use the
GNU GPL or GNU LGPL with a Faust-specific exception. Their original headers
must be retained.

`install/faust2api_a` is based on the Faust `faust2api` workflow and identifies
Allen Weng and GRAME as joint contributors. It is not relicensed solely under
the repository-level BSD license.

## libsndfile

The mobile templates contain libsndfile headers and prebuilt libraries, and
`install/faust/gui/LibsndfileReader.h` is a modified Faust architecture file
used for current iOS support. libsndfile and the Faust architecture file retain
their respective upstream and file-level terms. See the
[libsndfile project](https://github.com/libsndfile/libsndfile) and the headers
distributed with these components.

## OSC components and runtime libraries

The project can copy or link OSC components supplied by Faust, including
libOSCFaust and oscpack. Some Android templates also contain prebuilt C++
runtime libraries. These components are not covered by the repository-level
BSD license and retain their original terms and required notices.

## motion.lib

The motion interaction workflow integrates `motion.lib`, developed by
Christophe Lebreton. The generator refers to or copies that external library
from a Faust installation when requested. `motion.lib` is not relicensed by
this repository; consult its source distribution and file-level notices for
the applicable terms.

## Legacy iOS test templates

The following legacy test-template directories contain their own historical
copyright notices and are excluded from the repository-level BSD license:

- `install/smartphone/iOS/iOSTests/`
- `install/smartphone/iOS-plugin/iOSTests/`

They remain in the repository because the corresponding Xcode template
projects still reference their test targets. They should not be redistributed
under the faust2smartphone BSD license.

## Generated applications

Generated iOS and Android projects may include Faust-generated code, platform
templates, bindings, libraries, and runtime components with different license
terms. Anyone redistributing a generated application is responsible for
reviewing those components and preserving all notices required by their
licenses.

## Precedence

If this notice, the root `LICENSE`, and a notice embedded in a source file
differ, the embedded third-party or jointly authored notice governs that file.
