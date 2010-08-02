[schematic2]
uniq 264
[tools]
[detail]
w 138 2011 100 0 n#263 elongouts.wcspush.OUT -32 1904 64 1904 64 2000 272 2000 ecad4.setWcs.DIR
w -950 2027 100 0 DIR inhier.DIR.P -1040 2064 -976 2064 -976 2016 -864 2016 ecad4.selectWcs.DIR
w -1110 1019 100 0 n#261 ebos.wcsoverride.FLNK -1024 1296 -912 1296 -912 1008 -1248 1008 -1248 512 -1152 512 ecalcs.wcsORdisable.SLNK
w -1134 1371 100 0 n#260 ecalcs.wcsORdisable.VAL -864 704 -832 704 -832 896 -944 896 -944 1360 -1264 1360 -1264 1888 -1248 1888 embbos.wcsport.SDIS
w -1158 1051 100 0 n#259 ebos.wcsoverride.VAL -1024 1264 -976 1264 -976 1040 -1280 1040 -1280 896 -1152 896 ecalcs.wcsORdisable.INPA
w -1014 1243 100 0 n#256 ebos.wcsoverride.OUT -1024 1232 -944 1232 hwout.hwout#255.outp
w -326 2139 100 0 n#252 hwin.hwin#251.in -304 2128 -288 2128 -288 1968 -288 1968 elongouts.wcspush.DOL
w -222 1835 100 0 n#250 estringouts.wcsfile.FLNK -48 1760 -48 1776 -32 1776 -32 1824 -352 1824 -352 1936 -288 1936 elongouts.wcspush.SLNK
w -942 1835 100 0 n#247 embbos.wcsport.OUT -992 1920 -960 1920 -960 1824 -864 1824 ecad4.selectWcs.A
w -462 1547 100 0 n#245 ecad4.selectWcs.FLNK -544 1536 -320 1536 -320 1744 -304 1744 estringouts.wcsfile.SLNK
w -414 1787 100 0 n#244 ecad4.selectWcs.VALB -544 1760 -464 1760 -464 1776 -304 1776 estringouts.wcsfile.DOL
w 2 1739 100 0 n#243 estringouts.wcsfile.OUT -48 1728 112 1728 112 1808 272 1808 ecad4.setWcs.A
w -510 1835 100 0 n#240 ecad4.selectWcs.VALA -544 1824 -416 1824 -416 1712 -304 1712 estringouts.wcsfile.SDIS
w 642 2011 100 0 n#172 ecad4.setWcs.VAL 592 2000 752 2000 752 2100 912 2100 outhier.VAL.p
w 722 1979 100 0 n#170 ecad4.setWcs.MESS 592 1968 912 1968 outhier.MESS.p
s 1328 1440 150 0 doSetWcs
[cell use]
use ecalcs -1152 423 100 0 wcsORdisable
xform 0 -1008 688
p -1056 720 100 0 -1 CALC:A>0?0:1
use ebos -1280 1175 100 0 wcsoverride
xform 0 -1152 1264
p -1264 1072 100 0 -1 DTYP:vxWorks Variable (INST_IO)
p -1248 1136 100 0 1 ONAM:Manual_Control
p -1248 1104 100 0 1 ZNAM:AG_Control
use hwout -944 1191 100 0 hwout#255
xform 0 -848 1232
p -848 1223 100 0 -1 val(outp):@overridePort
use embbos -1248 1831 100 0 wcsport
xform 0 -1120 1920
p -1088 1886 100 0 0 FRST:4
p -1088 1854 100 0 0 FVST:5
p -1088 1982 100 0 0 ONST:1
p -1088 1918 100 0 0 THST:3
p -1088 1950 100 0 0 TWST:2
p -1088 2014 100 0 0 ZRST:0
p -992 1920 75 768 -1 pproc(OUT):PP
use hwin -496 2087 100 0 hwin#251
xform 0 -400 2128
p -493 2120 100 0 -1 val(in):3
use elongouts -288 1847 100 0 wcspush
xform 0 -160 1936
p -32 1904 75 768 -1 pproc(OUT):PP
use CBorder -1408 -280 -100 0 frame
xform 0 272 1024
p 1664 -148 75 1536 -1 Author:Janet E. Tvedt
p 1160 -144 100 1536 1 Date:24 Apr 97
p 1264 -48 300 1792 -1 Dnumber:
p 1392 -64 150 1536 -1 Title:setWcsCad.sch
use estringouts -304 1671 100 0 wcsfile
xform 0 -176 1744
p -224 1648 100 0 1 OMSL:closed_loop
use estringouts 432 999 100 0 wcs_ctype1
xform 0 560 1072
use estringouts 432 423 100 0 wcs_ctype2
xform 0 560 496
use estringouts 848 999 100 0 wcs_radecsys
xform 0 976 1072
use egenSub -480 167 100 0 astCtx
xform 0 -336 592
p -368 528 100 0 1 NOA:39
p -384 464 100 0 1 PINI:YES
p -352 160 100 0 1 SCAN:Passive
p -432 128 100 0 1 SNAM:updateAstCtx
p -912 928 100 0 1 def(INPA):tcs:ak:astCtx.VALA
use ecad4 272 1303 100 0 setWcs
xform 0 432 1680
p 336 1440 100 0 1 SNAM:initWcsCad
use ecad4 -864 1319 100 0 selectWcs
xform 0 -704 1696
p -928 1120 100 0 0 FTVA:LONG
p -800 1456 100 0 1 SNAM:selectWcs
p -1168 1728 100 0 -1 def(INPB):$(cctop)cameraSelect
p -1136 1664 100 0 -1 def(INPC):$(agtop)port:nirs
p -1184 1600 100 0 0 def(INPD):$(top)setWCS.A
p -752 1296 100 1024 0 name:$(top)$(I)
p -896 1792 75 1280 -1 pproc(INPA):PP
p -544 1728 75 768 -1 pproc(OUTB):NPP
use eaos 432 775 100 0 wcs_crpix1
xform 0 560 864
use eaos 432 583 100 0 wcs_crval1
xform 0 560 672
use eaos 432 7 100 0 wcs_crval2
xform 0 560 96
use eaos 432 231 100 0 wcs_crpix2
xform 0 560 320
use eaos 848 775 100 0 wcs_equinox
xform 0 976 864
use eaos 848 583 100 0 wcs_mjdobs
xform 0 976 672
use eaos 880 71 100 0 wcs_cd21
xform 0 1008 160
use eaos 880 327 100 0 wcs_cd11
xform 0 1008 416
p 624 270 100 0 0 PREC:14
use eaos 1312 327 100 0 wcs_cd12
xform 0 1440 416
use eaos 1312 71 100 0 wcs_cd22
xform 0 1440 160
use task 1120 1319 100 0 task#180
xform 0 1416 1488
use notes 1184 1751 100 0 notes#160
xform 0 1440 1936
p 1212 2062 100 0 -1 COMMENT1:This implements the setWcs command.
use outhier 880 1927 100 0 MESS
xform 0 896 1968
use outhier 880 2059 100 0 VAL
xform 0 896 2100
use inhier -1056 2023 100 0 DIR
xform 0 -1040 2064
[comments]
