[schematic2]
uniq 237
[tools]
[detail]
w 642 2011 100 0 n#172 ecad4.setWcs.VAL 592 2000 752 2000 752 2100 912 2100 outhier.VAL.p
w 722 1979 100 0 n#170 ecad4.setWcs.MESS 592 1968 912 1968 outhier.MESS.p
w 184 2003 100 0 n#164 inhier.DIR.P 64 2064 156 2064 156 2000 272 2000 ecad4.setWcs.DIR
s 1576 416 150 0 doSetWcs
[cell use]
use egenSub -480 167 100 0 astCtx
xform 0 -336 592
p -368 528 100 0 1 NOA:39
p -384 464 100 0 1 PINI:YES
p -352 160 100 0 1 SCAN:Passive
p -432 128 100 0 1 SNAM:updateAstCtx
p -912 928 100 0 1 def(INPA):tcs:ak:astCtx.VALA
use ecad4 -528 1319 100 0 ecad4#228
xform 0 -368 1696
p -464 1456 100 0 1 SNAM:selectWcs
p -416 1296 100 1024 -1 name:$(top)selectWcs
use ecad4 272 1303 100 0 setWcs
xform 0 432 1680
p 336 1440 100 0 1 SNAM:initWcsCad
use eaos 1856 743 100 0 wcs_cd22
xform 0 1984 832
use eaos 1856 999 100 0 wcs_cd12
xform 0 1984 1088
use eaos 1424 999 100 0 wcs_cd11
xform 0 1552 1088
p 1168 942 100 0 0 PREC:14
use eaos 1424 743 100 0 wcs_cd21
xform 0 1552 832
use eaos 1392 1255 100 0 wcs_mjdobs
xform 0 1520 1344
use eaos 1392 1447 100 0 wcs_equinox
xform 0 1520 1536
use eaos 976 903 100 0 wcs_crpix2
xform 0 1104 992
use eaos 976 679 100 0 wcs_crval2
xform 0 1104 768
use eaos 976 1255 100 0 wcs_crval1
xform 0 1104 1344
use eaos 976 1447 100 0 wcs_crpix1
xform 0 1104 1536
use estringouts 1392 1671 100 0 wcs_radecsys
xform 0 1520 1744
use estringouts 976 1095 100 0 wcs_ctype2
xform 0 1104 1168
use estringouts 976 1671 100 0 wcs_ctype1
xform 0 1104 1744
use task 1360 295 100 0 task#180
xform 0 1656 464
use CBorder -1044 -120 -100 0 frame
xform 0 636 1184
p 2028 12 75 1536 -1 Author:Janet E. Tvedt
p 1524 16 100 1536 1 Date:24 Apr 97
p 1628 112 300 1792 -1 Dnumber:
p 1756 96 150 1536 -1 Title:setWcsCad.sch
use notes 1560 1835 100 0 notes#160
xform 0 1816 2020
p 1588 2146 100 0 -1 COMMENT1:This implements the setWcs command.
use outhier 880 2059 100 0 VAL
xform 0 896 2100
use outhier 880 1927 100 0 MESS
xform 0 896 1968
use inhier 48 2023 100 0 DIR
xform 0 64 2064
[comments]
