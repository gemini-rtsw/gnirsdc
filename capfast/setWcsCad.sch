[schematic2]
uniq 220
[tools]
[detail]
w -62 1707 100 0 n#172 ecad4.setWcs.VAL -112 1696 48 1696 48 1796 208 1796 outhier.VAL.p
w 18 1675 100 0 n#170 ecad4.setWcs.MESS -112 1664 208 1664 outhier.MESS.p
w -520 1699 100 0 n#164 inhier.DIR.P -640 1760 -548 1760 -548 1696 -432 1696 ecad4.setWcs.DIR
s 1736 432 150 0 doSetWcs
[cell use]
use egenSub -400 71 100 0 astCtx
xform 0 -256 496
p -288 432 100 0 1 NOA:39
p -304 368 100 0 1 PINI:YES
p -272 64 100 0 1 SCAN:10 second
p -352 32 100 0 1 SNAM:updateAstCtx
p -832 832 100 0 1 def(INPA):tcs:ak:astCtx.VALA
use eaos 1264 871 100 0 wcs_cd22
xform 0 1392 960
use eaos 1264 1127 100 0 wcs_cd12
xform 0 1392 1216
use eaos 832 1127 100 0 wcs_cd11
xform 0 960 1216
use eaos 832 871 100 0 wcs_cd21
xform 0 960 960
use eaos 800 1383 100 0 wcs_mjdobs
xform 0 928 1472
use eaos 800 1575 100 0 wcs_equinox
xform 0 928 1664
use eaos 384 1031 100 0 wcs_crpix2
xform 0 512 1120
use eaos 384 807 100 0 wcs_crval2
xform 0 512 896
use eaos 384 1383 100 0 wcs_crval1
xform 0 512 1472
use eaos 384 1575 100 0 wcs_crpix1
xform 0 512 1664
use estringouts 800 1799 100 0 wcs_radecsys
xform 0 928 1872
use estringouts 384 1223 100 0 wcs_ctype2
xform 0 512 1296
use estringouts 384 1799 100 0 wcs_ctype1
xform 0 512 1872
use ecad4 -432 999 100 0 setWcs
xform 0 -272 1376
p -368 1136 100 0 1 SNAM:initWcsCad
use task 1520 311 100 0 task#180
xform 0 1816 480
use CBorder -1044 -120 -100 0 frame
xform 0 636 1184
p 2028 12 75 1536 -1 Author:Janet E. Tvedt
p 1524 16 100 1536 1 Date:24 Apr 97
p 1628 112 300 1792 -1 Dnumber:
p 1756 96 150 1536 -1 Title:setWcsCad.sch
use notes 1560 1835 100 0 notes#160
xform 0 1816 2020
p 1588 2146 100 0 -1 COMMENT1:This implements the setWcs command.
use outhier 176 1755 100 0 VAL
xform 0 192 1796
use outhier 176 1623 100 0 MESS
xform 0 192 1664
use inhier -656 1719 100 0 DIR
xform 0 -640 1760
[comments]
