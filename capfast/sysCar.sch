[schematic2]
uniq 117
[tools]
[detail]
w -684 -985 100 0 n#115 egenSub.combCars3.FLNK -1020 -996 -288 -996 -288 -800 junction
w -288 -103 100 0 n#115 egenSub.combCars2.FLNK -348 -36 -292 -36 -292 -160 junction
w -656 -149 100 0 n#115 egenSub.combCars1.FLNK -1024 324 -960 324 -960 -160 -292 -160 -292 -800 100 -800 egenSub.ovrAllCar.SLNK
w -222 -597 100 0 n#114 egenSub.combCars3.OUTC -1020 -420 -484 -420 -484 -608 100 -608 egenSub.ovrAllCar.I
w -764 -345 100 0 n#113 egenSub.combCars3.OUTB -1020 -356 -448 -356 -448 -544 100 -544 egenSub.ovrAllCar.H
w -748 -281 100 0 n#112 egenSub.combCars3.OUTA -1020 -292 -416 -292 -416 -480 100 -480 egenSub.ovrAllCar.G
w -164 57 100 0 n#97 egenSub.combCars2.OUTC -348 540 -160 540 -160 -416 100 -416 egenSub.ovrAllCar.F
w -132 121 100 0 n#96 egenSub.combCars2.OUTB -348 604 -128 604 -128 -352 100 -352 egenSub.ovrAllCar.E
w -100 189 100 0 n#95 egenSub.combCars2.OUTA -348 668 -96 668 -96 -280 100 -280 100 -288 egenSub.ovrAllCar.D
w 4 333 100 0 n#94 egenSub.combCars1.OUTC -1024 900 0 900 0 -224 100 -224 egenSub.ovrAllCar.C
w 36 397 100 0 n#93 egenSub.combCars1.OUTB -1024 964 32 964 32 -160 100 -160 egenSub.ovrAllCar.B
w 68 461 100 0 n#92 egenSub.combCars1.OUTA -1024 1028 64 1028 64 -96 100 -96 egenSub.ovrAllCar.A
w 612 -581 100 0 n#76 egenSub.ovrAllCar.FLNK 388 -832 608 -832 608 -320 832 -320 ecars.applyC.SLNK
w 696 -181 100 0 n#67 egenSub.ovrAllCar.OUTC 388 -256 608 -256 608 -192 832 -192 ecars.applyC.IMSS
w 664 -213 100 0 n#65 egenSub.ovrAllCar.OUTB 388 -192 544 -192 544 -224 832 -224 ecars.applyC.IERR
w 586 -117 100 0 n#53 egenSub.ovrAllCar.OUTA 388 -128 832 -128 ecars.applyC.IVAL
w 576 155 100 0 CLID inhier.CLID.P 448 480 572 480 572 -160 832 -160 ecars.applyC.ICID
s -1712 748 100 0 ------>
s -1756 788 100 0 lower level CARs
s -1744 820 100 0 inputs from
s -1732 -496 100 0 ------>
s -1776 -456 100 0 lower level CARs
s -1764 -424 100 0 inputs from
s -904 104 100 0 inputs from
s -916 72 100 0 lower level CARs
s -872 32 100 0 ------>
s 132 44 100 0 overall combination
s 140 12 100 0 of individual CARs
[cell use]
use notes 688 699 100 0 notes#116
xform 0 944 884
p 716 1010 100 0 -1 COMMENT1:NOTES:  This schematic contains the
p 716 978 100 0 -1 COMMENT2:records for hierarchically combining
p 716 948 100 0 -1 COMMENT3:individual CAR records.  Each genSub
p 716 916 100 0 -1 COMMENT4:takes up to 3 CAR inputs and outputs
p 716 884 100 0 -1 COMMENT5:the CAR value that is the highest along
p 716 852 100 0 -1 COMMENT6:with its corresponding error code and
p 716 820 100 0 -1 COMMENT7:message.  The ovrAllCar genSub takes
p 716 788 100 0 -1 COMMENT8:the intermediate results and reports the
p 716 756 100 0 -1 COMMENT9:overall CAR status in the top level CAR.
use CBorder -1916 -1300 -100 0 frame
xform 0 -236 4
p 1156 -1168 75 1536 -1 Author:Janet E. Tvedt
p 652 -1164 100 1536 1 Date:24 Apr 97
p 756 -1068 300 1792 -1 Dnumber:
p 884 -1084 150 1536 -1 Title:sysCar.sch
use egenSub -1216 -216 100 0 combCars3
xform 0 -1164 -628
p -1204 -352 65 0 1 FTA:LONG
p -1204 -368 65 0 1 FTB:LONG
p -1204 -384 65 0 1 FTC:STRING
p -1204 -400 65 0 1 FTD:LONG
p -1204 -416 65 0 1 FTE:LONG
p -1204 -432 65 0 1 FTF:STRING
p -1204 -448 65 0 1 FTG:LONG
p -1204 -464 65 0 1 FTH:LONG
p -1204 -480 65 0 1 FTI:STRING
p -1531 -1535 65 0 0 FTJ:DOUBLE
p -1204 -512 65 0 1 FTVA:LONG
p -1204 -528 65 0 1 FTVB:LONG
p -1204 -548 65 0 1 FTVC:STRING
p -1220 -968 65 0 1 PV:$(top)
p -1596 -358 100 0 0 SCAN:Passive
p -1220 -988 65 0 1 SNAM:combCars
p -1592 -292 65 0 1 def(INPA):$(top)observeC.VAL
p -1592 -356 65 0 1 def(INPB):$(top)observeC.OERR
p -1588 -420 65 0 1 def(INPC):$(top)observeC.OMSS
p -1588 -484 65 0 1 def(INPD):$(top)noopC.VAL
p -1588 -548 65 0 1 def(INPE):$(top)noopC.OERR
p -1592 -612 65 0 1 def(INPF):$(top)noopC.OMSS
p -1584 -672 65 0 1 def(INPG):$(top)parkC.VAL
p -1584 -736 65 0 1 def(INPH):$(top)parkC.OERR
p -1584 -800 65 0 1 def(INPI):$(top)parkC.OMSS
use egenSub -1208 1104 100 0 combCars1
xform 0 -1168 692
p -1212 1032 65 0 1 FTA:LONG
p -1212 1012 65 0 1 FTB:LONG
p -1212 992 65 0 1 FTC:STRING
p -1212 964 65 0 1 FTD:LONG
p -1212 944 65 0 1 FTE:LONG
p -1212 924 65 0 1 FTF:STRING
p -1212 896 65 0 1 FTG:LONG
p -1212 876 65 0 1 FTH:LONG
p -1212 856 65 0 1 FTI:STRING
p -1208 920 65 0 0 FTJ:LONG
p -1212 824 65 0 1 FTVA:LONG
p -1212 804 65 0 1 FTVB:LONG
p -1212 784 65 0 1 FTVC:STRING
p -1228 852 65 0 0 FTVF:DOUBLE
p -1224 536 65 0 0 FTVG:DOUBLE
p -1208 480 65 0 0 FTVH:DOUBLE
p -1208 460 65 0 0 FTVI:DOUBLE
p -1208 440 65 0 0 FTVJ:DOUBLE
p -1224 356 65 0 1 PV:$(top)
p -1228 380 65 0 1 SNAM:combCars
p -1548 1068 65 0 1 def(INPA):$(top)arSetupC.VAL
p -1564 1008 65 0 1 def(INPB):$(top)arSetupC.OERR
p -1564 944 65 0 1 def(INPC):$(top)arSetupC.OMSS
p -1544 880 65 0 1 def(INPD):$(top)obsSetupC.VAL
p -1556 816 65 0 1 def(INPE):$(top)obsSetupC.OERR
p -1560 752 65 0 1 def(INPF):$(top)obsSetupC.OMSS
p -1552 692 65 0 1 def(INPG):$(top)drRoiSetC.VAL
p -1568 624 65 0 1 def(INPH):$(top)drRoiSetC.OERR
p -1556 556 65 0 1 def(INPI):$(top)drRoiSetC.OMSS
p -1024 1038 75 0 -1 pproc(OUTA):NPP
use egenSub -552 740 100 0 combCars2
xform 0 -492 332
p -540 632 65 0 1 FTA:LONG
p -540 612 65 0 1 FTB:LONG
p -540 592 65 0 1 FTC:STRING
p -540 572 65 0 1 FTD:LONG
p -540 552 65 0 1 FTE:LONG
p -540 532 65 0 1 FTF:STRING
p -540 512 65 0 1 FTG:LONG
p -540 492 65 0 1 FTH:LONG
p -540 472 65 0 1 FTI:STRING
p -540 444 65 0 1 FTVA:LONG
p -540 424 65 0 1 FTVB:LONG
p -540 404 65 0 1 FTVC:STRING
p -532 -44 65 0 1 PV:$(top)
p -544 -24 65 0 1 SNAM:combCars
p -896 672 65 0 1 def(INPA):$(top)initC.VAL
p -900 608 65 0 1 def(INPB):$(top)initC.OERR
p -904 544 65 0 1 def(INPC):$(top)initC.OMSS
p -896 480 65 0 1 def(INPD):$(top)testC.VAL
p -904 416 65 0 1 def(INPE):$(top)testC.OERR
p -900 352 65 0 1 def(INPF):$(top)testC.OMSS
p -892 288 65 0 1 def(INPG):$(top)gSysC.VAL
p -900 224 65 0 1 def(INPH):$(top)gSysC.OERR
p -900 160 65 0 1 def(INPI):$(top)gSysC.OMSS
use egenSub 188 -48 100 0 ovrAllCar
xform 0 244 -464
p 200 -108 65 0 1 FTA:LONG
p 200 -124 65 0 1 FTB:LONG
p 200 -140 65 0 1 FTC:STRING
p 200 -156 65 0 1 FTD:LONG
p 200 -172 65 0 1 FTE:LONG
p 200 -188 65 0 1 FTF:STRING
p 200 -204 65 0 1 FTG:LONG
p 200 -220 65 0 1 FTH:LONG
p 200 -236 65 0 1 FTI:STRING
p 200 -260 65 0 1 FTVA:LONG
p 200 -276 65 0 1 FTVB:LONG
p 200 -292 65 0 1 FTVC:STRING
p 200 -840 65 0 1 PV:$(top)
p 200 -820 65 0 1 SNAM:combCars
use ecars 952 -84 100 0 applyC
xform 0 992 -240
p 932 -364 100 0 1 PV:$(top)
p 928 -480 100 0 0 SIMS:NO_ALARM
use inhier 432 439 100 0 CLID
xform 0 448 480
[comments]
