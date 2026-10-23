# RPMs for the two GNIRS detector-controller VME crates, built from this repo
# by the gemini-rtsw-ci pipeline (REL-5058):
#
#   gnirsdc-1-vme  DC1 ngnirsdc1 10.2.2.83  MVME2700, vxWorks 5.4.2
#                  coadder + DHS, no iocCore; built from ppc/ against GEM7
#   gnirsdc-2-vme  DC2 ngnirsdc2 10.2.2.84  MVME162, vxWorks 5.2, EPICS 3.12.2
#                  GEM5; built from the top level, plus its frozen kernel
#
# One build, two packages, so each crate can be upgraded or rolled back on its
# own. Both install at production's paths through its DC selector links, so
# the crates' boot parameters keep their startup-script lines; only the boot
# host changes (to mkotcsbootv2-lv1).

# The crates load these objects as data over NFS; nothing here runs on the
# build host, so skip the host-side post-processing and debug packages.
%global _build_id_links none
%global __os_install_post %{nil}
%global debug_package %{nil}
%global _binaries_in_noarch_packages_terminate_build 0

# Build values come from tools/linux-build/build.conf, the same file the
# setup scripts read, so the spec cannot disagree with a local build.
%define buildconf() %(. tools/linux-build/build.conf 2>/dev/null && echo $%1)
%global dc1 %{buildconf DC1_DEPLOY}
%global dc2 %{buildconf DC2_DEPLOY}
%if "%{dc1}" == ""
%{error:tools/linux-build/build.conf not readable -- rpmbuild must run from the repository root}
%endif

%define git_hash %(if [ -n "$GIT_HASH" ]; then echo "$GIT_HASH"; else git rev-parse --short HEAD 2>/dev/null || echo nogit; fi)

Name:           gnirsdc
Version:        1.13
Release:        1.git%{git_hash}%{?dist}
Summary:        GNIRS detector controller VME crate software (DC1 and DC2)
License:        Gemini Observatory (org-internal)
Source0:        %{name}-%{version}.tar.gz
AutoReqProv:    no
BuildArch:      noarch

# DC1: GEM7 / Tornado 2.0 ppc604, DHS headers -- the hrwfs toolchain.
BuildRequires:  gem-tornado20-linux = 2.0.2-1%{?dist}
BuildRequires:  gem-epics3134gem7 = 3.13.4-1%{?dist}
BuildRequires:  hrwfs-dhs-vxlibs = 0.16-1%{?dist}
# DC2: GEM5 / vxWorks 5.2b with ANL's Linux 68k gcc -- the gnirscc toolchain.
BuildRequires:  gem-vxworks52-linux = 5.2b-1%{?dist}
BuildRequires:  gem-epics3122gem5 = 3.12.2-1%{?dist}
BuildRequires:  gem5-deplibs = 2026.10.08-1%{?dist}
# Host side: applSetup (perl for GEM7, csh for 3.12), and a 32-bit gcc for
# DC2's state-notation compiler (tools/linux-build/snc-1.9.2).
BuildRequires:  make, gcc, perl, tcsh, sed, file, findutils, diffutils
BuildRequires:  glibc-devel(x86-32)

%description
GNIRS detector controller software for its two VME crates. This source
package builds gnirsdc-1-vme (DC1) and gnirsdc-2-vme (DC2).

%package -n gnirsdc-1-vme
Summary:        GNIRS DC1 (ngnirsdc1) coadder/DHS crate software, vxWorks 5.4 ppc604
Requires:       hrwfs-dhs-vxlibs
# The mv2700-niri kernel DC1 boots.
Requires:       gem-vxworks-tornado20 >= 2.0.2

%description -n gnirsdc-1-vme
The coadder, DHS client and RPC server that DC1 loads at boot, with its
generated startup and local scripts and DHS startup file, installed under
%{dc1}.

%package -n gnirsdc-2-vme
Summary:        GNIRS DC2 (ngnirsdc2) EPICS 3.12 IOC software, vxWorks 5.2 mv162
Requires:       gem5-epics-runtime
Requires:       gem5-deplibs

%description -n gnirsdc-2-vme
The GNIRS DC EPICS IOC that DC2 loads at boot: objects, generated startup and
local scripts, databases and display files, the transputer network files
(tpSource), installed under %{dc2}; and DC2's frozen vxWorks 5.2 kernel under
/gemini/gnirs/vw/mv162.

%package devel
Summary:        Build environment for gnirsdc development images
Requires:       gem-tornado20-linux, gem-epics3134gem7, hrwfs-dhs-vxlibs
Requires:       gem-vxworks52-linux, gem-epics3122gem5, gem5-deplibs
Requires:       make, gcc, perl, tcsh, sed, file, findutils, diffutils
Requires:       glibc-devel(x86-32)

%description devel
Pulls the pinned gnirsdc build dependencies into a dev container. No files.

%prep
%setup -q

%build
# Exactly what a developer runs: each tree's Makefile runs its setup script
# when needed, then the checks fail the build on anything that would be silent
# here and fatal at the crate.
make -C ppc
make
./tools/linux-build/check-build.sh

%install
rm -rf $RPM_BUILD_ROOT

# DC1
D=$RPM_BUILD_ROOT%{dc1}
mkdir -p $D/bin $D/data
cp -a ppc/bin/ppc604 $D/bin/
cp -a ppc/data/* $D/data/
rm -f $D/bin/ppc604/Distfile*

# DC2
D=$RPM_BUILD_ROOT%{dc2}
mkdir -p $D/bin
cp -a bin/mv162 $D/bin/
rm -f $D/bin/mv162/Distfile*
cp -a data tpSource RELEASE.NOTES $D/

K=$RPM_BUILD_ROOT/gemini/gnirs/vw/mv162
mkdir -p $K
cp -p kernel/mv162/vxWorks kernel/mv162/vxWorks.sym $K/

%files -n gnirsdc-1-vme
%defattr(-,root,root,-)
%{dc1}

%files -n gnirsdc-2-vme
%defattr(-,root,root,-)
%{dc2}
/gemini/gnirs/vw/mv162

%files devel

%changelog
* Fri Oct 23 2026 Hawi Stecher <hawi.stecher@noirlab.edu> - 1.13-1
- Initial RPM packaging via the Linux cross-builds (REL-5058). DC1 is
  production's DC/V1-10/ppc plus the GNFR-75615 DhsConnect fix; DC2 is
  production's DC/V1-13 plus GNFR-75537. Every object exports and imports
  the same symbols as production. Re-homed to mkotcsbootv2-lv1.
