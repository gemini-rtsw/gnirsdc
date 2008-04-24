[schematic2]
uniq 175
[tools]
[detail]
w -206 1867 100 0 n#169 ecad4.observe.OUTA -224 1856 -128 1856 hwout.hwout#168.outp
w -732 2155 100 0 n#159 inhier.DIR.P -764 2144 -640 2144 -640 2080 -544 2080 ecad4.observe.DIR
w -62 2187 100 0 n#157 ecad4.observe.VAL -224 2080 -160 2080 -160 2176 96 2176 outhier.VAL.p
w -94 2059 100 0 n#156 ecad4.observe.MESS -224 2048 96 2048 outhier.MESS.p
s 372 1672 150 0 doObserve
s -676 1900 100 0 (data label)
s -220 1896 100 0 (data label)
s -668 1828 100 0 (filename)
s -216 1832 100 0 (filename)
s 0 1920 100 0 This link updates the data label record
s 0 1888 100 0 in the Status Alarm Database
[cell use]
use ebos 480 1488 100 0 DCAReady
xform 0 544 1408
p 96 1262 100 0 0 ONAM:Ready
p 480 1312 100 0 1 PV:$(top)
p 96 1294 100 0 0 ZNAM:Not Ready
use ebos 432 1111 100 0 frameReady
xform 0 560 1200
p 112 1054 100 0 0 ONAM:ready
p 112 1086 100 0 0 ZNAM:waiting
use estringouts -512 1123 100 0 sciProgstr
xform 0 -384 1196
use hwout -128 1815 100 0 hwout#168
xform 0 -32 1856
p -32 1847 100 0 -1 val(outp):$(sadtop)dataLabel.VAL PP MS
use task 172 1551 100 0 task#167
xform 0 468 1720
use CBorder -1052 -88 -100 0 frame
xform 0 628 1216
p 2020 44 75 1536 -1 Author:Janet E. Tvedt
p 1516 48 100 1536 1 Date:24 Apr 97
p 1620 144 300 1792 -1 Dnumber:
p 1748 128 150 1536 -1 Title:observeCad.sch
use ecad4 -432 2124 100 0 observe
xform 0 -384 1760
p -420 1468 65 0 1 PV:$(top)
p -444 1448 65 0 1 SNAM:observeProc
p -844 1736 65 0 1 def(INPC):$(top)observeC.VAL
p -192 1856 75 768 -1 palrm(OUTA):MS
p -224 1856 75 768 -1 pproc(OUTA):PP
use ecars 1284 1832 100 0 observeC
xform 0 1344 1680
p 1316 1548 65 0 1 PV:$(top)
p 1540 1564 65 0 1 def(FLNK):$(top)combCars3.VAL
p 964 1752 65 0 1 def(ICID):$(top)apply.CLID
use notes 1636 1899 100 0 notes#160
xform 0 1892 2084
p 1664 2210 100 0 -1 COMMENT1:This implements the observe command.
use outhier 64 2007 100 0 MESS
xform 0 80 2048
use outhier 64 2135 100 0 VAL
xform 0 80 2176
use inhier -780 2103 100 0 DIR
xform 0 -764 2144
[comments]
